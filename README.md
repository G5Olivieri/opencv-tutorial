# Opencv-Tutorial

![opencv](http://opencv.org/wp-content/themes/opencv/images/logo.png)

OpenCV(Open Source Computer Vision Library)是一個集合數百種演算法的跨平台電腦視覺庫。只要是針對影像做辨識、操作、分析等，不管是要做人臉辨識、物件辨識、車牌辨識、人形偵測、物件追蹤、影像壓縮、影像加密等各種影像處理，OpenCV確實是一個很好的輔助工具，目前已經可以在Windows、Linux、iOS及Android平台上使用，支援的程式語言有C/C++、Java、Python、Matlab、Ruby及C#等，已經是大部分影像處理使用者必備的涵式庫了，以下會介紹OpenCV的主要功能、使用方式及範例程式碼。


## 模組 (Module)

**Main**
- core. 基本資料結構的緊湊模組，包含操作影像像素及1.0與2.0版本格式交換
- imgproc. 影像處理模組，包含線性與非線性的影像濾波器及幾何影像的轉換(影像縮放翻轉、色彩空間轉換和直方圖操作等)
- imgcodecs. 影像格式編碼、解碼及影像存取
- videoio. 攝影機操作
- highgui. 提供簡易的視窗介面及鍵盤與滑鼠操作
- video. 物件追蹤、背景相減及移動方向預估等
- calib3d. 多視角幾何演算法，影像校正、3D物件重建及姿態估測等
- features2d. 特徵擷取及特徵描述
- objdetect. 物件偵測，如人臉偵測、眼睛偵測、嘴巴偵測、鼻子偵測及身形偵測等
- ml. 機器學習演算法，如KNN、貝式機率分類器、SVM等
- flann. 實現FLANN演算法
- photo. 影像去雜訊、HDR
- stitching. 影像合成相關技術
- cudaarithm. 使用CUDA資料結構操作
- cudabgsegm. 使用CUDA的背景相減MOG
- cudacodec. 使用CUDA的影片存取讀取
- cudafeatures2d. 使用CUDA實現部分特徵擷取技術
- cudafilters. Image Filtering
- cudaimgproc. Image Processing
- cudalegacy. Legacy support
- cudaobjdetect. Object Detection
- cudaoptflow. Optical Flow
- cudastereo. Stereo Correspondence
- cudawarping. Image Warping
- cudev. Device layer
- shape. Shape Distance and Matching
- superres. Super Resolution
- videostab. Video Stabilization
- viz. 3D Visualizer

**Extra**
- aruco. ArUco Marker Detection
- bgsegm. Improved Background-Foreground Segmentation Methods
- bioinspired. Biologically inspired vision models and derivated tools
- ccalib. Custom Calibration Pattern for 3D reconstruction
- cvv. GUI for Interactive Visual Debugging of Computer Vision Programs
- datasets. Framework for working with different datasets
- dnn. Deep Neural Network module
- dpm. Deformable Part-based Models
- face. Face Recognition
- fuzzy. Image processing based on fuzzy mathematics
- hdf. Hierarchical Data Format I/O routines
- line_descriptor. Binary descriptors for lines extracted from an image
- matlab. MATLAB Bridge
- optflow. Optical Flow Algorithms
- plot. Plot function for Mat data
- reg. Image Registration
- rgbd. RGB-Depth Processing
- saliency. Saliency API
- sfm. Structure From Motion
- stereo. Stereo Correspondance Algorithms
- structured_light. Structured Light API
- surface_matching. Surface Matching
- text. Scene Text Detection and Recognition
- tracking. Tracking API
- xfeatures2d. Extra 2D Features Framework
- ximgproc. Extended Image Processing
- xobjdetect. Extended object detection
- xphoto. Additional photo processing algorithms

## 下載 (Download)
- [OpenCV Windows](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/) - C++、C、Python、JAVA (最新版本3.1.0、2.4.12)
- [OpenCV Linux](https://sourceforge.net/projects/opencvlibrary/files/opencv-unix/) - C++、C、Python、JAVA (最新版本3.1.0、2.4.12)
- [OpenCV iOS](http://sourceforge.net/projects/opencvlibrary/files/opencv-ios/) -  (最新版本3.1.0、2.4.11)
- [OpenCV Android](http://sourceforge.net/projects/opencvlibrary/files/opencv-android/) -  (最新版本3.1.0、2.4.11)
- [JavaCV](https://github.com/bytedeco/javacv) - Java
- [EmguCV](http://www.emgu.com/wiki/index.php/Main_Page) - C#版本(最新版本3.1.0、2.4.10)
- [OpenCVSharp](https://github.com/shimat/opencvsharp) - C# .NET Framework(最新版本3.1.0、2.4.10)
- [Adaptive Vision Studio](http://www.adaptive-vision.com/en/software/) - 以資料流程 (dataflow) 為基礎，專為機器視覺工程師的視覺環境編程軟體

## 安裝 (Installer)
- [Install OpenCV 2.3.1 with Visual Studio 2008 on Windows](http://ccw1986.blogspot.tw/2013/01/opencvvisual-studio-2008-opencv-231.html)
- [Install OpenCV 2.4.4 with Visual Studio 2010 on Windows](http://ccw1986.blogspot.tw/2013/06/opencvvisual-studio-2010-opencv-244.html)
- [Install OpenCV 2.4.X with QT Creator on Windows](http://ccw1986.blogspot.tw/2014/05/opencvinstall-opencv24x-with-qt-52-on.html)
- [Install OpenCV 2.4.8 with Dev-C++ 5.7.1 on Windows](http://ccw1986.blogspot.tw/2014/09/dev-c571-opencv-248-opencv-with-dev-c.html)
- [Install Python and OpenCV 3.1 on Ubuntu 14.04 64bits](http://ccw1986.blogspot.tw/2016/03/install-python-and-opencv-31-on-ubuntu.html)
- [Install Python and OpenCV 3 on Raspbian Jessie](http://ccw1986.blogspot.tw/2016/03/install-python-and-opencv-3-on-raspbian.html)
- [Build OpenCV 2.4.8 Library on Windows using MinGW Compiler](http://ccw1986.blogspot.tw/2014/06/windowmingwopencv-248-install-opencv.html)
- [Build OpenCV 2.4.8 Static Library on Ubuntu](http://ccw1986.blogspot.tw/2014/03/opencvbuild-opencv-static-library-on.html)


{% gist 8f37726ef001a3de41c7 Basic Matrix Operation.md %}
