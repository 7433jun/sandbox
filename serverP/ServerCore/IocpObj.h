#pragma once
#include "IocpEvent.h"

class IocpObj : public enable_shared_from_this<IocpObj>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void ObserveIO(IocpEvent* iocpEvent, DWORD bytesTransferred = 0) abstract;
};

