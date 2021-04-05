//=========================================================
//
// �Q�[�W�N���X	[gage.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "gage.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"

//=========================================================
// �}�N����`
//=========================================================
#define DECREASE_LIFE_SPEED		(1)		// �̗͂����炷���x

//=========================================================
// �R���X�g���N�^
//=========================================================
CGage::CGage(PRIORITY Priority) : CScene(Priority)
{
	m_pVtxBuff = nullptr;
	m_nGage = 0;
	m_nMaxGage = 0;
	m_nSubNum = 0;
	m_size = ZeroVector3;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=========================================================
// �f�X�g���N�^
//=========================================================
CGage::~CGage()
{
}

//=========================================================
// ����������
//=========================================================
HRESULT CGage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = nullptr;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	m_Pos = pos;
	m_size = size;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	// HP���������ꍇ�A�摜�̉E������`�����߂�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + (m_size.x)*((float)m_nGage / m_nMaxGage)), m_Pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + (m_size.x)*((float)m_nGage / m_nMaxGage)), m_Pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�i�l��1.0�Őݒ肷��j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[��ݒ�i0�`255�̒l�Őݒ肷��j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================
// �I������
//=========================================================
void CGage::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�I�u�W�F�N�g�j��
	Release();
}

//=========================================================
// �X�V����
//=========================================================
void CGage::Update(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// HP���������ꍇ�A�摜�̉E������`�����߂�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + (m_size.x * 2)*((float)m_nGage / m_nMaxGage)), m_Pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + (m_size.x * 2)*((float)m_nGage / m_nMaxGage)), m_Pos.y + m_size.y, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[��ݒ�i0�`255�̒l�Őݒ肷��j
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		pVtx[nCount].col = m_color;
	}

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================================
// �`�揈��
//=========================================================
void CGage::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	CTexture *pTexture = GET_TEXTURE_PTR;

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_GAGEBAR));

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, nullptr);
}

//=========================================================
// �̗͂̍ő吔
//=========================================================
void CGage::SetMaxGage(int nMaxGage)
{
	m_nMaxGage = nMaxGage;
}

//=========================================================
// �̗͂̐ݒ�
//=========================================================
void CGage::SetGage(int nGage)
{
	m_nGage = nGage;
}

//=========================================================
// �F�̐ݒ�
//=========================================================
void CGage::SetColor(D3DXCOLOR color)
{
	m_color = color;
}

//=========================================================
// �_���[�W�l
//=========================================================
void CGage::SetSubNum(int nSubNum)
{
	m_nSubNum = nSubNum;
}

//=========================================================
// �Q�[�W�����炷
//=========================================================
void CGage::SubGage(int nGage)
{
	m_nGage -= nGage;

	if (m_nGage <= 0)
	{
		m_nGage = 0;
	}
}

//=========================================================
// �Q�[�W�����X�Ɍ��炷����
//=========================================================
void CGage::AddSubNum(int nAddNum)
{
	m_nSubNum -= nAddNum;
	m_nGage -= nAddNum;
}

//=========================================================
// �Q�[�W�̉�
//=========================================================
void CGage::HealGage(int nHealGage)
{
	// �Q�[�W�̍ő��菭�Ȃ�������
	if (m_nMaxGage > m_nGage)
	{
		// �Q�[�W�𑝂₷
		m_nGage += nHealGage;

		// ���₵���Q�[�W���ő吔�𒴂�����
		if (m_nGage > m_nMaxGage)
		{
			// �ő吔�Ɠ����l�ɂ���
			m_nGage = m_nMaxGage;
		}
	}
}