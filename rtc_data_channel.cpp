//
// Created by RGAA
//

#include "rtc_data_channel.h"
#include "tc_common_new/log.h"
#include "tc_common_new/net_tlv_header.h"

namespace tc
{

    RtcDataChannel::RtcDataChannel(RtcConnection* client, rtc::scoped_refptr<webrtc::DataChannelInterface> ch, const std::string& name) {
        this->client_ = client;
        this->data_channel_ = ch;
        this->data_channel_->RegisterObserver(this);
        this->name_ = name;
    }

    RtcDataChannel::~RtcDataChannel() {
        this->data_channel_->UnregisterObserver();
    }

    void RtcDataChannel::OnStateChange() {
        if (exit_via_reconnect_) {
            return;
        }
        if (data_channel_->state() == webrtc::DataChannelInterface::kOpen) {
            connected_ = true;
            //context_->SendAppMessage(ClientEvtDataChannelReady{});

        } else if (data_channel_->state() == webrtc::DataChannelInterface::kClosed) {
            connected_ = false;
            //context_->SendAppMessage(ClientEvtDataChannelClosed{});

        }
        LOGI("DataChannel state changed: {}, connected: {}", (int)data_channel_->state(), connected_);
    }

    void RtcDataChannel::OnMessage(const webrtc::DataBuffer &buffer) {
        //LOGI("DataChannel Message: {}", buffer.size());
        auto header = (NetTlvHeader*)buffer.data.data();

        std::string data;
        data.resize(header->this_buffer_length_);
        memcpy(data.data(), (char*)header + sizeof(NetTlvHeader), header->this_buffer_length_);

        if (header->type_ == kNetTlvFull) {
            if (data_cbk_) {
                data_cbk_(data);
            }
        }
        else {
            LOGI("DataChannel message type: {}", header->type_);
            if (header->type_ == kNetTlvBegin) {
                cached_messages_.clear();
            }
            cached_messages_.push_back(NetTlvMessage {
                .type_ = header->type_,
                .buffer_ = data,
            });

            if (header->type_ == kNetTlvEnd) {
                uint32_t total_size = 0;
                for (const auto& m : cached_messages_) {
                    total_size += (uint32_t)m.buffer_.size();
                }

                std::string total_data;
                total_data.resize(total_size);
                uint32_t offset = 0;
                for (const auto& m : cached_messages_) {
                    memcpy((char*)total_data.data() + offset, m.buffer_.data(), m.buffer_.size());
                    offset += m.buffer_.size();
                }
                if (data_cbk_) {
                    data_cbk_(total_data);
                }
                cached_messages_.clear();
            }
        }
    }

    void RtcDataChannel::OnBufferedAmountChange(uint64_t sent_data_size) {
        DataChannelObserver::OnBufferedAmountChange(sent_data_size);
        //LOGI("OnBufferAmount changed: {}", sent_data_size);
    }

    bool RtcDataChannel::IsConnected() {
        return connected_;
    }

    void RtcDataChannel::SendData(const std::string& msg) {
        if (!connected_) {
            LOGW("DataChannel is invalid: {}", name_);
            return;
        }
        ++pending_data_count_;
        this->data_channel_->Send(webrtc::DataBuffer(msg));
        //RLogI("send data via data channel: {}", msg.size());
        --pending_data_count_;
        if (name_ == "ft_data_channel") {
            //LOGI("send data via data channel, size: {}, pending count: {}", msg.size(), pending_data_count_);
        }
    }

    int RtcDataChannel::GetPendingDataCount() {
        return pending_data_count_;
    }

    void RtcDataChannel::Close() {
        LOGI("RtcDataChannel Close!");
        if (data_channel_) {
            data_channel_->Close();
        }
        connected_ = false;
    }

    void RtcDataChannel::SetOnDataCallback(OnDataCallback&& cbk) {
        data_cbk_ = cbk;
    }

} // namespace dl