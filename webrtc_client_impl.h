////
//// Created by RGAA on 2024/2/1.
////
//
#ifndef WEBRTC_WEBRTC_CLIENT_H
#define WEBRTC_WEBRTC_CLIENT_H

#include "webrtc_helper.h"
#include "observers/video_frame_observer.h"

namespace tc
{

    class PeerConnObserverImpl;
    class SetSessionDescObserverImpl;
    class CreateSessionDescObserverImpl;

    class WebRtcClientParam {
    public:
        RtcDecodedVideoFrame::RtcFrameType frame_type_;
        std::string remote_ip_;
        int port_;
        OnFrameCallback frame_callback_;
    };

    class WebRtcClientImpl : public std::enable_shared_from_this<WebRtcClientImpl> {
    public:

        static std::shared_ptr<WebRtcClientImpl> Make();

        WebRtcClientImpl();
        void Init(const WebRtcClientParam& param);
        void Exit();

        std::shared_ptr<PeerConnObserverImpl> GetPeerConnObserver();
        std::shared_ptr<VideoFrameObserver> GetVideoFrameObserver();
        rtc::scoped_refptr<SetSessionDescObserverImpl> GetSetSessionDescObserver();
        rtc::scoped_refptr<CreateSessionDescObserverImpl> GetCreateSessionDescObserver();
        rtc::scoped_refptr<webrtc::PeerConnectionInterface> GetPeerConnection();
        void SetPeerConnection(const rtc::scoped_refptr<webrtc::PeerConnectionInterface>& pc);

        // callbacks
        void OnSessionCreated(webrtc::SessionDescriptionInterface *desc);
        void OnIceCandidate(const webrtc::IceCandidateInterface *candidate);
        void OnIceGatheringComplete();
        void OnTrack(rtc::scoped_refptr<webrtc::RtpTransceiverInterface> transceiver);

    private:
        void RequestRemoteSDP();
        static void CreateSomeMediaDeps(webrtc::PeerConnectionFactoryDependencies& media_deps);
        void InitPeerConnectionFactory();
        void InitPeerConnection();

    private:
        std::string sdp_;
        WebRtcClientParam client_param_;
        std::shared_ptr<PeerConnObserverImpl> peer_conn_observer_ = nullptr;
        std::shared_ptr<VideoFrameObserver> video_frame_observer_ = nullptr;
        rtc::scoped_refptr<SetSessionDescObserverImpl> set_session_desc_observer_ = nullptr;
        rtc::scoped_refptr<CreateSessionDescObserverImpl> create_session_desc_observer_ = nullptr;
        rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_conn_ = nullptr;
        std::unique_ptr<rtc::Thread> network_thread_;
        std::unique_ptr<rtc::Thread> worker_thread_;
        std::unique_ptr<rtc::Thread> signaling_thread_;
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
        webrtc::PeerConnectionInterface::RTCConfiguration configuration_;
    };

}

#endif