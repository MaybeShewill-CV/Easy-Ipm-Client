#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <regex>

#include <QDir>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFileDialog>
#include <QMessageBox>

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

#include <common/file_system_utils/file_system_processor.h>
#include <ipm_transform_worker/ipmtransformworker.h>
#include <common/log_utils/beecLogger.h>

using beec::common::file_system_utils::FileSystemProcessor;
using beec::camera_calibration::CamerCalibrator;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_ui_para();

    setup_signal_connections();
}

MainWindow::~MainWindow()
{
    if (_m_batch_generate_ipm_process_thread->isRunning() ||
            !_m_batch_generate_ipm_process_thread->isFinished()) {
        _m_batch_generate_ipm_process_thread->quit();
        _m_batch_generate_ipm_process_thread->wait();
    }

    if (_m_single_generate_ipm_process_thread->isRunning() ||
            !_m_single_generate_ipm_process_thread->isFinished()) {
        _m_single_generate_ipm_process_thread->quit();
        _m_single_generate_ipm_process_thread->wait();
    }

    if (_m_ipm_cam_calib_process_thread->isRunning() ||
            !_m_ipm_cam_calib_process_thread->isFinished()) {
        _m_ipm_cam_calib_process_thread->quit();
        _m_ipm_cam_calib_process_thread->wait();
    }

    delete _m_qimg;
    delete _m_ipm_image_viewer;
    delete ui;

    delete _m_batch_generate_ipm_process_thread;
    delete _m_single_generate_ipm_process_thread;
    delete _m_ipm_cam_calib_process_thread;

    ui = nullptr;
    _m_qimg = nullptr;
    _m_ipm_image_viewer = nullptr;
    _m_batch_generate_ipm_process_thread = nullptr;
    _m_single_generate_ipm_process_thread = nullptr;
    _m_ipm_cam_calib_process_thread = nullptr;
}

void MainWindow::ipm_cam_calib_para_save_btn_clicked() {

    QString calib_save_file_path = QFileDialog::getSaveFileName(
                this,
                tr("Open Calibration result save path"),
                ".",
                tr("Yaml files (*.yml)"));

    if (calib_save_file_path.isNull()) {
        return;
    }

    if (calib_save_file_path != "") {
        ui->ipm_calib_paras_save_lineEdit->setText(calib_save_file_path);
    }

}

/****
 * Private Slots
 *
 */

/*
 * select calib file
 */
void MainWindow::generate_single_ipm_calib_file_btn_clicked() {

    QString calib_file_path = QFileDialog::getOpenFileName(
                this,
                tr("Open Calibration result file"),
                ".",
                tr("Yaml files (*.yml)"));

    if (calib_file_path.isNull()) {
        return;
    }

    if (calib_file_path != "") {
        ui->lineEdit->setText(calib_file_path);
    }
}

/*
 * generate single ipm
 */
void MainWindow::generate_single_ipm_start_btn_clicked() {

    // update ipm model paras
    generate_single_ipm_update_paras_parser();

    // check ipm model paras
    if (!generate_single_ipm_check_paras()) {
        return;
    }

    // generate single ipm image
    generate_single_ipm();
}

/*
 * select single ccd image path for adjusting the cam pos
 */
void MainWindow::generate_single_ipm_ccd_image_path_btn_clicked() {

    QString ccd_image_file_path = QFileDialog::getOpenFileName(
                this,
                tr("Open CCD Image File"),
                ".",
                tr("image files (*.jpg *.png *.bmp *.tif)"));

    if (ccd_image_file_path.isNull()) {
        return;
    }

    ui->ccd_img_path_line_edit->setText(ccd_image_file_path);

    // show ccd image
    _m_ipm_image_viewer->set_image(QImage(ccd_image_file_path));
    _m_ipm_image_viewer->fit_image();
}

void MainWindow::generate_single_ipm_ccd_image_dir_btn_clicked() {

    QString ccd_image_dir =  QFileDialog::getExistingDirectory(
                this, tr("Open CCD Image Directory"),
                ".",
                QFileDialog::ShowDirsOnly
                | QFileDialog::DontResolveSymlinks);

    if (ccd_image_dir.isNull()) {
        return;
    }

    if (ccd_image_dir != "") {
        ui->ccd_img_dir_path_line_edit->setText(ccd_image_dir);
    }

    if (!_m_image_paths.empty()) {
        _m_image_paths.clear();
        std::vector<std::string>().swap(_m_image_paths);

        _m_image_paths.reserve(static_cast<size_t>(FileSystemProcessor::get_directory_file_nums(
                                                       ccd_image_dir.toStdString(),
                                                       ".jpg",
                                                       FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES)) +
                               static_cast<size_t>(FileSystemProcessor::get_directory_file_nums(
                                                       ccd_image_dir.toStdString(),
                                                       ".png",
                                                       FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES)));
    }
    FileSystemProcessor::get_directory_files(ccd_image_dir.toStdString(),
                                             _m_image_paths,
                                             ".jpg",
                                             FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES);
    FileSystemProcessor::get_directory_files(ccd_image_dir.toStdString(),
                                             _m_image_paths,
                                             ".png",
                                             FileSystemProcessor::SEARCH_OPTION_T::ALLDIRECTORIES);

    // sort images if the images are stand ccd images or stand ipm images with file name of 'xxxx_xxxx.jpg' format.
    auto example_image_name = FileSystemProcessor::get_file_name(*(_m_image_paths.begin()));
    std::regex ccd_ipm_image_name_regex{R"(\d{5}(_)\d{5}.*)"};
    if (std::regex_match(example_image_name, ccd_ipm_image_name_regex)) {
        std::sort(_m_image_paths.begin(), _m_image_paths.end(),
                  [](const std::string &image_path_a,
                  const std::string &image_path_b) -> bool {

            auto image_name_a = FileSystemProcessor::get_file_name(image_path_a);
            auto image_name_b = FileSystemProcessor::get_file_name(image_path_b);

            auto image_a_id = boost::lexical_cast<int>(image_name_a.substr(
                                                           0, image_name_a.find_first_of('_')).c_str());
            auto image_b_id = boost::lexical_cast<int>(image_name_b.substr(
                                                           0, image_name_b.find_first_of('_')).c_str());

            return image_b_id > image_a_id;
        });
    }

    _m_images_iter = _m_image_paths.begin();

    _m_ipm_image_viewer->set_image(QImage(QString::fromStdString(*_m_images_iter)));
    _m_ipm_image_viewer->fit_image();
}

/*
 * select ccd image dir for batch processing
 */
void MainWindow::generate_batch_ipms_ccd_image_dir_btn_clicked() {

    QString ccd_image_dir =  QFileDialog::getExistingDirectory(
                this, tr("Open CCD Image Directory"),
                "~/",
                QFileDialog::ShowDirsOnly
                | QFileDialog::DontResolveSymlinks);

    if (ccd_image_dir.isNull()) {
        return;
    }

    if (ccd_image_dir != "") {
        ui->ccd_dir_lineEdit->setText(ccd_image_dir);
    }
}

/*
 * select the ipm result save dir
 */
void MainWindow::generate_batch_ipms_result_image_dir_btn_clicked() {

    QString ipm_ret_image_dir =  QFileDialog::getExistingDirectory(
                this, tr("Open Ipm Result Directory"),
                "~/",
                QFileDialog::ShowDirsOnly
                | QFileDialog::DontResolveSymlinks);

    if (ipm_ret_image_dir != "") {
        ui->ipm_dir_lineEdit->setText(ipm_ret_image_dir);
    }
}

/*
 * select frametime file path
 */
void MainWindow::generate_batch_ipms_frametime_path_btn_clicked() {

    QString frametime_file_path = QFileDialog::getOpenFileName(
                this,
                tr("Open Frametime File Path"),
                ".",
                tr("frametime files(*.frametime)"));

    if (frametime_file_path.isNull()) {
        return;
    }

    if (frametime_file_path != "") {
        ui->frame_path_lineEdit->setText(frametime_file_path);
    }
}

void MainWindow::generate_single_ipm_load_paras_btn_clicked() {

    QString ipm_generate_paras_file_path = QFileDialog::getOpenFileName(
                this,
                tr("Open Ipm Generate Paras File Path"),
                ".",
                tr("yaml files (*.yml)"));

    if (ipm_generate_paras_file_path.isNull()) {
        return;
    }

    if (!FileSystemProcessor::is_file_exist(ipm_generate_paras_file_path.toStdString())) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm generate parameters file path did not exist"));
        return;
    }

    cv::FileStorage ipm_generate_paras_file;
    ipm_generate_paras_file.open(ipm_generate_paras_file_path.toStdString(), cv::FileStorage::READ);

    if (!ipm_generate_paras_file.isOpened()) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm stitch parameters file path open failed"));
        return;
    }

    // judge para type
    std::string para_type;
    ipm_generate_paras_file["Parameters Type"] >> para_type;

    if (para_type != "Ipm Generate") {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm generate parameters file path is not a generate paras file"));
        return;
    }

    // read parameters
    std::string camera_name = "";
    std::string calib_file_path = "";
    double pitch = 0.0;
    double yaw = 0.0;
    cv::Size calib_img_size;
    cv::Size ipm_img_size;
    cv::Point2d vannish_point;

    ipm_generate_paras_file["camera name"] >> camera_name;
    ipm_generate_paras_file["calib file path"] >> calib_file_path;
    ipm_generate_paras_file["calib image size"] >> calib_img_size;
    ipm_generate_paras_file["camera pitch"] >> pitch;
    ipm_generate_paras_file["camera yaw"] >> yaw;
    ipm_generate_paras_file["vanish point"] >> vannish_point;
    ipm_generate_paras_file["vanish point"] >> vannish_point;
    ipm_generate_paras_file["ipm image size"] >> ipm_img_size;

    // update ipm generate panel
    ui->lineEdit->setText(QString::fromStdString(calib_file_path));
    ui->lineEdit_2->setText(QString::number(calib_img_size.width));
    ui->lineEdit_3->setText(QString::number(calib_img_size.height));
    ui->lineEdit_4->setText(QString::number(pitch));
    ui->lineEdit_10->setText(QString::number(yaw));
    ui->lineEdit_5->setText(QString::fromStdString(camera_name));
    ui->lineEdit_6->setText(QString::number(vannish_point.x));
    ui->lineEdit_7->setText(QString::number(vannish_point.y));
    ui->lineEdit_8->setText(QString::number(ipm_img_size.width));
    ui->lineEdit_9->setText(QString::number(ipm_img_size.height));

    ipm_generate_paras_file.release();

    LOG(INFO) << "Load ipm generate paras complete";

    QMessageBox::information(this, tr("Info Messagebox"),
                             tr("Ipm Generate Parameters are correctly loaded"));

    return;
}

/*
 * batch generate ipm images
 */
void MainWindow::generate_batch_ipms_process_btn_clicked() {

    // select if dynamically generating ipm image
    if (!ui->dynamic_radio_btn->isChecked() && !ui->static_radio_btn->isChecked()) {
        QMessageBox::warning(this, tr("Warning Message"), tr("Please select dynamic model or static model"));
        return;
    }

    auto is_dynamic = false;
    if (ui->dynamic_radio_btn->isChecked()) {
        is_dynamic = true;
    }

    if (is_dynamic) {
        ui->frametime_path_toolButton->setEnabled(true);
    } else {
        ui->frametime_path_toolButton->setEnabled(false);
    }

    auto ccd_image_dir = ui->ccd_dir_lineEdit->text().toStdString();
    auto ipm_ret_dir = ui->ipm_dir_lineEdit->text().toStdString();
    auto frametime_path = ui->frame_path_lineEdit->text().toStdString();

    if (!FileSystemProcessor::is_directory_exist(ccd_image_dir) ||
            !FileSystemProcessor::is_directory_exist(ipm_ret_dir)) {
        return;
    }

    if (is_dynamic) {
        // frametime file not exist
        if (!FileSystemProcessor::is_file_exist(frametime_path)) {
            QMessageBox::warning(this, tr("Warn Messagebox"), tr("Frametime file did not exist"));
            return;
        }
        generate_batch_ipms_dynamic(ccd_image_dir, ipm_ret_dir, frametime_path);
    } else {
        generate_batch_ipms_static(ccd_image_dir, ipm_ret_dir);
    }
}

void MainWindow::generate_batch_ipms_show_results() {

    *_m_qimg = _m_ipm_transform_worker->get_ipm_qimage().copy();

    if (_m_qimg->isNull()) {
        LOG(INFO) << "Ipm Generate Result Image is nullptr";
        return;
    }

    // status bar show infomation
    if (!ui->statusBar->currentMessage().isEmpty() || !ui->statusBar->currentMessage().isNull()) {
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage(tr("Batch Generating Ipm Images......"));
    } else {
        ui->statusBar->showMessage(tr("Batch Generating Ipm Images......"));
    }

    _m_ipm_image_viewer->set_image(*_m_qimg);
    _m_ipm_image_viewer->fit_image();

    return;
}

void MainWindow::generate_batch_ipms_show_results_after_other_task() {

    if (_m_batch_generate_ipm_process_thread->isRunning()) {
        connect(_m_ipm_transform_worker, SIGNAL(report_ipm_image()),
                this, SLOT(show_ipm_batch_generate_ret()));
    }
}

/*
 * cancel batch generate ipm images
 */
void MainWindow::generate_batch_ipms_cancle_btn_clicked() {

    if (_m_batch_generate_ipm_process_thread->isRunning()) {
        _m_ipm_transform_worker->terminate_batch_process();
        _m_batch_generate_ipm_process_thread->quit();
        _m_batch_generate_ipm_process_thread->wait();
        LOG(INFO) << "Batch Generate Ipm Process Thread has been terminated";
    } else {
        LOG(INFO) << "Batch Generate Ipm Process Thread has already been dead";
    }
}

void MainWindow::generate_batch_ipms_process_finished(bool m_is_finished) {

    if (m_is_finished && _m_batch_generate_ipm_process_thread->isRunning()) {

        // messagebox remind user the process is finished
        QMessageBox::information(this, tr("Info Messagebox"),
                                 tr("Batch Generating Ipm Process finished"));

        // release resource and quit thread
        _m_batch_generate_ipm_process_thread->quit();
        _m_batch_generate_ipm_process_thread->wait();

        if (_m_batch_generate_ipm_process_thread->isFinished()) {
            LOG(INFO) << "Batch Generate Ipm Process Thread is finished";

            if (!ui->statusBar->currentMessage().isEmpty() ||
                    !ui->statusBar->currentMessage().isNull()) {
                ui->statusBar->showMessage("Batch Generating Ipm Images Finished");
            } else {
                ui->statusBar->showMessage("Batch Generating Ipm Images Finished");
            }
        } else {
            LOG(INFO) << "Batch Generate Ipm Process Thread is not finished";

            if (!ui->statusBar->currentMessage().isEmpty() ||
                    !ui->statusBar->currentMessage().isNull()) {
                ui->statusBar->showMessage("Batch Generating Ipm Images Not Finished");
            } else {
                ui->statusBar->showMessage("Batch Generating Ipm Images Not Finished");
            }
        }
    } else {
        LOG(INFO) << "Batch Generate Ipm Process Thread has been finished";

        if (!ui->statusBar->currentMessage().isEmpty() ||
                !ui->statusBar->currentMessage().isNull()) {
            ui->statusBar->showMessage("Batch Generating Ipm Images Have Been Finished");
        } else {
            ui->statusBar->showMessage("Batch Generating Ipm Images Have Been Finished");
        }
    }
}

void MainWindow::generate_single_ipm_process_finished(bool m_is_finished) {

    // once the single ipm image is generated then show it
    _m_ipm_transform_worker->get_ipm_image().copyTo(_m_ipm_image);
    generate_single_ipm_show();

    if (m_is_finished && _m_single_generate_ipm_process_thread->isRunning()) {
        _m_single_generate_ipm_process_thread->quit();
        _m_single_generate_ipm_process_thread->wait();
        if (_m_single_generate_ipm_process_thread->isFinished()) {
            LOG(INFO) << "Single Generate Ipm Process Thread is finished";
        } else {
            LOG(INFO) << "Single Generate Ipm Process Thread is not finished";
        }
    } else {
        LOG(INFO) << "Single Generate Ipm Process Thread has been finished";
    }
}

void MainWindow::generate_single_ipm_save_para_btn_clicked() {

    generate_single_ipm_update_paras_parser();

    QString ipm_para_file_path = QFileDialog::getSaveFileName(
                   this,
                   tr("Save IPM Parameters File Path"),
                   ".",
                   tr("yaml files (*.yml)"));

    if (ipm_para_file_path.isNull()) {
        return;
    }

    if (ipm_para_file_path.toStdString().empty() ||
        !FileSystemProcessor::is_file_end_with(ipm_para_file_path.toStdString(), ".yml") ||
        FileSystemProcessor::is_directory(ipm_para_file_path.toStdString())) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Wrong Ipm Generate Parameters Yml file path, Please Check Again!!"));
        return;
    }

    cv::FileStorage para_save_file;
    para_save_file.open(ipm_para_file_path.toStdString(), cv::FileStorage::WRITE);

    auto calib_file_path = _m_ipm_para_parser.get_calib_file_path().toStdString();
    auto calib_ret_img_width = _m_ipm_para_parser.get_calib_image_width();
    auto calib_ret_img_height = _m_ipm_para_parser.get_calib_image_height();
    auto camera_pitch = _m_ipm_para_parser.get_camera_pitch();
    auto camera_yaw = _m_ipm_para_parser.get_camera_yaw();
    auto camera_name = _m_ipm_para_parser.get_camera_name().toStdString();
    auto vp_point_x = _m_ipm_para_parser.get_vp_point_x();
    auto vp_point_y = _m_ipm_para_parser.get_vp_point_y();
    auto ipm_img_width = _m_ipm_para_parser.get_ipm_image_width();
    auto ipm_img_height = _m_ipm_para_parser.get_ipm_image_height();

    para_save_file << "Parameters Type" << "Ipm Generate";

    para_save_file << "camera name" << camera_name;
    para_save_file << "calib file path" << calib_file_path;
    para_save_file << "calib image size" << cv::Size(calib_ret_img_width, calib_ret_img_height);
    para_save_file << "camera pitch" << camera_pitch;
    para_save_file << "camera yaw" << camera_yaw;
    para_save_file << "vanish point" << cv::Point2d(vp_point_x, vp_point_y);
    para_save_file << "ipm image size" << cv::Size(ipm_img_width, ipm_img_height);

    para_save_file.release();

    LOG(INFO) << "Ipm generating para has been saved to " << ipm_para_file_path.toStdString();

    QMessageBox::information(this, tr("Info Messagebox"),
                             tr("Ipm Generating Parameters has been saved"));
}

void MainWindow::ipm_cam_calib_start_btn_clicked() {

    // if the thread is working return
    if (_m_ipm_cam_calib_process_thread->isRunning()) {
        LOG(INFO) << "Ipm Camera Calibration Process Thread is running";
        return;
    }

    // update ipm cam calib paras parser
    ipm_cam_calib_update_paras_parser();

    if (_m_ipm_cam_calib_para_parser.get_calib_image_size().width == 0 ||
            _m_ipm_cam_calib_para_parser.get_calib_image_size().height == 0 ||
            _m_ipm_cam_calib_para_parser.get_calib_board_size().width == 0 ||
            _m_ipm_cam_calib_para_parser.get_calib_board_size().height == 0 ||
            _m_ipm_cam_calib_para_parser.get_calib_square_size().width == 0 ||
            _m_ipm_cam_calib_para_parser.get_calib_square_size().height == 0) {
        QMessageBox::warning(this, tr("Warning Messagebox"),
                                     tr("Wrong Ipm Camera Calibration Paras, Please check again"));
        return;
    }

    // reset progress bar
    ui->ipm_calib_vis_result_progressBar->setValue(0);
    ui->ipm_calib_extract_corners_progressBar->setValue(0);
    ui->ipm_calib_evaluate_result_progressBar->setValue(0);

    // get the calib image dir
    auto calib_image_dir = QFileDialog::getExistingDirectory(
                this, tr("Calib Image File Dir"), "~/",
                QFileDialog::ShowDirsOnly
                | QFileDialog::DontResolveSymlinks);

    if (calib_image_dir.isNull()) {
        return;
    }

    // update the ipm cam calib worker
    _m_ipm_cam_calib_worker = new CamerCalibrator(_m_ipm_cam_calib_para_parser);
    _m_ipm_cam_calib_worker->set_calib_image_dir(calib_image_dir.toStdString());

    _m_ipm_cam_calib_worker->moveToThread(_m_ipm_cam_calib_process_thread);

    // work thread signal slots connections
    connect(_m_ipm_cam_calib_process_thread, SIGNAL(finished()),
            _m_ipm_cam_calib_worker, SLOT(deleteLater()));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_extract_corners_progress(int)),
            ui->ipm_calib_extract_corners_progressBar, SLOT(setValue(int)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_evaluate_calib_result_progress(int)),
            ui->ipm_calib_evaluate_result_progressBar, SLOT(setValue(int)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_vis_calib_result_progress(int)),
            ui->ipm_calib_vis_result_progressBar, SLOT(setValue(int)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_is_calib_process_finished(bool)),
            this, SLOT(ipm_cam_calib_process_finished(bool)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_is_calib_process_finished(bool)),
            ui->ipm_calib_start_pushButton, SLOT(setEnabled(bool)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_calib_process_error_code(int)),
            this, SLOT(ipm_cam_calib_show_process_error_msg(int)));

    if (_m_batch_generate_ipm_process_thread->isRunning()) {
        connect(_m_batch_generate_ipm_process_thread, SIGNAL(finished()),
                this, SLOT(ipm_cam_calib_show_extract_corner_result_image_after_other_task()));
    } else {
        connect(_m_ipm_cam_calib_worker, SIGNAL(report_extract_corners_image()),
                this, SLOT(ipm_cam_calib_show_extract_corner_result_image()));
    }

    if (ui->ipm_calib_plain_cam_radioButton->isChecked() && !ui->ipm_calib_fisheye_cam_radioButton->isChecked()) {
        connect(_m_ipm_cam_calib_process_thread, SIGNAL(started()),
                _m_ipm_cam_calib_worker, SLOT(calibrate_camera()));
    } else if (!ui->ipm_calib_plain_cam_radioButton->isChecked() && ui->ipm_calib_fisheye_cam_radioButton->isChecked()) {
        connect(_m_ipm_cam_calib_process_thread, SIGNAL(started()),
                _m_ipm_cam_calib_worker, SLOT(calibrate_fisheye_camera()));
    } else {
        QMessageBox::warning(this, tr("Warning Messagebox"),
                                     tr("You can either select plain cam or fisheye "
                                        "cam but do not select them both or select none of them"));
        return;
    }

    _m_ipm_cam_calib_process_thread->start();
}

void MainWindow::ipm_cam_calib_process_finished(bool is_finished) {

    if (is_finished && _m_ipm_cam_calib_process_thread->isRunning()) {

        // release resource and quit the thread
        _m_ipm_cam_calib_process_thread->quit();
        _m_ipm_cam_calib_process_thread->wait();
        if (_m_ipm_cam_calib_process_thread->isFinished()) {
            LOG(INFO) << "Ipm Camera Calibration Process Thread is finished";

            if (!ui->statusBar->currentMessage().isEmpty() ||
                    !ui->statusBar->currentMessage().isNull()) {
                ui->statusBar->showMessage("Calibrating Ipm Camera Finished");
            } else {
                ui->statusBar->showMessage("Calibrating Ipm Camera Finished");
            }
        } else {
            LOG(INFO) << "Ipm Camera Calibration Process Thread is not finished";

            if (!ui->statusBar->currentMessage().isEmpty() ||
                    !ui->statusBar->currentMessage().isNull()) {
                ui->statusBar->showMessage("Calibrating Ipm Camera Not Finished");
            } else {
                ui->statusBar->showMessage("Calibrating Ipm Camera Not Finished");
            }
        }
    } else {
        LOG(INFO) << "Ipm Camera Calibration Process Thread has been finished";

        if (!ui->statusBar->currentMessage().isEmpty() ||
                !ui->statusBar->currentMessage().isNull()) {
            ui->statusBar->showMessage("Calibrating Ipm Camera Have Been Finished");
        } else {
            ui->statusBar->showMessage("Calibrating Ipm Camera Have Been Finished");
        }
    }
}

void MainWindow::ipm_cam_calib_cancle_btn_clicked() {

    if (_m_ipm_cam_calib_process_thread->isRunning()) {
        _m_ipm_cam_calib_worker->terminate_calibration_process();
        // delay 1 sec for the worker to stop current work
        QTime die_time = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < die_time)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        _m_ipm_cam_calib_process_thread->quit();
        _m_ipm_cam_calib_process_thread->wait();
        LOG(INFO) << "Ipm Camera Calibration Process Thread has been terminated";
    } else {
        LOG(INFO) << "Ipm Camera Calibration Process Thread has already been dead";
    }
}

void MainWindow::ipm_cam_calib_show_extract_corner_result_image() {

    cv::Mat extract_corner_image = _m_ipm_cam_calib_worker->get_extract_corner_result_image();

    if (extract_corner_image.empty() || !extract_corner_image.data) {
        QMessageBox::warning(this, tr("Warn Messagebox"), tr("Extract corner result image is empty"));
        return;
    }

    // status bar show information
    if (!ui->statusBar->currentMessage().isEmpty() || !ui->statusBar->currentMessage().isNull()) {
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage(tr("Calibrating Ipm Camera......"));
    } else {
        ui->statusBar->showMessage(tr("Calibrating Ipm Camera......"));
    }

    if (extract_corner_image.channels() == 4) {
        cv::cvtColor(extract_corner_image, extract_corner_image, cv::COLOR_BGRA2RGBA);
        *_m_qimg = QImage(static_cast<uchar*>(extract_corner_image.data), extract_corner_image.cols, extract_corner_image.rows,
                     extract_corner_image.cols * extract_corner_image.channels(), QImage::Format_RGBA8888);
    } else {
        cv::cvtColor(extract_corner_image, extract_corner_image, cv::COLOR_BGR2RGB);
        *_m_qimg = QImage(static_cast<uchar*>(extract_corner_image.data), extract_corner_image.cols, extract_corner_image.rows,
                     extract_corner_image.cols * extract_corner_image.channels(), QImage::Format_RGB888);
    }

    _m_ipm_image_viewer->set_image(*_m_qimg);
    _m_ipm_image_viewer->fit_image();
}

void MainWindow::ipm_cam_calib_show_extract_corner_result_image_after_other_task() {

    if (_m_ipm_cam_calib_process_thread->isRunning()) {
        connect(_m_ipm_cam_calib_worker, SIGNAL(report_extract_corners_image()),
                this, SLOT(show_cam_calib_extract_corner_result_image()));
    }
}

void MainWindow::ipm_cam_calib_show_process_error_msg(int error_code) {

    if (error_code == -1) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm camera calibration extract corners falied"));
    }

    if (error_code == -2) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm camera calibration calibrate inner paras falied"));
    }

    if (error_code == -3) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm camera calibration evaluate camera paras falied"));
    }

    if (error_code == -4) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm camera calibration visualize calib results falied"));
    }

    if (error_code == -5) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm camera calibration results save falied"));
    }

    if (error_code == 5) {
        QMessageBox::information(this, tr("Information Messagebox"),
                             tr("Ipm camera calibration results save success"));
    }

    if (error_code == -6) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm camera calibration result file can not open"));
    }

    if (error_code == -7) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("This paras file is not a camera calibration paras file"));
    }

    if (error_code == -8) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Source ccd image for calibrating is empty or invalid"));
    }
}

void MainWindow::ipm_cam_calib_distorate_image_btn_clicked() {

    // if the thread is working return
    if (_m_ipm_cam_calib_process_thread->isRunning() ||
            _m_batch_generate_ipm_process_thread->isRunning()) {

        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Please wait for other task to finish"));
        LOG(INFO) << "Wait for other task to finish";
        return;
    }

    // obtain the ccd image path and calib result file path
    auto src_image_path = QFileDialog::getOpenFileName(
                this,
                tr("Open Source CCD Image Path"),
                ".",
                tr("jpg files (*.jpg)"));

    if (src_image_path.isNull()) {
        return;
    }

    auto calib_file_path = QFileDialog::getOpenFileName(
                this,
                tr("Open Camera Calib File Path"),
                ".",
                tr("yml files (*.yml)"));

    if (calib_file_path.isNull()) {
        return;
    }

    // read source ccd image
    cv::Mat src_ccd_image = cv::imread(src_image_path.toStdString(), cv::IMREAD_UNCHANGED);

    // update the ipm cam calib worker
    _m_ipm_cam_calib_worker = new CamerCalibrator(calib_file_path);
    _m_ipm_cam_calib_worker->set_calib_source_image(src_ccd_image);

    _m_ipm_cam_calib_worker->moveToThread(_m_ipm_cam_calib_process_thread);

    // work thread signal slots connections
    connect(_m_ipm_cam_calib_process_thread, SIGNAL(finished()),
            _m_ipm_cam_calib_worker, SLOT(deleteLater()));
    connect(_m_ipm_cam_calib_process_thread, SIGNAL(started()),
            _m_ipm_cam_calib_worker, SLOT(distorate_plain_image()));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_calib_result_image()),
            this, SLOT(ipm_cam_calib_show_distoration_result_image()));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_is_calib_process_finished(bool)),
            this, SLOT(ipm_cam_calib_process_finished(bool)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_is_calib_process_finished(bool)),
            ui->ipm_calib_start_pushButton, SLOT(setEnabled(bool)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_is_calib_process_finished(bool)),
            ui->ipm_calib_distorate_image_pushButton, SLOT(setEnabled(bool)));
    connect(_m_ipm_cam_calib_worker, SIGNAL(report_calib_process_error_code(int)),
            this, SLOT(ipm_cam_calib_show_process_error_msg(int)));

    _m_ipm_cam_calib_process_thread->start();
}

void MainWindow::ipm_cam_calib_show_distoration_result_image() {

    cv::Mat calib_result_image = _m_ipm_cam_calib_worker->get_calib_result_image();
    cv::Mat calib_source_image = _m_ipm_cam_calib_worker->get_calib_source_image();

    if (calib_result_image.empty() || !calib_result_image.data) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Calibration result image is empty"));
        return;
    }

    // status bar show information
    if (!ui->statusBar->currentMessage().isEmpty() || !ui->statusBar->currentMessage().isNull()) {
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage(tr("Showing Calibration Result"));
    } else {
        ui->statusBar->showMessage(tr("Showing Calibration Result"));
    }

    if (calib_result_image.channels() == 4) {
        cv::cvtColor(calib_result_image, calib_result_image, cv::COLOR_BGRA2RGBA);
        *_m_qimg = QImage(static_cast<uchar*>(calib_result_image.data), calib_result_image.cols,
                          calib_result_image.rows, calib_result_image.cols * calib_result_image.channels(),
                          QImage::Format_RGBA8888);
    } else {
        cv::cvtColor(calib_result_image, calib_result_image, cv::COLOR_BGR2RGB);
        *_m_qimg = QImage(static_cast<uchar*>(calib_result_image.data), calib_result_image.cols,
                          calib_result_image.rows, calib_result_image.cols * calib_result_image.channels(),
                          QImage::Format_RGB888);
    }

    _m_ipm_image_viewer->set_image(*_m_qimg);
    _m_ipm_image_viewer->fit_image();
}

void MainWindow::image_view_show_mouse_information_on_status_bar() {

    QString mouse_scene_coordinates_info = QString("x, y: (%1, %2) && r, g, b: (%3, %4, %5)").arg(
                QString::number(_m_ipm_image_viewer->get_mouse_coordinates().x()),
                QString::number(_m_ipm_image_viewer->get_mouse_coordinates().y()),
                QString::number(_m_ipm_image_viewer->get_mouse_location_qcolor().red()),
                QString::number(_m_ipm_image_viewer->get_mouse_location_qcolor().green()),
                QString::number(_m_ipm_image_viewer->get_mouse_location_qcolor().blue()));

    if (!ui->statusBar->currentMessage().isEmpty() ||
            !ui->statusBar->currentMessage().isNull()) {
        ui->statusBar->showMessage(mouse_scene_coordinates_info);
    } else {
        ui->statusBar->showMessage(mouse_scene_coordinates_info);
    }
}

/****
 * Private Functions
 *
 */

void MainWindow::generate_single_ipm_update_paras_parser() {

   auto calib_file_path = ui->lineEdit->text();
   auto calib_image_width = ui->lineEdit_2->text().toInt();
   auto calib_image_height = ui->lineEdit_3->text().toInt();
   auto cam_pitch = ui->lineEdit_4->text().toDouble();
   auto cam_yaw = ui->lineEdit_10->text().toDouble();
   auto cam_name = ui->lineEdit_5->text();
   auto vp_pt_x = ui->lineEdit_6->text().toDouble();
   auto vp_pt_y = ui->lineEdit_7->text().toDouble();
   auto ipm_image_size_width = ui->lineEdit_8->text().toInt();
   auto ipm_image_size_height = ui->lineEdit_9->text().toInt();
   auto ipm_image_path = ui->ccd_img_path_line_edit->text();

   _m_ipm_para_parser.set_vp_point_x(vp_pt_x);
   _m_ipm_para_parser.set_vp_point_y(vp_pt_y);
   _m_ipm_para_parser.set_camera_name(cam_name);
   _m_ipm_para_parser.set_camera_pitch(cam_pitch);
   _m_ipm_para_parser.set_camera_yaw(cam_yaw);
   _m_ipm_para_parser.set_calib_file_path(calib_file_path);
   _m_ipm_para_parser.set_calib_image_width(calib_image_width);
   _m_ipm_para_parser.set_calib_image_height(calib_image_height);
   _m_ipm_para_parser.set_ipm_image_width(ipm_image_size_width);
   _m_ipm_para_parser.set_ipm_image_height(ipm_image_size_height);
   _m_ipm_para_parser.set_ccd_path(ipm_image_path);
}

void MainWindow::ipm_cam_calib_update_paras_parser() {

    auto calib_image_width = ui->ipm_calib_image_width_lineEdit->text().toInt();
    auto calib_image_height = ui->ipm_calib_image_height_lineEdit->text().toInt();
    auto board_width = ui->ipm_calib_board_width_lineEdit->text().toInt();
    auto board_height = ui->ipm_calib_board_height_lineEdit->text().toInt();
    auto square_width = ui->ipm_calib_square_width_lineEdit->text().toInt();
    auto square_height = ui->ipm_calib_square_height_lineEdit->text().toInt();
    auto calib_paras_save_path = ui->ipm_calib_paras_save_lineEdit->text().toStdString();

    cv::Size calib_image_size(calib_image_width, calib_image_height);
    cv::Size calib_board_size(board_width, board_height);
    cv::Size calib_square_size(square_width, square_height);

    _m_ipm_cam_calib_para_parser.set_calib_image_size(calib_image_size);
    _m_ipm_cam_calib_para_parser.set_calib_board_size(calib_board_size);
    _m_ipm_cam_calib_para_parser.set_calib_square_size(calib_square_size);
    _m_ipm_cam_calib_para_parser.set_calib_para_save_path(calib_paras_save_path);
}

void MainWindow::init_ui_para() {

    _m_qimg = new QImage();
    _m_ipm_image_viewer = new IpmImageViewer(true, this);

    _m_batch_generate_ipm_process_thread = new QThread();
    _m_single_generate_ipm_process_thread = new QThread();

    _m_ipm_cam_calib_process_thread = new QThread();

    _m_ipm_transform_worker = new IpmTransformWorker();

    _m_ipm_cam_calib_worker = new CamerCalibrator();

    ui->static_radio_btn->setEnabled(true);
    ui->dynamic_radio_btn->setEnabled(false);

    ui->batch_process_ipm_progressBar->setOrientation(Qt::Horizontal);
    ui->batch_process_ipm_progressBar->setValue(0);
    ui->batch_process_ipm_progressBar->setMinimum(0);
    ui->batch_process_ipm_progressBar->setMaximum(100);
    ui->frametime_path_toolButton->setEnabled(false);

    ui->ipm_stitch_stack_progressBar->setOrientation(Qt::Horizontal);
    ui->ipm_stitch_stack_progressBar->setValue(0);
    ui->ipm_stitch_stack_progressBar->setMinimum(0);
    ui->ipm_stitch_stack_progressBar->setMaximum(100);

    ui->ipm_stitch_render_progressBar->setOrientation(Qt::Horizontal);
    ui->ipm_stitch_render_progressBar->setValue(0);
    ui->ipm_stitch_render_progressBar->setMinimum(0);
    ui->ipm_stitch_render_progressBar->setMaximum(100);

    ui->ipm_calib_vis_result_progressBar->setOrientation(Qt::Horizontal);
    ui->ipm_calib_vis_result_progressBar->setValue(0);
    ui->ipm_calib_vis_result_progressBar->setMinimum(0);
    ui->ipm_calib_vis_result_progressBar->setMaximum(100);

    ui->ipm_calib_extract_corners_progressBar->setOrientation(Qt::Horizontal);
    ui->ipm_calib_extract_corners_progressBar->setValue(0);
    ui->ipm_calib_extract_corners_progressBar->setMinimum(0);
    ui->ipm_calib_extract_corners_progressBar->setMaximum(100);

    ui->ipm_calib_evaluate_result_progressBar->setOrientation(Qt::Horizontal);
    ui->ipm_calib_evaluate_result_progressBar->setValue(0);
    ui->ipm_calib_evaluate_result_progressBar->setMinimum(0);
    ui->ipm_calib_evaluate_result_progressBar->setMaximum(100);

    ui->ipm_calib_board_width_lineEdit->setText("8");
    ui->ipm_calib_board_height_lineEdit->setText("6");
    ui->ipm_calib_square_width_lineEdit->setText("10");
    ui->ipm_calib_square_height_lineEdit->setText("10");
    ui->ipm_calib_image_width_lineEdit->setText("4096");
    ui->ipm_calib_image_height_lineEdit->setText("2160");

    _m_ipm_image_viewer->setGeometry(321, 1, 691, 811);
    _m_ipm_image_viewer->setBackgroundBrush(QBrush(QColor(227, 237, 205)));
}

void MainWindow::setup_signal_connections() {

    // ui signals slots connections

    // ---- generate single ipm image process
    connect(ui->toolButton, SIGNAL(clicked()),
            this, SLOT(generate_single_ipm_calib_file_btn_clicked()));
    connect(ui->generate_ipm_btn, SIGNAL(clicked()),
            this, SLOT(generate_single_ipm_start_btn_clicked()));
    connect(ui->load_ccd_img_btn, SIGNAL(clicked()),
            this, SLOT(generate_single_ipm_ccd_image_path_btn_clicked()));
    connect(ui->generate_load_ipm_ccd_dir_pushButton, SIGNAL(clicked()),
            this, SLOT(generate_single_ipm_ccd_image_dir_btn_clicked()));
    connect(ui->load_generate_ipm_para_pushButton, SIGNAL(clicked()),
            this, SLOT(generate_single_ipm_load_paras_btn_clicked()));
    connect(ui->save_ipm_para_btn, SIGNAL(clicked()),
            this, SLOT(generate_single_ipm_save_para_btn_clicked()));

    // ---- generate batch ipms image process
    connect(ui->ccd_dir_toolButton, SIGNAL(clicked()),
            this, SLOT(generate_batch_ipms_ccd_image_dir_btn_clicked()));
    connect(ui->ipm_ret_dir_toolButton, SIGNAL(clicked()),
            this, SLOT(generate_batch_ipms_result_image_dir_btn_clicked()));
    connect(ui->frametime_path_toolButton, SIGNAL(clicked()),
            this, SLOT(generate_batch_ipms_frametime_path_btn_clicked()));
    connect(ui->batch_generate_ipm_pushButton, SIGNAL(clicked()),
            this, SLOT(generate_batch_ipms_process_btn_clicked()));
    connect(ui->cancel_generate_ipm_pushButton, SIGNAL(clicked()),
            this, SLOT(generate_batch_ipms_cancle_btn_clicked()));

    // ---- calibrate camera process
    connect(ui->ipm_calib_start_pushButton, SIGNAL(clicked()),
            this, SLOT(ipm_cam_calib_start_btn_clicked()));
    connect(ui->ipm_calib_cancel_pushButton, SIGNAL(clicked()),
            this, SLOT(ipm_cam_calib_cancle_btn_clicked()));
    connect(ui->ipm_calib_paras_save_path_toolButton, SIGNAL(clicked()),
            this, SLOT(ipm_cam_calib_para_save_btn_clicked()));
    connect(ui->ipm_calib_distorate_image_pushButton, SIGNAL(clicked()),
            this, SLOT(ipm_cam_calib_distorate_image_btn_clicked()));

    // ---- image view process
    connect(_m_ipm_image_viewer, SIGNAL(report_mouse_scene_information()),
            this, SLOT(image_view_show_mouse_information_on_status_bar()));
}

void MainWindow::generate_single_ipm_show() {

    cv::Mat rgba;

    if (_m_ipm_image.empty() || !_m_ipm_image.data) {
        QMessageBox::warning(this, tr("Warn Messagebox"), tr("Ipm image did not generate correctly"));
        return;
    }

    if (_m_ipm_image.channels() == 4) {
        cv::cvtColor(_m_ipm_image, rgba, cv::COLOR_BGRA2RGBA);
        *_m_qimg = QImage(static_cast<uchar*>(rgba.data), rgba.cols, rgba.rows,
                     rgba.cols * rgba.channels(), QImage::Format_RGBA8888);
    } else {
        cv::cvtColor(_m_ipm_image, rgba, cv::COLOR_BGR2RGB);
        *_m_qimg = QImage(static_cast<uchar*>(rgba.data), rgba.cols, rgba.rows,
                     rgba.cols * rgba.channels(), QImage::Format_RGB888);
    }

    _m_ipm_image_viewer->set_image(*_m_qimg);
    _m_ipm_image_viewer->fit_image();
}

void MainWindow::generate_batch_ipms_dynamic(
        const std::string &ccd_image_dir,
        const std::string &ipm_ret_dir,
        const std::string &frametime_path,
        const std::string &task_name) {

    if (_m_batch_generate_ipm_process_thread->isRunning()) {
        LOG(INFO) << "Batch Generate Ipm Process Thread is running";
        return;
    }

    generate_single_ipm_update_paras_parser();

    _m_ipm_transform_worker = new IpmTransformWorker(_m_ipm_para_parser, ccd_image_dir,
                                                 ipm_ret_dir, frametime_path, task_name);

    if (!_m_ipm_transform_worker->is_distoration_remap_matrix_loded()) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Camera Calibration parameters may not be loaded correctly, please check again"));
        LOG(INFO) << "Camera Calibration parameters may not be loaded correctly, please check again";
        return;
    }

    _m_ipm_transform_worker->moveToThread(_m_batch_generate_ipm_process_thread);

    // work thread signal slots connections
    connect(_m_batch_generate_ipm_process_thread, SIGNAL(finished()),
            _m_ipm_transform_worker, SLOT(deleteLater()));
    connect(_m_batch_generate_ipm_process_thread, SIGNAL(started()),
            _m_ipm_transform_worker, SLOT(process_batch_image_dynamic()));
    connect(_m_ipm_transform_worker, SIGNAL(progress_value_changed(int)),
            ui->batch_process_ipm_progressBar, SLOT(setValue(int)));
    connect(_m_ipm_transform_worker, SIGNAL(progress_range_changed(int, int)),
            ui->batch_process_ipm_progressBar, SLOT(setRange(int, int)));
    connect(_m_ipm_transform_worker, SIGNAL(is_process_finished(bool)),
            this, SLOT(generate_batch_ipms_process_finished(bool)));
    connect(_m_ipm_transform_worker, SIGNAL(is_process_finished(bool)),
            ui->batch_generate_ipm_pushButton, SLOT(setEnabled(bool)));

    if (_m_ipm_cam_calib_process_thread->isRunning()) {
        connect(_m_ipm_cam_calib_process_thread, SIGNAL(finished()),
                this, SLOT(generate_batch_ipms_show_results_after_other_task()));
    } else {
        connect(_m_ipm_transform_worker, SIGNAL(report_ipm_image()),
                this, SLOT(generate_batch_ipms_show_results()));
    }

    _m_batch_generate_ipm_process_thread->start();
}

void MainWindow::generate_batch_ipms_static(
        const std::string &ccd_image_dir,
        const std::string &ipm_ret_dir,
        const std::string &task_name) {

    if (_m_batch_generate_ipm_process_thread->isRunning()) {
        LOG(INFO) << "Batch Generate Ipm Process Thread is running";
        return;
    }

    generate_single_ipm_update_paras_parser();

    _m_ipm_transform_worker = new IpmTransformWorker(_m_ipm_para_parser, ccd_image_dir, ipm_ret_dir, task_name);

    if (!_m_ipm_transform_worker->is_distoration_remap_matrix_loded()) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Camera Calibration parameters may not be loaded correctly, please check again"));
        LOG(INFO) << "Camera Calibration parameters may not be loaded correctly, please check again";
        return;
    }

    _m_ipm_transform_worker->moveToThread(_m_batch_generate_ipm_process_thread);

    // work thread signal slots connections
    connect(_m_batch_generate_ipm_process_thread, SIGNAL(finished()),
            _m_ipm_transform_worker, SLOT(deleteLater()));
    connect(_m_batch_generate_ipm_process_thread, SIGNAL(started()),
            _m_ipm_transform_worker, SLOT(process_batch_image_static()));
    connect(_m_ipm_transform_worker, SIGNAL(progress_value_changed(int)),
            ui->batch_process_ipm_progressBar, SLOT(setValue(int)));
    connect(_m_ipm_transform_worker, SIGNAL(progress_range_changed(int, int)),
            ui->batch_process_ipm_progressBar, SLOT(setRange(int, int)));
    connect(_m_ipm_transform_worker, SIGNAL(is_process_finished(bool)),
            this, SLOT(generate_batch_ipms_process_finished(bool)));
    connect(_m_ipm_transform_worker, SIGNAL(is_process_finished(bool)),
            ui->batch_generate_ipm_pushButton, SLOT(setEnabled(bool)));

    if (_m_ipm_cam_calib_process_thread->isRunning()) {
        connect(_m_ipm_cam_calib_process_thread, SIGNAL(finished()),
                this, SLOT(generate_batch_ipms_show_results_after_other_task()));
    } else {
        connect(_m_ipm_transform_worker, SIGNAL(report_ipm_image()),
                this, SLOT(generate_batch_ipms_show_results()));
    }

    _m_batch_generate_ipm_process_thread->start();
}

void MainWindow::generate_single_ipm() {

    if (_m_single_generate_ipm_process_thread->isRunning()) {
        LOG(INFO) << "Single Generate Ipm Process Thread is running";
        return;
    }

    _m_ipm_transform_worker = new IpmTransformWorker(_m_ipm_para_parser);
    _m_ipm_transform_worker->moveToThread(_m_single_generate_ipm_process_thread);

    // work thread signal slots connections
    connect(_m_single_generate_ipm_process_thread, SIGNAL(finished()),
            _m_ipm_transform_worker, SLOT(deleteLater()));
    connect(_m_single_generate_ipm_process_thread, SIGNAL(started()),
            _m_ipm_transform_worker, SLOT(process_single_image()));
    connect(_m_ipm_transform_worker, SIGNAL(is_process_finished(bool)),
            this, SLOT(generate_single_ipm_process_finished(bool)));

    _m_single_generate_ipm_process_thread->start();
}

bool MainWindow::generate_single_ipm_check_paras() {

    auto calib_file_path = _m_ipm_para_parser.get_calib_file_path();
    auto calib_image_width = _m_ipm_para_parser.get_calib_image_width();
    auto calib_image_height = _m_ipm_para_parser.get_calib_image_height();
    auto vp_pt_x = _m_ipm_para_parser.get_vp_point_x();
    auto vp_pt_y = _m_ipm_para_parser.get_vp_point_y();;
    auto ipm_image_size_width = _m_ipm_para_parser.get_ipm_image_width();
    auto ipm_image_size_height = _m_ipm_para_parser.get_ipm_image_height();
    auto ccd_image_path = _m_ipm_para_parser.get_ccd_image_path();

    if (calib_file_path.isEmpty() ||
            calib_file_path.isNull() ||
            !FileSystemProcessor::is_file_exist(calib_file_path.toStdString())) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Camera calibration file may not load correctly, please check again"));
        return false;
    }

    if (calib_image_width == 0 || calib_image_height == 0 ) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Calibration result image size can not be zero"));
        return false;
    }

    if (vp_pt_x <= 0 || vp_pt_x >= calib_image_width) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Vannish point x value not in range (0, calib_image_width)"));
        return false;
    }

    if (vp_pt_y <= 0 || vp_pt_y >= calib_image_height) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Vannish point y value not in range (0, calib_image_height)"));
        return false;
    }

    if (ipm_image_size_width == 0 || ipm_image_size_height == 0) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("Ipm result image size can not be zero"));
        return false;
    }

    if (ccd_image_path.isNull() ||
            ccd_image_path.isEmpty() ||
            !FileSystemProcessor::is_file_exist(ccd_image_path.toStdString())) {
        QMessageBox::warning(this, tr("Warn Messagebox"),
                             tr("CCD image path file not exist"));
        return false;
    }

    return true;
}

/***
 *
 * Protected functions
 */

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (_m_image_paths.empty()) {
        return;
    }

    bool is_first_show_image = _m_ipm_image_viewer->is_image_viewer_empty();

    if (event->key() == Qt::Key_A) {

        if (_m_images_iter == _m_image_paths.begin()) {
            _m_images_iter = _m_image_paths.end() - 1;
        } else {
            --_m_images_iter;
        }

        _m_ipm_image_viewer->set_image(QImage(QString::fromStdString(*_m_images_iter)));
        if (is_first_show_image) {
            _m_ipm_image_viewer->fit_image();
        }
    }

    if (event->key() == Qt::Key_D) {

        if (_m_images_iter == _m_image_paths.end() - 1) {
            _m_images_iter = _m_image_paths.begin();
        } else {
            ++_m_images_iter;
        }

        _m_ipm_image_viewer->set_image(QImage(QString::fromStdString(*_m_images_iter)));
        if (is_first_show_image) {
            _m_ipm_image_viewer->fit_image();
        }
    }

    event->accept();

    QWidget::keyPressEvent(event);
}
