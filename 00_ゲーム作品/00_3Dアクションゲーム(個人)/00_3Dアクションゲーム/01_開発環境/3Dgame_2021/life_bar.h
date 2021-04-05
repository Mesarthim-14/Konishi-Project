#ifndef _LIFE_BAR_H_
#define _LIFE_BAR_H_
//=========================================================
//
// �̗̓o�[�N���X�w�b�_�[	[life_bar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "gage.h"
#include "life_frame.h"
#include "character.h"

//=========================================================
// �}�N����`
//=========================================================
#define PLAYER_LIFE_BAR_SIZE_X		(150.0f)
#define PLAYER_LIFE_BAR_COLOR		(D3DCOLOR_RGBA(70, 185, 127, 255))
#define PLAYER_LIFE_BAR_POS			(D3DXVECTOR3(PLAYER_LIFE_FLAME_POS_X -PLAYER_LIFE_FLAME_SIZE_X , PLAYER_LIFE_FLAME_POS_Y, 0.0f))							// �̗̓o�[�̍��W
#define PLAYER_LIFE_BAR_SIZE		(D3DXVECTOR3(PLAYER_LIFE_BAR_SIZE_X, PLAYER_LIFE_FLAME_SIZE_Y, 0.0f))		// �̗̓o�[�̑傫��

#define ENEMY_LIFE_BAR_SIZE_X		(ENEMY_LIFE_FLAME_SIZE_X)
#define ENEMY_LIFE_BAR_COLOR		(D3DCOLOR_RGBA(200, 20, 200, 255))
#define ENEMY_LIFE_BAR_POS			(D3DXVECTOR3(ENEMY_LIFE_FLAME_POS_X -ENEMY_LIFE_FLAME_SIZE_X , ENEMY_LIFE_FLAME_POS_Y, 0.0f))							// �̗̓o�[�̍��W
#define ENEMY_LIFE_BAR_SIZE			(D3DXVECTOR3(ENEMY_LIFE_BAR_SIZE_X, ENEMY_LIFE_FLAME_SIZE_Y, 0.0f))		// �̗̓o�[�̑傫��

//=========================================================
// �q�b�g�|�C���g�o�[�N���X
//=========================================================
class CLifeBar : public CGage
{
public:
	CLifeBar(PRIORITY Priority = PRIORITY_1);										// �R���X�g���N�^
	~CLifeBar();																	// �f�X�g���N�^

	static CLifeBar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,
		CCharacter::CHARACTER_TYPE Ctype, int nLife);								// �|���S������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��

	void ColorChange(void);															// �J���[�̕ύX
private:
	CCharacter::CHARACTER_TYPE m_Ctype;		// �^�C�v
};
#endif