#ifndef _UI_OPERATION_H_
#define _UI_OPERATION_H_
//=============================================================================
//
// �����UI�N���X�w�b�_�[ [ui_operation.h]
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
#define UI_OPERATION_POS_X		(1100.0f)	// X���W
#define UI_OPERATION_POS_Y		(520.0f)	// Y���W
#define UI_OPERATION_SIZE_X		(95.0f)		// X�T�C�Y
#define UI_OPERATION_SIZE_Y		(95.0f)		// Y�T�C�Y

#define UI_OPERATION_POS		(D3DXVECTOR3(UI_OPERATION_POS_X, UI_OPERATION_POS_Y, 0.0f))		// ���W
#define UI_OPERATION_SIZE		(D3DXVECTOR3(UI_OPERATION_SIZE_X, UI_OPERATION_SIZE_Y, 0.0f))	// �T�C�Y

//=============================================================================
// �X�L����UI�N���X�錾
//=============================================================================
class CUiOperation : public CUi
{
public:
	CUiOperation();		// �R���X�g���N�^
	~CUiOperation();	// �f�X�g���N�^

	static CUiOperation *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bUse);	// �I�u�W�F�N�g����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
private:
};

#endif
