/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: adaptiveIpmModel.h
* Date: 18-10-30 下午1:25
************************************************/

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>

#include <opencv2/opencv.hpp>

#include "camera_model/cameraModel.h"
#include "interface/ipmparameterparser.h"

#define FLOAT_MAT_ELEM_TYPE float
#define FLOAT_MAT_TYPE CV_32FC1
#define UCHAR_COLOR_MAT_TYPE CV_8UC4

namespace beec {
namespace ipm_model {

typedef struct {

    // 世界坐标系下的x坐标的最大值和最小值
    float x_limits[2];
    // 世界坐标系下的y坐标的最大值和最小值
    float y_limits[2];

    // 毫米和像素距离的转换比例关系(x方向)
    float x_scale;
    // 毫米和像素距离的转换比例关系(y方向)
    float y_scale;

    // 俯视图宽
    int ipm_width;
    // 俯视图高
    int ipm_height;

    // 灭点的y坐标的偏移比例
    float vp_portion;
    // 初始灭点y坐标偏移比例
    float vp_init_portion;

    // 俯视图对应的原图像的左边界
    float ipm_left;
    // 俯视图对应的原图像的右边界
    float ipm_right;
    // 俯视图对应的原图像的上边界
    float ipm_top;
    // 俯视图对应的原图像的下边界
    float ipm_bottom;

    // 俯视图插值方法 (0 双线性, 1 最近邻)
    int ipm_interpolation;

} IPMInfo;

class AdaptiveIpmModel {

public:
    AdaptiveIpmModel();

    ~AdaptiveIpmModel() = default;

    explicit AdaptiveIpmModel(const beec::camera_model::CameraModel &cam);

    explicit AdaptiveIpmModel(const std::string &cam_matrix_path);

    explicit AdaptiveIpmModel(const IpmParameterParser &ipm_para_parser);

    AdaptiveIpmModel &operator=(const AdaptiveIpmModel &ipm_model);
    AdaptiveIpmModel(const AdaptiveIpmModel &ipm_model);

    // 设置相机模型
    inline void set_camera(const beec::camera_model::CameraModel &cam) {
        _m_cam.set_camera(cam);
    }

    // 设置动态相机姿态
    inline void set_dynamic() {
        _m_cam.set_dynamic();
        _m_is_dynamic = true;
    }

    // 设置静态相机姿态
    inline void set_static() {
        _m_cam.set_static();
        _m_is_dynamic = false;
    }

    // 设置灭点
    inline void set_vp_point(const cv::Point &pt) {
        _m_vp_pt = pt;
    }

    // 设置需要处理的图像和生成的俯视图大小信息
    inline void set_image(const cv::Mat &image) {
        _m_src_img = image;
        _m_ipm_img.create(_m_ipm_image_height, _m_ipm_image_width, UCHAR_COLOR_MAT_TYPE);
        _m_ipm_info.ipm_bottom = _m_src_img.rows;
        _m_ipm_info.ipm_right = _m_src_img.cols;
    }

    // 获取俯视图
    inline cv::Mat get_ipm() const {
        return _m_ipm_img;
    }

    inline bool is_dynamic() const {
        return _m_is_dynamic;
    }

    // 基于灭点和相机姿态俯视图转换
    void ipm_transform(bool is_dynamic=false);

    // 创建remap矩阵用于后续批量生产
    void create_remap(const std::string &remap_output_path);

    void undistortion_image(const cv::Mat &src_image, cv::Mat &dst_image) {

        return _m_cam.undistortion_image(src_image, dst_image);
    }

private:

    cv::Point _m_vp_pt; // 灭点

    cv::Mat _m_src_img; // 原始图
    cv::Mat _m_ipm_img; // 俯视图

    IPMInfo _m_ipm_info; // 俯视图信息

    int _m_ipm_image_width = 1280;
    int _m_ipm_image_height = 1280;

    beec::camera_model::CameraModel _m_cam; // 相机模型

    bool _m_is_dynamic = false; // 是否使用动态相机姿态

    // 初始化俯视图信息
    void init_ipm_info();

    // 根据相机模型估计灭点
    cv::Point2d get_vanish_point(const beec::camera_model::CameraModel &cam);

    // 像平面坐标转换到地面平面
    void transform_image2ground(
        const cv::Mat &inPoints,
        cv::Mat &outPoints,
        beec::camera_model::CameraModel &cam,
        bool is_dynamic=false);

    // 地面平面坐标转换到像平面
    void transform_ground2image(
        const cv::Mat &inPoints,
        cv::Mat &outPoints,
        beec::camera_model::CameraModel &cam,
        bool is_dynamic=false);
};

}
}
