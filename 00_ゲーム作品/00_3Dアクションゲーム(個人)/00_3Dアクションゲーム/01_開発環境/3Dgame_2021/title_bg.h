#ifndef _TITLEBG_H_
#define _TITLEBG_H_
//=============================================================================
//
// �^�C�g���w�i�̏��� [titlebg.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define TITLE_BG_POS_X		(SCREEN_WIDTH / 2)		// �^�C�g����X���W
#define TITLE_BG_POS_Y		(SCREEN_HEIGHT / 2)		// �^�C�g����Y���W
#define TITLE_BG_SIZE_X		(SCREEN_WIDTH / 2)		// �^�C�g����X�T�C�Y
#define TITLE_BG_SIZE_Y		(SCREEN_HEIGHT / 2)		// �^�C�g����Y�T�C�Y

#define TITLE_BG_POS		(D3DXVECTOR3(TITLE_BG_POS_X, TITLE_BG_POS_Y, 0.0f))		// �^�C�g���w�i�̍��W
#define TITLE_BG_SIZE		(D3DXVECTOR3(TITLE_BG_SIZE_X, TITLE_BG_SIZE_Y, 0.0f))		// �^�C�g���w�i�̍��W

//=============================================================================
//�N���X�錾
//=============================================================================
class CTitleBg : public CScene2D
{
public:
	CTitleBg();		// �R���X�g���N�^
	~CTitleBg();	// �f�X�g���N�^

	static CTitleBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �I�u�W�F�N�g�����֐�

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
};
#endif // ! _TITLEBG_H_
