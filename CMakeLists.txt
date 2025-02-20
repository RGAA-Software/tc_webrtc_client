cmake_minimum_required(VERSION 3.26)

project(tc_rtc)

set(WEBRTC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../tc_3rdparty/webrtc)
include_directories(${WEBRTC_ROOT}/include)
include_directories(${WEBRTC_ROOT}/include/third_party/abseil-cpp)
include_directories(${WEBRTC_ROOT}/include/third_party/jsoncpp/source/include/)
include_directories(${WEBRTC_ROOT}/include/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
if(MSVC)
    add_compile_options($<IF:$<CONFIG:Debug>,/MTd,/MT>)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

if (WIN32)
    add_definitions(-DWEBRTC_WIN=1 -DWEBRTC_USE_H264=1)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN -DNOMINMAX)
    add_definitions(-DQT_DEPRECATED_WARNINGS -DQT_NO_KEYWORDS)
    link_directories(${WEBRTC_ROOT}/lib/x64)
elseif (APPLE)

elseif (ANDROID)
elseif (UNIX)
endif ()

set(SRCS
    webrtc_client_impl.cpp
    webrtc_client_api.cpp
    observers/create_session_desc_observer_impl.cpp
    observers/data_channel_observer_impl.cpp
    observers/peer_conn_observer_impl.cpp
    observers/set_session_desc_observer_impl.cpp
    observers/video_frame_observer.cpp
)

add_library(${PROJECT_NAME} ${SRCS})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${WEBRTC_ROOT}/lib/win64/webrtc.lib
            Winmm ws2_32 Secur32 Crypt32 Msdmo dmoguids tc_common_new
            wmcodecdspuuid Iphlpapi.lib Strmiids Quartz Ole32
    )
elseif (APPLE)

elseif (ANDROID)
elseif (UNIX)
endif ()