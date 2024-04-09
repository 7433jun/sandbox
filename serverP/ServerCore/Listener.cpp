#include "pch.h"
#include "Listener.h"
#include "Service.h"

Listener::Listener()
{
	iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);
}

Listener::~Listener()
{
	CloseSocket();
}

bool Listener::StartAccept(Service& service)
{
	socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (socket == INVALID_SOCKET)
		return false;

	// 家南 SO_REUSEADDR 可记 眠啊
	bool enable = true;
	if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable)) == SOCKET_ERROR)
		return false;

	// 家南 LINGER 可记 眠啊
	LINGER linger;
	linger.l_onoff = 0;
	linger.l_linger = 0;
	if (setsockopt(socket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger)) == SOCKET_ERROR)
		return false;

	if (bind(socket, (SOCKADDR*)&service.GetSockAddr(), sizeof(service.GetSockAddr())) == SOCKET_ERROR)
		return false;

	if (listen(socket, SOMAXCONN) == SOCKET_ERROR)
		return false;

	printf("listening...\n");

	DWORD dwBytes;


	if (WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx),
		&lpfnAcceptEx, sizeof(lpfnAcceptEx), &dwBytes, NULL, NULL) == SOCKET_ERROR)
		return false;

	SOCKET acceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (acceptSocket == INVALID_SOCKET)
		return false;

	ULONG_PTR key = 0;
	CreateIoCompletionPort((HANDLE)socket, iocpHandle, key, 0);

	char lpOutputBuf[1024];
	WSAOVERLAPPED overlapped = {};

	if (lpfnAcceptEx(socket, acceptSocket, lpOutputBuf, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &dwBytes, &overlapped) == FALSE)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
			return false;
	}

	return true;
}

void Listener::CloseSocket()
{
	if (socket != INVALID_SOCKET)
	{
		closesocket(socket);
		socket = INVALID_SOCKET;
	}
}