/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: mainWindow.h
* Date: 18-12-24 下午5:28
************************************************/

#pragma once

#include <string>
#include <vector>

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QFuture>
#include <QThread>
#include <QFutureWatcher>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>

#include "ipm_transform_worker/ipmtransformworker.h"
#include "camera_calibration/camerCalibrator.h"
#include "interface/ipmparameterparser.h"
#include "interface/ipmCamCalibParamParser.h"
#include "interface/ipmImageViewer.h"
#include "interface/qWaitDialog.h"

class QComboBox;
class QLineEdit;
class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

    QImage *_m_qimg;
    IpmImageViewer *_m_ipm_image_viewer;
    QWaitDialog *_m_qwait_dialog;

    // backend ipm generator work thread
    QThread *_m_batch_generate_ipm_process_thread;
    QThread *_m_single_generate_ipm_process_thread;

    // backend ipm camera calibration work thread
    QThread *_m_ipm_cam_calib_process_thread;

    // ipm transform worker
    IpmTransformWorker *_m_ipm_transform_worker;

    // ipm cam calibrator
    beec::camera_calibration::CamerCalibrator *_m_ipm_cam_calib_worker;

    // ipm generate para parser
    IpmParameterParser _m_ipm_para_parser;

    // ipm cam calib para parser
    IpmCamCalibParamParser _m_ipm_cam_calib_para_parser;

    // ipm transformed image
    cv::Mat _m_ipm_image;

    // ccd image path vectors
    std::vector<std::string> _m_image_paths;
    std::vector<std::string>::iterator _m_images_iter;

private:

    // setup ui and connections between singnals and slots
    void init_ui_para();
    void setup_signal_connections();

    // generate single ipm image process
    bool generate_single_ipm_check_paras();

    void generate_single_ipm();

    void generate_single_ipm_show();

    void generate_single_ipm_update_paras_parser(); // update ipm parser for generate single ipm image

    // generate batch ipm images process
    void generate_batch_ipms_static(const std::string &ccd_image_dir,
                                   const std::string &ipm_ret_dir,
                                   const std::string &task_name = "test_job");
    void generate_batch_ipms_dynamic(const std::string &ccd_image_dir,
                                    const std::string &ipm_ret_dir,
                                    const std::string &frametime_path,
                                    const std::string &task_name = "test_job");
    // Calibarate Camera process
    void ipm_cam_calib_update_paras_parser(); // update ipm calibration parser for calibrating camera

private slots:

    // Single Ipm image generate process
    void generate_single_ipm_calib_file_btn_clicked(); // select calib result file

    void generate_single_ipm_start_btn_clicked(); // generate single ipm image for adjusting the cam pos info

    void generate_single_ipm_ccd_image_path_btn_clicked(); // select the single ccd image path

    void generate_single_ipm_ccd_image_dir_btn_clicked(); // select the ccd image dir path for generate ipm images

    void generate_single_ipm_process_finished(bool m_is_finished=false); // generate single ipm image finished slot

    void generate_single_ipm_load_paras_btn_clicked(); // select paras for ipm generate

    void generate_single_ipm_save_para_btn_clicked(); // save ipm generation paras

    // Batch Ipm images generate process
    void generate_batch_ipms_ccd_image_dir_btn_clicked(); // select the ccd image dir path for batch process

    void generate_batch_ipms_result_image_dir_btn_clicked(); // select the ipm image result dir path

    void generate_batch_ipms_frametime_path_btn_clicked(); // select frame time path

    void generate_batch_ipms_process_btn_clicked(); // batch generate ipm images

    void generate_batch_ipms_cancle_btn_clicked(); // cancel batch generate ipm images

    void generate_batch_ipms_show_results(); // show ipm generate result during batch generating process

    void generate_batch_ipms_show_results_after_other_task(); // show ipm batch generate result after other task thread is finished

    void generate_batch_ipms_process_finished(bool m_is_finished=false); //

    // Calibarate Camera process
    void ipm_cam_calib_start_btn_clicked(); // start ipm cam calibration process

    void ipm_cam_calib_process_finished(bool m_is_finished=false); //

    void ipm_cam_calib_cancle_btn_clicked(); // cancel ipm camera calibration process

    void ipm_cam_calib_show_extract_corner_result_image(); // show extract corner result image

    void ipm_cam_calib_show_extract_corner_result_image_after_other_task(); // show extract corner result image after other task is finished

    void ipm_cam_calib_para_save_btn_clicked(); // ipm cam calib result save pushbotton clicked

    void ipm_cam_calib_show_process_error_msg(int); // show camera calib process error msgbox

    void ipm_cam_calib_distorate_image_btn_clicked(); // distorate image using calib result file

    void ipm_cam_calib_show_distoration_result_image(); // show image distoration result

    void ipm_cam_calib_show_wait_dialog_for_camera_intrinsics_calculation(bool); // shwo wait dialog while calculating camera intrinsics

    // Image view process
    void image_view_show_mouse_information_on_status_bar(); // show the coordinates of the mouse on the scene and the rgb info of the mouse location

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};
