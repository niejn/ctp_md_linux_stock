cmake_minimum_required(VERSION 3.9)
project(ctp_md_linux)

set(CMAKE_CXX_STANDARD 14)
add_library(Mdapi SHARED IMPORTED)
SET_PROPERTY(TARGET Mdapi PROPERTY IMPORTED_LOCATION ./v1.0_20160628_api_tradeapi_linux64/thostmduserapi.so)

set(SOURCE_FILES
        main.cpp
        md/MdSpi.h
        md/MdSpi.cpp
        v1.0_20160628_api_tradeapi_linux64/ThostFtdcMdApi.h
        v1.0_20160628_api_tradeapi_linux64/ThostFtdcUserApiDataType.h
        v1.0_20160628_api_tradeapi_linux64/ThostFtdcUserApiStruct.h)
include_directories(.)
include_directories(md)
include_directories(v1.0_20160628_api_tradeapi_linux64)


#add_executable(ctp_md_linux main.cpp)
add_executable(ctp_md_linux ${SOURCE_FILES})
target_link_libraries(ctp_md_linux Mdapi)
#find_package(Threads REQUIRED)
#target_link_libraries(ctp_md_linux Threads::Threads)