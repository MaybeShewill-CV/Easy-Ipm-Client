/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: camerCalibrator.cpp
* Date: 18-7-26 下午5:28
************************************************/

#include "camerCalibrator.h"

#include <iomanip>
#include <chrono>

#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

#include "common/log_utils/beecLogger.h"
#include "common/file_system_utils/file_system_processor.h"

#define DEBUG

using beec::common::file_system_utils::FileSystemProcessor;

namespace beec {
namespace camera_calibration {

/***
 * Constructor
 */
CamerCalibrator::CamerCalibrator(const IpmCamCalibParamParser &ipm_cam_calib_param_parser) {

    _image_size = ipm_cam_calib_param_parser.get_calib_image_size();
    _board_size = ipm_cam_calib_param_parser.get_calib_board_size();
    _square_size = ipm_cam_calib_param_parser.get_calib_square_size();
    _m_calib_paras_save_path = ipm_cam_calib_param_parser.get_calib_para_save_path();
    _m_worker_construct_time_stamp = QDateTime::currentDateTime().toTime_t();
}

CamerCalibrator::CamerCalibrator(const QString &ipm_cam_calib_file_path) {

    cv::FileStorage ipm_cam_calib_paras_file;
    ipm_cam_calib_paras_file.open(ipm_cam_calib_file_path.toStdString(), cv::FileStorage::READ);

    if (!ipm_cam_calib_paras_file.isOpened()) {
        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-6);
        return;
    }

    // judge para type
    std::string para_type;
    ipm_cam_calib_paras_file["Parameters Type"] >> para_type;

    if (para_type != "Ipm Calibration") {
        emit report_calib_process_error_code(-7);
        emit report_is_calib_process_finished(true);
        return;
    }

    int calib_image_width = 0;
    int calib_image_height = 0;
    int board_width = 0;
    int board_height = 0;
    int square_width = 0;
    int square_height = 0;

    cv::Mat camera_matrix;
    cv::Mat distoration_coefficient;

    ipm_cam_calib_paras_file["image_width"] >> calib_image_width;
    ipm_cam_calib_paras_file["image_height"] >> calib_image_height;
    ipm_cam_calib_paras_file["board_cols"] >> board_width;
    ipm_cam_calib_paras_file["board_rows"] >> board_height;
    ipm_cam_calib_paras_file["square_width"] >> square_width;
    ipm_cam_calib_paras_file["square_height"] >> square_height;
    ipm_cam_calib_paras_file["camera_matrix"] >> camera_matrix;
    ipm_cam_calib_paras_file["distortion_coefficients"] >> distoration_coefficient;

    // init class memeber
    _board_size = cv::Size(board_width, board_height);
    _image_size = cv::Size(calib_image_width, calib_image_height);
    _square_size = cv::Size(square_width, square_height);
    camera_matrix.copyTo(_camera_matrix);
    if (distoration_coefficient.rows == 5) {
        distoration_coefficient.copyTo(_dist_coeffs);
    } else if (distoration_coefficient.rows == 4) {
        distoration_coefficient.copyTo(_dist_coeffs_fish);
    }
}

/***
 * 标定相机内参
 * @param board_images_path
 */
void CamerCalibrator::calibrate_camera() {

    auto board_images_path = _m_calib_board_image_path;

    LOG(INFO) << "开始平面相机标定....";
    time_t t_start = clock();

    // 检查标定板图像输入路径
    if (!FileSystemProcessor::is_directory_exist(board_images_path)) {
        LOG(INFO) << "标定板图像输入路径: " << board_images_path << " 不存在,请检查路径后重新输入";
        emit report_is_calib_process_finished(true);
        return;
    }

    // 获取所有标定板图像路径
    std::vector<std::string> image_paths;
    FileSystemProcessor::get_directory_files(
        board_images_path,
        image_paths,
        ".jpg",
        FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES);

    emit report_is_calib_process_finished(false);

    // 提取标定板图像角点信息
    if (!extract_corners(image_paths)) {

        LOG(INFO) << "Ipm camera calibration extract corners falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-1);

        return;
    }
    // 标定相机内参
    if (!calibrate_camera_params()) {

        LOG(INFO) << "Ipm camera calibration calibrate inner paras falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-2);

        return;
    }
    // 评估参数
    if (!evaluate_camera_params()) {

        LOG(INFO) << "Ipm camera calibration evaluate camera paras falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-3);

        return;
    }
    // 可视化相机标定结果
    if (!show_calibration_result(image_paths)) {

        LOG(INFO) << "Ipm camera calibration visualize calib results falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-4);

        return;
    }

    // 保存相机标定参数
    if (!save_camera_params()) {

        LOG(INFO) << "Ipm camera calibration results save falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-5);

        return;
    } else {

        LOG(INFO) << "Ipm camera calibration results save success";
        emit report_calib_process_error_code(5);
    }

    auto cost_time = static_cast<double>((clock() - t_start)) / static_cast<double>(CLOCKS_PER_SEC);
    LOG(INFO) << "相机标定完毕, 耗时: " << cost_time << "s";

    emit report_is_calib_process_finished(true);
}

/***
 * 标定相机内参
 * @param board_images_path
 */
void CamerCalibrator::calibrate_fisheye_camera() {

    auto board_images_path = _m_calib_board_image_path;

    LOG(INFO) << "开始标定鱼眼相机...";
    auto t_start = clock();

    // 获取所有标定板图像路径
    std::vector<std::string> image_paths;
    FileSystemProcessor::get_directory_files(
        board_images_path,
        image_paths,
        ".jpg",
        FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES);

    emit report_is_calib_process_finished(false);

    // 提取标定板图像角点信息
    if (!extract_corners(image_paths)) {

        LOG(INFO) << "Ipm camera calibration extract corners falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-1);

        return;
    }
    // 标定相机内参
    if (!calibrate_camera_params(true)) {

        LOG(INFO) << "Ipm camera calibration calibrate inner paras falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-2);

        return;
    }
    // 评估参数
    if (!evaluate_camera_params(true)) {

        LOG(INFO) << "Ipm camera calibration evaluate camera paras falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-3);

        return;
    }
    // 可视化相机标定结果
    if (!show_calibration_result(image_paths, true)) {

        LOG(INFO) << "Ipm camera calibration visualize calib results falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-4);

        return;
    }

    // 保存相机标定参数
    if (!save_camera_params()) {

        LOG(INFO) << "Ipm camera calibration results save falied";

        emit report_is_calib_process_finished(true);
        emit report_calib_process_error_code(-5);

        return;
    } else {

        LOG(INFO) << "Ipm camera calibration results save success";
        emit report_calib_process_error_code(5);
    }

    auto cost_time = static_cast<double>((clock() - t_start)) / static_cast<double>(CLOCKS_PER_SEC);
    LOG(INFO) << "相机标定完毕, 耗时: " << cost_time << "s";

    emit report_is_calib_process_finished(true);
}

/***
 * Plain image distoration
 * @param output_path
 */
void CamerCalibrator::distorate_plain_image() {

    emit report_is_calib_process_finished(false);

    cv::Mat mapx = cv::Mat(_image_size, CV_32FC1);  // remap矩阵x
    cv::Mat mapy = cv::Mat(_image_size, CV_32FC1);  // remap矩阵y
    cv::Mat R = cv::Mat::eye(3, 3, CV_32F);  // R矩阵

    if (_m_calib_source_image.empty() || !_m_calib_source_image.data) {

        emit report_calib_process_error_code(-8);
        emit report_is_calib_process_finished(true);
        return;
    }

    cv::initUndistortRectifyMap(
            _camera_matrix, _dist_coeffs, R, _camera_matrix,
            _image_size, CV_32FC1, mapx, mapy);

    cv::remap(_m_calib_source_image, _m_calib_ret, mapx, mapy, cv::INTER_CUBIC, cv::BORDER_CONSTANT);

    emit report_calib_result_image();
    emit report_is_calib_process_finished(true);

    return;
}

/***
 * Fisheye image distoration
 * @param output_path
 */
void CamerCalibrator::distorate_fisheye_image() {

    emit report_is_calib_process_finished(false);

    cv::Mat mapx = cv::Mat(_image_size, CV_32FC1);  // remap矩阵x
    cv::Mat mapy = cv::Mat(_image_size, CV_32FC1);  // remap矩阵y
    cv::Mat R = cv::Mat::eye(3, 3, CV_32F);  // R矩阵

    if (_m_calib_source_image.empty() || !_m_calib_source_image.data) {

        emit report_calib_process_error_code(-8);
        emit report_is_calib_process_finished(true);
        return;
    }

    cv::fisheye::initUndistortRectifyMap(
        _camera_matrix, _dist_coeffs_fish, R,
        cv::getOptimalNewCameraMatrix(
            _camera_matrix,
            _dist_coeffs_fish,
            _image_size, 1, _image_size, nullptr),
        _image_size, CV_32FC1, mapx, mapy);

    cv::remap(_m_calib_source_image, _m_calib_ret, mapx, mapy, cv::INTER_CUBIC, cv::BORDER_CONSTANT);

    emit report_calib_result_image();
    emit report_is_calib_process_finished(true);

    return;
}

/***
 * 保存相机标定参数
 * @param output_path
 */
bool CamerCalibrator::save_camera_params() {

   if (_m_calib_paras_save_path.empty()) {
       return false;
   }

    cv::FileStorage fs;
    fs.open(_m_calib_paras_save_path, cv::FileStorage::WRITE);

    if (!fs.isOpened()) {
        LOG(INFO) << "相机标定参数结果: " << _m_calib_paras_save_path << "创建失败";
        return false;
    }

    // write down para type
    fs << "Parameters Type" << "Ipm Calibration";

    //　标定时间
    auto now_second_level = std::chrono::time_point_cast<std::chrono::duration<int,
            std::ratio<1> > >(std::chrono::high_resolution_clock::now());
    auto ut_second = std::chrono::high_resolution_clock::to_time_t(now_second_level);

    fs << "calibration_time" << ctime(&ut_second);

    // 标定板和标定图像信息
    fs << "nframes" << static_cast<int>(_image_corners_seq.size());
    fs << "image_width" << _image_size.width;
    fs << "image_height" << _image_size.height;
    fs << "board_cols" << _board_size.width;
    fs << "board_rows" << _board_size.height;
    fs << "square_width" << _square_size.width;
    fs << "square_height" << _square_size.height;

    // 相机标定参数
    fs << "camera_matrix" << _camera_matrix;
    fs << "distortion_coefficients" << _dist_coeffs;

    // 相机标定参数评估结果
    fs << "avg_reprojection_error" << _total_err;

    fs.release();

    return true;
}

/***
 * 提取所有标定图像角点信息
 * @param input_image_paths
 */
bool CamerCalibrator::extract_corners(const std::vector<std::string> &input_image_paths) {

    LOG(INFO) << "开始提取标定图像角点信息.....";

    // 提取每张标定图像上的角点坐标
    for (size_t index = 0; index < input_image_paths.size(); ++index) {

        auto image_path = input_image_paths[index];

        if (_m_is_process_finished) {
            return false;
        }

        auto image_name = FileSystemProcessor::get_file_name(image_path);

        _m_calib_source_image = cv::imread(image_path, cv::IMREAD_COLOR);

        std::vector<cv::Point2f> corners;

        cv::cvtColor(_m_calib_source_image, _m_extract_corners_ret , CV_RGB2GRAY);

        if (!cv::findChessboardCorners(
                    _m_calib_source_image,
                    _board_size,
                    corners,
                    CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_NORMALIZE_IMAGE +
                    CV_CALIB_CB_FAST_CHECK)) {
            LOG(ERROR) << "未能正确找到图像: " << image_path << " 的棋盘格角点信息";
            continue;
        };

        // 亚像素精确化棋盘格角点位置
        cv::find4QuadCornerSubpix(_m_extract_corners_ret, corners, cv::Size(5, 5));  //对粗提取的角点进行精确化

        _image_corners_seq.push_back(corners);  //保存亚像素角点

        // debug时候保存棋盘格角点图像
#ifdef DEBUG
        auto output_name = image_name.replace(image_name.find(".jpg"), 4, "_corner_vis.jpg");
        auto output_dir = FileSystemProcessor::get_parent_path(image_path);
        auto output_path = FileSystemProcessor::combine_path(output_dir, output_name);
        cv::drawChessboardCorners(_m_extract_corners_ret, _board_size, corners, true);  //用于在图片中标记角点
        cv::cvtColor(_m_extract_corners_ret, _m_extract_corners_ret, cv::COLOR_GRAY2BGR);
        cv::imwrite(output_path, _m_extract_corners_ret);  //显示图片
#endif

        auto progress_value = static_cast<int>((index + 1 ) * 100 / input_image_paths.size());
        emit report_extract_corners_progress(progress_value);

        emit report_extract_corners_image();
    }

    // 输出每张图像上找到的角点坐标
    int image_index = 0;
    for (auto &corners : _image_corners_seq) {

        if (_m_is_process_finished) {
            return false;
        }

        LOG(INFO) << "--图像: " << std::to_string(image_index++) << "张图像角点信息";

        for (auto &corner : corners) {
            LOG(INFO) << std::setprecision(10) << std::showpoint
                      << "----x: " << corner.x
                      << "----y: " << corner.y;
        }
    }
    LOG(INFO) << "标定图像角点坐标提取完毕";
    return true;
}

/***
 * 标定相机内参
 */
bool CamerCalibrator::calibrate_camera_params(bool is_fish_eye) {

    if (_image_corners_seq.empty()) {
        return false;
    }

    LOG(INFO) << "开始标定相机参数";
    LOG(INFO) << "标定图像序列长度: " << _image_corners_seq.size();

    auto image_count = static_cast<int>(_image_corners_seq.size());  // 标定图像张数

    // 初始化标定板上的三维点坐标
    for (int t = 0; t < image_count; t++) {

        if (_m_is_process_finished) {
            return false;
        }

        std::vector<cv::Point3f> tempPointSet;
        for (int i = 0; i < _board_size.height; i++) {
            for (int j = 0; j < _board_size.width; j++) {
                cv::Point3d realPoint;
                // 假设标定板放在世界坐标系中z=0的平面上
                realPoint.x = static_cast<float>(i * _square_size.width);
                realPoint.y = static_cast<float>(j * _square_size.height);
                realPoint.z = 0.0;
                tempPointSet.push_back(realPoint);
            }
        }
        _object_points.push_back(tempPointSet);
    }

    // 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板
    std::vector<int> point_counts;
    for (int i = 0; i < image_count; i++) {

        if (_m_is_process_finished) {
            return false;
        }

        point_counts.push_back(_board_size.width * _board_size.height);
    }

    // 标定相机内参数
    if (!is_fish_eye) {

        if (_m_is_process_finished) {
            return false;
        }

        int flags = 0;
        calibrateCamera(_object_points, _image_corners_seq, _image_size,
                        _camera_matrix, _dist_coeffs, _rvecs_mat, _tvecs_mat, flags);
    } else {

        if (_m_is_process_finished) {
            return false;
        }

        int flags = 0;
        flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
        flags |= cv::fisheye::CALIB_CHECK_COND;
        flags |= cv::fisheye::CALIB_FIX_SKEW;
        cv::fisheye::calibrate(_object_points, _image_corners_seq, _image_size,
                               _camera_matrix, _dist_coeffs_fish, _rvecs_mat, _tvecs_mat, flags);
    }
    LOG(INFO) << "相机标定完成";

    return true;
}

/***
 * 评估标定相机参数
 */
bool CamerCalibrator::evaluate_camera_params(bool is_fish_eye) {

    if (_image_corners_seq.empty()) {
        return false;
    }

    auto image_count = static_cast<int>(_image_corners_seq.size());

    double err = 0.0;  // 每幅图像的平均误差
    std::vector<cv::Point2f> proj_image_points;  // 保存重新计算得到的投影点

    LOG(INFO) << "每幅图像的标定误差:";
    for (int i = 0; i < image_count; i++) {

        if (_m_is_process_finished) {
            return false;
        }

        std::vector<cv::Point3f> tempPointSet = _object_points[i];

        // 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点
        if (!is_fish_eye) {
            cv::projectPoints(tempPointSet, _rvecs_mat[i], _tvecs_mat[i],
                              _camera_matrix, _dist_coeffs, proj_image_points);
        } else {
            cv::fisheye::projectPoints(tempPointSet, proj_image_points, _rvecs_mat[i],
                                       _tvecs_mat[i], _camera_matrix, _dist_coeffs_fish);
        }

        // 计算新的投影点和旧的投影点之间的误差
        std::vector<cv::Point2f> tempImagePoint = _image_corners_seq[i];
        cv::Mat tempImagePointMat = cv::Mat(1, static_cast<int>(tempImagePoint.size()), CV_32FC2);
        cv::Mat image_points2Mat = cv::Mat(1, static_cast<int>(proj_image_points.size()), CV_32FC2);
        for (size_t j = 0; j < tempImagePoint.size(); j++) {
            image_points2Mat.at<cv::Vec2f>(0, j) = cv::Vec2f(proj_image_points[j].x, proj_image_points[j].y);
            tempImagePointMat.at<cv::Vec2f>(0, j) = cv::Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
        }
        err = cv::norm(image_points2Mat, tempImagePointMat, cv::NORM_L2);
        _total_err += err /= _board_size.width * _board_size.height;
        LOG(INFO) << "第" << i + 1 << "幅图像的平均误差：" << err << "像素";

        auto progress_value = static_cast<int>((i + 1 ) * 100 / image_count);
        emit report_evaluate_calib_result_progress(progress_value);
    }
    _total_err /= image_count;
    LOG(INFO) << "总体平均误差：" << _total_err << "像素";
    LOG(INFO) << "评估完成完成！";

    return true;
}

/***
 * 显示标定结果
 * @param input_image_paths
 */
bool CamerCalibrator::show_calibration_result(
    const std::vector<std::string> &input_image_paths,
    bool is_fish_eye) {

    if (_image_corners_seq.empty()) {
        return false;
    }

    LOG(INFO) << "开始可视化标定结果";

    cv::Mat mapx = cv::Mat(_image_size, CV_32FC1);  // remap矩阵x
    cv::Mat mapy = cv::Mat(_image_size, CV_32FC1);  // remap矩阵y
    cv::Mat R = cv::Mat::eye(3, 3, CV_32F);  // R矩阵

    for (size_t index = 0; index < input_image_paths.size(); ++index) {

        auto image_path = input_image_paths[index];

        if (_m_is_process_finished) {
            return false;
        }

        LOG(INFO) << "Frame: " << image_path;

        // 计算去畸变变换矩阵
        if (!is_fish_eye) {
            cv::initUndistortRectifyMap(
                    _camera_matrix, _dist_coeffs, R, _camera_matrix,
                    _image_size, CV_32FC1, mapx, mapy);
        } else {
            cv::fisheye::initUndistortRectifyMap(
                _camera_matrix, _dist_coeffs_fish, R,
                cv::getOptimalNewCameraMatrix(
                    _camera_matrix,
                    _dist_coeffs_fish,
                    _image_size, 1, _image_size, nullptr),
                _image_size, CV_32FC1, mapx, mapy);
        }

        cv::Mat board_image = cv::imread(image_path, cv::IMREAD_COLOR);
        cv::remap(board_image, _m_calib_ret, mapx, mapy, cv::INTER_CUBIC, cv::BORDER_CONSTANT);

        // 保存标定结果图像
        auto image_name = FileSystemProcessor::get_file_name(image_path);
        auto image_dir = FileSystemProcessor::get_parent_path(image_path);
        image_name = image_name.replace(image_name.find(".jpg"), 4, "_calibration.jpg");
        auto output_path = FileSystemProcessor::combine_path(image_dir, image_name);
        cv::imwrite(output_path, _m_calib_ret);

        auto progress_value = static_cast<int>((index + 1 ) * 100 / input_image_paths.size());
        emit report_vis_calib_result_progress(progress_value);
    }

    LOG(INFO) << "可视化完毕";

    return true;
}
}
}
