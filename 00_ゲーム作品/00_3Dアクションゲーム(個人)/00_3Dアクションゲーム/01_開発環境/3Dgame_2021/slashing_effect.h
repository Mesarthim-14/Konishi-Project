#ifndef _SLASHING_EFFECT_H_
#define _SLASHING_EFFECT_H_
//=============================================================================
//
// �a���G�t�F�N�g�̃N���X�w�b�_�[ [slashing_effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �}�N����`
//=========================================================================
#define SLASHING_EFFECT_SIZE_X (5.0f)		// ���̃T�C�Y
#define SLASHING_EFFECT_SIZE_Y (7.0f)		// �c�̃T�C�Y
#define SLASHING_EFFECT_SIZE_Z (5.0f)		// ���s�̃T�C�Y

#define SLASHING_EFFECT_SIZE (D3DXVECTOR3(SLASHING_EFFECT_SIZE_X, SLASHING_EFFECT_SIZE_Y, SLASHING_EFFECT_SIZE_Z))

//=========================================================================
// �a���G�t�F�N�g�N���X
//=========================================================================
class CSlashingEffect :public CModel
{
public:
	CSlashingEffect(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CSlashingEffect();										// �f�X�g���N�^

	static CSlashingEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
private:
};
#endif