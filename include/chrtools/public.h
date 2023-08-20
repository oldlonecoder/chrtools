#pragma once

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   pragma warning(disable : 4996)
//#   pragma warning(disable : 4005)
//#   pragma warning(disable : 4267)
#   pragma warning(disable : 4251)
//class __declspec(dllimport) std::thread;
#   define _CRT_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS

#   ifdef STR_EXPORTS
#       define STR_PUBLIC __declspec(dllexport)
#   else
#       define STR_PUBLIC __declspec(dllimport)
#   endif
#   define NOMINMAX
#   include <Windows.h> // Must be included before anything else
#   include <shlwapi.h>
#   include <winsqlite/winsqlite3.h> // Ne fonctionne plus, allez savoir! -- La on sait : C'est mon cerveau qui ne fonctionnait plus!


#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#       define STR_PUBLIC
#endif

//---------------------------------------------
#include <cstdint>
#include <thread>
// --  Basic pseudo reflexion macros : --
#ifndef CLASSNAME
# define CLASSNAME(CLASS) \
    public:\
        virtual const char*  class_name() const noexcept\
        {\
            return #CLASS;\
        }\
    private:
#endif

#ifndef CLASSNAME_D
# define CLASSNAME_D(CLASS) \
    public:\
        const char*  class_name() const noexcept override\
        {\
            return #CLASS;\
        }\
    private:
#endif

#ifndef CLASSNAME_A
# define CLASSNAME_A(CLASS) \
    public:\
        const char*  class_name()\
        {\
            return #CLASS;\
        }\
    private:
#endif

//----------------------------------------------------------------------------
