#-------------------------------------------------
#
# Project created by QtCreator 2020-05-06T14:37:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stuInfoSysv2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        logscreen.cpp \
    globle.cpp \
    adminscreen.cpp \
    stuscreen.cpp \
    stumodifypassself.cpp \
    stuinfoshowself.cpp \
    allstuinfo.cpp \
    addstudent.cpp \
    modifystupass.cpp \
    modifyadmpass.cpp \
    selectgradeself.cpp \
    addstugrades.cpp \
    allstugrades.cpp \
    modifystuinfo.cpp

HEADERS  += logscreen.h \
    globle.h \
    adminscreen.h \
    stuscreen.h \
    stumodifypassself.h \
    stuinfoshowself.h \
    allstuinfo.h \
    addstudent.h \
    modifystupass.h \
    modifyadmpass.h \
    selectgradeself.h \
    addstugrades.h \
    allstugrades.h \
    modifystuinfo.h

FORMS    += logscreen.ui \
    adminscreen.ui \
    stuscreen.ui \
    stumodifypassself.ui \
    stuinfoshowself.ui \
    allstuinfo.ui \
    addstudent.ui \
    modifystupass.ui \
    modifyadmpass.ui \
    selectgradeself.ui \
    addstugrades.ui \
    allstugrades.ui \
    modifystuinfo.ui

RESOURCES += \
    res.qrc

DISTFILES +=
