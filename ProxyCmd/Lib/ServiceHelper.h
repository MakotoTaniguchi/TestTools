#ifndef __INTERFACE_SERVICE_BASE_H__
#define __INTERFACE_SERVICE_BASE_H__

class IServiceHelper
{
public:
	virtual void ServiceOpen( HANDLE hEvent ) = 0;

	virtual void ServiceClose() = 0;

	virtual void ServiceMain() = 0;

	virtual void ServiceStop() = 0;

	virtual void ServicePause() = 0;

	virtual void ServiceContinue() = 0;
};

#endif