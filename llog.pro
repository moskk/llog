TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += main.cpp \
    log.cpp \
    llog_utils.cpp

HEADERS += \
    llog.hpp \
    llog_sinks.hpp \
    llog_utils.hpp \
    llog_record.hpp \
    log.hpp \
    llog_bit_mask.hpp \
    llog_ctxinfo.hpp
