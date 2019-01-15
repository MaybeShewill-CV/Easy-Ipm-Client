/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QToolBox *toolBox;
    QWidget *Page;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *ipm_calib_plain_cam_radioButton;
    QRadioButton *ipm_calib_fisheye_cam_radioButton;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_10;
    QLabel *label_23;
    QLineEdit *ipm_calib_image_width_lineEdit;
    QLabel *label_24;
    QLineEdit *ipm_calib_image_height_lineEdit;
    QLabel *label_25;
    QLineEdit *ipm_calib_board_width_lineEdit;
    QLabel *label_27;
    QLineEdit *ipm_calib_board_height_lineEdit;
    QLabel *label_26;
    QLineEdit *ipm_calib_square_width_lineEdit;
    QLabel *label_28;
    QLineEdit *ipm_calib_square_height_lineEdit;
    QLineEdit *ipm_calib_paras_save_lineEdit;
    QToolButton *ipm_calib_paras_save_path_toolButton;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_15;
    QPushButton *ipm_calib_distorate_image_pushButton;
    QPushButton *ipm_calib_start_pushButton;
    QPushButton *ipm_calib_cancel_pushButton;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_11;
    QProgressBar *ipm_calib_extract_corners_progressBar;
    QLabel *label_29;
    QProgressBar *ipm_calib_evaluate_result_progressBar;
    QLabel *label_31;
    QProgressBar *ipm_calib_vis_result_progressBar;
    QLabel *label_30;
    QWidget *ipm_para_panel;
    QGroupBox *camera_model_groupbox;
    QGridLayout *gridLayout;
    QToolButton *toolButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLabel *label_9;
    QLineEdit *lineEdit_10;
    QLabel *label_4;
    QLineEdit *lineEdit_5;
    QGroupBox *ipm_model_groupbox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *label_32;
    QLineEdit *ccd_img_path_line_edit;
    QLabel *label_33;
    QLineEdit *ccd_img_dir_path_line_edit;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_6;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_3;
    QPushButton *load_ccd_img_btn;
    QPushButton *generate_ipm_btn;
    QPushButton *load_generate_ipm_para_pushButton;
    QPushButton *save_ipm_para_btn;
    QPushButton *generate_load_ipm_ccd_dir_pushButton;
    QWidget *ipm_exec_panel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_5;
    QToolButton *ccd_dir_toolButton;
    QLineEdit *ccd_dir_lineEdit;
    QToolButton *ipm_ret_dir_toolButton;
    QLineEdit *ipm_dir_lineEdit;
    QToolButton *frametime_path_toolButton;
    QLineEdit *frame_path_lineEdit;
    QHBoxLayout *horizontalLayout;
    QRadioButton *dynamic_radio_btn;
    QRadioButton *static_radio_btn;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_6;
    QPushButton *batch_generate_ipm_pushButton;
    QProgressBar *batch_process_ipm_progressBar;
    QPushButton *cancel_generate_ipm_pushButton;
    QWidget *ipm_stitch_panel;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_7;
    QToolButton *ipm_stitch_dir_toolButton;
    QLineEdit *ipm_stitch_ipm_dir_lineEdit;
    QToolButton *ipm_stitch_panob_path_toolButton;
    QLineEdit *ipm_stitch_panob_path_lineEdit;
    QToolButton *ipm_stitch_output_path_toolButton;
    QLineEdit *ipm_stitch_output_path_lineEdit;
    QLabel *label_10;
    QLineEdit *ipm_stitch_pitch_lineEdit;
    QLabel *label_11;
    QLineEdit *ipm_stitch_yaw_lineEdit;
    QLabel *label_12;
    QLineEdit *ipm_stitch_fy_lineEdit;
    QLabel *label_13;
    QLineEdit *ipm_stitch_ratio_lineEdit;
    QLabel *label_14;
    QLineEdit *ipm_stitch_stepsize_lineEdit;
    QLabel *label_15;
    QLineEdit *ipm_stitch_start_idx_lineEdit;
    QLabel *label_20;
    QLineEdit *ipm_stitch_end_idx_lineEdit;
    QLabel *label_16;
    QLineEdit *ipm_stitch_centert_x_lineEdit;
    QLabel *label_17;
    QLineEdit *ipm_stitch_centert_y_lineEdit;
    QLabel *label_18;
    QLineEdit *ipm_stitch_centert_top_offset_lineEdit;
    QLabel *label_19;
    QLineEdit *ipm_stitch_centert_bottom_offset_lineEdit;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_8;
    QPushButton *ipm_stitch_load_para_pushButton;
    QPushButton *ipm_stitch_start_pushButton;
    QPushButton *ipm_stitch_save_para_pushButton;
    QPushButton *ipm_stitch_cancel_pushButton;
    QProgressBar *ipm_stitch_stack_progressBar;
    QProgressBar *ipm_stitch_render_progressBar;
    QLabel *label_21;
    QLabel *label_22;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_6;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1019, 835);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(10, 0, 321, 791));
        Page = new QWidget();
        Page->setObjectName(QStringLiteral("Page"));
        Page->setGeometry(QRect(0, 0, 321, 667));
        groupBox_4 = new QGroupBox(Page);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 10, 311, 391));
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 330, 301, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        ipm_calib_plain_cam_radioButton = new QRadioButton(layoutWidget);
        ipm_calib_plain_cam_radioButton->setObjectName(QStringLiteral("ipm_calib_plain_cam_radioButton"));

        horizontalLayout_3->addWidget(ipm_calib_plain_cam_radioButton);

        ipm_calib_fisheye_cam_radioButton = new QRadioButton(layoutWidget);
        ipm_calib_fisheye_cam_radioButton->setObjectName(QStringLiteral("ipm_calib_fisheye_cam_radioButton"));

        horizontalLayout_3->addWidget(ipm_calib_fisheye_cam_radioButton);

        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(14, 41, 291, 271));
        gridLayout_10 = new QGridLayout(layoutWidget1);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(layoutWidget1);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_10->addWidget(label_23, 0, 0, 1, 1);

        ipm_calib_image_width_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_image_width_lineEdit->setObjectName(QStringLiteral("ipm_calib_image_width_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_image_width_lineEdit, 0, 1, 1, 1);

        label_24 = new QLabel(layoutWidget1);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_10->addWidget(label_24, 1, 0, 1, 1);

        ipm_calib_image_height_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_image_height_lineEdit->setObjectName(QStringLiteral("ipm_calib_image_height_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_image_height_lineEdit, 1, 1, 1, 1);

        label_25 = new QLabel(layoutWidget1);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_10->addWidget(label_25, 2, 0, 1, 1);

        ipm_calib_board_width_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_board_width_lineEdit->setObjectName(QStringLiteral("ipm_calib_board_width_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_board_width_lineEdit, 2, 1, 1, 1);

        label_27 = new QLabel(layoutWidget1);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_10->addWidget(label_27, 3, 0, 1, 1);

        ipm_calib_board_height_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_board_height_lineEdit->setObjectName(QStringLiteral("ipm_calib_board_height_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_board_height_lineEdit, 3, 1, 1, 1);

        label_26 = new QLabel(layoutWidget1);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_10->addWidget(label_26, 4, 0, 1, 1);

        ipm_calib_square_width_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_square_width_lineEdit->setObjectName(QStringLiteral("ipm_calib_square_width_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_square_width_lineEdit, 4, 1, 1, 1);

        label_28 = new QLabel(layoutWidget1);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_10->addWidget(label_28, 5, 0, 1, 1);

        ipm_calib_square_height_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_square_height_lineEdit->setObjectName(QStringLiteral("ipm_calib_square_height_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_square_height_lineEdit, 5, 1, 1, 1);

        ipm_calib_paras_save_lineEdit = new QLineEdit(layoutWidget1);
        ipm_calib_paras_save_lineEdit->setObjectName(QStringLiteral("ipm_calib_paras_save_lineEdit"));

        gridLayout_10->addWidget(ipm_calib_paras_save_lineEdit, 6, 1, 1, 1);

        ipm_calib_paras_save_path_toolButton = new QToolButton(layoutWidget1);
        ipm_calib_paras_save_path_toolButton->setObjectName(QStringLiteral("ipm_calib_paras_save_path_toolButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ipm_calib_paras_save_path_toolButton->sizePolicy().hasHeightForWidth());
        ipm_calib_paras_save_path_toolButton->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(ipm_calib_paras_save_path_toolButton, 6, 0, 1, 1);

        groupBox_5 = new QGroupBox(Page);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 420, 311, 221));
        layoutWidget2 = new QWidget(groupBox_5);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 140, 311, 71));
        gridLayout_15 = new QGridLayout(layoutWidget2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        ipm_calib_distorate_image_pushButton = new QPushButton(layoutWidget2);
        ipm_calib_distorate_image_pushButton->setObjectName(QStringLiteral("ipm_calib_distorate_image_pushButton"));

        gridLayout_15->addWidget(ipm_calib_distorate_image_pushButton, 0, 0, 1, 1);

        ipm_calib_start_pushButton = new QPushButton(layoutWidget2);
        ipm_calib_start_pushButton->setObjectName(QStringLiteral("ipm_calib_start_pushButton"));

        gridLayout_15->addWidget(ipm_calib_start_pushButton, 0, 1, 1, 1);

        ipm_calib_cancel_pushButton = new QPushButton(layoutWidget2);
        ipm_calib_cancel_pushButton->setObjectName(QStringLiteral("ipm_calib_cancel_pushButton"));

        gridLayout_15->addWidget(ipm_calib_cancel_pushButton, 1, 0, 1, 1);

        layoutWidget3 = new QWidget(groupBox_5);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 30, 311, 101));
        gridLayout_11 = new QGridLayout(layoutWidget3);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        ipm_calib_extract_corners_progressBar = new QProgressBar(layoutWidget3);
        ipm_calib_extract_corners_progressBar->setObjectName(QStringLiteral("ipm_calib_extract_corners_progressBar"));
        ipm_calib_extract_corners_progressBar->setValue(24);

        gridLayout_11->addWidget(ipm_calib_extract_corners_progressBar, 0, 0, 1, 1);

        label_29 = new QLabel(layoutWidget3);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_29, 0, 1, 1, 1);

        ipm_calib_evaluate_result_progressBar = new QProgressBar(layoutWidget3);
        ipm_calib_evaluate_result_progressBar->setObjectName(QStringLiteral("ipm_calib_evaluate_result_progressBar"));
        ipm_calib_evaluate_result_progressBar->setValue(24);

        gridLayout_11->addWidget(ipm_calib_evaluate_result_progressBar, 1, 0, 1, 1);

        label_31 = new QLabel(layoutWidget3);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_11->addWidget(label_31, 1, 1, 1, 1);

        ipm_calib_vis_result_progressBar = new QProgressBar(layoutWidget3);
        ipm_calib_vis_result_progressBar->setObjectName(QStringLiteral("ipm_calib_vis_result_progressBar"));
        ipm_calib_vis_result_progressBar->setValue(24);

        gridLayout_11->addWidget(ipm_calib_vis_result_progressBar, 2, 0, 1, 1);

        label_30 = new QLabel(layoutWidget3);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_30, 2, 1, 1, 1);

        toolBox->addItem(Page, QStringLiteral("Ipm Camera Clibration"));
        ipm_para_panel = new QWidget();
        ipm_para_panel->setObjectName(QStringLiteral("ipm_para_panel"));
        ipm_para_panel->setGeometry(QRect(0, 0, 321, 667));
        camera_model_groupbox = new QGroupBox(ipm_para_panel);
        camera_model_groupbox->setObjectName(QStringLiteral("camera_model_groupbox"));
        camera_model_groupbox->setGeometry(QRect(0, 10, 321, 241));
        gridLayout = new QGridLayout(camera_model_groupbox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        toolButton = new QToolButton(camera_model_groupbox);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        lineEdit = new QLineEdit(camera_model_groupbox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(camera_model_groupbox);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(camera_model_groupbox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_2 = new QLabel(camera_model_groupbox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(camera_model_groupbox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        label_3 = new QLabel(camera_model_groupbox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lineEdit_4 = new QLineEdit(camera_model_groupbox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 3, 1, 1, 1);

        label_9 = new QLabel(camera_model_groupbox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        lineEdit_10 = new QLineEdit(camera_model_groupbox);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));

        gridLayout->addWidget(lineEdit_10, 4, 1, 1, 1);

        label_4 = new QLabel(camera_model_groupbox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        lineEdit_5 = new QLineEdit(camera_model_groupbox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 5, 1, 1, 1);

        ipm_model_groupbox = new QGroupBox(ipm_para_panel);
        ipm_model_groupbox->setObjectName(QStringLiteral("ipm_model_groupbox"));
        ipm_model_groupbox->setGeometry(QRect(0, 260, 321, 241));
        gridLayout_4 = new QGridLayout(ipm_model_groupbox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_32 = new QLabel(ipm_model_groupbox);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_32, 4, 0, 1, 2);

        ccd_img_path_line_edit = new QLineEdit(ipm_model_groupbox);
        ccd_img_path_line_edit->setObjectName(QStringLiteral("ccd_img_path_line_edit"));

        gridLayout_2->addWidget(ccd_img_path_line_edit, 4, 2, 1, 1);

        label_33 = new QLabel(ipm_model_groupbox);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_33, 5, 0, 1, 2);

        ccd_img_dir_path_line_edit = new QLineEdit(ipm_model_groupbox);
        ccd_img_dir_path_line_edit->setObjectName(QStringLiteral("ccd_img_dir_path_line_edit"));

        gridLayout_2->addWidget(ccd_img_dir_path_line_edit, 5, 2, 1, 1);

        lineEdit_9 = new QLineEdit(ipm_model_groupbox);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout_2->addWidget(lineEdit_9, 3, 2, 1, 1);

        lineEdit_8 = new QLineEdit(ipm_model_groupbox);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        gridLayout_2->addWidget(lineEdit_8, 2, 2, 1, 1);

        lineEdit_7 = new QLineEdit(ipm_model_groupbox);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        gridLayout_2->addWidget(lineEdit_7, 1, 2, 1, 1);

        lineEdit_6 = new QLineEdit(ipm_model_groupbox);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        gridLayout_2->addWidget(lineEdit_6, 0, 2, 1, 1);

        label_5 = new QLabel(ipm_model_groupbox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 2);

        label_6 = new QLabel(ipm_model_groupbox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 1, 0, 1, 2);

        label_7 = new QLabel(ipm_model_groupbox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 2, 0, 1, 2);

        label_8 = new QLabel(ipm_model_groupbox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 3, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(ipm_para_panel);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 510, 321, 161));
        gridLayout_13 = new QGridLayout(groupBox_7);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        load_ccd_img_btn = new QPushButton(groupBox_7);
        load_ccd_img_btn->setObjectName(QStringLiteral("load_ccd_img_btn"));

        gridLayout_3->addWidget(load_ccd_img_btn, 0, 0, 1, 1);

        generate_ipm_btn = new QPushButton(groupBox_7);
        generate_ipm_btn->setObjectName(QStringLiteral("generate_ipm_btn"));

        gridLayout_3->addWidget(generate_ipm_btn, 4, 0, 1, 1);

        load_generate_ipm_para_pushButton = new QPushButton(groupBox_7);
        load_generate_ipm_para_pushButton->setObjectName(QStringLiteral("load_generate_ipm_para_pushButton"));

        gridLayout_3->addWidget(load_generate_ipm_para_pushButton, 2, 0, 1, 1);

        save_ipm_para_btn = new QPushButton(groupBox_7);
        save_ipm_para_btn->setObjectName(QStringLiteral("save_ipm_para_btn"));

        gridLayout_3->addWidget(save_ipm_para_btn, 5, 0, 1, 1);

        generate_load_ipm_ccd_dir_pushButton = new QPushButton(groupBox_7);
        generate_load_ipm_ccd_dir_pushButton->setObjectName(QStringLiteral("generate_load_ipm_ccd_dir_pushButton"));

        gridLayout_3->addWidget(generate_load_ipm_ccd_dir_pushButton, 1, 0, 1, 1);


        gridLayout_13->addLayout(gridLayout_3, 0, 0, 1, 1);

        toolBox->addItem(ipm_para_panel, QStringLiteral("Ipm Para Panel"));
        ipm_exec_panel = new QWidget();
        ipm_exec_panel->setObjectName(QStringLiteral("ipm_exec_panel"));
        ipm_exec_panel->setGeometry(QRect(0, 0, 321, 667));
        groupBox = new QGroupBox(ipm_exec_panel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 10, 321, 231));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        ccd_dir_toolButton = new QToolButton(groupBox);
        ccd_dir_toolButton->setObjectName(QStringLiteral("ccd_dir_toolButton"));

        gridLayout_5->addWidget(ccd_dir_toolButton, 0, 0, 1, 1);

        ccd_dir_lineEdit = new QLineEdit(groupBox);
        ccd_dir_lineEdit->setObjectName(QStringLiteral("ccd_dir_lineEdit"));

        gridLayout_5->addWidget(ccd_dir_lineEdit, 0, 1, 1, 1);

        ipm_ret_dir_toolButton = new QToolButton(groupBox);
        ipm_ret_dir_toolButton->setObjectName(QStringLiteral("ipm_ret_dir_toolButton"));

        gridLayout_5->addWidget(ipm_ret_dir_toolButton, 1, 0, 1, 1);

        ipm_dir_lineEdit = new QLineEdit(groupBox);
        ipm_dir_lineEdit->setObjectName(QStringLiteral("ipm_dir_lineEdit"));

        gridLayout_5->addWidget(ipm_dir_lineEdit, 1, 1, 1, 1);

        frametime_path_toolButton = new QToolButton(groupBox);
        frametime_path_toolButton->setObjectName(QStringLiteral("frametime_path_toolButton"));

        gridLayout_5->addWidget(frametime_path_toolButton, 2, 0, 1, 1);

        frame_path_lineEdit = new QLineEdit(groupBox);
        frame_path_lineEdit->setObjectName(QStringLiteral("frame_path_lineEdit"));

        gridLayout_5->addWidget(frame_path_lineEdit, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        dynamic_radio_btn = new QRadioButton(groupBox);
        dynamic_radio_btn->setObjectName(QStringLiteral("dynamic_radio_btn"));

        horizontalLayout->addWidget(dynamic_radio_btn);

        static_radio_btn = new QRadioButton(groupBox);
        static_radio_btn->setObjectName(QStringLiteral("static_radio_btn"));

        horizontalLayout->addWidget(static_radio_btn);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_6 = new QGroupBox(ipm_exec_panel);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 270, 321, 151));
        gridLayout_12 = new QGridLayout(groupBox_6);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        batch_generate_ipm_pushButton = new QPushButton(groupBox_6);
        batch_generate_ipm_pushButton->setObjectName(QStringLiteral("batch_generate_ipm_pushButton"));

        gridLayout_6->addWidget(batch_generate_ipm_pushButton, 0, 0, 1, 1);

        batch_process_ipm_progressBar = new QProgressBar(groupBox_6);
        batch_process_ipm_progressBar->setObjectName(QStringLiteral("batch_process_ipm_progressBar"));
        batch_process_ipm_progressBar->setValue(24);

        gridLayout_6->addWidget(batch_process_ipm_progressBar, 1, 0, 1, 1);

        cancel_generate_ipm_pushButton = new QPushButton(groupBox_6);
        cancel_generate_ipm_pushButton->setObjectName(QStringLiteral("cancel_generate_ipm_pushButton"));

        gridLayout_6->addWidget(cancel_generate_ipm_pushButton, 2, 0, 1, 1);


        gridLayout_12->addLayout(gridLayout_6, 0, 0, 1, 1);

        toolBox->addItem(ipm_exec_panel, QStringLiteral("Ipm Exec Panel"));
        ipm_stitch_panel = new QWidget();
        ipm_stitch_panel->setObjectName(QStringLiteral("ipm_stitch_panel"));
        ipm_stitch_panel->setGeometry(QRect(0, 0, 321, 667));
        groupBox_2 = new QGroupBox(ipm_stitch_panel);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(8, 5, 311, 521));
        gridLayout_14 = new QGridLayout(groupBox_2);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        ipm_stitch_dir_toolButton = new QToolButton(groupBox_2);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(ipm_stitch_dir_toolButton);
        ipm_stitch_dir_toolButton->setObjectName(QStringLiteral("ipm_stitch_dir_toolButton"));
        ipm_stitch_dir_toolButton->setEnabled(true);
        sizePolicy.setHeightForWidth(ipm_stitch_dir_toolButton->sizePolicy().hasHeightForWidth());
        ipm_stitch_dir_toolButton->setSizePolicy(sizePolicy);
        ipm_stitch_dir_toolButton->setLayoutDirection(Qt::LeftToRight);

        gridLayout_7->addWidget(ipm_stitch_dir_toolButton, 0, 0, 1, 1);

        ipm_stitch_ipm_dir_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_ipm_dir_lineEdit->setObjectName(QStringLiteral("ipm_stitch_ipm_dir_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_ipm_dir_lineEdit, 0, 1, 1, 1);

        ipm_stitch_panob_path_toolButton = new QToolButton(groupBox_2);
        buttonGroup->addButton(ipm_stitch_panob_path_toolButton);
        ipm_stitch_panob_path_toolButton->setObjectName(QStringLiteral("ipm_stitch_panob_path_toolButton"));
        sizePolicy.setHeightForWidth(ipm_stitch_panob_path_toolButton->sizePolicy().hasHeightForWidth());
        ipm_stitch_panob_path_toolButton->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(ipm_stitch_panob_path_toolButton, 1, 0, 1, 1);

        ipm_stitch_panob_path_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_panob_path_lineEdit->setObjectName(QStringLiteral("ipm_stitch_panob_path_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_panob_path_lineEdit, 1, 1, 1, 1);

        ipm_stitch_output_path_toolButton = new QToolButton(groupBox_2);
        buttonGroup->addButton(ipm_stitch_output_path_toolButton);
        ipm_stitch_output_path_toolButton->setObjectName(QStringLiteral("ipm_stitch_output_path_toolButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ipm_stitch_output_path_toolButton->sizePolicy().hasHeightForWidth());
        ipm_stitch_output_path_toolButton->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(ipm_stitch_output_path_toolButton, 2, 0, 1, 1);

        ipm_stitch_output_path_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_output_path_lineEdit->setObjectName(QStringLiteral("ipm_stitch_output_path_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_output_path_lineEdit, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_10, 3, 0, 1, 1);

        ipm_stitch_pitch_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_pitch_lineEdit->setObjectName(QStringLiteral("ipm_stitch_pitch_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_pitch_lineEdit, 3, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_11, 4, 0, 1, 1);

        ipm_stitch_yaw_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_yaw_lineEdit->setObjectName(QStringLiteral("ipm_stitch_yaw_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_yaw_lineEdit, 4, 1, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_12, 5, 0, 1, 1);

        ipm_stitch_fy_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_fy_lineEdit->setObjectName(QStringLiteral("ipm_stitch_fy_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_fy_lineEdit, 5, 1, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_13, 6, 0, 1, 1);

        ipm_stitch_ratio_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_ratio_lineEdit->setObjectName(QStringLiteral("ipm_stitch_ratio_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_ratio_lineEdit, 6, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_14, 7, 0, 1, 1);

        ipm_stitch_stepsize_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_stepsize_lineEdit->setObjectName(QStringLiteral("ipm_stitch_stepsize_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_stepsize_lineEdit, 7, 1, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_15, 8, 0, 1, 1);

        ipm_stitch_start_idx_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_start_idx_lineEdit->setObjectName(QStringLiteral("ipm_stitch_start_idx_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_start_idx_lineEdit, 8, 1, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_20, 9, 0, 1, 1);

        ipm_stitch_end_idx_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_end_idx_lineEdit->setObjectName(QStringLiteral("ipm_stitch_end_idx_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_end_idx_lineEdit, 9, 1, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_16, 10, 0, 1, 1);

        ipm_stitch_centert_x_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_centert_x_lineEdit->setObjectName(QStringLiteral("ipm_stitch_centert_x_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_centert_x_lineEdit, 10, 1, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_17, 11, 0, 1, 1);

        ipm_stitch_centert_y_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_centert_y_lineEdit->setObjectName(QStringLiteral("ipm_stitch_centert_y_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_centert_y_lineEdit, 11, 1, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_18, 12, 0, 1, 1);

        ipm_stitch_centert_top_offset_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_centert_top_offset_lineEdit->setObjectName(QStringLiteral("ipm_stitch_centert_top_offset_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_centert_top_offset_lineEdit, 12, 1, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_19, 13, 0, 1, 1);

        ipm_stitch_centert_bottom_offset_lineEdit = new QLineEdit(groupBox_2);
        ipm_stitch_centert_bottom_offset_lineEdit->setObjectName(QStringLiteral("ipm_stitch_centert_bottom_offset_lineEdit"));

        gridLayout_7->addWidget(ipm_stitch_centert_bottom_offset_lineEdit, 13, 1, 1, 1);


        gridLayout_14->addLayout(gridLayout_7, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(ipm_stitch_panel);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 540, 311, 131));
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        ipm_stitch_load_para_pushButton = new QPushButton(groupBox_3);
        ipm_stitch_load_para_pushButton->setObjectName(QStringLiteral("ipm_stitch_load_para_pushButton"));
        sizePolicy.setHeightForWidth(ipm_stitch_load_para_pushButton->sizePolicy().hasHeightForWidth());
        ipm_stitch_load_para_pushButton->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(ipm_stitch_load_para_pushButton, 2, 0, 1, 1);

        ipm_stitch_start_pushButton = new QPushButton(groupBox_3);
        ipm_stitch_start_pushButton->setObjectName(QStringLiteral("ipm_stitch_start_pushButton"));
        sizePolicy.setHeightForWidth(ipm_stitch_start_pushButton->sizePolicy().hasHeightForWidth());
        ipm_stitch_start_pushButton->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(ipm_stitch_start_pushButton, 2, 1, 1, 1);

        ipm_stitch_save_para_pushButton = new QPushButton(groupBox_3);
        ipm_stitch_save_para_pushButton->setObjectName(QStringLiteral("ipm_stitch_save_para_pushButton"));

        gridLayout_8->addWidget(ipm_stitch_save_para_pushButton, 2, 2, 1, 1);

        ipm_stitch_cancel_pushButton = new QPushButton(groupBox_3);
        ipm_stitch_cancel_pushButton->setObjectName(QStringLiteral("ipm_stitch_cancel_pushButton"));
        sizePolicy.setHeightForWidth(ipm_stitch_cancel_pushButton->sizePolicy().hasHeightForWidth());
        ipm_stitch_cancel_pushButton->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(ipm_stitch_cancel_pushButton, 2, 3, 1, 1);

        ipm_stitch_stack_progressBar = new QProgressBar(groupBox_3);
        ipm_stitch_stack_progressBar->setObjectName(QStringLiteral("ipm_stitch_stack_progressBar"));
        ipm_stitch_stack_progressBar->setValue(24);

        gridLayout_8->addWidget(ipm_stitch_stack_progressBar, 0, 0, 1, 3);

        ipm_stitch_render_progressBar = new QProgressBar(groupBox_3);
        ipm_stitch_render_progressBar->setObjectName(QStringLiteral("ipm_stitch_render_progressBar"));
        ipm_stitch_render_progressBar->setValue(24);

        gridLayout_8->addWidget(ipm_stitch_render_progressBar, 1, 0, 1, 3);

        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_21, 0, 3, 1, 1);

        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_22, 1, 3, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 0, 0, 1, 1);

        toolBox->addItem(ipm_stitch_panel, QStringLiteral("Ipm Stitch Panel"));
        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        layoutWidget5 = new QWidget(centralWidget);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Ipm Camera Calibration Parameters", 0));
        ipm_calib_plain_cam_radioButton->setText(QApplication::translate("MainWindow", "Plain Camera", 0));
        ipm_calib_fisheye_cam_radioButton->setText(QApplication::translate("MainWindow", "Fisheye Camera", 0));
        label_23->setText(QApplication::translate("MainWindow", "Calib Image Width", 0));
        label_24->setText(QApplication::translate("MainWindow", "Calib Image Height", 0));
        label_25->setText(QApplication::translate("MainWindow", "Calib board Width", 0));
        label_27->setText(QApplication::translate("MainWindow", "Calib board Height", 0));
        label_26->setText(QApplication::translate("MainWindow", "Calib Square Width", 0));
        label_28->setText(QApplication::translate("MainWindow", "Calib Square Height", 0));
        ipm_calib_paras_save_path_toolButton->setText(QApplication::translate("MainWindow", "Calib Sava Path", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Ipm Camera Calibration Console", 0));
        ipm_calib_distorate_image_pushButton->setText(QApplication::translate("MainWindow", "Distor Image", 0));
        ipm_calib_start_pushButton->setText(QApplication::translate("MainWindow", "Start Calib", 0));
        ipm_calib_cancel_pushButton->setText(QApplication::translate("MainWindow", "Cancel Calib", 0));
        label_29->setText(QApplication::translate("MainWindow", "Extract Corners", 0));
        label_31->setText(QApplication::translate("MainWindow", "Evaluate Results", 0));
        label_30->setText(QApplication::translate("MainWindow", "Visualize Results", 0));
        toolBox->setItemText(toolBox->indexOf(Page), QApplication::translate("MainWindow", "Ipm Camera Clibration", 0));
        camera_model_groupbox->setTitle(QApplication::translate("MainWindow", "Ipm Camera Model Para", 0));
        toolButton->setText(QApplication::translate("MainWindow", "Calib File", 0));
        label->setText(QApplication::translate("MainWindow", "Calib Width", 0));
        label_2->setText(QApplication::translate("MainWindow", "Calib Height", 0));
        label_3->setText(QApplication::translate("MainWindow", "Camera Pitch", 0));
        label_9->setText(QApplication::translate("MainWindow", "Camera Yaw", 0));
        label_4->setText(QApplication::translate("MainWindow", "Camera Name", 0));
        ipm_model_groupbox->setTitle(QApplication::translate("MainWindow", "Ipm Model Para", 0));
        label_32->setText(QApplication::translate("MainWindow", "CCD Img Path", 0));
        label_33->setText(QApplication::translate("MainWindow", "CCD Dir Path", 0));
        label_5->setText(QApplication::translate("MainWindow", "Vp Point X", 0));
        label_6->setText(QApplication::translate("MainWindow", "Vp Point Y", 0));
        label_7->setText(QApplication::translate("MainWindow", "Ipm Width", 0));
        label_8->setText(QApplication::translate("MainWindow", "Ipm Height", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Ipm Transform Console", 0));
        load_ccd_img_btn->setText(QApplication::translate("MainWindow", "Load Image", 0));
        generate_ipm_btn->setText(QApplication::translate("MainWindow", "Generate Ipm", 0));
        load_generate_ipm_para_pushButton->setText(QApplication::translate("MainWindow", "Load Ipm Generate Parameters", 0));
        save_ipm_para_btn->setText(QApplication::translate("MainWindow", "Save Ipm Parameters", 0));
        generate_load_ipm_ccd_dir_pushButton->setText(QApplication::translate("MainWindow", "Load Image Dir", 0));
        toolBox->setItemText(toolBox->indexOf(ipm_para_panel), QApplication::translate("MainWindow", "Ipm Para Panel", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Ipm Exec Para", 0));
        ccd_dir_toolButton->setText(QApplication::translate("MainWindow", "CCD Dir", 0));
        ipm_ret_dir_toolButton->setText(QApplication::translate("MainWindow", "Ipm Dir", 0));
        frametime_path_toolButton->setText(QApplication::translate("MainWindow", "Frame Path", 0));
        dynamic_radio_btn->setText(QApplication::translate("MainWindow", "Dynamic Model", 0));
        static_radio_btn->setText(QApplication::translate("MainWindow", "Static Model", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Ipm Exec Console", 0));
        batch_generate_ipm_pushButton->setText(QApplication::translate("MainWindow", "Batch Generate Ipm", 0));
        cancel_generate_ipm_pushButton->setText(QApplication::translate("MainWindow", "Cancel Generate Ipm", 0));
        toolBox->setItemText(toolBox->indexOf(ipm_exec_panel), QApplication::translate("MainWindow", "Ipm Exec Panel", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Ipm Stitch Para", 0));
        ipm_stitch_dir_toolButton->setText(QApplication::translate("MainWindow", "Ipm Dir Path", 0));
        ipm_stitch_panob_path_toolButton->setText(QApplication::translate("MainWindow", "PanotimeB Path", 0));
        ipm_stitch_output_path_toolButton->setText(QApplication::translate("MainWindow", "Output Path", 0));
        label_10->setText(QApplication::translate("MainWindow", "Pitch", 0));
        label_11->setText(QApplication::translate("MainWindow", "Yaw", 0));
        label_12->setText(QApplication::translate("MainWindow", "Fy", 0));
        label_13->setText(QApplication::translate("MainWindow", "Ratio", 0));
        label_14->setText(QApplication::translate("MainWindow", "Step Size", 0));
        label_15->setText(QApplication::translate("MainWindow", "Start Idx", 0));
        label_20->setText(QApplication::translate("MainWindow", "End Idx", 0));
        label_16->setText(QApplication::translate("MainWindow", "Ipm Center X", 0));
        label_17->setText(QApplication::translate("MainWindow", "Ipm Center Y", 0));
        label_18->setText(QApplication::translate("MainWindow", "Ipm Offset Top", 0));
        label_19->setText(QApplication::translate("MainWindow", "Ipm Offset Bottom", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Ipm Stitch Console", 0));
        ipm_stitch_load_para_pushButton->setText(QApplication::translate("MainWindow", "Load Para", 0));
        ipm_stitch_start_pushButton->setText(QApplication::translate("MainWindow", "Start", 0));
        ipm_stitch_save_para_pushButton->setText(QApplication::translate("MainWindow", "Save Para", 0));
        ipm_stitch_cancel_pushButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
        label_21->setText(QApplication::translate("MainWindow", "Stack", 0));
        label_22->setText(QApplication::translate("MainWindow", "Render", 0));
        toolBox->setItemText(toolBox->indexOf(ipm_stitch_panel), QApplication::translate("MainWindow", "Ipm Stitch Panel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
