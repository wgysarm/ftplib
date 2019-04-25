#-------------------------------------------------
#
# Project created by QtCreator 2018-01-08T09:37:06
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = CIVFDFtp
TEMPLATE = lib

DEFINES += CIVFDFTP_LIBRARY

SOURCES += CIVFDFtp.cpp \
    appsettings.cpp \
    ftpdatasocket.cpp \
    ftpfilesocket.cpp \
    ftplistitem.cpp \
    ftpmlsitem.cpp \
    ftpplugin.cpp \
    ftpport.cpp \
    ftpserver.cpp

HEADERS += CIVFDFtp.h\
        civfdftp_global.h \
    appsettings.h \
    ftpdatasocket.h \
    ftpfilesocket.h \
    ftplistitem.h \
    ftpmlsitem.h \
    ftpplugin.h \
    ftpport.h \
    ftpserver.h \
    PluginInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
