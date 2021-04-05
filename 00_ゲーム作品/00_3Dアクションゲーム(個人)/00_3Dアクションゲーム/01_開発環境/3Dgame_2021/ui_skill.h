#ifndef _UI_SKILL_H_
#define _UI_SKILL_H_
//=============================================================================
//
// �X�L����UI�N���X�w�b�_�[ [ui_skill.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define UI_SKILL_POS_X		(SCREEN_WIDTH / 2)	// X���W
#define UI_SKILL_POS_Y		(500.0f)			// Y���W
#define UI_SKILL_SIZE_X		(200.0f)			// X�T�C�Y
#define UI_SKILL_SIZE_Y		(25.0f)				// Y�T�C�Y

#define UI_SKILL_POS		(D3DXVECTOR3(UI_SKILL_POS_X, UI_SKILL_POS_Y, 0.0f))		// ���W
#define UI_SKILL_SIZE		(D3DXVECTOR3(UI_SKILL_SIZE_X, UI_SKILL_SIZE_Y, 0.0f))	// �T�C�Y

//=============================================================================
// �X�L����UI�N���X�錾
//=============================================================================
class CUiSkill : public CUi
{
public:
	CUiSkill();		// �R���X�g���N�^
	~CUiSkill();	// �f�X�g���N�^

	static CUiSkill *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bUse);	// �I�u�W�F�N�g����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
private:
};

#endif
