# Easy-Ipm-Client
An easy, interface friendly cross-platform client to generate top view 
images using inverse perspective mapping method. Since a lot of lane 
detection work are based on ipm images it is important to generate high
quality ipm image for those users. This repo implement a easy use client
for users who have no knowledge or experience with the inverse perspective
mapping technology to generate top-view images.The clinet is mainly based
on Qt so it is convenient to compile on other platform.

## Inverse Perspective Map Model
This repo implement the model supplement in the paper "Adaptive Inverse Perspective Mapping
for Lane Map Generation with SLAM". Use the camera's motion information to
implement an adaptive model for the IPM to accurately transform 
camera images to bird’s-eye view images. The model's schematic diagram are
as follows

`Side view of the IPM model`

![IPM_Model_Side_View](/images/ipm_side_view.png)

`Top view of the IPM model`

![IPM_Model_Top_View](/images/ipm_top_view.png)

## Install && System information
The system information and library used in this project are as follows:

##### os: Ubuntu 16.04 LTS
##### compiler: GCC 5.4 supported with c++ 11
##### qt library: qt 5.6
##### ide: qt creator 4.8
##### boost: boost 1.58.0
##### opencv: opencv 3.4

To use this software you need first install qt library. You may follow
the instruction [how_to_install_qt_lib](http://doc.qt.io/qt-5/gettingstarted.html)
. Then you need opencv and boost installed on your local machine the two
following instructions will lead you to the how to page. 
[how_to_install_boost](https://www.boost.org/doc/libs/1_58_0/more/getting_started/unix-variants.html)
[how_to_install_opencv](https://docs.opencv.org/3.4.0/d7/d9f/tutorial_linux_install.html)
. Then you can use qt creator to open the .pro file to configure the 
project. A prebuiilt release version and a prebuilt debug version of the
client has already been uploaded into the ROOT_DIR/release and 
ROOT_DIR/debug folder.

## Usage and Examples
This client contains three work panel. Camera calibration module, 
inverse perspective map module and batch process ipm images module.

### Camera Calibration Module
Select the camera calibration panel and adjust the parameters which fits
your dataset and run the calibration. During the process progress you may 
watch the progressbar to monitor progress and the corner detection result
may be seen on the screen panel. When process finished the calibration 
result will be written in the yml file. You may use the calibration 
result to distorate the source image.

`Start Up Example`

![Start_Up_Example](/images/start_up_example.png)

`Camera Calibration Example`

![Camera_Calibration_Example](/images/cam_calib_example.png)
![Camera_Calibration_Process_Example](/images/cam_calib_corner_example.png)

### Adaptive Inverse Perspective Mapping Module
Select the Ipm Para Panel and adjust all the parameters needed to generate
ipm images.Here is a simple glimpse at the description of the parameters.

**Calib Width/Height**: the image size of the camera calibration result image

**Camera Pitch**: the camera pitch angle

**Camera Yaw**: the camera yaw angle

**Vp Point X/Y**: the vanish point which is used with image boundary to locate
the image roi to generate the ipm image

**Ipm Width/Height**: the image size of the result ipm image

The two most important parameter you need to adjust are the pitch angle 
and the vp point y. The pitch angle control the camera's motion and the 
vp point y control the roi location. You may save all the parameters you
use to generate the ipm image into a yml file which may be used during
future batch process work.

Follows are two ipm images generated
with different parameter.


`Ipm Parameter Example`

![Ipm_Para_Example](/images/ipm_para_source.jpg)
![Ipm_Para_Example](/images/ipm_para_example.png)
![Ipm_Para_Example](/images/ipm_para_example_2.png)

### Batch Process Ipm Module
Select the Ipm Exec Panel and fill in the process parameter. Only static 
model was released for now and the model will use the parameter which was 
set on the Ipm Para Panel to batch generate the ipm images in the ccd dir.
The progress and ipm images will show in the work panel.

`Batch process Example`

![Batch_Process_Example](/images/batch_process_example.png)

### Short cuts
The client support a few kinds of short cuts and tools to allow you 
adjust the model. You may check the image pixel coordinate and rgb
value in the status bar. 

**A**: previous image when you select a image dir

**D**: next image when you select a image dir

**ctrl + scroll down**: image zoom out

**ctrl + scroll up**: image zoom in

### Future Release
The batch processed ipm image may be stitched together to get the ipm
map.This kind of map will overcome the drawback of occlusion in 
tradition map.To make this kind of map you need know the geographic 
coordinates of every pictures.A lot of camera will record this 
information in the image EXIF data for example Iphone.

Here are some examples of ipm stitch result

`Ipm Stitch Panel Example`

![Ipm_Stitch_Example](/images/ipm_stitch_example.png)

`Ipm Stitch Result Example`

![Ipm_Stitch_Example](/images/ipm_stitch_result.png)
