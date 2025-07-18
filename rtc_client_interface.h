//
// Created by RGAA on 13/04/2025.
//

#ifndef GAMMARAY_RTC_CLIENT_INTERFACE_H
#define GAMMARAY_RTC_CLIENT_INTERFACE_H

#include <memory>
#include <string>
#include <functional>

namespace tc
{

    class Data;

    using OnLocalSdpSetCallback = std::function<void(const std::string&)>;
    using OnLocalIceCallback = std::function<void(const std::string& ice, const std::string& mid, int sdp_mline_index)>;

    using OnMediaMessageCallback = std::function<void(std::shared_ptr<Data>)>;
    using OnFtMessageCallback = std::function<void(std::shared_ptr<Data>)>;

    class RtcClientInterface {
    public:
        virtual bool Init(const std::string& remote_device_id) {
            return false;
        }

        virtual bool Exit() {
            return false;
        }

        virtual bool OnRemoteSdp(const std::string& sdp) {
            return false;
        }

        virtual bool OnRemoteIce(const std::string& ice, const std::string& mid, int32_t sdp_mline_index) {
            return false;
        }

        virtual void SetOnLocalSdpSetCallback(OnLocalSdpSetCallback&& cbk) {
            local_sdp_set_cbk_ = cbk;
        }

        virtual void SetOnLocalIceCallback(OnLocalIceCallback&& cbk) {
            local_ice_cbk_ = cbk;
        }

        virtual void PostMediaMessage(std::shared_ptr<Data> msg) = 0;
        virtual void PostFtMessage(std::shared_ptr<Data> msg) = 0;

        virtual void SetMediaMessageCallback(const OnMediaMessageCallback& cbk) {
            media_msg_cbk_ = cbk;
        }

        virtual void SetFtMessageCallback(const OnFtMessageCallback& cbk) {
            ft_msg_cbk_ = cbk;
        }

        virtual int64_t GetQueuingMediaMsgCount() = 0;
        virtual int64_t GetQueuingFtMsgCount() = 0;

        virtual bool HasEnoughBufferForQueuingMediaMessages() = 0;
        virtual bool HasEnoughBufferForQueuingFtMessages() = 0;

        virtual bool IsMediaChannelReady() = 0;
        virtual bool IsFtChannelReady() = 0;

        virtual void On16msTimeout() {}

    protected:
        std::string remote_device_id_;

        OnLocalSdpSetCallback local_sdp_set_cbk_;
        OnLocalIceCallback local_ice_cbk_;

        OnMediaMessageCallback media_msg_cbk_;
        OnFtMessageCallback ft_msg_cbk_;
    };

}

#endif //GAMMARAY_RTC_CLIENT_INTERFACE_H
