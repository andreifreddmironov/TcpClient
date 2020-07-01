#-------------------------------------------------
#
# Project created by QtCreator 2020-06-30T16:22:48
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TestTcpClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tcpclient.cpp \
    client.cpp

HEADERS += \
    tcpclient.h \
    client.h
