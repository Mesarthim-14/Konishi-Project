#ifndef _ROAR_EFFECT_H_
#define _ROAR_EFFECT_H_
//=============================================================================
//
// ���K���̉��N���X�w�b�_�[ [roar_effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"

//=============================================================================
// �O���錾
//=============================================================================
class CBillboard;

//=============================================================================
// BG�N���X
//=============================================================================
class CRoarFire : public CBillboard
{
public:
	CRoarFire(PRIORITY Priority = PRIORITY_PARTICLE);	// �R���X�g���N�^
	~CRoarFire();										// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CRoarFire * Create(							// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void Collision(void);								// �����蔻��̊֐�
private:
	int m_nCounter;			// �N���X�̃t���[���J�E���^�[
};

#endif