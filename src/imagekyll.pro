#-------------------------------------------------
#
# Project created by QtCreator 2018-09-26T21:57:14
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = imagekyll
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
RC_FILE = icon.rc

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        color_changer.cpp \
        conf_module.cpp \
        image_editor.cpp \
        image_resize.cpp \
        imagecompressor.cpp \
        info_window.cpp \
        jekyll_repo.cpp \
        main.cpp \
        option.cpp \
        paint_scene.cpp

HEADERS += \
        ColorChanger.h \
        Config.h \
        ImageCompressor.h \
        ImageEditor.h \
        ImageResize.h \
        InfoWindow.h \
        JekyllRepo.h \
        Option.h \
        PaintScene.h

FORMS += \
        color_changer.ui \
        image_editor.ui \
        image_resize.ui \
        imagecompressor.ui \
        info_window.ui \
        jekyll_repo.ui \
        option.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
