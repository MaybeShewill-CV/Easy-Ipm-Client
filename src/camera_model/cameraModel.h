/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* file: cameraModel.h
* Date: 18-10-30 上午10:48
************************************************/

#pragma once

#include <string>

#include <opencv2/opencv.hpp>

#include "tracefile_parser/frametimeParser.h"
#include "interface/ipmparameterparser.h"

namespace beec {
namespace camera_model {
class CameraModel {

public:

    CameraModel();

    explicit CameraModel(const std::string &camera_matrix_path);

    explicit CameraModel(const IpmParameterParser &ipm_para_parser);

    ~CameraModel() = default;

    CameraModel &operator=(const CameraModel &cam);

    CameraModel(const CameraModel &cam);

    void set_camera(const CameraModel &cam);

    void update_camera_with_imu(const beec::tracefile_parser::IMUAttitude &attitude);

    void set_k1(const double k1) {
        _m_k1 = k1;
    }

    void set_k2(const double k2) {
        _m_k2 = k2;
    }

    void set_k3(const double k3) {
        _m_k3 = k3;
    }

    void set_k4(const double k4) {
        _m_k4 = k4;
    }

    void set_p1(const double p1) {
        _m_p1 = p1;
    }

    void set_p2(const double p2) {
        _m_p2 = p2;
    }

    void set_fx(const double fx) {
        _m_fx = fx;
    }

    void set_fy(const double fy) {
        _m_fy = fy;
    }

    void set_cx(const double cx) {
        _m_cx = cx;
    }

    void set_cy(const double cy) {
        _m_cy = cy;
    }

    void set_dynamic() {
        _m_is_dynamic = true;
    }

    void set_static() {
        _m_is_dynamic = false;
    }

    void set_roll(const double roll) {

        if (_m_is_dynamic) {
            _m_roll_angle_dynamic = roll;
        } else {
            _m_roll_angle_base = roll;
        }
    }

    void set_yaw(const double yaw) {

        if (_m_is_dynamic) {
            _m_yaw_angle_dynamic = yaw;
        } else {
            _m_yaw_angle_base = yaw;
        }
    }

    void set_pitch(const double pitch) {

        if (_m_is_dynamic) {
            _m_pitch_angle_dynamic = pitch;
        } else {
            _m_pitch_angle_base = pitch;
        };

    }

    void set_height(const double height) {

        if (_m_is_dynamic) {
            _m_height_dynamic = height;
        } else {
            _m_height_base = height;
        };
    }

    void set_camera_name(const std::string &camera_name) {
        _m_camera_name = camera_name;
    }

    void set_distortion_remap_x(const cv::Mat &remap_x) {
        _m_distortion_remap_x = remap_x;
    }

    void set_distortion_remap_y(const cv::Mat &remap_y) {
        _m_distortion_remap_y = remap_y;
    }

    double get_k1() const {
        return _m_k1;
    }

    double get_k2() const {
        return _m_k2;
    }

    double get_k3() const {
        return _m_k3;
    }

    double get_k4() const {
        return _m_k4;
    }

    double get_p1() const {
        return _m_p1;
    }

    double get_p2() const {
        return _m_p2;
    }

    double get_fx() const {
        return _m_fx;
    }

    double get_fy() const {
        return _m_fy;
    }

    double get_cx() const {
        return _m_cx;
    }

    double get_cy() const {
        return _m_cy;
    }

    double get_roll() const {

        if (_m_is_dynamic) {
            return _m_roll_angle_dynamic;
        } else {
            return _m_roll_angle_base;
        }

    }

    double get_yaw() const {

        if (_m_is_dynamic) {
            return _m_yaw_angle_dynamic;
        } else {
            return _m_yaw_angle_base;
        }
    }

    double get_pitch() const {

        if (_m_is_dynamic) {
            return _m_pitch_angle_dynamic;
        } else {
            return _m_pitch_angle_base;
        }
    }

    double get_height() const {

        if (_m_is_dynamic) {
            return _m_height_dynamic;
        } else {
            return _m_height_base;
        }
    }

    std::string get_camera_name() const {
        return _m_camera_name;
    }

    bool is_camera_dynamic() const {
        return _m_is_dynamic;
    }

    void undistortion_image(const cv::Mat &src_image, cv::Mat &dst_image);

    void print_camera_info();

    inline bool is_distoration_remap_matrix_loded() {
        return !_m_distortion_remap_x.empty() && _m_distortion_remap_x.data
                && !_m_distortion_remap_y.empty() && _m_distortion_remap_y.data;
    }

private:
    //内参
    double _m_k1;
    double _m_k2;
    double _m_k3;
    double _m_k4;
    double _m_p1;
    double _m_p2;

    double _m_fx;
    double _m_fy;

    double _m_cx;
    double _m_cy;

    //外参
    double _m_roll_angle_base; // 基准roll角度
    double _m_yaw_angle_base; // 基准yaw角度
    double _m_pitch_angle_base; // 基准pitch角度
    double _m_height_base;

    double _m_roll_angle_dynamic; // 动态roll角度
    double _m_yaw_angle_dynamic; // 动态yaw角度
    double _m_pitch_angle_dynamic; // 动态pitch角度
    double _m_height_dynamic;

    bool _m_is_dynamic = false;

    std::string _m_camera_name;

    cv::Mat _m_distortion_remap_x; // 去畸变remap_x矩阵
    cv::Mat _m_distortion_remap_y; // 去畸变remap_y矩阵

    void init_camera();
};
}
}
