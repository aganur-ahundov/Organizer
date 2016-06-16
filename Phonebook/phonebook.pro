#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T20:58:32
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phonebook
TEMPLATE = app
QT       += xml

SOURCES += main.cpp\
        phonebook.cpp \
    input_dialog.cpp \
    dom_parser.cpp

HEADERS  += phonebook.h \
    input_dialog.h \
    dom_parser.h \
    mobile_number_validator.h
