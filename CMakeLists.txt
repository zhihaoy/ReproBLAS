cmake_minimum_required(VERSION 3.17)

project(reproBLAS LANGUAGES C)

include(GenerateExportHeader)

option(BUILD_SHARED_LIBS "Build shared library" ON)

if(BUILD_SHARED_LIBS)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
set(CMAKE_VS_JUST_MY_CODE_DEBUGGING ON)
if(MSVC)
	foreach(flagvar
	    CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS_RELWITHDEBINFO)
		string(REGEX REPLACE "/Ob1" "/Ob2" ${flagvar} "${${flagvar}}")
	endforeach()
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/W3>)
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/w34389>)
else()
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wall>)
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wconversion>)
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wsign-conversion>)
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wsign-compare>)
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color>)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_subdirectory(src/binned)
add_subdirectory(src/binnedBLAS)
add_subdirectory(src/reproBLAS)

target_sources(binned PRIVATE include/binned.h)
target_sources(binnedBLAS PRIVATE include/binnedBLAS.h)
target_sources(reproBLAS PRIVATE include/reproBLAS.h)

target_link_libraries(reproBLAS PRIVATE binned binnedBLAS)

generate_export_header(reproBLAS
    EXPORT_MACRO_NAME REPROBLAS_API
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/reproBLAS_api.h)

set_target_properties(reproBLAS PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    INSTALL_RPATH_USE_LINK_PATH TRUE
    BUILD_RPATH_USE_ORIGIN TRUE)

if(BUILD_TESTING)
endif()
