#include "ipmtransformworker.h"

#include <chrono>

#include <QDir>
#include <QFuture>
#include <QVector>
#include <QFutureWatcher>
#include <QDateTime>
#include <QtConcurrent/QtConcurrent>

#include <boost/lexical_cast.hpp>

#include "common/log_utils/beecLogger.h"
#include "common/file_system_utils/file_system_processor.h"

using beec::common::file_system_utils::FileSystemProcessor;
using beec::camera_model::CameraModel;
using beec::ipm_model::AdaptiveIpmModel;

bool less_first(const std::string &image_path_a, const std::string &image_path_b) {

    auto image_name_a = FileSystemProcessor::get_file_name(image_path_a);
    auto image_name_b = FileSystemProcessor::get_file_name(image_path_b);

    auto image_a_id = boost::lexical_cast<int>(image_name_a.substr(0, image_name_a.find_first_of('_')).c_str());
    auto image_b_id = boost::lexical_cast<int>(image_name_b.substr(0, image_name_b.find_first_of('_')).c_str());

    return image_b_id > image_a_id;
}

IpmTransformWorker::IpmTransformWorker(const IpmParameterParser &ipm_para_parser) {

    _m_ipm_model = AdaptiveIpmModel(ipm_para_parser);

    cv::Point2d pt_vp(ipm_para_parser.get_vp_point_x(), ipm_para_parser.get_vp_point_y());
    _m_ipm_model.set_vp_point(pt_vp);

    _m_cam = CameraModel(ipm_para_parser);

    _m_ipm_para_parser = ipm_para_parser;

    _m_worker_construct_time_stamp = QDateTime::currentDateTime().toTime_t();
}

IpmTransformWorker::IpmTransformWorker(const IpmParameterParser &ipm_para_parser,
                                       const std::string &ccd_dir,
                                       const std::string &ipm_ret_dir,
                                       const std::string &task_name) {
    _m_ipm_model = AdaptiveIpmModel(ipm_para_parser);

    cv::Point2d pt_vp(ipm_para_parser.get_vp_point_x(), ipm_para_parser.get_vp_point_y());
    _m_ipm_model.set_vp_point(pt_vp);

    _m_cam = CameraModel(ipm_para_parser);

    _m_ccd_dir = ccd_dir;
    _m_ipm_ret_dir = ipm_ret_dir;
    _m_task_name = task_name;

    _m_ipm_para_parser = ipm_para_parser;

    _m_worker_construct_time_stamp = QDateTime::currentDateTime().toTime_t();
}

IpmTransformWorker::IpmTransformWorker(const IpmParameterParser &ipm_para_parser,
                                       const std::string &ccd_dir,
                                       const std::string &ipm_ret_dir,
                                       const std::string &frametime_path,
                                       const std::string &task_name) {
    _m_ipm_model = AdaptiveIpmModel(ipm_para_parser);

    cv::Point2d pt_vp(ipm_para_parser.get_vp_point_x(), ipm_para_parser.get_vp_point_y());
    _m_ipm_model.set_vp_point(pt_vp);

    _m_cam = CameraModel(ipm_para_parser);

    _m_ccd_dir = ccd_dir;
    _m_ipm_ret_dir = ipm_ret_dir;
    _m_task_name = task_name;
    _m_frametime_path = frametime_path;

    _m_ipm_para_parser = ipm_para_parser;

    _m_worker_construct_time_stamp = QDateTime::currentDateTime().toTime_t();
}

/***
 * 使用静态相机模型多线程批量处理车天任务
 * @param src_image_dir
 * @param dst_image_dir
 * @param task_name
 */
void IpmTransformWorker::process_batch_image_static() {

    std::string src_image_dir = _m_ccd_dir;
    std::string dst_image_dir = _m_ipm_ret_dir;
    std::string task_name = _m_task_name;

    if (!FileSystemProcessor::is_directory_exist(src_image_dir)) {
        LOG(INFO) << "任务地址: " << src_image_dir << "不存在";
        return;
    }

    // 获取所有任务图像
    std::vector<std::string> image_file_list;
    FileSystemProcessor::get_directory_files(
        src_image_dir, image_file_list, ".jpg",
        FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES);

    std::sort(image_file_list.begin(), image_file_list.end(), less_first);

    if (image_file_list.empty()) {
        LOG(INFO) << "未能正确获取: " << src_image_dir << " 中的CCD图像";
        return;
    }

    QVector<args> args_vec;
    args_vec.reserve(static_cast<int>(image_file_list.size()));
    for (auto &image_path : image_file_list) {
        args tmp;
        tmp.ccd_path = image_path;
        tmp.ipm_ret_dir = dst_image_dir;
        tmp.is_dynamic = false;
        tmp.ccd_pics_nums = static_cast<int>(image_file_list.size());
        args_vec.push_back(tmp);
    }

    image_file_list.clear();
    std::vector<std::string>().swap(image_file_list);

    emit is_process_finished(false);

    QFuture<void> batch_process_future = QtConcurrent::run(this, &IpmTransformWorker::process_batch_image, args_vec);

    QFutureWatcher<void> batch_process_futurewatcher;
    batch_process_futurewatcher.setFuture(batch_process_future);

    batch_process_futurewatcher.waitForFinished();

    emit is_process_finished(true);
}

/***
 * 使用动态相机模型多线程批量处理车天任务
 * @param src_image_dir
 * @param dst_image_dir
 * @param frametime_path
 * @param task_name
 */
void IpmTransformWorker::process_batch_image_dynamic() {

    std::string src_image_dir = _m_ccd_dir;
    std::string dst_image_dir = _m_ipm_ret_dir;
    std::string task_name = _m_task_name;
    std::string frametime_path = _m_frametime_path;

    if (!FileSystemProcessor::is_directory_exist(src_image_dir)) {
        LOG(INFO) << "任务地址: " << src_image_dir << "不存在";
        return;
    }

    // 初始化frametime解析器
    init_frametime_parser(frametime_path);

    // 获取所有任务图像
    std::vector<std::string> image_file_list;
    FileSystemProcessor::get_directory_files(
        src_image_dir, image_file_list, ".jpg",
        FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES);

    std::sort(image_file_list.begin(), image_file_list.end(), less_first);

    if (image_file_list.empty()) {
        LOG(INFO) << "未能正确获取: " << src_image_dir << " 中的CCD图像";
        return;
    }

    if (!FileSystemProcessor::is_directory_exist(src_image_dir)) {
        LOG(INFO) << "任务地址: " << src_image_dir << "不存在";
        return;
    }

    QVector<args> args_vec;
    args_vec.reserve(static_cast<int>(image_file_list.size()));
    for (auto &image_path : image_file_list) {
        args tmp;
        tmp.ccd_path = image_path;
        tmp.ipm_ret_dir = dst_image_dir;
        tmp.is_dynamic = true;
        tmp.ccd_pics_nums = static_cast<int>(image_file_list.size());
        args_vec.push_back(tmp);
    }

    image_file_list.clear();
    std::vector<std::string>().swap(image_file_list);

    emit is_process_finished(false);

    QFuture<void> batch_process_future = QtConcurrent::run(this, &IpmTransformWorker::process_batch_image, args_vec);

    QFutureWatcher<void> batch_process_futurewatcher;
    batch_process_futurewatcher.setFuture(batch_process_future);

    batch_process_futurewatcher.waitForFinished();

    emit is_process_finished(true);
}

void IpmTransformWorker::process_single_image() {

    auto src_image_path = _m_ipm_para_parser.get_ccd_image_path().toStdString();
    args arg;
    arg.ccd_path = src_image_path;
    arg.is_dynamic = false;
    arg.ipm_ret_dir = "";
    arg.ccd_pics_nums = 1;

    QFuture<void> single_process_future = QtConcurrent::run(
                this,
                &IpmTransformWorker::process_single_image_within_multithread,
                arg);
    QFutureWatcher<void> single_process_futurewatcher;
    single_process_futurewatcher.setFuture(single_process_future);

    single_process_futurewatcher.waitForFinished();

    emit is_process_finished(true);
}

void IpmTransformWorker::init_frametime_parser(const std::string &frametime_path) {

    if (!FileSystemProcessor::is_file_exist(frametime_path)) {
        LOG(INFO) << "Frametime文件： " << frametime_path << " 不存在";
    }
}

void IpmTransformWorker::process_single_image_within_multithread(const args &m_arg) {

    auto src_image_path = m_arg.ccd_path;
    auto is_dynamic = m_arg.is_dynamic;
    auto dst_image_dir = m_arg.ipm_ret_dir;

    auto image_name = FileSystemProcessor::get_file_name(src_image_path);

    image_name = image_name.substr(0, image_name.rfind('.')) + ".png";

    auto image_id = image_name.substr(0, image_name.rfind('.'));

    if (!FileSystemProcessor::is_file_exist(src_image_path)) {
        LOG(ERROR) << "原始输入图像: " << src_image_path << " 不存在";
        return;
    }

    auto dst_image_path = FileSystemProcessor::combine_path(dst_image_dir, image_name);

    if (FileSystemProcessor::is_file_exist(dst_image_path)) {
        LOG(ERROR) << "Ipm Result: " << dst_image_path << " already exist";
        return;
    }

    auto src_image = cv::imread(src_image_path, cv::IMREAD_COLOR);

    cv::Mat distorition_image;
    _m_ipm_model.undistortion_image(src_image, distorition_image);

    _m_ipm_model.set_image(distorition_image);

    if (is_dynamic) {
        LOG(ERROR) << "Not support for now and will be released soon";
    } else {
        _m_cam.set_static();
        _m_ipm_model.set_static();
        _m_ipm_model.set_camera(_m_cam);
        _m_ipm_model.ipm_transform(false);
    }

    cv::Mat ipm = _m_ipm_model.get_ipm();

    ipm.copyTo(_m_ipm_image);

    // 保存结果图像
    if (!dst_image_dir.empty()) {
        cv::imwrite(dst_image_path, _m_ipm_image);
    }

    // Change progress value bar
    auto q_dir = QDir(dst_image_dir.c_str());
    q_dir.setNameFilters(QStringList() << "*.png" << "*.jpg");
    auto ipm_ret_nums = q_dir.entryList().size();
    auto progress_value = static_cast<int>(ipm_ret_nums * 100 / m_arg.ccd_pics_nums);

    if (m_arg.ccd_pics_nums >= 1000) {
        emit progress_value_changed(ipm_ret_nums);
    } else {
        emit progress_value_changed(progress_value);
    }

    if (!dst_image_dir.empty()) {
        LOG(INFO) << "Emit singnal: " << progress_value << ", CCD pic nums: "
                  << m_arg.ccd_pics_nums << ", Ipm ret nums: " << ipm_ret_nums;
    } else {
        LOG(INFO) << "Emit signal: process single image";
    }

}

void IpmTransformWorker::process_batch_image(const QVector<args> &m_args) {

    if (m_args.size() > 1000) {
        emit progress_range_changed(0, static_cast<int>(m_args.size()));
    }

    for (auto &m_arg : m_args) {

        if (_m_is_stopped) {
            return;
        }
        process_single_image_within_multithread(m_arg);
        emit report_ipm_image();
    }
}
