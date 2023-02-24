#include "NetworkWebSocket.h"

NetworkWebSocket* NetworkWebSocket::create(string url)
{
	auto socket = new NetworkWebSocket(url);

	return socket;
}

NetworkWebSocket::NetworkWebSocket(string url)
{
	this->_url = url;
}

NetworkWebSocket::~NetworkWebSocket()
{
	this->_socket->close();
}

string NetworkWebSocket::getUrl()
{
	return this->_url;
}

cocos2d::extension::WebSocket* NetworkWebSocket::getSocket()
{
	return this->_socket;
}

cocos2d::extension::WebSocket::State NetworkWebSocket::getState()
{
	if (this->_socket != nullptr)
		return this->_socket->getReadyState();

	return cocos2d::extension::WebSocket::State();
}

bool NetworkWebSocket::connect()
{
	try
	{
		this->_socket = new cocos2d::extension::WebSocket();

		return this->_socket->init(*this, this->_url);
	}
	catch (const std::exception&)
	{
		throw;
	}

	return false;
}

bool NetworkWebSocket::close()
{
	try
	{
		if (this->_socket != nullptr && this->_socket->getReadyState() == cocos2d::extension::WebSocket::State::kStateOpen)
			this->_socket->close();

		return true;
	}
	catch (const std::exception&)
	{
		throw;
	}

	return false;
}

bool NetworkWebSocket::send(string message)
{
	try
	{
        if (this != nullptr) {
            if (this->_socket != nullptr) {
                if (this->_socket->getReadyState() == cocos2d::extension::WebSocket::State::kStateOpen)
                    this->_socket->send(message);
                else if (this->_socket->getReadyState() == cocos2d::extension::WebSocket::State::kStateConnecting)
                    this->_pendingMessages.push_back(message);
            }

            return true;
        }
	}
	catch (const std::exception&)
	{
		throw;
	}

	return false;
}

void NetworkWebSocket::setOnMessageReceivedCallBack(MessageRecivedCallBack callBack)
{
	this->_onMessageReceivedCallBack = callBack;
}

void NetworkWebSocket::setOnConnectionClosedCallBack(ConnectionClosedCallBack callBack)
{
	this->_onConnectionClosedCallBack = callBack;
}

void NetworkWebSocket::setOnErrorOccurredCallBack(ErrorOccurredCallBack callBack)
{
	this->_onErrorOccurredCallBack = callBack;
}

void NetworkWebSocket::setOnConnectionOpenedCallBack(ConnectionOpenedCallBack callBack)
{
	this->_onConnectionOpenedCallBack = callBack;
}

void NetworkWebSocket::onOpen(cocos2d::extension::WebSocket* ws)
{
	if (this->_pendingMessages.size() > 0) {
		for (string message : _pendingMessages)
			send(message);

		this->_pendingMessages.clear();
	}

	if (_onConnectionOpenedCallBack != nullptr)
		_onConnectionOpenedCallBack();
}

void NetworkWebSocket::onMessage(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::Data& data)
{
	if (_onMessageReceivedCallBack != nullptr)
		_onMessageReceivedCallBack(std::string(data.bytes, data.len));
}

void NetworkWebSocket::onClose(cocos2d::extension::WebSocket* ws)
{
	if (_onConnectionClosedCallBack != nullptr)
		_onConnectionClosedCallBack();
}

void NetworkWebSocket::onError(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::ErrorCode& error)
{
	if (_onErrorOccurredCallBack != nullptr)
		_onErrorOccurredCallBack(error);
}