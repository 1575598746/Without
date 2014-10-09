#-------------------------------------------------
#
# Project created by QtCreator 2014-01-18T23:35:03
#
#-------------------------------------------------

QT       += core gui sql

TARGET = DoctorCares_1
TEMPLATE = app


SOURCES += main.cpp\
        login_dialog.cpp \
    getuserdatabase.cpp \
    loginqmessage_dialog.cpp \
    insert_dialog.cpp \
    instorage_dialog.cpp \
    add_dialog.cpp \
    insertqmessage_dialog.cpp \
    diarythread.cpp \
    checkdiary_dialog.cpp \
    register_dialog.cpp \
    forget_dialog.cpp \
    detail_dialog.cpp \
    operator_dialog.cpp \
    customer_dialog.cpp \
    customerdetail_dialog.cpp

HEADERS  += login_dialog.h \
    getuserdatabase.h \
    loginqmessage_dialog.h \
    insert_dialog.h \
    instorage_dialog.h \
    add_dialog.h \
    insertqmessage_dialog.h \
    diarythread.h \
    checkdiary_dialog.h \
    register_dialog.h \
    forget_dialog.h \
    detail_dialog.h \
    operator_dialog.h \
    customer_dialog.h \
    customerdetail_dialog.h

FORMS    += login_dialog.ui \
    loginqmessage_dialog.ui \
    insert_dialog.ui \
    instorage_dialog.ui \
    add_dialog.ui \
    insertqmessage_dialog.ui \
    checkdiary_dialog.ui \
    register_dialog.ui \
    forget_dialog.ui \
    detail_dialog.ui \
    operator_dialog.ui \
    customer_dialog.ui \
    customerdetail_dialog.ui

RESOURCES += \
    qsource.qrc
