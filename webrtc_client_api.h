#ifndef _WEBRTC_CLIENT_API_H_
#define _WEBRTC_CLIENT_API_H_

#include <stdint.h>

#if defined(_WIN32)
	#if defined(__cplusplus)
		#define RTC_CLIENT_API extern "C" __declspec(dllexport)
	#else
		#define RTC_CLIENT_API __declspec(dllexport)
	#endif
#elif defined(__ANDROID__) || defined(__APPLE__)
	#define DLCA_WEBRTC_API extern "C" __attribute__((visibility("default")))
#endif

enum rtc_decoded_video_frame_type {
	kApiRtcFrameRGB24,
	kApiRtcFrameI420,
	kApiRtcFrameYUY2,
};

typedef void(*rtc_client_frame_callback)(const unsigned char* buffer, int size, int frame_width, int frame_height, 
	rtc_decoded_video_frame_type frame_type, void* priv_data);


struct rtc_client_param {
public:
	rtc_decoded_video_frame_type frame_type_;
	char remote_ip_[64];
	int port_;
	rtc_client_frame_callback frame_callback_;
};

RTC_CLIENT_API int rtc_client_init(const rtc_client_param& param, void* priv_data);

RTC_CLIENT_API void rtc_client_exit();


#endif
