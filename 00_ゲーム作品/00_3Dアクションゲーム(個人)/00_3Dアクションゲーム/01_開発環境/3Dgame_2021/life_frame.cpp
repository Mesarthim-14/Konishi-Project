//=============================================================================
//
// ���C�t�Q�[�W�̘g [life_frame.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "life_frame.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLifeFrame::CLifeFrame(PRIORITY Priority) : CUi(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLifeFrame::~CLifeFrame()
{

}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CLifeFrame *CLifeFrame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������m��
	CLifeFrame *pLifeFrame = new CLifeFrame;

	// ����������
	pLifeFrame->Init(pos, size);

	return S_OK;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLifeFrame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CUi::Init(pos, size);												// ���W�A�T�C�Y

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAGEFLAME));	// �e�N�X�`���ݒ�

	return S_OK;
}