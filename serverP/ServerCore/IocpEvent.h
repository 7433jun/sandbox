#pragma once

enum class EventType : uint8
{
	CONNECT,
	DISCONNECT,
	ACCEPT,
	RECV,
	SEND,

};

class IocpObj;
class Session;

class IocpEvent : public OVERLAPPED
{
public:
	EventType eventType;
	shared_ptr<IocpObj> iocpObj;
public:
	IocpEvent(EventType type);
public:
	void Init();
};

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::CONNECT) {}
};

class DisconnectEvent : public IocpEvent
{
public:
	DisconnectEvent() : IocpEvent(EventType::DISCONNECT) {}
};

class AcceptEvent : public IocpEvent
{
public:
	shared_ptr<Session> session = nullptr;
public:
	AcceptEvent() : IocpEvent(EventType::ACCEPT) {}
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::RECV) {}
};

class SendEvent : public IocpEvent
{
public:
	// SendBuffer class ·Î º¯È¯
	vector<shared_ptr<class SendBuffer>> sendBuffers;
public:
	SendEvent() : IocpEvent(EventType::SEND) {}
};