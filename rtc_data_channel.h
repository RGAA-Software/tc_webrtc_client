//
// Created by RGAA
//

#ifndef TC_DATA_CHANNEL_OBSERVER_H
#define TC_DATA_CHANNEL_OBSERVER_H
#include <atomic>
#include <vector>
#include "tc_common_new/webrtc_helper.h"

namespace tc
{

    using OnDataCallback = std::function<void(const std::string&)>;

    class RtcConnection;

    class NetTlvMessage {
    public:
        uint32_t type_{0};
        std::string buffer_;
    };

    class RtcDataChannel :  public webrtc::DataChannelObserver {
    public:
        RtcDataChannel(RtcConnection* client, rtc::scoped_refptr<webrtc::DataChannelInterface> ch, const std::string& name);
        ~RtcDataChannel();

        void OnStateChange() override;
        void OnMessage(const webrtc::DataBuffer& buffer) override;
        void OnBufferedAmountChange(uint64_t sent_data_size) override;
        bool IsConnected();
        void SendData(const std::string& data);
        int GetPendingDataCount();
        void SetExitViaReconnect(bool reconn) { exit_via_reconnect_ = reconn; }
        void Close();

        bool HasEnoughBufferForQueuingMessages();
        void SetOnDataCallback(OnDataCallback&& cbk);

    private:
        rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel_ = nullptr;
        std::atomic<bool> connected_ = false;
        RtcConnection* client_ = nullptr;
        std::atomic<int> pending_data_count_ = 0;  //只是表达排队数,并没有关心data发送是否成功
        bool exit_via_reconnect_ = false;
        OnDataCallback data_cbk_;
        std::vector<NetTlvMessage> cached_messages_;
        std::string name_;
        std::atomic<uint64_t> send_pkt_index_ = 0;
        std::atomic<uint64_t> last_recv_pkt_index_ = 0;

        // test beg //
        uint64_t total_recv_content_bytes_ = 0;
        // test end //
    };

} // namespace dl

#endif //TEST_WEBRTC_DATA_CHANNEL_OBSERVER_IMPL_H
