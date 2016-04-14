## 模組 (Module)

![opencv](http://opencv.org/wp-content/themes/opencv/images/logo.png)

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
...

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
...