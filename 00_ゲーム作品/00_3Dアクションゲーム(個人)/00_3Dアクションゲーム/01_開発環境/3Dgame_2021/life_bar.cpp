//=========================================================
//
// �̗̓o�[�N���X	[life_bar.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "life_bar.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"

//=========================================================
// �}�N����`
//=========================================================
#define DECREASE_LIFE_SPEED		(1)		// �̗͂����炷���x

//=========================================================
// �|���S������
//=========================================================
CLifeBar * CLifeBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,
	CCharacter::CHARACTER_TYPE Ctype, int nLife)
{
	// �������m��
	CLifeBar *pLifeBar = new CLifeBar;

	pLifeBar->SetGage(nLife);			// �̗͂̐ݒ�
	pLifeBar->SetMaxGage(nLife);		// ���C�t�̐ݒ�
	pLifeBar->Init(pos, size);			// ������
	pLifeBar->m_Ctype = Ctype;			// �o�[�̎��
	pLifeBar->SetColor(color);			// �F�̐ݒ�

	return pLifeBar;
}

//=========================================================
// �R���X�g���N�^
//=========================================================
CLifeBar::CLifeBar(PRIORITY Priority) : CGage(Priority)
{

}

//=========================================================
// �f�X�g���N�^
//=========================================================
CLifeBar::~CLifeBar()
{
}

//=========================================================
// ����������
//=========================================================
HRESULT CLifeBar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CGage::Init(pos, size);

	return S_OK;
}

//=========================================================
// �I������
//=========================================================
void CLifeBar::Uninit(void)
{
	// �I������
	CGage::Uninit();
}

//=========================================================
// �X�V����
//=========================================================
void CLifeBar::Update(void)
{
	// ���X�Ɍ��炵�Ă���
	if (GetSubGage() > 0)
	{
		// �o�[�̌��Z
		AddSubNum(DECREASE_LIFE_SPEED);
	}
	else
	{
		// �����Ȃ�����0�ɖ߂�
		SetSubNum(0);
	}

	// �X�V����
	CGage::Update();

	// �v���C���[�̃^�C�v
	if (m_Ctype == CCharacter::CHARACTER_TYPE_PLAYER)
	{
		// �J���[�̕ύX�֐�
		ColorChange();
	}
}

//=========================================================
// �`�揈��
//=========================================================
void CLifeBar::Draw(void)
{
	// �`�揈��
	CGage::Draw();
}

//=========================================================
// �J���[�̕ύX
//=========================================================
void CLifeBar::ColorChange(void)
{
	//HP�ɉ����ăJ���[��ς���i���^�����甼���܂ŗ΁j
	if (GetGage() <= GetMaxGage() && GetGage() > GetMaxGage() / 2)
	{
		SetColor(D3DCOLOR_RGBA(70, 185, 127, 255));
	}

	// HP�ɉ����ăJ���[��ς���i��������4����1�܂ŉ��F�j
	if (GetGage() <= GetMaxGage() / 2 && GetGage() > GetMaxGage() / 4)
	{
		SetColor(D3DCOLOR_RGBA(254, 236, 0, 255));
	}

	// HP�ɉ����ăJ���[��ς���i4����1����͐ԐF�j
	if (GetGage() <= GetMaxGage() / 4)
	{
		SetColor(D3DCOLOR_RGBA(254, 83, 12, 255));
	}
}