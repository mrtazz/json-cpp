// No gards, this header can be included multiple time

// Generic header to automatically link against a specified library
// The library name prefix must be defined in CPPTL_AUTOLINK_NAME.
// CPPTL_AUTOLINK_NAME will be undefined after including this header.

// The full library name is build according to the following rules:
// (0) CPPTL_AUTOLINK_NAME: library name prefix (json,...)
// (a) TOOLSET: vc6, vc70, vc71, vc80, bcb4, bcb5, bcb6
// (b) LINKAGE: lib(static), dll(dynamic)
//              The macro CPPTL_AUTOLINK_DLL must be defined to indicate that we are linking
//              against a DLL.
// (c) This suffix depends on threading mode and CRT linkage
//     This suffix follow Microsoft Visual Studio c++ compiler command-line option
//     used to select the CRT library (/mt, /mtd...)
//     Threading    / Run-time library / suffix
//     single       / static           / ml
//     mutli-thread / static           / mt
//     multi-thread / dynamic library  / md
// (e) DEBUG MODE: nothing (release), d(debug)
// FULLNAME: 0_(a)_bcd.lib
// Example:
// Compiling library "cpptl" with vc 7.1 as a static library with debug dll CRT (/MDD)
// "cpptl_vc71_libmdd"
#if !defined(CPPTL_AUTOLINK_NAME)
# error Macro CPPTL_AUTOLINK_NAME should be defined. You should not include this header directly.
#endif

#undef CPPTL_AUTOLINK_TOOLSET_
#undef CPPTL_AUTOLINK_CRT_
#undef CPPTL_AUTOLINK_LINKAGE_
#undef CPPTL_AUTOLINK_DEBUG_MODE_

// Select compiler
// Visual Studio
#if defined(_MSC_VER)
# if defined(_WIN32_WCE)
#  define CPPTL_AUTOLINK_TOOLSET_ "evc4"
# elif (_MSC_VER < 1300) //VC6
#  define CPPTL_AUTOLINK_TOOLSET_ "vc6"
# elif (_MSC_VER < 1310) //VC7.0 (.NET 2002)
#  define CPPTL_AUTOLINK_TOOLSET_ "vc70"
# elif (_MSC_VER < 1400) //VC7.1 (.NET 2003)
#  define CPPTL_AUTOLINK_TOOLSET_ "vc71"
# else
#  define CPPTL_AUTOLINK_TOOLSET_ "vc80"
# endif
// Borland C++
#elif defined(__BORLANDC__)
# if (__BORLANDC__ >= 0x560) // CBuilder 6
#  define CPPTL_AUTOLINK_TOOLSET_ "bcb6"
# elif (__BORLANDC__ >= 0x550)
#  define CPPTL_AUTOLINK_TOOLSET_ "bcb5"
# elif (__BORLANDC__ >= 0x540)
#  define CPPTL_AUTOLINK_TOOLSET_ "bcb4"
# endif
#endif

// Select CRT library: threading & linkage
#if defined(_MT) || defined(__MT__)
# if defined(_DLL)
#  define CPPTL_AUTOLINK_CRT_ "md"
# else
#  define CPPTL_AUTOLINK_CRT_ "mt"
# endif
#else
# define CPPTL_AUTOLINK_CRT_ "ml"
#endif

// Select debug mode
#if defined(_DEBUG)
# define CPPTL_AUTOLINK_DEBUG_MODE_ "d"
#else
# define CPPTL_AUTOLINK_DEBUG_MODE_ ""
#endif

// Select linkage
#if defined(CPPTL_AUTOLINK_DLL)
# define CPPTL_AUTOLINK_LINKAGE_ "dll"
#else
# define CPPTL_AUTOLINK_LINKAGE_ "lib"
#endif

// Automatic link
#if defined(CPPTL_AUTOLINK_TOOLSET_)    && \
    defined(CPPTL_AUTOLINK_CRT_)  && \
    defined(CPPTL_AUTOLINK_LINKAGE_)    && \
    defined(CPPTL_AUTOLINK_DEBUG_MODE_)
# define CPPTL_AUTOLINK_FULL_NAME                                              \
    CPPTL_AUTOLINK_NAME "_" CPPTL_AUTOLINK_TOOLSET_ "_" CPPTL_AUTOLINK_LINKAGE_  \
    CPPTL_AUTOLINK_CRT_ CPPTL_AUTOLINK_DEBUG_MODE_ ".lib"
# pragma comment(lib,CPPTL_AUTOLINK_FULL_NAME)

# if defined(CPPTL_AUTOLINK_VERBOSE)  &&  defined(_MSC_VER)
#  pragma message( "Linking with" CPPTL_AUTOLINK_FULL_NAME )
# endif

#endif

#undef CPPTL_AUTOLINK_TOOLSET_
#undef CPPTL_AUTOLINK_CRT_
#undef CPPTL_AUTOLINK_LINKAGE_
#undef CPPTL_AUTOLINK_DEBUG_MODE_
#undef CPPTL_AUTOLINK_FULL_NAME

