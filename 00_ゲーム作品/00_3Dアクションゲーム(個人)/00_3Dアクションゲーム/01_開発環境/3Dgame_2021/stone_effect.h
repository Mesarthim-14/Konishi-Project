#ifndef _STONE_EFFECT_H_
#define _STONE_EFFECT_H_
//=============================================================================
//
// ��̃G�t�F�N�g�N���X�w�b�_�[ [stone_effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CStoneEffect
{
public:
	// �p�[�e�B�N���̍\����
	typedef struct
	{
		D3DXVECTOR3 size;		// �T�C�Y
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 Distance;	// ����
		int nLife;				// ���C�t
		int nNum;				// ��
		D3DXCOLOR color;		// �F
	}STONE;

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		STONE_NUM_NONE = -1,	// �����l
		STONE_NUM_000,			// ��̔ԍ�
		STONE_NUM_001,			// ��̔ԍ�
		STONE_NUM_002,			// ��̔ԍ�
		STONE_NUM_MAX
	}STONE_TYPE;

	CStoneEffect();			// �R���X�g���N�^
	~CStoneEffect();		// �f�X�g���N�^

	static HRESULT ReadFile(void);				// �t�@�C���̓ǂݍ���
	static void CreateStone(D3DXVECTOR3 pos);	// ��̐����N���X
private:
	static STONE m_Stone[STONE_NUM_MAX];		// �p�[�e�B�N��
};
#endif
