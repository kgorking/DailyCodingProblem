cmake_minimum_required(VERSION 3.24)

project (DailyCodingProblem CXX)
add_library(DailyCodingProblem INTERFACE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cppcoro REQUIRED)
target_link_libraries(DailyCodingProblem INTERFACE cppcoro)

# Include sub-projects.
add_subdirectory ("intro")
add_subdirectory ("day1_find_pair_sum")
add_subdirectory ("day2_exclusive_product")

if (MSVC)
    target_compile_options(DailyCodingProblem INTERFACE
        /std:c++latest

        # enable lots of warnings
        /W4

		# allow `import std.core`
		/experimental:module

        # treat warnings as errors
        #/WX

        # -- Dump compilation info ---
        #/Bt                     # total time spent in frontend (d1) and backend (d2)
        #/d1templateStats        # show info regarding template use
        #/d1reportTimeSummary    # show frontend compile time summary
        #/d1reportTime           # show (very) detailed frontend compile time info
        #/d2cgsummary            # show backend compile time summary

        # -- Enable conversion warnings --
        /w44191     # 'operator': unsafe conversion from 'type_of_expression' to 'type_required'.
        /w44242     # 'identifier': conversion from 'type1' to 'type2', possible loss of data.
        /w44254     # 'operator': conversion from 'type1' to 'type2', possible loss of data.
        /w44800     # Implicit conversion from 'type' to bool. Possible information loss.
        /w44826     # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
        /w45219     # implicit conversion from 'type-1' to 'type-2', possible loss of data.
        /w44388     # signed/unsigned mismatch
        #/w44365     # 'action': conversion from 'type_1' to 'type_2', signed/unsigned mismatch.

		# Shows the layout of the struct name 'chunk'
		#/d1reportSingleClassLayoutchunk

        # Enable address sanitizer
        #/fsanitize=address
    )

    # enable profiling
    #target_compile_options(ecs INTERFACE /Zi)
    #target_link_options(ecs INTERFACE /PROFILE)

    # Disable C++ exceptions.
    #string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c-")
    #add_definitions(-D_HAS_EXCEPTIONS=0)

    # Disable RTTI.
    #string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
else()
    # lots of warnings
    target_compile_options(DailyCodingProblem INTERFACE
        -std=c++2a
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        #-Wsign-conversion
        #-ftime-trace  # produce json flamegraph files. open with chrome://tracing or edge://tracing
	)
    target_link_options(DailyCodingProblem INTERFACE -pthread)

    # Disable C++ exceptions.
    # - fails to compile on gcc 10
    if (Clang)
        string(REGEX REPLACE "-fexceptions" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
    endif()

    # Disable RTTI.
    # - clang's std::function::target needs rtti -_-
    if (GNU)
        string(REGEX REPLACE "-frtti" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
    endif()
endif()
