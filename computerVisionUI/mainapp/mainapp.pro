
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Specifies the name of the target file. Contains the base name of the project file by default.
TARGET = ComputerVisionUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port yo ur code away from it.

# qmake adds the values of this variable as compiler C preprocessor macros (-D option).
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Specifies the #include directories which should be searched when compiling the project.
INCLUDEPATH += ../cvplugininterface

HEADERS += \
        mainwindow.h \
        qenhancedgraphicsview.h

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        qenhancedgraphicsview.cpp

FORMS += \
        mainwindow.ui

win32: {
    include("c:/dev/opencv/opencv.pri")
}

unix: !macx{
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

unix: macx{
INCLUDEPATH += /usr/local/include
LIBS += -L"/usr/local/lib" \
    -lopencv_world
}

# Add more language entries here, following the same naming rule
# Specifies a list of translation (.ts) files that contain translations of the user interface text into non-native languages.
TRANSLATIONS = language_tr.ts
