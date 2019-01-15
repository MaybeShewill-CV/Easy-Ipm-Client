#pragma once

#include<string>

class IpmStitchParamParser
{
public:
    IpmStitchParamParser() = default;
    ~IpmStitchParamParser() = default;

    IpmStitchParamParser &operator=(const IpmStitchParamParser &ipm_stitch_para_parser);

    IpmStitchParamParser(const IpmStitchParamParser &ipm_stitch_para_parser);

    inline void set_pitch(double pitch) {
        _m_pitch = pitch;
    }

    inline void set_yaw(double yaw) {
        _m_yaw = yaw;
    }

    inline void set_fy(double fy) {
        _m_fy = fy;
    }

    inline void set_ratio(double ratio) {
        _m_ratio = ratio;
    }

    inline void set_step_size(uint32_t step_size) {
        _m_step_size = step_size;
    }

    inline void set_start_index(uint32_t start_index) {
        _m_start_index = start_index;
    }

    inline void set_end_index(uint32_t end_index) {
        _m_end_index = end_index;
    }

    inline void set_center_x(int center_w) {
        _m_center_w = center_w;
    }

    inline void set_center_y(int center_h) {
        _m_center_h = center_h;
    }

    inline void set_center_h_top_offset(int offset) {
        _m_center_h_top_offset = offset;
    }

    inline void set_center_h_bottom_offset(int offset) {
        _m_center_h_bottom_offset = offset;
    }

    inline void set_ipm_dir(std::string &ipm_dir) {
        _m_ipm_dir = ipm_dir;
    }

    inline void set_panob_path(std::string &path) {
        _m_panotimeb_path = path;
    }

    inline void set_output_path(std::string &path) {
        _m_output_path = path;
    }

    inline double get_pitch() const {
        return _m_pitch;
    }

    inline double get_yaw() const {
        return _m_yaw;
    }

    inline double get_fy() const {
        return _m_fy;
    }

    inline double get_ratio() const {
        return _m_ratio;
    }

    inline uint32_t get_step_size() const {
        return _m_step_size;
    }

    inline uint32_t get_start_index() const {
        return _m_start_index;
    }

    inline uint32_t get_end_index() const {
        return _m_end_index;
    }

    inline int get_center_w() const {
        return _m_center_w;
    }

    inline int get_center_h() const {
        return _m_center_h;
    }

    inline int get_center_top_offset() const {
        return _m_center_h_top_offset;
    }

    inline int get_center_bottom_offset() const {
        return _m_center_h_bottom_offset;
    }

    inline std::string get_ipm_dir() const {
        return _m_ipm_dir;
    }

    inline std::string get_panob_path() const {
        return _m_panotimeb_path;
    }

    inline std::string get_output_path() const {
        return _m_output_path;
    }

private:

    double _m_pitch = 0.0; // 相机姿态
    double _m_yaw = 0.0; // 相机姿态
    double _m_fy = 0.0; // 相机fy内参
    double _m_ratio = 0.0; // 像素和实际距离的换算比例
    uint32_t _m_step_size = 0; // 拼接步长(每几张拼接一次)
    uint32_t _m_start_index = 0; // 待拼接俯视图起始编号
    uint32_t _m_end_index = 0; // 待拼接俯视图结束编号

    int _m_center_w = 0; // 俯视图中心点横坐标
    int _m_center_h = 0; // 俯视图中心点纵坐标
    int _m_center_h_top_offset = 0; // 俯视图roi区域中心点向上偏移量(一般偏移到能看到三到四根车道线的位置)
    int _m_center_h_bottom_offset = 0; // 俯视图roi区域中心点向下偏移量(一般偏移到俯视图车头最顶端处)

    float _m_tx = 0.0; // 张正友模型tx
    float _m_ty = 0.0; // 张正友模型ty
    float _m_tz = 0.0; // 张正友模型tz

    std::string _m_ipm_dir = ""; // 单张俯视图存放路径
    std::string _m_panotimeb_path = ""; // 车天轨迹信息panotimeb文件路径
    std::string _m_output_path = ""; // 俯视图拼接结果保存路径

};
