//=============================================================================
//
// ���C�g�G�t�F�N�g�̃N���X [light_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "light_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLightEffect::CLightEffect(PRIORITY Priority) : CModel(Priority)
{
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLightEffect::~CLightEffect()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CLightEffect * CLightEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
{
	// �������m��
	CLightEffect *pLightEffect = new CLightEffect;

	// nullchack
	if (pLightEffect != NULL)
	{
		//�����������Ăяo��
		pLightEffect->Init(pos, size);		// ���W�E�T�C�Y
		pLightEffect->m_nLife = nLife;		// ���C�t
	}

	return pLightEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLightEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CModel::Init(pos, size);

	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	// ���f�����
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_SWORD_EFFECT));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_SWORD_EFFECT));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLightEffect::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLightEffect::Update(void)
{
	// �X�V����
	CModel::Update();
	
	// �������Z
	m_nLife--;

	// �������C�t���w�肳�ꂽ�t���[���ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLightEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	// �}�e���A�����擾
	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.3f, 1.0f, 0.3f, 0.2f);
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