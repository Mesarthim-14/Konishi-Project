//=============================================================================
//
// �Ռ��G�t�F�N�g�N���X [impact.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "impact.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define IMPACT_SCALE_CHANGE_NUM		(0.02f)		// �ς������
#define IMPACT_SUB_ALPHA_NUM		(0.08f)		// �����x
#define IMPACT_CHANGE_TIME			(20)		// ����̃t���[��

//=============================================================================
// �C���X�^���X����
//=============================================================================
CImpact * CImpact::Create(D3DXVECTOR3 pos, CEffectFactory::EFFECT Particle,
	int nTexInfo, bool bInverse, float fNum)
{
	// �C���X�^���X����
	CImpact *pImpact = new CImpact;

	// nullcheck
	if (pImpact != nullptr)
	{
		// �����̐ݒ�
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x),
			(float)(rand() % (int)Particle.Distance.y + rand() % (int)Particle.Distance.y),
			(float)(rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		// ����������
		pImpact->Init(TargetPos, Particle.size);

		CTexture *pTexture = GET_TEXTURE_PTR;

		// �A�j���[�V�������
		if (Particle.bAnimation == false)
		{
			// �e�N�X�`���ݒ�
			pImpact->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));
		}
		else
		{
			// �A�j���[�V�����e�N�X�`���ݒ�
			pImpact->BindTexture(pTexture->GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));

			// �A�j���[�V�������
			pImpact->InitAnimation(
				pTexture->GetSparateTexInfo((CTexture::SEPARATE_TEX_TYPE)nTexInfo),
				pTexture->GetSparateTexLoop((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
		}

		// �ړ��ʂ����ȏ�Ȃ�
		if (Particle.move.x >= 1.0f &&
			Particle.move.y >= 1.0f &&
			Particle.move.z >= 1.0f)
		{
			// �ړ��ʐݒ�
			D3DXVECTOR3 move;
			switch (Particle.bGravity)
			{
				// �d�͖���
			case false:
				// �ړ���
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;

				// �d�͂���
			case true:
				// �ړ���
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;
			}

			// �ړ���
			pImpact->SetMove(move);
		}
		else
		{
			// �ړ���
			pImpact->SetMove(Particle.move);
		}

		// �l�̑��
		pImpact->SetColor(Particle.color);			// �F�̐ݒ�
		pImpact->SetLife(Particle.nLife);			// �̗͂̐ݒ�
		pImpact->SetAlpha(Particle.bAlpha);			// �A���t�@�e�X�g�̐ݒ�
		pImpact->SetAlphaNum(Particle.nAlphaNum);	// �A���t�@�e�X�g�̒l
		pImpact->SetBlend(Particle.bBlend);			// ���Z�������s����
		pImpact->SetInverse(bInverse);				// �t�s����s����
		pImpact->m_fScaleNum = fNum;				// �X�P�[���l�̐ݒ�
	}

	return pImpact;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CImpact::CImpact()
{
	m_nCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CImpact::~CImpact()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CImpact::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CEffect3D::Init(pos, size);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CImpact::Uninit(void)
{
	// �I������
	CEffect3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CImpact::Update(void)
{
	m_nCounter++;

	// ���ȏ��
	if (m_nCounter >= IMPACT_CHANGE_TIME)
	{
		// �g�傷��
		ScaleUp(IMPACT_SCALE_CHANGE_NUM);
		SubAlpha(IMPACT_SUB_ALPHA_NUM);
	}
	else
	{
		// �g�傷��
		ScaleUp(m_fScaleNum);
	}

	// �X�V����
	CEffect3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CImpact::Draw(void)
{
	// �`�揈��
	CEffect3D::Draw();
}