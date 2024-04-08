#include "pch.h"
#include <Service.h>

// 비동기 I/O 작업을 처리하는 스레드 함수
void AcceptThread(HANDLE iocpHandle)
{
	DWORD bytesTransferred = 0;
	ULONG_PTR key = 0;
	WSAOVERLAPPED overlapped = {};

	while (true)
	{
		printf("Waiting...\n");
		if (GetQueuedCompletionStatus(iocpHandle, &bytesTransferred, &key, (LPOVERLAPPED*)&overlapped, INFINITE))
		{
			printf("Client Connected\n");

		}
	}
}

int main()
{
	printf("==== SERVER ====\n");

	Service service(L"127.0.0.1", 27015);

	// 리슨 소켓 생성
	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("socket function failed with error : %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// listenSocket에 주소 등록
	if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("bind failed with error : %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// 수신 대기
	if (listen(listenSocket, 10) == SOCKET_ERROR)
	{
		printf("listen failed with error : %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	printf("listening...\n");


	DWORD dwBytes;
	LPFN_ACCEPTEX lpfnAcceptEx = NULL;
	GUID guidAcceptEx = WSAID_ACCEPTEX;

	// 함수 포인터에다가 값을 넣어줌
	// WSAIoctl(소켓, 제어코드, 입력버퍼, 입력 버퍼 크기, 출력 버퍼 포인터, 출력 버퍼 크기, 실제 출력 바이트수, NULL, NULL);
	// WSAIoctl(소켓, 제어코드, GUID, GUID크기, accept함수포인터, LPFN_ACCEPTEX크기, 실제 출력 바이트수, NULL, NULL);
	if (WSAIoctl(listenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx),
		&lpfnAcceptEx, sizeof(lpfnAcceptEx), &dwBytes, NULL, NULL) == SOCKET_ERROR)
	{
		printf("WSAIoctl failed with error : %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// 클라이언트와 연결 수락할 소켓을 미리 생성
	SOCKET acceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (acceptSocket == INVALID_SOCKET)
	{
		printf("Accept Socket failed with error : %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// IOCP 핸들 생성, 초기화
	HANDLE iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);
	thread t(AcceptThread, iocpHandle);

	ULONG_PTR key = 0;
	CreateIoCompletionPort((HANDLE)listenSocket, iocpHandle, key, 0);

	char lpOutputBuf[1024];

	WSAOVERLAPPED overlapped = {};

	// 비동기 Accept
	// lpfnAcceptEx(listen 소켓, accept 소켓, 설정값..., overlapped)
	if (lpfnAcceptEx(listenSocket, acceptSocket, lpOutputBuf, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &dwBytes, &overlapped) == FALSE)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			printf("AcceptEx failed with error : %d\n", WSAGetLastError());
			closesocket(acceptSocket);
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}
	}


	t.join();

	// 소켓 닫기
	closesocket(listenSocket);
	// 해제
	WSACleanup();

	return 0;
}