#pragma once

#ifndef __SERVERLISTENER_H
#define __SERVERLISTENER_H

#include "cocos2d.h"
#include "includes.h"
#include "network/WebSocket.h"
#include "NetworkWebSocket.h"


class ServerListener { 

protected:

    static ServerListener* _listener;

public:

    static ServerListener* instance();
    ServerListener();
    void sendMessage(std::string);

private:
    NetworkWebSocket* _webSocket = nullptr;

    void onConnectionOpened();
    void onMessageReceived(string message);
    void onConnectionClosed();
    void onConnectionError(const cocos2d::extension::WebSocket::ErrorCode& error);
};

#endif