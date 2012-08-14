#ifndef __CRITICALSECTION_H__
#define __CRITICALSECTION_H__

#include "windows.h"

class CCriticalSectionHelper
{
public:
	CCriticalSectionHelper();
	~CCriticalSectionHelper();

	void Rock();

	void Release();

private:
	CRITICAL_SECTION m_CriticalSection;
};

#endif