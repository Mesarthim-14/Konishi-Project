#ifndef _IMPACT_H_
#define _IMPACT_H_
//=============================================================================
//
// �Ռ��G�t�F�N�g�N���X�w�b�_�[ [impact.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect_3d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define IMPACT_SCALE_NUM			(0.045f)	// �g��̒l
#define ATTACK_IMPACT_SCALE_NUM		(0.05f)		// �U�����̃X�P�[��
#define DUSH_IMPACT_SCALE_NUM		(0.1f)		// �U�����̃X�P�[��

//=============================================================================
// �Ռ��N���X
//=============================================================================
class CImpact : public CEffect3D
{
public:
	CImpact();			// �R���X�g���N�^
	~CImpact();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CImpact * Create(D3DXVECTOR3 pos,			// �C���X�^���X����
		CEffectFactory::EFFECT Particle,
		int nTexInfo, bool bInverse, float fNum);

private:
	int m_nCounter;		// �J�E���^�[
	float m_fScaleNum;	// �g��̒l
};

#endif