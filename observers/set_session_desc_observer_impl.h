//
// Created by RGAA on 2024/2/18.
//

#ifndef TEST_WEBRTC_SET_SESSION_DESC_OBSERVER_IMPL_H
#define TEST_WEBRTC_SET_SESSION_DESC_OBSERVER_IMPL_H

#include "webrtc_helper.h"

namespace tc
{
    class WebRtcClientImpl;

    class SetSessionDescObserverImpl : public webrtc::SetSessionDescriptionObserver {
    public:

        static rtc::scoped_refptr<SetSessionDescObserverImpl> Make(const std::shared_ptr<WebRtcClientImpl>& client);
        SetSessionDescObserverImpl(const std::shared_ptr<WebRtcClientImpl>& client);

        // overrides
        void OnSuccess() override;

        void OnFailure(webrtc::RTCError error) override;

    private:

        std::shared_ptr<WebRtcClientImpl> webrtc_client_ = nullptr;

    };

}

#endif //TEST_WEBRTC_SET_SESSION_DESC_OBSERVER_IMPL_H
