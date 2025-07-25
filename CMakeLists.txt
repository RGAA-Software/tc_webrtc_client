project(tc_rtc_client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DWEBRTC_WIN=1 -DWEBRTC_USE_H264=1)
add_definitions(-D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN -DNOMINMAX)
add_definitions(-DQT_DEPRECATED_WARNINGS -DQT_NO_KEYWORDS) #

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#target_compile_options(${PROJECT_NAME}
#        PRIVATE
#        $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
#        $<$<CXX_COMPILER_ID:GNU>:-Wa,-mbig-obj>)

#set(WEBRTC_ROOT ${GR_PROJECT_PATH}/deps/tc_3rdparty/webrtc)
include_directories(${WEBRTC_ROOT}/)
include_directories(${WEBRTC_ROOT}/include)
include_directories(${WEBRTC_ROOT}/include/third_party/abseil-cpp)
include_directories(${WEBRTC_ROOT}/include/third_party/jsoncpp/source/include/)
include_directories(${WEBRTC_ROOT}/include/base)
link_directories(${GR_PROJECT_PATH}/deps/tc_3rdparty/webrtc/x64)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(PLUGIN_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/peer_callback.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rtc_connection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rtc_data_channel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rtc_client_interface.cpp
)

add_library(${PROJECT_NAME} SHARED ${PLUGIN_SRCS})
#add_library(${PROJECT_NAME} ${PLUGIN_SRCS})
target_link_libraries(${PROJECT_NAME} PUBLIC tc_common_new Qt6::Core
        ${WEBRTC_ROOT}/x64/webrtc.lib
        Winmm
        ws2_32
        Secur32
        Crypt32
        Msdmo
        dmoguids
        wmcodecdspuuid Iphlpapi.lib
        dxgi d3d11 d3d12 dxguid Strmiids Quartz Ole32
        Shcore.lib Dwmapi.lib
)