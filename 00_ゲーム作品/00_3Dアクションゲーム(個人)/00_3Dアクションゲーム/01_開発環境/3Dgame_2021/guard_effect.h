#ifndef _GUARD_EFFECT_H_
#define _GUARD_EFFECT_H_
//=============================================================================
//
// �K�[�h�G�t�F�N�g�̃N���X�w�b�_�[ [guard_effect.h]
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
#define GUARD_EFFECT_SIZE_X (6.0f)		// ���̃T�C�Y
#define GUARD_EFFECT_SIZE_Y (6.0f)		// �c�̃T�C�Y
#define GUARD_EFFECT_SIZE_Z (6.0f)		// ���s�̃T�C�Y

#define GUARD_EFFECT_SIZE (D3DXVECTOR3(GUARD_EFFECT_SIZE_X, GUARD_EFFECT_SIZE_Y, GUARD_EFFECT_SIZE_Z))

//=========================================================================
// �K�[�h�G�t�F�N�g�N���X
//=========================================================================
class CGuardEffect :public CModel
{
public:
	CGuardEffect(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CGuardEffect();									// �f�X�g���N�^

	static CGuardEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	void Luminous(void);								// �����̏���

private:
	float m_fSubNum;									// ���Z�̒l
	bool m_bLuminous;									// �������Ă���t���O
	D3DXCOLOR m_Emissive;								// �����̒l
};
#endif