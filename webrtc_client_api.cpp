#include "webrtc_client_api.h"
#include "webrtc_client_impl.h"
#include "tc_common_new/log.h"

#include <sstream>

using namespace tc;

static std::shared_ptr<tc::WebRtcClientImpl> g_rtc_client = nullptr;

RTC_CLIENT_API int rtc_client_init(const rtc_client_param& param, void* priv_data) {
	g_rtc_client = WebRtcClientImpl::Make();
	auto client_param = WebRtcClientParam{};
	client_param.remote_ip_ = std::string(param.remote_ip_);
	client_param.port_ = param.port_;
	client_param.frame_type_ = (RtcDecodedVideoFrame::RtcFrameType)param.frame_type_;
	client_param.frame_callback_ = [=](std::shared_ptr<RtcDecodedVideoFrame>&& frame) {
		if (param.frame_callback_) {
			LOGI("-----xx--->" + std::to_string(frame->buffer_.size()));
			param.frame_callback_(frame->buffer_.data(), frame->buffer_.size(), frame->frame_width_, frame->frame_height_, param.frame_type_, priv_data);
		}
	};
	g_rtc_client->Init(client_param);
	return 0;
}

RTC_CLIENT_API void rtc_client_exit() {
	if (g_rtc_client) {
		g_rtc_client->Exit();
	}
}