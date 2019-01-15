/************************************************
* Copyright 2014 Baidu Inc. All Rights Reserved.
* Author: Luo Yao (luoyao@baidu.com)
* File: ipmTransformWorker.h
* Date: 18-12-24 下午3:43
************************************************/

#pragma once

#include <QObject>
#include <QImage>

#include <boost/thread.hpp>
#include <opencv2/opencv.hpp>

#include "interface/ipmparameterparser.h"
#include "ipm_model/adaptiveIpmModel.h"
#include "camera_model/cameraModel.h"
#include "tracefile_parser/frametimeParser.h"

class IpmTransformWorker : public QObject
{
    Q_OBJECT

public:
    explicit IpmTransformWorker(QObject *parent = nullptr) : QObject(parent) {}
    ~IpmTransformWorker() = default;

    IpmTransformWorker(const IpmParameterParser &ipm_para_parser);

    IpmTransformWorker(const IpmParameterParser &ipm_para_parser,
                       const std::string &ccd_dir,
                       const std::string &ipm_ret_dir,
                       const std::string &task_name);

    IpmTransformWorker(const IpmParameterParser &ipm_para_parser,
                       const std::string &ccd_dir,
                       const std::string &ipm_ret_dir,
                       const std::string &frametime_path,
                       const std::string &task_name);

    inline void set_ccd_dir(const std::string &ccd_dir) {
        _m_ccd_dir = ccd_dir;
    }

    inline void set_ipm_ret_dir(const std::string &ipm_ret_dir) {
        _m_ipm_ret_dir = ipm_ret_dir;
    }

    inline void set_task_name(const std::string &task_name) {
        _m_task_name = task_name;
    }

    inline void set_frametime_path(const std::string &frametime_path) {
        _m_frametime_path = frametime_path;
    }

    inline cv::Mat get_ipm_image() const {
        return _m_ipm_image;
    }

    inline QImage get_ipm_qimage() const {

        return QImage(_m_ipm_image.data, _m_ipm_image.cols, _m_ipm_image.rows,
                      static_cast<int>(_m_ipm_image.step), QImage::Format_RGB32);
    }

    inline uint get_worker_construct_stamp() const {
        return _m_worker_construct_time_stamp;
    }

private:

    typedef struct {
        std::string ccd_path;
        std::string ipm_ret_dir;
        bool is_dynamic;
        int ccd_pics_nums;
    } args;

    int _m_threads_nums = 4; // thread nums

    beec::ipm_model::AdaptiveIpmModel _m_ipm_model;

    beec::camera_model::CameraModel _m_cam;

    beec::tracefile_parser::FrametimeParser _m_frametime_parser;

    IpmParameterParser _m_ipm_para_parser;

    std::string _m_ccd_dir = "";
    std::string _m_ipm_ret_dir = "";
    std::string _m_task_name = "";
    std::string _m_frametime_path = "";

    bool _m_is_stopped = false;

    uint _m_worker_construct_time_stamp = 0;

    cv::Mat _m_ipm_image;

    void init_frametime_parser(const std::string &frametime_path);

    void process_single_image_within_multithread(const args &m_arg);

    void process_batch_image(const QVector<args> &m_args);

public slots:

    // 处理单张图像(使用静态相机姿态)
    void process_single_image();

    // 多线程处理多张图像(使用静态相机姿态)
    void process_batch_image_static();

    // 多线程处理多张图像(使用动态相机姿态)
    void process_batch_image_dynamic();

    // terminate batch process
    void terminate_batch_process() {
        _m_is_stopped = true;
    }

    inline bool is_distoration_remap_matrix_loded() {
        return _m_cam.is_distoration_remap_matrix_loded();
    }

signals:

    void progress_value_changed(int process_nums);

    void progress_range_changed(int min, int max);

    void is_process_finished(bool);

    void report_ipm_image();
};
