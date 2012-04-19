
#-------------------------------------------------
#
# QtCreator project include file
#
#-------------------------------------------------

INCLUDEPATH += $$JSON_CPP_SRC/include

SOURCES +=  $$JSON_CPP_SRC/src/lib_json/json_reader.cpp\
    $$JSON_CPP_SRC/src/lib_json/json_value.cpp\
    $$JSON_CPP_SRC/src/lib_json/json_writer.cpp


HEADERS  +=$$JSON_CPP_SRC/include/json/assertions.h \
    $$JSON_CPP_SRC/include/json/config.h\
    $$JSON_CPP_SRC/include/json/features.h\
    $$JSON_CPP_SRC/include/json/forwards.h\
    $$JSON_CPP_SRC/include/json/reader.h\
    $$JSON_CPP_SRC/include/json/value.h\
    $$JSON_CPP_SRC/include/json/writer.h
