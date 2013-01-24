#include "stdafx.h"
#include "CriticalSectionHelper.h"

CCriticalSectionHelper::CCriticalSectionHelper()
{
	// 初期化
	InitializeCriticalSection( &m_CriticalSection );
}

CCriticalSectionHelper::~CCriticalSectionHelper()
{
	// 破棄
	DeleteCriticalSection( &m_CriticalSection );
}

void CCriticalSectionHelper::Rock()
{
	// クリティカルセクションの取得
	EnterCriticalSection( &m_CriticalSection );
}

void CCriticalSectionHelper::Release()
{
	// 開放
	LeaveCriticalSection( &m_CriticalSection );
}