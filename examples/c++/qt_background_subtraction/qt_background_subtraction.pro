TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

## Vars Setting
############################################################
BASE = $${PWD}

## DIRS
############################################################
DESTDIR     = $${PWD}/release
TMP_DIR     = $$_PRO_FILE_PWD_/.tmp/$${BUILD_MODE}
UI_DIR      = $${TMP_DIR}
MOC_DIR     = $${TMP_DIR}
RCC_DIR     = $${TMP_DIR}
OBJECTS_DIR = $${TMP_DIR}

OPENCV_DLL_PATH     = $${PWD}/../lib/opencv/x64/vc12/bin
OPENCV_LIB_PATH     = $${PWD}/../lib/opencv/x64/vc12/lib
OPENCV_HEADER_PATH  = $${PWD}/../lib/opencv/x64/vc12/include

DATA_IMAGES         = $${PWD}/../../data/images

BUILD_DIR       = $${DESTDIR}

## File Setting
############################################################
OPENCV_DLLS = opencv_world310.dll
IMAGES = lena.jpg

## Platform Setting
############################################################
win32-msvc2013{
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("QMake Windows VS2013 32")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
        }
    }else{
        message("QMake Windows VS2013 64")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
            INCLUDEPATH += $${OPENCV_HEADER_PATH}
            LIBS += $${OPENCV_LIB_PATH}/opencv_world310.lib

            for( files, OPENCV_DLLS ):eval( QMAKE_POST_LINK += xcopy /R /Q /Y /I $$replace( OPENCV_DLL_PATH, /, \\ )\\$${files} $$replace( BUILD_DIR, /, \\ ) & )
            export(QMAKE_POST_LINK)

            for( files, IMAGES ):eval( QMAKE_POST_LINK += xcopy /R /Q /Y /I $$replace( DATA_IMAGES, /, \\ )\\$${files} $$replace( BUILD_DIR, /, \\ ) & )
            export(QMAKE_POST_LINK)
        }
    }
}
