//=============================================================================
//
// �K�[�h�G�t�F�N�g�̃N���X [guard_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "guard_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GUARD_EFFECT_ALPHA_NUM		(0.7f)												// �K�[�h�G�t�F�N�g�̓��ߒl
#define GUARD_EFFECT_LUMINOUS_COLOR (D3DXCOLOR(0.9f, 1.0f, 0.9f, 0.8f))					// ���s�̒l
#define GUARD_EFFECT_ADD_NUM		(0.01f)												// �F�̉��Z�l

#define GUARD_EFFECT_COLOR_R	(0.3f)													// �F�̐ݒ�
#define GUARD_EFFECT_COLOR_G	(1.0f)													// �F�̐ݒ�
#define GUARD_EFFECT_COLOR_B	(0.3f)													// �F�̐ݒ�
#define GUARD_EFFECT_COLOR_A	(0.2f)													// �F�̐ݒ�

#define GUARD_EFFECT_COLOR	(D3DXCOLOR(GUARD_EFFECT_COLOR_R, GUARD_EFFECT_COLOR_G, GUARD_EFFECT_COLOR_B, GUARD_EFFECT_COLOR_A))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGuardEffect::CGuardEffect(PRIORITY Priority) : CModel(Priority)
{
	m_fSubNum = 0.0f;
	m_bLuminous = false;
	m_Emissive = WhiteColor;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGuardEffect::~CGuardEffect()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CGuardEffect * CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//3D�|���S���N���X�̃|�C���^�ϐ�
	CGuardEffect *pGuardEffect = new CGuardEffect;

	//���������m�ۂł��Ă�����
	if (pGuardEffect != nullptr)
	{
		//�����������Ăяo��
		pGuardEffect->Init(pos, size);
	}

	return pGuardEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGuardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CModel::Init(pos, size);
	SubAlpha(GUARD_EFFECT_ALPHA_NUM);

	// X�t�@�C���̃|�C���^
	CXfile *pXFile = GET_XFILE_PTR;

	// ���f�����擾
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_GUARD_EFFECT));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_GUARD_EFFECT));

	// �F�̐ݒ�
	m_Emissive = GUARD_EFFECT_COLOR;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGuardEffect::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGuardEffect::Update(void)
{
	// �X�V����
	CModel::Update();

	// ������
	if (m_bLuminous == true)
	{
		// �F�̌��Z
			m_Emissive.r -= GUARD_EFFECT_ADD_NUM;
			m_Emissive.g -= GUARD_EFFECT_ADD_NUM;
			m_Emissive.b -= GUARD_EFFECT_ADD_NUM;
			m_Emissive.a -= GUARD_EFFECT_ADD_NUM;

			// ���ȏ��
		if (m_Emissive.r <= GUARD_EFFECT_COLOR_R)
		{
			// �J���[��߂�
			m_Emissive = GUARD_EFFECT_COLOR;

			m_bLuminous = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGuardEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pMat[nCntMat].MatD3D.Emissive = m_Emissive;

		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;
	}

	// �`�揈��
	CModel::Draw();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}
}

//=============================================================================
// �����̏���
//=============================================================================
void CGuardEffect::Luminous(void)
{
	// �F�𔒂ɂ���
	m_Emissive = GUARD_EFFECT_LUMINOUS_COLOR;

	m_bLuminous = true;
}