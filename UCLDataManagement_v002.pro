#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T15:43:11
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++0x

TARGET = UCLDataManagement_v002
TEMPLATE = app


SOURCES += main.cpp\
    ServerInformation.cc \
    Person.cc \
    User.cc \
    AccessPermissionList.cc \
    Login.cc \
    Connection.cc \
    ViewMainScreen.cc \
    Participant.cc \
    Question.cc \
    BooleanQuestion.cc \
    NumberQuestion.cc \
    TextQuestion.cc \
    Questionnaire.cc

HEADERS  += \
    ServerInformation.h \
    Person.h \
    User.h \
    AccessPermissionList.h \
    Login.h \
    Connection.h \
    ViewMainScreen.h \
    Participant.h \
    Question.h \
    BooleanQuestion.h \
    NumberQuestion.h \
    TextQuestion.h \
    Questionnaire.h

FORMS    += \
    ViewMainScreen.ui

INCLUDEPATH += C:/boost/boost_1_53_0

LIBS += -LC:/boost_lib/boost/bin.v2/libs/serialization/build/gcc-mingw-4.7.2/debug/link-static/threading-multi -lboost_serialization-mgw47-mt-d-1_53
