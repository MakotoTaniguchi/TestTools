#include "Lib/ThreadBase.h"
#include "Lib/PipeBase.h"

// サービスクラス
class CProxyCmdThread : public CThreadBase
{
public:

	// コンストラクタ
	CProxyCmdThread();

	// デストラクタ
	~CProxyCmdThread();
	
public:
	
	// スレッドメイン
	UINT ThreadMain();

	// パイプ通信
	CPipeBase m_PipeBase;
};