/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: ipmCamCalibParamParser.cpp
* Date: 18-12-26 下午2:23
************************************************/

#include "ipmCamCalibParamParser.h"

IpmCamCalibParamParser::IpmCamCalibParamParser(const IpmCamCalibParamParser &parser)
{
    this->_m_image_size = parser._m_image_size;
    this->_m_board_size = parser._m_board_size;
    this->_m_square_size = parser._m_square_size;
    this->_m_calib_para_save_path = parser._m_calib_para_save_path;
}

IpmCamCalibParamParser& IpmCamCalibParamParser::operator=(const IpmCamCalibParamParser &parser) {

    if (this == &parser) {
        return *this;
    }

    this->_m_image_size = parser._m_image_size;
    this->_m_board_size = parser._m_board_size;
    this->_m_square_size = parser._m_square_size;
    this->_m_calib_para_save_path = parser._m_calib_para_save_path;

    return *this;
}
