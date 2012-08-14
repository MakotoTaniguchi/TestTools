#include "Lib/ServiceHelper.h"

// �T�[�r�X�N���X
class CProxyCmdService : public IServiceHelper
{
public:

	// �R���X�g���N�^
	CProxyCmdService();

	// �f�X�g���N�^
	~CProxyCmdService();

	// �T�[�r�X������
	void ServiceOpen( HANDLE hStop = NULL );

	// �T�[�r�X�㏈��
	void ServiceClose();

	// �T�[�r�X�̃C�x���g�n���h��
	void ServiceMain();

	void ServiceStop();

	void ServicePause();

	void ServiceContinue();
	
private:
	
	HANDLE m_hStop;
};