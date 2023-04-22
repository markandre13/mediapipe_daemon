#pragma once

#include "EventHandler.hh"
#include <wslay/wslay.h>

class EchoWebSocketHandler : public EventHandler
{
public:
    EchoWebSocketHandler(int fd);
    virtual ~EchoWebSocketHandler();
    virtual int on_read_event() { return wslay_event_recv(ctx_) == 0 ? 0 : -1; }
    virtual int on_write_event() { return wslay_event_send(ctx_) == 0 ? 0 : -1; }

    ssize_t send_data(const uint8_t *data, size_t len, int flags);
    ssize_t recv_data(uint8_t *data, size_t len, int flags);

    virtual bool want_read() { return wslay_event_want_read(ctx_); }
    virtual bool want_write() { return wslay_event_want_write(ctx_); }
    virtual int fd() const { return fd_; }
    virtual bool finish() { return !want_read() && !want_write(); }
    virtual EventHandler *next() { return 0; }

private:
    int fd_;
    wslay_event_context_ptr ctx_;
};
