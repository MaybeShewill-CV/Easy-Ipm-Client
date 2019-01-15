#include "ipmparameterparser.h"

IpmParameterParser::IpmParameterParser(const IpmParameterParser &ipm_para_parser) {
    this->_m_vp_pt_x = ipm_para_parser._m_vp_pt_x;
    this->_m_vp_pt_y = ipm_para_parser._m_vp_pt_y;
    this->_m_camera_name = ipm_para_parser._m_camera_name;
    this->_m_camera_pitch = ipm_para_parser._m_camera_pitch;
    this->_m_camera_height = ipm_para_parser._m_camera_pitch;
    this->_m_calib_file_path = ipm_para_parser._m_calib_file_path;
    this->_m_ipm_image_width = ipm_para_parser._m_ipm_image_width;
    this->_m_ipm_image_height = ipm_para_parser._m_ipm_image_height;
    this->_m_calib_image_width = ipm_para_parser._m_calib_image_width;
    this->_m_calib_image_height = ipm_para_parser._m_calib_image_height;
    this->_m_ccd_image_path = ipm_para_parser._m_ccd_image_path;
}

IpmParameterParser &IpmParameterParser::operator=(const IpmParameterParser &ipm_para_parser) {

    if (this == &ipm_para_parser) {
        return *this;
    }

    this->_m_vp_pt_x = ipm_para_parser._m_vp_pt_x;
    this->_m_vp_pt_y = ipm_para_parser._m_vp_pt_y;
    this->_m_camera_name = ipm_para_parser._m_camera_name;
    this->_m_camera_pitch = ipm_para_parser._m_camera_pitch;
    this->_m_camera_height = ipm_para_parser._m_camera_pitch;
    this->_m_calib_file_path = ipm_para_parser._m_calib_file_path;
    this->_m_ipm_image_width = ipm_para_parser._m_ipm_image_width;
    this->_m_ipm_image_height = ipm_para_parser._m_ipm_image_height;
    this->_m_calib_image_width = ipm_para_parser._m_calib_image_width;
    this->_m_calib_image_height = ipm_para_parser._m_calib_image_height;
    this->_m_ccd_image_path = ipm_para_parser._m_ccd_image_path;

    return *this;
}
