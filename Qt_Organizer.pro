#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T14:01:08
#
#-------------------------------------------------

QT       += core gui
QT       += xml

-std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Organizer
TEMPLATE = app


SOURCES += main.cpp\
        organizer.cpp \
    Alarm/alarm.cpp \
    Calendar/calendar.cpp \
    Calendar/dom_parser_notebook.cpp \
    Calendar/notebook.cpp \
    Phonebook/dom_parser.cpp \
    Phonebook/input_dialog.cpp \
    Phonebook/phonebook.cpp

HEADERS  += organizer.h \
    Alarm/alarm.h \
    Calendar/calendar.h \
    Calendar/day.h \
    Calendar/dom_parser_notebook.h \
    Calendar/notebook.h \
    Phonebook/dom_parser.h \
    Phonebook/input_dialog.h \
    Phonebook/mobile_number_validator.h \
    Phonebook/phonebook.h
