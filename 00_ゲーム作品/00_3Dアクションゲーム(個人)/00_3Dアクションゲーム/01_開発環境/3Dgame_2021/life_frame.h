#ifndef _LIFE_FRAME_H_
#define _LIFE_FRAME_H_

//=============================================================================
//
// ���C�t�Q�[�W�̂킭�N���X�w�b�_�[	[life_frame.h]
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
#define PLAYER_LIFE_FLAME_POS_X		(SCREEN_WIDTH / 2)		// ���̈ʒu
#define PLAYER_LIFE_FLAME_POS_Y		(600.0f)				// �c�̈ʒu
#define PLAYER_LIFE_FLAME_SIZE_X	(225.0f)				// ���̑傫��
#define PLAYER_LIFE_FLAME_SIZE_Y	(5.0f)					// �c�̑傫��
#define PLAYER_LIFE_FRAME_POS		(D3DXVECTOR3(PLAYER_LIFE_FLAME_POS_X, PLAYER_LIFE_FLAME_POS_Y, 0.0f))
#define PLAYER_LIFE_FRAME_SIZE		(D3DXVECTOR3(PLAYER_LIFE_FLAME_SIZE_X+1.0f, PLAYER_LIFE_FLAME_SIZE_Y+1.0f, 0.0f))

#define ENEMY_LIFE_FLAME_POS_X		(SCREEN_WIDTH / 2)		// ���̈ʒu
#define ENEMY_LIFE_FLAME_POS_Y		(80.0f)					// �c�̈ʒu
#define ENEMY_LIFE_FLAME_SIZE_X		(400.0f)				// ���̑傫��
#define ENEMY_LIFE_FLAME_SIZE_Y		(5.0f)					// �c�̑傫��
#define ENEMY_LIFE_FRAME_POS		(D3DXVECTOR3(ENEMY_LIFE_FLAME_POS_X, ENEMY_LIFE_FLAME_POS_Y, 0.0f))
#define ENEMY_LIFE_FRAME_SIZE		(D3DXVECTOR3(ENEMY_LIFE_FLAME_SIZE_X+1.0f, ENEMY_LIFE_FLAME_SIZE_Y+1.0f, 0.0f))

//=============================================================================
// ���C�t�t���[���N���X
//=============================================================================
class CLifeFrame : public CUi
{
public:
	CLifeFrame(PRIORITY Priority = PRIORITY_1);			// �R���X�g���N�^
	~CLifeFrame();										// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������

	static CLifeFrame * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �|���S������

private:
};

#endif