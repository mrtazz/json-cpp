#-------------------------------------------------
#
# QtCreator project include file
#
#-------------------------------------------------

# This does not build a library or an app, it just links in the source.
# Use include(libthing.pri) in your qmake file to add the sources.

INCLUDEPATH += $$PWD/include

SOURCES +=  $$PWD/src/lib_json/json_reader.cpp \
    $$PWD/src/lib_json/json_value.cpp \
    $$PWD/src/lib_json/json_writer.cpp


HEADERS  += $$PWD/include/json/config.h \
    $$PWD/include/json/features.h \
    $$PWD/include/json/forwards.h \
    $$PWD/include/json/reader.h \
    $$PWD/include/json/value.h \
    $$PWD/include/json/writer.h
