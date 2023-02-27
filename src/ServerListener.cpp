#include "ServerListener.h"
#include "Callback.h"
#include <CocoStudio/Json/rapidjson/document.h>
#include "Utils.h"
#include <chrono>
#include <thread>

ServerListener::ServerListener()
{
    _listener = this;
    if (_listener != nullptr) {
        std::thread thread([] {
            _listener->_webSocket = NetworkWebSocket::create("24.199.87.19:4732");
            //_listener->_webSocket = NetworkWebSocket::create("127.0.0.1:4732");
            if (_listener->_webSocket->connect()) {
                _listener->_webSocket->setOnConnectionOpenedCallBack(CC_CALLBACK_0(ServerListener::onConnectionOpened, _listener));
                _listener->_webSocket->setOnMessageReceivedCallBack(CC_CALLBACK_1(ServerListener::onMessageReceived, _listener));
                _listener->_webSocket->setOnConnectionClosedCallBack(CC_CALLBACK_0(ServerListener::onConnectionClosed, _listener));
                _listener->_webSocket->setOnErrorOccurredCallBack(CC_CALLBACK_1(ServerListener::onConnectionError, _listener));
            }
            _listener->sendMessage("name: " + std::string(gd::GJAccountManager::sharedState()->getUsername()));
          
        });
        thread.detach();
    }
}

ServerListener::~ServerListener() {
    delete _webSocket;
}

void ServerListener::sendMessage(std::string msg) {
    this->_webSocket->send(msg);
}


void ServerListener::onConnectionOpened()
{
    
}


void ServerListener::onMessageReceived(string message)
{
    gd::PlayLayer* playLayer = gd::GameManager::sharedState()->getPlayLayer();

    if (message == "dead") {
        if (playLayer != nullptr) {
            playLayer->destroyPlayer(playLayer->m_pPlayer1, nullptr);
        }
    }
}


void ServerListener::onConnectionClosed()
{
    _listener = nullptr;
    this->instance();
}

void ServerListener::onConnectionError(const cocos2d::extension::WebSocket::ErrorCode& error)
{
    string errorCodeValue = "";
    switch (error)
    {
    case cocos2d::extension::WebSocket::ErrorCode::kErrorConnectionFailure:
        errorCodeValue = "CONNECTION_FAILURE";
        break;
    case cocos2d::extension::WebSocket::ErrorCode::kErrorTimeout:
        errorCodeValue = "TIME_OUT";
        break;
    case cocos2d::extension::WebSocket::ErrorCode::kErrorUnknown:
        errorCodeValue = "UNKNOWN";
        break;
    }
}

ServerListener* ServerListener::_listener = nullptr;

ServerListener* ServerListener::instance() {

    if (_listener == nullptr) {
        delete _listener;
        _listener = new ServerListener();
    }

    return _listener;
}

