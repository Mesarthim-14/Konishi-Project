//=============================================================================
//
// �O�Ղ̏��� [locus.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "locus.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LOCUS_ALPHA_NUM	(0.08f)									// �����x�̒l
#define LOCUS_COLOR		(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f))		// �F�̐ݒ�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLocus::CLocus()
{
	m_nLife = 0;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTexture = nullptr;
	m_fAlphaNum = 0.0f;
	m_color = LOCUS_COLOR;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLocus::~CLocus()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CLocus * CLocus::Create(D3DXVECTOR3 Origin, D3DXVECTOR3 Top, D3DXVECTOR3 OldOrigin, D3DXVECTOR3 OldTop,
	D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, LPDIRECT3DTEXTURE9 pTex)
{
	//�|�C���^�ϐ�
	CLocus *pLocus = nullptr;

	//�������̊m��
	pLocus = new CLocus;

	// nullchack
	if (pLocus != nullptr)
	{
		//�����������Ăяo��
		pLocus->Init(Origin, Top, OldOrigin, OldTop);	// 4���_�̍��W
		pLocus->m_rot = rot;							// �p�x
		pLocus->m_nLife = nLife;						// ���C�t
		pLocus->m_pTexture = pTex;						// �e�N�X�`��
	}
	else
	{
		return nullptr;
	}

	return pLocus;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLocus::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	return S_OK;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLocus::Init(D3DXVECTOR3 Origin, D3DXVECTOR3 Top, D3DXVECTOR3 OldOrigin, D3DXVECTOR3 OldTop)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = OldTop;
	pVtx[1].pos = Top;
	pVtx[2].pos = OldOrigin;
	pVtx[3].pos = Origin;

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLocus::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLocus::Update(void)
{
	// �����x���Z
	m_fAlphaNum += LOCUS_ALPHA_NUM;

	// ���������炷
	m_nLife--;

	// ���C�t�������Ȃ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLocus::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = nullptr;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�̃}�g���N�X

	pDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// �����x���g����
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�B�X�e�B�l�[�V�����J���[�̎w��

	// �A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	// �F�̐ݒ�
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = D3DXCOLOR(1.0f - m_fAlphaNum, 1.0f - m_fAlphaNum, 1.0f - m_fAlphaNum, 1.0f - m_fAlphaNum);
	material.Diffuse = D3DXCOLOR(m_color.r - m_fAlphaNum, m_color.g - m_fAlphaNum, m_color.b - m_fAlphaNum, m_color.a - m_fAlphaNum);
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���[���h�}�g���N�X
	D3DXMATRIX EffectMtx;

	// ������
	D3DXMatrixIdentity(&EffectMtx);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &EffectMtx);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	// �}�e���A�������ɖ߂�
	pDevice->SetMaterial(&OldMaterial);	

	// �A���t�@�e�X�g�̒l��߂�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	
	// �e�N�X�`������߂�
	pDevice->SetTexture(0, nullptr);
}