#include "ipmStitchParamParser.h"

IpmStitchParamParser::IpmStitchParamParser(const IpmStitchParamParser &ipm_stitch_para_parser) {

    this->_m_fy = ipm_stitch_para_parser._m_fy;
    this->_m_tx = ipm_stitch_para_parser._m_tx;
    this->_m_ty = ipm_stitch_para_parser._m_ty;
    this->_m_tz = ipm_stitch_para_parser._m_tz;
    this->_m_yaw = ipm_stitch_para_parser._m_yaw;
    this->_m_pitch = ipm_stitch_para_parser._m_pitch;
    this->_m_ratio = ipm_stitch_para_parser._m_ratio;
    this->_m_ipm_dir = ipm_stitch_para_parser._m_ipm_dir;
    this->_m_center_h = ipm_stitch_para_parser._m_center_h;
    this->_m_center_w = ipm_stitch_para_parser._m_center_w;
    this->_m_end_index = ipm_stitch_para_parser._m_end_index;
    this->_m_step_size = ipm_stitch_para_parser._m_step_size;
    this->_m_output_path = ipm_stitch_para_parser._m_output_path;
    this->_m_start_index = ipm_stitch_para_parser._m_start_index;
    this->_m_panotimeb_path = ipm_stitch_para_parser._m_panotimeb_path;
    this->_m_center_h_top_offset = ipm_stitch_para_parser._m_center_h_top_offset;
    this->_m_center_h_bottom_offset = ipm_stitch_para_parser._m_center_h_bottom_offset;
}

IpmStitchParamParser& IpmStitchParamParser::operator=(const IpmStitchParamParser &ipm_stitch_para_parser) {

    if (this == &ipm_stitch_para_parser) {
        return *this;
    }

    this->_m_fy = ipm_stitch_para_parser._m_fy;
    this->_m_tx = ipm_stitch_para_parser._m_tx;
    this->_m_ty = ipm_stitch_para_parser._m_ty;
    this->_m_tz = ipm_stitch_para_parser._m_tz;
    this->_m_yaw = ipm_stitch_para_parser._m_yaw;
    this->_m_pitch = ipm_stitch_para_parser._m_pitch;
    this->_m_ratio = ipm_stitch_para_parser._m_ratio;
    this->_m_ipm_dir = ipm_stitch_para_parser._m_ipm_dir;
    this->_m_center_h = ipm_stitch_para_parser._m_center_h;
    this->_m_center_w = ipm_stitch_para_parser._m_center_w;
    this->_m_end_index = ipm_stitch_para_parser._m_end_index;
    this->_m_step_size = ipm_stitch_para_parser._m_step_size;
    this->_m_output_path = ipm_stitch_para_parser._m_output_path;
    this->_m_start_index = ipm_stitch_para_parser._m_start_index;
    this->_m_panotimeb_path = ipm_stitch_para_parser._m_panotimeb_path;
    this->_m_center_h_top_offset = ipm_stitch_para_parser._m_center_h_top_offset;
    this->_m_center_h_bottom_offset = ipm_stitch_para_parser._m_center_h_bottom_offset;

    return *this;
}
