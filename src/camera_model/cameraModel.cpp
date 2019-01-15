/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: cameraModel.cpp
* Date: 18-10-30 上午10:48
************************************************/

#include "cameraModel.h"

#include <opencv2/core/persistence.hpp>

#include "common/file_system_utils/file_system_processor.h"
#include "common/log_utils/beecLogger.h"

namespace beec {
namespace camera_model {

using beec::tracefile_parser::IMUAttitude;
using beec::common::file_system_utils::FileSystemProcessor;

const double DEG2RAD = 0.01745329252;

/***********
 * Public Function Sets
 */

/***
 * 构造函数
 */
CameraModel::CameraModel() {
    init_camera();
}

/***
 * 构造函数
 */
CameraModel::CameraModel(const std::string &camera_matrix_path) {

    if (!FileSystemProcessor::is_file_exist(camera_matrix_path)) {
        LOG(INFO) << "相机标定参数: " << camera_matrix_path << " 不存在";
        init_camera();
        return;
    }

    cv::FileStorage fs(camera_matrix_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        LOG(INFO) << "相机标定参数: " << camera_matrix_path << " 无法正常打开";
        init_camera();
        return;
    }

    cv::Mat camera_matrix;
    cv::Mat distortion_coefficients;

    (*fs["camera_matrix"].end()) >> camera_matrix;
    (*fs["distortion_coefficients"].end()) >> distortion_coefficients;

    fs.release();

//    auto image_size = cv::Size(2448, 2048); // ccd图像尺寸
    auto image_size = cv::Size(4096, 2160); // cmos图像尺寸

    // 平面相机内参初始化去畸变remap矩阵
    cv::initUndistortRectifyMap(
            camera_matrix,
            distortion_coefficients,
            cv::Mat(),
            camera_matrix,
            image_size, CV_32FC1,
            _m_distortion_remap_x, _m_distortion_remap_y);

    // 鱼眼相机内参初始化去畸变remap矩阵
//    cv::fisheye::initUndistortRectifyMap(
//            camera_matrix, distortion_coefficients, cv::Mat(),
//            cv::getOptimalNewCameraMatrix(
//                    camera_matrix,
//                    distortion_coefficients,
//                    image_size, 1, image_size, nullptr),
//            image_size, CV_32FC1, _m_distortion_remap_x, _m_distortion_remap_y);

    _m_cx = camera_matrix.at<double>(0, 2);
    _m_cy = camera_matrix.at<double>(1, 2);
    _m_fx = camera_matrix.at<double>(0, 0);
    _m_fy = camera_matrix.at<double>(1, 1);
    _m_k1 = distortion_coefficients.at<double>(0, 0);
    _m_k2 = distortion_coefficients.at<double>(1, 0);
    _m_k3 = distortion_coefficients.at<double>(2, 0);
    _m_k4 = distortion_coefficients.at<double>(3, 0);
    _m_p1 = 0.001186043659633;
    _m_p2 = 0.0;

    _m_roll_angle_base = 0;
    _m_yaw_angle_base = 0;
    _m_pitch_angle_base = 15.5 * DEG2RAD;
    _m_height_base = 3500;

    _m_roll_angle_dynamic = 0;
    _m_yaw_angle_dynamic = 0;
    _m_pitch_angle_dynamic = 0;
    _m_height_dynamic = 0;

    _m_camera_name = "CCD_Camera";
}

/***
 * 构造函数
 */
CameraModel::CameraModel(const IpmParameterParser &ipm_para_parser) {

    auto camera_matrix_path = ipm_para_parser.get_calib_file_path().toStdString();

    if (!FileSystemProcessor::is_file_exist(camera_matrix_path)) {
        LOG(INFO) << "相机标定参数: " << camera_matrix_path << " 不存在";
        init_camera();
        return;
    }

    cv::FileStorage fs(camera_matrix_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        LOG(INFO) << "相机标定参数: " << camera_matrix_path << " 无法正常打开";
        init_camera();
        return;
    }

    cv::Mat camera_matrix;
    cv::Mat distortion_coefficients;

    (*fs["camera_matrix"].end()) >> camera_matrix;
    (*fs["distortion_coefficients"].end()) >> distortion_coefficients;

    fs.release();

    auto image_size = cv::Size(ipm_para_parser.get_calib_image_width(),
                               ipm_para_parser.get_calib_image_height()); // distorition image size

    // 平面相机内参初始化去畸变remap矩阵
    cv::initUndistortRectifyMap(
            camera_matrix,
            distortion_coefficients,
            cv::Mat(),
            camera_matrix,
            image_size, CV_32FC1,
            _m_distortion_remap_x, _m_distortion_remap_y);

    // 鱼眼相机内参初始化去畸变remap矩阵
//    cv::fisheye::initUndistortRectifyMap(
//            camera_matrix, distortion_coefficients, cv::Mat(),
//            cv::getOptimalNewCameraMatrix(
//                    camera_matrix,
//                    distortion_coefficients,
//                    image_size, 1, image_size, nullptr),
//            image_size, CV_32FC1, _m_distortion_remap_x, _m_distortion_remap_y);

    _m_cx = camera_matrix.at<double>(0, 2);
    _m_cy = camera_matrix.at<double>(1, 2);
    _m_fx = camera_matrix.at<double>(0, 0);
    _m_fy = camera_matrix.at<double>(1, 1);
    _m_k1 = distortion_coefficients.at<double>(0, 0);
    _m_k2 = distortion_coefficients.at<double>(1, 0);
    _m_k3 = distortion_coefficients.at<double>(2, 0);
    _m_k4 = distortion_coefficients.at<double>(3, 0);
    _m_p1 = 0.001186043659633;
    _m_p2 = 0.0;

    _m_roll_angle_base = 0.0;
    _m_yaw_angle_base = ipm_para_parser.get_camera_yaw() * DEG2RAD;
    _m_pitch_angle_base = ipm_para_parser.get_camera_pitch() * DEG2RAD;
    _m_height_base = ipm_para_parser.get_camera_height();

    _m_roll_angle_dynamic = 0;
    _m_yaw_angle_dynamic = 0;
    _m_pitch_angle_dynamic = 0;
    _m_height_dynamic = 0;

    _m_camera_name = ipm_para_parser.get_camera_name().toStdString();
}

/***
 * 复制构造函数
 * @param cam
 */
CameraModel::CameraModel(const CameraModel &cam) {
    this->set_camera(cam);
}

/***
 * 赋值构造函数
 * @param cam
 * @return
 */
CameraModel &CameraModel::operator=(const CameraModel &cam) {
    this->set_camera(cam);

    return *this;
}

/***
 * 设置相机模型参数=
 * @param cam
 */
void CameraModel::set_camera(const CameraModel &cam) {

    this->set_cx(cam.get_cx());
    this->set_cy(cam.get_cy());
    this->set_fx(cam.get_fx());
    this->set_fy(cam.get_fy());
    this->set_k1(cam.get_k1());
    this->set_k2(cam.get_k2());
    this->set_k3(cam.get_k3());
    this->set_k4(cam.get_k4());
    this->set_p1(cam.get_p1());
    this->set_p2(cam.get_p2());

    this->set_distortion_remap_x(cam._m_distortion_remap_x);
    this->set_distortion_remap_y(cam._m_distortion_remap_y);

    if (cam.is_camera_dynamic()) {
        this->set_dynamic();
    } else {
        this->set_static();
    }

    this->set_roll(cam.get_roll());
    this->set_pitch(cam.get_pitch());
    this->set_yaw(cam.get_yaw());
    this->set_height(cam.get_height());

    this->set_camera_name(cam.get_camera_name());
}

void CameraModel::undistortion_image(
        const cv::Mat &src_image,
        cv::Mat &dst_image) {

    // 去畸变remap矩阵为空则返回原图
    if (_m_distortion_remap_x.empty() || !_m_distortion_remap_x.data ||
    _m_distortion_remap_y.empty() || !_m_distortion_remap_y.data) {
        dst_image = src_image;
    }

    cv::remap(src_image, dst_image, _m_distortion_remap_x, _m_distortion_remap_y, cv::INTER_CUBIC);
}

/***
 * 利用imu姿态动态更新相机姿态
 * @param attitude
 */
void CameraModel::update_camera_with_imu(const IMUAttitude &attitude) {

    auto imu_pitch = attitude.pitch;
//    auto imu_yaw = attitude.yaw;  // yaw值不需要修改 统一默认为全部指向同一个方向
    auto imu_roll = attitude.roll;
    auto imu_hell_diff = attitude.hell_diff;

    _m_pitch_angle_dynamic = _m_pitch_angle_base + imu_pitch * DEG2RAD;
//    _m_yaw_angle_dynamic = _m_yaw_angle_base + imu_yaw * DEG2RAD;
    _m_roll_angle_dynamic = _m_roll_angle_base + imu_roll * DEG2RAD;
    _m_height_dynamic = _m_height_base + imu_hell_diff * 1000;
}

/***
 *
 */
void CameraModel::print_camera_info() {

    LOG(INFO) << "相机模型如下: ";
    LOG(INFO) << "fx: " << this->get_fx();
    LOG(INFO) << "fy: " << this->get_fy();
    LOG(INFO) << "cx: " << this->get_cx();
    LOG(INFO) << "cy: " << this->get_cy();
    LOG(INFO) << "k1: " << this->get_k1();
    LOG(INFO) << "k2: " << this->get_k2();
    LOG(INFO) << "k3: " << this->get_k3();
    LOG(INFO) << "k4: " << this->get_k4();
    LOG(INFO) << "p1: " << this->get_p1();
    LOG(INFO) << "p2: " << this->get_p2();
    LOG(INFO) << "yaw: " << this->get_yaw();
    LOG(INFO) << "pitch: " << this->get_pitch();
    LOG(INFO) << "roll: " << this->get_roll();
    LOG(INFO) << "height: " << this->get_height();
    LOG(INFO) << "dis_remap_x size: " << _m_distortion_remap_x.size();
    LOG(INFO) << "dis_remap_y size: " << _m_distortion_remap_y.size();

}

/****
 * Private function sets
 */

/***
 * 初始化相机模型
 */
void CameraModel::init_camera() {

    // 按照GH车的标定参数作为相机模型的初始化参数
    _m_cx = 1242.326488564706300;
    _m_cy = 1026.097849335014600;
    _m_fx = 1447.202463181167800;
    _m_fy = 1444.830918355060500;
    _m_k1 = -0.033850581058052;
    _m_k2 = 0.049601944838468;
    _m_k3 = 0.001294207618177;
    _m_k4 = 0.0;
    _m_p1 = 0.001186043659633;
    _m_p2 = 0.0;

    _m_roll_angle_base = 0;
    _m_yaw_angle_base = 0;
    _m_pitch_angle_base = 15 * DEG2RAD;
    _m_height_base = 3500;

    _m_roll_angle_dynamic = 0;
    _m_yaw_angle_dynamic = 0;
    _m_pitch_angle_dynamic = 0;
    _m_height_dynamic = 0;

    _m_camera_name = "CCD_Camera";
}

}
}
