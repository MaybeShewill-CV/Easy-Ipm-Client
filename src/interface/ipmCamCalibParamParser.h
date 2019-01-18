/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: ipmCamCalibParamParser.h
* Date: 18-12-29 下午5:28
************************************************/

#pragma once

#include <QObject>

#include <string>

#include <opencv2/opencv.hpp>

class IpmCamCalibParamParser
{
public:
    IpmCamCalibParamParser() = default;
    ~IpmCamCalibParamParser() = default;

    IpmCamCalibParamParser &operator=(const IpmCamCalibParamParser &ipm_para_parser);

    IpmCamCalibParamParser(const IpmCamCalibParamParser &ipm_para_parser);

    inline cv::Size get_calib_image_size() const {
        return _m_image_size;
    }

    inline cv::Size get_calib_board_size() const {
        return _m_board_size;
    }

    inline cv::Size get_calib_square_size() const {
        return _m_square_size;
    }

    inline std::string get_calib_para_save_path() const {
        return _m_calib_para_save_path;
    }

    inline void set_calib_image_size(const cv::Size &size) {
        _m_image_size = size;
    }

    inline void set_calib_board_size(const cv::Size &size) {
        _m_board_size = size;
    }

    inline void set_calib_square_size(const cv::Size &size) {
        _m_square_size = size;
    }

    inline void set_calib_para_save_path(const std::string& path) {
        _m_calib_para_save_path = path;
    }

private:

    cv::Size _m_image_size;  // 标定图像尺寸
    cv::Size _m_board_size;  // 标定板行列数
    cv::Size _m_square_size;  // 标定板每个棋盘格实际大小

    std::string _m_calib_para_save_path;
};
