#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"
#include "Session.h"
#include "IocpObj.h"

IocpCore::IocpCore()
{
	iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);
}

IocpCore::~IocpCore()
{
	CloseHandle(iocpHandle);
}

bool IocpCore::Register(IocpObj* iocpObj)
{
	return CreateIoCompletionPort(iocpObj->GetHandle(), iocpHandle, 0, 0);
}

bool IocpCore::ObserveIO(DWORD time)
{
	DWORD bytesTransferred = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	printf("Waiting...\n");
	if (GetQueuedCompletionStatus(iocpHandle, &bytesTransferred, &key, (LPOVERLAPPED*)&iocpEvent, time))
	{
		// Session�� Listener�� IocpObj ��ӹ�������
		IocpObj* iocpObj = iocpEvent->iocpObj;
		// iocpObj�� ObserveIO�� �����Լ��̱� ������
		// �Ҵ�� �ڽ��� Session�̶�� Session->ObserveIO
		// �Ҵ�� �ڽ��� Listener��� Listener->ObserveIO
		iocpObj->ObserveIO(iocpEvent, bytesTransferred);
	}
	else
	{
		switch (GetLastError())
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			break;
		}
		return false;
	}

	return true;
}