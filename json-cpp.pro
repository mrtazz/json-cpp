#-------------------------------------------------
#
# Project created by QtCreator 2012-04-03T16:22:51
#
#-------------------------------------------------

QT       -= core gui

TARGET = json-cpp
TEMPLATE = lib

DEFINES += JSONCPP_LIBRARY

SOURCES += \
    src/test_lib_json/main.cpp \
    src/test_lib_json/jsontest.cpp \
    src/lib_json/json_writer.cpp \
    src/lib_json/json_value.cpp \
    src/lib_json/json_reader.cpp

HEADERS += \
    src/test_lib_json/jsontest.h \
    src/lib_json/json_tool.h \
    src/lib_json/json_batchallocator.h

INCLUDEPATH += include/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE80BF41E
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = json-cpp.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
