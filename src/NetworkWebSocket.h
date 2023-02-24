#pragma once

#ifndef __NETWORKWEBSOCKET_HPP
#define __NETWORKWEBSOCKET_HPP

#include "cocos2d.h"
#include "cocos-ext.h"
#include <functional>

using namespace cocos2d;
using namespace std;

class NetworkWebSocket : public cocos2d::extension::WebSocket::Delegate
{
public:
	typedef function<void(string message)> MessageRecivedCallBack;
	typedef function<void()> ConnectionClosedCallBack;
	typedef function<void(const cocos2d::extension::WebSocket::ErrorCode& error)> ErrorOccurredCallBack;
	typedef function<void()> ConnectionOpenedCallBack;

	static NetworkWebSocket* create(string url);

	NetworkWebSocket(string url);
	~NetworkWebSocket();

	string getUrl();

	
	cocos2d::extension::WebSocket* getSocket();
	cocos2d::extension::WebSocket::State getState();

	bool connect();
	bool close();

	bool send(string message);

	void setOnMessageReceivedCallBack(MessageRecivedCallBack callBack);
	void setOnConnectionClosedCallBack(ConnectionClosedCallBack callBack);
	void setOnErrorOccurredCallBack(ErrorOccurredCallBack callBack);
	void setOnConnectionOpenedCallBack(ConnectionOpenedCallBack callBack);
private:
	cocos2d::extension::WebSocket* _socket = nullptr;
	string _url = "";
	vector<string> _pendingMessages;

	virtual void onOpen(cocos2d::extension::WebSocket* ws);
	virtual void onMessage(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::Data& data);
	virtual void onError(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::ErrorCode& error);
	virtual void onClose(cocos2d::extension::WebSocket* ws);

	MessageRecivedCallBack _onMessageReceivedCallBack;
	ConnectionClosedCallBack _onConnectionClosedCallBack;
	ErrorOccurredCallBack _onErrorOccurredCallBack;
	ConnectionOpenedCallBack _onConnectionOpenedCallBack;
};

#endif