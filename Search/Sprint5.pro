TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    data.cpp \
    hashtableindex.cpp \
    indexhandler.cpp \
    manip.cpp \
    parse.cpp \
    queryhandler.cpp \
    searchengine.cpp \
    userinterface.cpp \
    porter2_stemmer/porter2_stemmer.cpp

HEADERS += \
    avltree.h \
    avltreeindex.h \
    data.h \
    hashtableindex.h \
    indexhandler.h \
    indexinterface.h \
    manip.h \
    parse.h \
    queryhandler.h \
    searchengine.h \
    userinterface.h \
    porter2_stemmer/porter2_stemmer.h \
    rapidjson/document.h \
    rapidjson/stringbuffer.h \
    rapidjson/writer.h
