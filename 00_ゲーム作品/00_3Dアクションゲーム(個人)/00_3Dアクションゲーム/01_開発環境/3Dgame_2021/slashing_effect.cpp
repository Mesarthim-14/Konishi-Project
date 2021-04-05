//=============================================================================
//
// �a���G�t�F�N�g�̃N���X [slashing_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "slashing_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSlashingEffect::CSlashingEffect(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSlashingEffect::~CSlashingEffect()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CSlashingEffect * CSlashingEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//3D�|���S���N���X�̃|�C���^�ϐ�
	CSlashingEffect *pLightEffect = new CSlashingEffect;

	//���������m�ۂł��Ă�����
	if (pLightEffect != NULL)
	{
		//�����������Ăяo��
		pLightEffect->Init(pos, size);
	}

	return pLightEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSlashingEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CModel::Init(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), size);

	// X�t�@�C���̃|�C���^
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	// X�t�@�C���̐ݒ�
//	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_SWORD_LOCUS_EFFECT));				// ���f�����
//	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_SWORD_LOCUS_EFFECT));		// �e�N�X�`�����

	return S_OK;
}