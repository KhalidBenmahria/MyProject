QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    createfolderdialog.cpp \
    createpartitiondialog.cpp \
    creatfiledialog.cpp \
    deletedialog.cpp \
    directory.cpp \
    disk.cpp \
    entry.cpp \
    entrytreemodell.cpp \
    fatfile.cpp \
    fatpartition.cpp \
    festplatteerstellendialog.cpp \
    file.cpp \
    inodefile.cpp \
    inodepartition.cpp \
    main.cpp \
    mainwindow.cpp \
    partition.cpp \
    partitiondetaisdialog.cpp \
    qtreewidgetfile.cpp \
    readcddialog.cpp \
    rootdirectory.cpp \
    writecddialog.cpp

HEADERS += \
    block.h \
    createfolderdialog.h \
    createpartitiondialog.h \
    creatfiledialog.h \
    deletedialog.h \
    directory.h \
    disk.h \
    entry.h \
    entrytreemodell.h \
    fatfile.h \
    fatpartition.h \
    festplatteerstellendialog.h \
    file.h \
    inodefile.h \
    inodepartition.h \
    mainwindow.h \
    partition.h \
    partitiondetaisdialog.h \
    qtreewidgetfile.h \
    readcddialog.h \
    rootdirectory.h \
    writecddialog.h

FORMS += \
    createfolderdialog.ui \
    createpartitiondialog.ui \
    creatfiledialog.ui \
    deletedialog.ui \
    dialog.ui \
    festplatteerstellendialog.ui \
    mainwindow.ui \
    partitiondetaisdialog.ui \
    readcddialog.ui \
    writecddialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
