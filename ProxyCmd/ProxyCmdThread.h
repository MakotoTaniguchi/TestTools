#include "Lib/ThreadBase.h"
#include "Lib/PipeBase.h"

// �T�[�r�X�N���X
class CProxyCmdThread : public CThreadBase
{
public:

	// �R���X�g���N�^
	CProxyCmdThread();

	// �f�X�g���N�^
	~CProxyCmdThread();
	
public:
	
	// �X���b�h���C��
	UINT ThreadMain();

	// �p�C�v�ʐM
	CPipeBase m_PipeBase;
};