TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    log.cpp

HEADERS += \
    llog.hpp \
    llog_sinks.hpp \
    llog_utils.hpp \
    llog_record.hpp \
    log.hpp
