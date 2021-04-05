#ifndef _STONE_H_
#define _STONE_H_
//=============================================================================
//
// ��̃N���X�w�b�_�[ [stone.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"
#include "stone_effect.h"

//=========================================================================
// �}�N����`
//=========================================================================
#define STONE_SIZE_X (6.0f)				// ���̃T�C�Y
#define STONE_SIZE_Y (6.0f)				// �c�̃T�C�Y
#define STONE_SIZE_Z (6.0f)				// ���s�̃T�C�Y

#define STONE_SIZE (D3DXVECTOR3(GUARD_EFFECT_SIZE_X, GUARD_EFFECT_SIZE_Y, GUARD_EFFECT_SIZE_Z))

#define STONE_RADIAN		(25.0f)		// ���s�̃T�C�Y
#define STONE_RADIAN_INTER	(2.0f)		// ���s�̃T�C�Y
#define STONE_LIFE			(2)			// ���C�t

//=========================================================================
// 3D�|���S���N���X
//=========================================================================
class CStone :public CModel
{
public:
	CStone(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CStone();										// �f�X�g���N�^

	static CStone *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
		CStoneEffect::STONE stone, CXfile::XFILE_NUM StoneNum);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
private:
};
#endif