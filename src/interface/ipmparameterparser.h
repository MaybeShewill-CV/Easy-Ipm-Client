#pragma once

#include <QObject>
#include <QString>

class IpmParameterParser
{
public:
    IpmParameterParser() = default;
    ~IpmParameterParser() = default;

    IpmParameterParser &operator=(const IpmParameterParser &ipm_para_parser);

    IpmParameterParser(const IpmParameterParser &ipm_para_parser);

    inline QString get_calib_file_path() const {
        return _m_calib_file_path;
    }

    inline int get_calib_image_width() const {
        return _m_calib_image_width;
    }

    inline int get_calib_image_height() const {
        return _m_calib_image_height;
    }

    inline double get_vp_point_x() const {
        return _m_vp_pt_x;
    }

    inline double get_vp_point_y() const {
        return _m_vp_pt_y;
    }

    inline int get_ipm_image_width() const {
        return _m_ipm_image_width;
    }

    inline int get_ipm_image_height() const {
        return _m_ipm_image_height;
    }

    inline QString get_camera_name() const {
        return _m_camera_name;
    }

    inline double get_camera_pitch() const {
        return _m_camera_pitch;
    }

    inline double get_camera_yaw() const {
        return _m_camera_yaw;
    }

    inline double get_camera_height() const {
        return _m_camera_height;
    }

    inline QString get_ccd_image_path() const {
        return _m_ccd_image_path;
    }

    inline void set_calib_file_path(QString &calib_file_path) {
        _m_calib_file_path = calib_file_path;
    }

    inline void set_calib_image_width(int image_width) {
        _m_calib_image_width = image_width;
    }

    inline void set_calib_image_height(int image_height) {
        _m_calib_image_height = image_height;
    }

    inline void set_vp_point_x(double x) {
        _m_vp_pt_x = x;
    }

    inline void set_vp_point_y(double y) {
        _m_vp_pt_y = y;
    }

    inline void set_ipm_image_width(int image_width) {
        _m_ipm_image_width = image_width;
    }

    inline void set_ipm_image_height(int image_height) {
        _m_ipm_image_height = image_height;
    }

    inline void set_camera_name(const QString &cam_name) {
        _m_camera_name = cam_name;
    }

    inline void set_camera_pitch(double pitch) {
        _m_camera_pitch = pitch;
    }

    inline void set_camera_yaw(double yaw) {
        _m_camera_yaw = yaw;
    }

    inline void set_camera_height(double height) {
        _m_camera_height = height;
    }

    inline void set_ccd_path(QString &ccd_path) {
        _m_ccd_image_path = ccd_path;
    }

private:
    QString _m_calib_file_path = ""; // camera calib file path

    int _m_calib_image_width = 0; // distorition image width
    int _m_calib_image_height = 0; // distorition image height

    QString _m_camera_name = ""; // camera name
    double _m_camera_pitch = 0.0; // camera pos pitch
    double _m_camera_yaw = 0.0; // camera pos roll
    double _m_camera_height = 3500.0; // camera pos height

    double _m_vp_pt_x = 0.0; // ipm model vanish point x
    double _m_vp_pt_y = 0.0; // ipm model vanish point y

    int _m_ipm_image_width = 1280; // ipm image width
    int _m_ipm_image_height = 1280; // ipm image height

    QString _m_ccd_image_path = ""; // ccd image path

};
