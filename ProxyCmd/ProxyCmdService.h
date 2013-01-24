#include "Lib/ServiceHelper.h"

// サービスクラス
class CProxyCmdService : public IServiceHelper
{
public:

	// コンストラクタ
	CProxyCmdService();

	// デストラクタ
	~CProxyCmdService();

	// サービス初期化
	void ServiceOpen( HANDLE hStop = NULL );

	// サービス後処理
	void ServiceClose();

	// サービスのイベントハンドラ
	void ServiceMain();

	void ServiceStop();

	void ServicePause();

	void ServiceContinue();
	
private:
	
	HANDLE m_hStop;
};