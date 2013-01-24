#include "stdafx.h"
#include "CriticalSectionHelper.h"

CCriticalSectionHelper::CCriticalSectionHelper()
{
	// ������
	InitializeCriticalSection( &m_CriticalSection );
}

CCriticalSectionHelper::~CCriticalSectionHelper()
{
	// �j��
	DeleteCriticalSection( &m_CriticalSection );
}

void CCriticalSectionHelper::Rock()
{
	// �N���e�B�J���Z�N�V�����̎擾
	EnterCriticalSection( &m_CriticalSection );
}

void CCriticalSectionHelper::Release()
{
	// �J��
	LeaveCriticalSection( &m_CriticalSection );
}