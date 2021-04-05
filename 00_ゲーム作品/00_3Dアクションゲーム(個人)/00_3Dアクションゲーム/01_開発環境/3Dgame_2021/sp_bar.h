#ifndef _SP_BAR_H_
#define _SP_BAR_H_
//=========================================================
//
// �̗̓o�[�N���X�w�b�_�[	[sp_bar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "gage.h"
#include "life_frame.h"
#include "life_bar.h"

//=========================================================
// �}�N����`
//=========================================================
#define PLAYER_SP_BAR_SIZE_X	(75.0f)		// SP�o�[�̉���
#define PLAYER_SP_BAR_POS		(D3DXVECTOR3(PLAYER_LIFE_FLAME_POS_X -PLAYER_LIFE_FLAME_SIZE_X + PLAYER_LIFE_BAR_SIZE_X*2 , PLAYER_LIFE_FLAME_POS_Y, 0.0f))		// �̗̓o�[�̍��W
#define PLAYER_SP_BAR_SIZE		(D3DXVECTOR3(PLAYER_SP_BAR_SIZE_X, PLAYER_LIFE_FLAME_SIZE_Y, 0.0f))						// �̗̓o�[�̑傫��

//=========================================================
// SP�o�[�N���X
//=========================================================
class CSpBar : public CGage
{
public:
	CSpBar(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CSpBar();									// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	static CSpBar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSp);		// �|���S������
	void SpRegene(void);													// SP�̃��W�F�l����

private:
	int m_nRegeneCnt;		// ���W�F�l�̃t���[���J�E���g
};
#endif