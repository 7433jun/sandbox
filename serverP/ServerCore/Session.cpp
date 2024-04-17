#include "pch.h"
#include "Session.h"
#include "SocketHelper.h"
#include "Service.h"

Session::Session()
{
	socket = SocketHelper::CreateSocket();
}

Session::~Session()
{
	SocketHelper::CloseSocket(socket);
}

void Session::ProcessConnect()
{
	isConnected.store(true);

	// Service에 내꺼 추가
	GetService()->AddSession(this);

	OnConnected();

	RegisterRecv();
}

void Session::RegisterRecv()
{
	if (!IsConnected())
		return;

	// 초기화 : 재활용 용도
	recvEvent.Init();
	// 이벤트 iocpObj에 내꺼 등록
	recvEvent.iocpObj = this;

	WSABUF wsaBuf;
	wsaBuf.buf = (char*)recvBuffer;
	wsaBuf.len = sizeof(recvBuffer);

	DWORD recvLen = 0;
	DWORD flags = 0;

	if (WSARecv(socket, &wsaBuf, 1, &recvLen, &flags, &recvEvent, nullptr) == SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			recvEvent.iocpObj = nullptr;
		}

	}

}

void Session::ObserveIO(IocpEvent* iocpEvent, DWORD bytesTransferred)
{
	// iocpEvent는 RecvEvent 일꺼니까 eventType은 RECV
	switch (iocpEvent->eventType)
	{
	case EventType::RECV:
		ProcessRecv(bytesTransferred);
		break;
	default:
		break;
	}
}

void Session::ProcessRecv(int numOfBytes)
{
	recvEvent.iocpObj = nullptr;
	printf("Recv Data : %d\n", numOfBytes);
	// 물고기 잡고 낚시줄 다시 던지기
	RegisterRecv();
}

void Session::HandleError(int errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		printf("Handle Error\n");
		break;
	default:
		break;
	}
}
