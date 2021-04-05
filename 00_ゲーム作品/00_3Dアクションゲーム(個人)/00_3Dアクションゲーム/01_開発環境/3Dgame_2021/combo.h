#ifndef _COMBO_H_
#define _COMBO_H_
//=============================================================================
//
// �R���{�N���X�w�b�_�[ [combo.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NUMBER_NUM		(4)			// �ő�̌���
#define MAX_DAMAGE_NUM		(6)			// �_���[�W�̍ő包��
#define DAMAGE_MAG			(1.05f)		// �_���[�W�{��

//=============================================================================
// �O���錾
//=============================================================================
class CNumber2d;
class CUi;

//=============================================================================
// �R���{�N���X
//=============================================================================
class CCombo
{
public:
	CCombo();							// �R���X�g���N�^
	~CCombo();							// �f�X�g���N�^

	void Uninit(void);					// �I������
	void Update(void);					// �X�V����

	static CCombo *Create(void);		// �C���X�^���X����

	void Combo(int nDamage);			// �R���{�̏����֐�
	void UiCreate(void);				// UI�̐���
	void UiUninit(void);				// Ui�̏I��
	void ComboNum(void);				// �R���{���̏���
	void DamageNum(void);				// �_���[�W�̏���
	void ComboBreak(void);				// �R���{�̏I���̊֐�

	// Get�֐�
	int GetComboNum(void) { return m_nCounter; }			// �R���{���̏��

private:
	CNumber2d *m_apCombo[MAX_NUMBER_NUM];	// ������
	CNumber2d *m_apDamage[MAX_DAMAGE_NUM];	// �_���[�W��
	CUi *m_pHitUi;							// HIT��UI
	CUi *m_pDamageUi;						// �_���[�W��UI
	int m_nCounter;							// �R���{�̃J�E���^�[
	int m_nFlameCounter;					// �R���{�̃t���[���J�E���g
	int m_nDamage;							// �R���{���̃_���[�W�̑���
	int m_nOldDamageDig;					// �_���[�W�̌Â�����
	bool m_bCombo;							// �R���{�̃t���O
};

#endif