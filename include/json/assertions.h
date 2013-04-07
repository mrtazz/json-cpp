// Copyright 2007-2010 Baptiste Lepilleur
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef CPPTL_JSON_ASSERTIONS_H_INCLUDED
# define CPPTL_JSON_ASSERTIONS_H_INCLUDED

#include <stdlib.h>
#include <stdexcept>

#if !defined(JSON_IS_AMALGAMATION)
# include <json/config.h>
#endif // if !defined(JSON_IS_AMALGAMATION)

namespace Json{
    class json_error : public std::runtime_error
    {
    public:
        explicit json_error( const std::string &what )
        : runtime_error( what )
        {}
    };
}


#if JSON_USE_EXCEPTION

//Perhaps this should be defined in a source file instead, but which one?
#include <cstdio>
#include <string>
namespace Json{
    namespace internal{
        namespace{
            int throwAssertException(const std::string& failMessage, const std::string& file, int line){
                char buf[24];
                snprintf(buf, 24, "%d", line);
                std::string complete(failMessage);
                complete.reserve(failMessage.size() + file.size() + 32);
                complete += file;
                complete += ", line ";
                complete += buf;
                throw Json::json_error(complete);
                return 0;
            }
        }
    }
}

#define JSON_ASSERT( condition ) ( (condition) ? 0 : Json::internal::throwAssertException("Json assertion failed: " #condition ", file ", __FILE__, __LINE__) );
#define JSON_FAIL_MESSAGE( message ) throw Json::json_error( message );
#else  // JSON_USE_EXCEPTION
#define JSON_ASSERT( condition ) assert( condition );

// The call to assert() will show the failure message in debug builds. In
// release bugs we write to invalid memory in order to crash hard, so that a
// debugger or crash reporter gets the chance to take over. We still call exit()
// afterward in order to tell the compiler that this macro doesn't return.
#define JSON_FAIL_MESSAGE( message ) { assert(false && message); strcpy(reinterpret_cast<char*>(666), message); exit(123); }

#endif

#define JSON_ASSERT_MESSAGE( condition, message ) if (!( condition )) { JSON_FAIL_MESSAGE( message ) }

#endif // CPPTL_JSON_ASSERTIONS_H_INCLUDED
