//=============================================================================
//
// �R���{�N���X [combo.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "combo.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include "texture.h"
#include "ui.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COMBO_NUMBER_INTERVAL	(50.0f)														// �R���{���̊Ԋu
#define COMBO_DAMAGE_INTERVAL	(30.0f)														// �R���{���̊Ԋu
#define MAX_NUMBER				(3)															// �����̌��ő吔
#define COMBO_RIMIT				(500)														// �R���{�̃t���[������

// HIT��UI���
#define HIT_UI_POS_X	(1100.0f)															// HIT��UI���W
#define HIT_UI_POS_Y	(230.0f)															// HIT��UI���W
#define HIT_UI_POS		(D3DXVECTOR3(HIT_UI_POS_X, HIT_UI_POS_Y, 0.0f))

#define HIT_UI_SIZE_X	(50.0f)																// HIT��UI�T�C�Y
#define HIT_UI_SIZE_Y	(40.0f)																// HIT��UI�T�C�Y
#define HIT_UI_SIZE		(D3DXVECTOR3(HIT_UI_SIZE_X, HIT_UI_SIZE_Y, 0.0f))

// HIT��UI���
#define DAMAGE_UI_POS_X		(1140.0f)														// HIT��UI���W
#define DAMAGE_UI_POS_Y		(310.0f)														// HIT��UI���W
#define DAMAGE_UI_POS		(D3DXVECTOR3(DAMAGE_UI_POS_X, DAMAGE_UI_POS_Y, 0.0f))

#define DAMAGE_UI_SIZE_X	(80.0f)															// HIT��UI�T�C�Y
#define DAMAGE_UI_SIZE_Y	(25.0f)															// HIT��UI�T�C�Y
#define DAMAGE_UI_SIZE		(D3DXVECTOR3(DAMAGE_UI_SIZE_X, DAMAGE_UI_SIZE_Y, 0.0f))

// �R���{��UI�̏��
#define COMBO_NUMBER_POS_X (HIT_UI_POS_X-100.0f)											// �R���{���̍��W
#define COMBO_NUMBER_POS_Y	(HIT_UI_POS_Y)													// �R���{���̍��W
#define COMBO_NUMBER_POS	(D3DXVECTOR3(COMBO_NUMBER_POS_X, COMBO_NUMBER_POS_Y, 0.0f))

#define COMBO_NUMBER_SIZE_X (70.0f)															// �R���{���̍��W
#define COMBO_NUMBER_SIZE_Y	(70.0f)															// �R���{���̍��W
#define COMBO_NUMBER_SIZE	(D3DXVECTOR3(COMBO_NUMBER_SIZE_X, COMBO_NUMBER_SIZE_Y, 0.0f))

// �R���{�_���[�W�����̏��
#define COMBO_DAMAGE_POS_X (DAMAGE_UI_POS_X-115.0f)											// �R���{���̍��W
#define COMBO_DAMAGE_POS_Y	(DAMAGE_UI_POS_Y)												// �R���{���̍��W
#define COMBO_DAMAGE_POS	(D3DXVECTOR3(COMBO_DAMAGE_POS_X, COMBO_DAMAGE_POS_Y, 0.0f))

#define COMBO_DAMAGE_SIZE_X (40.0f)															// �R���{���̍��W
#define COMBO_DAMAGE_SIZE_Y	(40.0f)															// �R���{���̍��W
#define COMBO_DAMAGE_SIZE	(D3DXVECTOR3(COMBO_DAMAGE_SIZE_X, COMBO_DAMAGE_SIZE_Y, 0.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCombo::CCombo()
{
	m_nCounter = 0;
	m_nFlameCounter = 0;
	m_nDamage = 0;
	m_nOldDamageDig = 0;
	m_bCombo = false;
	m_pHitUi = nullptr;
	m_pDamageUi = nullptr;
	memset(m_apCombo, 0, sizeof(m_apCombo));
	memset(m_apDamage, 0, sizeof(m_apDamage));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCombo::~CCombo()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCombo * CCombo::Create(void)
{
	// �������m��
	CCombo *pCombo = new CCombo;

	return pCombo;
}

//=============================================================================
// �I������
//=============================================================================
void CCombo::Uninit(void)
{
	// �R���{���q�����Ă���Ƃ�
	if (m_bCombo == true)
	{
		// UI�̏I������
		UiUninit();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CCombo::Update(void)
{
	// �R���{����Ă���Ƃ�
	if (m_bCombo == true)
	{
		// �J�E���^�[��i�߂�
		m_nFlameCounter++;

		// �J�E���^�[�����ɂȂ�����
		if (m_nFlameCounter >= COMBO_RIMIT)
		{
			// UI�̏I��
			UiUninit();

			// �l�̏�����
			m_nFlameCounter = 0;
			m_nCounter = 0;
			m_nDamage = 0;
			m_bCombo = false;
		}
	}
}

//=============================================================================
// �R���{���̏���
//=============================================================================
void CCombo::Combo(int nDamage)
{
	m_nCounter++;			// �R���{��
	m_nDamage += nDamage;	// �_���[�W�̉��Z

	// �R���{���g���Ă��Ȃ�������
	if (m_bCombo == false)
	{
		// UI�̐���
		UiCreate();
	}
	else
	{
		// �R���{���̏���
		ComboNum();

		// �_���[�W�l����
		DamageNum();

		// �J�E���^�[��߂�
		m_nFlameCounter = 0;
	}
}

//=============================================================================
// UI�̐���
//=============================================================================
void CCombo::UiCreate(void)
{
	// �R���{��
	int nComboDigit = 0;
	int nConboNum = m_nCounter;

	// ���������߂�
	while (nConboNum != 0)
	{
		nConboNum /= 10;
		nComboDigit++;
	}

	// �e�N�X�`���̃|�C���^
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �R���{���̏���
	for (int nCount = 0; nCount < nComboDigit; nCount++)
	{
		if (m_apCombo[nCount] == nullptr)
		{
			// �����̃������m��
			m_apCombo[nCount] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_NUMBER_POS_X - nCount*COMBO_NUMBER_INTERVAL, COMBO_NUMBER_POS_Y, 0.0f), COMBO_NUMBER_SIZE);							// ���W�A�T�C�Y

			if (m_apCombo[nCount] != nullptr)
			{
				// �e�N�X�`���̐ݒ�
				m_apCombo[nCount]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER));

				// �����̐ݒ�
				m_apCombo[nCount]->SetNumber(m_nCounter);
			}
		}
	}

	// �_���[�W����
	int nDamageDigit = 0;
	int nDamageNum = m_nDamage;

	// ���������߂�
	while (nDamageNum != 0)
	{
		nDamageNum /= 10;
		nDamageDigit++;
	}

	// �����ۊ�
	m_nOldDamageDig = nDamageDigit;

	// �R���{���̏���
	for (int nCount = 0; nCount < nDamageDigit; nCount++)
	{
		if (m_apDamage[nCount] == nullptr)
		{
			// �����̃������m��
			m_apDamage[nCount] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_DAMAGE_POS_X - nCount*COMBO_DAMAGE_INTERVAL, COMBO_DAMAGE_POS_Y, 0.0f), COMBO_DAMAGE_SIZE);							// ���W�A�T�C�Y

			if (m_apDamage[nCount] != nullptr)
			{
				m_apDamage[nCount]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER_000));	// �e�N�X�`���̐ݒ�

					// ���̒l���o��
				int nNum = (m_nDamage / (int)(pow(10, nCount))) % 10;

				// �����̐ݒ�
				m_apDamage[nCount]->SetNumber(nNum);
			}
		}
	}

	// HIT��UI���g���Ă��Ȃ�������
	if (m_pHitUi == nullptr)
	{
		// �C���X�^���X����
		m_pHitUi = CUi::Create(HIT_UI_POS, HIT_UI_SIZE);
		m_pHitUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_HIT_UI));
	}

	// �_���[�W��UI���g���Ă��Ȃ�������
	if (m_pDamageUi == nullptr)
	{
		// �C���X�^���X����
		m_pDamageUi = CUi::Create(DAMAGE_UI_POS, DAMAGE_UI_SIZE);
		m_pDamageUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_DAMAGE_UI));
	}

	// �R���{���Ă����Ԃɂ���
	m_bCombo = true;

}

//=============================================================================
// UI�̏I��
//=============================================================================
void CCombo::UiUninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apCombo[nCount] != nullptr)
		{
			// �����̃������m��
			m_apCombo[nCount]->Uninit();
			m_apCombo[nCount] = nullptr;
		}
	}

	for (int nCount = 0; nCount < MAX_DAMAGE_NUM; nCount++)
	{
		if (m_apDamage[nCount] != nullptr)
		{
			// �����̃������m��
			m_apDamage[nCount]->Uninit();
			m_apDamage[nCount] = nullptr;
		}
	}

	// HIT��UI���g���Ă�����
	if (m_pHitUi != nullptr)
	{
		// �I������
		m_pHitUi->Uninit();
		m_pHitUi = nullptr;
	}

	// �_���[�W��UI���g���Ă�����
	if (m_pDamageUi != nullptr)
	{
		// �I������
		m_pDamageUi->Uninit();
		m_pDamageUi = nullptr;
	}
}

//=============================================================================
// �V���������������Ƃ�
//=============================================================================
void CCombo::ComboNum(void)
{
	int nDigit = 0;
	int nNumber = m_nCounter;

	// ���������߂�
	while (nNumber != 0)
	{
		nNumber /= 10;
		nDigit++;
	}

	CTexture *pTexture = GET_TEXTURE_PTR;

	//�@������������
	if (m_nCounter == 10 || m_nCounter == 100 || m_nCounter == 1000)
	{
		if (m_apCombo[nDigit - 1] == nullptr)
		{
			// �����̃������m��
			m_apCombo[nDigit - 1] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_NUMBER_POS_X - (nDigit - 1) *COMBO_NUMBER_INTERVAL, COMBO_NUMBER_POS_Y, 0.0f), COMBO_NUMBER_SIZE);							// ���W�A�T�C�Y

			if (m_apCombo[nDigit - 1] != nullptr)
			{
				m_apCombo[nDigit - 1]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER));	// �e�N�X�`���̐ݒ�

				// �����̐ݒ�
				m_apCombo[nDigit - 1]->SetNumber(0);
			}
		}
	}

	for (int nCount = 0; nCount < nDigit; nCount++)
	{
		// ���̒l���o��
		int nNum = (m_nCounter / (int)(pow(10, nCount))) % 10;

		// �����̐ݒ�
		m_apCombo[nCount]->SetNumber(nNum);
	}
}

//=============================================================================
// �_���[�W���̏���
//=============================================================================
void CCombo::DamageNum(void)
{
	int nDigit = 0;
	int nNumber = m_nDamage;

	// ���������߂�
	while (nNumber != 0)
	{
		nNumber /= 10;
		nDigit++;
	}

	CTexture *pTexture = GET_TEXTURE_PTR;

	// �O���茅���傫��������
	if (m_nOldDamageDig < nDigit)
	{
		if (m_apDamage[nDigit - 1] == nullptr)
		{
			// �����̃������m��
			m_apDamage[nDigit - 1] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_DAMAGE_POS_X - (nDigit - 1) *COMBO_DAMAGE_INTERVAL, COMBO_DAMAGE_POS_Y, 0.0f), COMBO_DAMAGE_SIZE);							// ���W�A�T�C�Y

			if (m_apDamage[nDigit - 1] != nullptr)
			{
				m_apDamage[nDigit - 1]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER_000));	// �e�N�X�`���̐ݒ�

				// �����̐ݒ�
				m_apDamage[nDigit - 1]->SetNumber(0);
			}
		}

		// �����m��
		m_nOldDamageDig = nDigit;
	}

	for (int nCount = 0; nCount < nDigit; nCount++)
	{
		// ���̒l���o��
		int nNum = (m_nDamage / (int)(pow(10, nCount))) % 10;

		// �����̐ݒ�
		m_apDamage[nCount]->SetNumber(nNum);
	}
}

//=============================================================================
// �R���{�̏I���֐�
//=============================================================================
void CCombo::ComboBreak(void)
{
	// �R���{���I���t���[���܂Ői�߂�
	m_nFlameCounter = COMBO_RIMIT;
}