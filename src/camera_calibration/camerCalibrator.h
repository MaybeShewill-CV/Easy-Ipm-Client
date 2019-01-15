/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: camerCalibrator.h
* Date: 18-7-26 下午5:28
************************************************/

#pragma once

#include <QObject>

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

#include "interface/ipmCamCalibParamParser.h"

// 相机标定类

namespace beec {
namespace camera_calibration {

class CamerCalibrator : public QObject{

    Q_OBJECT

public slots:

    void calibrate_camera();

    void calibrate_fisheye_camera();

    void distorate_plain_image();

    void distorate_fisheye_image();

    void terminate_calibration_process() {
        _m_is_process_finished = true;
    }

public:

    explicit CamerCalibrator(QObject *parent = nullptr) : QObject(parent) {}

    CamerCalibrator(const IpmCamCalibParamParser &ipm_cam_calib_param_parser);

    CamerCalibrator(const QString &ipm_cam_calib_file_path);

    ~CamerCalibrator() = default;

    inline void set_calib_para_save_path(const std::string& path) {
        _m_calib_paras_save_path = path;
    }

    inline void set_calib_source_image(const cv::Mat &image) {
        image.copyTo(_m_calib_source_image);
    }

    inline void set_calib_image_dir(const std::string& path) {
        _m_calib_board_image_path = path;
    }

    inline std::string get_calib_image_dir() const {
        return _m_calib_board_image_path;
    }

    inline std::string get_calib_para_save_path() const {
        return _m_calib_paras_save_path;
    }

    inline cv::Mat get_extract_corner_result_image() const {
        return _m_extract_corners_ret;
    }

    inline cv::Mat get_calib_result_image() const {
        return _m_calib_ret;
    }

    inline cv::Mat get_calib_source_image() const {
        return _m_calib_source_image;
    }

    inline uint get_worker_construct_time_stamp() const {
        return _m_worker_construct_time_stamp;
    }

private:
    cv::Size _image_size;  // 标定图像尺寸
    cv::Size _board_size;  // 标定板行列数
    cv::Size _square_size;  // 标定板每个棋盘格实际大小
    double _total_err = 0.0;  // 所有图像的平均误差的总和

    std::vector<std::vector<cv::Point2f> > _image_corners_seq;  // 所有标定板上的角点坐标
    std::vector<std::vector<cv::Point3f> > _object_points;  //保存标定板上角点的三维坐标

    cv::Mat _camera_matrix = cv::Mat(3, 3, CV_64FC1, cv::Scalar::all(0));  // 相机内参矩阵
    cv::Mat _dist_coeffs = cv::Mat(5, 1, CV_64FC1, cv::Scalar::all(0));  // 摄像机的5个畸变系数：k1,k2,p1,p2,k3
    cv::Mat _dist_coeffs_fish = cv::Mat(4, 1, CV_64FC1, cv::Scalar::all(0));  // 摄像机的4个畸变系数：k1,k2,p1,p2

    std::vector<cv::Mat> _tvecs_mat;  //每幅图像的旋转向量
    std::vector<cv::Mat> _rvecs_mat;  //每幅图像的平移向量

    bool _m_is_process_finished = false;

    std::string _m_calib_board_image_path = ""; // calib board image path
    std::string _m_calib_paras_save_path = ""; // calib result save path

    cv::Mat _m_extract_corners_ret; // extract corners result image
    cv::Mat _m_calib_ret; // calibration result image
    cv::Mat _m_calib_source_image; // input source image

    uint _m_worker_construct_time_stamp = 0;

    // 提取所有标定图像角点信息
    bool extract_corners(const std::vector<std::string> &input_image_paths);

    // 相机内参数标定
    bool calibrate_camera_params(bool is_fish_eye = false);

    // 评估相机标定参数
    bool evaluate_camera_params(bool is_fish_eye = false);

    // 显示标定结果
    bool show_calibration_result(
        const std::vector<std::string> &input_image_paths,
        bool is_fish_eye = false);

    // 保存相机标定参数
    bool save_camera_params();

signals:

    void report_extract_corners_progress(int);

    void report_evaluate_calib_result_progress(int);

    void report_vis_calib_result_progress(int);

    void report_is_calib_process_finished(bool);

    void report_extract_corners_image();

    void report_calib_result_image();

    void report_calib_process_error_code(int);
};
}
}
