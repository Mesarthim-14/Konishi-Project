#ifndef _LIGHT_EFFECT_H_
#define _LIGHT_EFFECT_H_
//=============================================================================
//
// ���C�g�G�t�F�N�g�̃N���X�w�b�_�[ [light_effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �}�N����`
//=========================================================================
#define LIGHT_EFFECT_SIZE_X (25.0f)				// ���̃T�C�Y
#define LIGHT_EFFECT_SIZE_Y (25.0f)				// �c�̃T�C�Y
#define LIGHT_EFFECT_SIZE_Z (25.0f)				// ���s�̃T�C�Y

#define LIGHT_EFFECT_SIZE (D3DXVECTOR3(LIGHT_EFFECT_SIZE_X, LIGHT_EFFECT_SIZE_Y, LIGHT_EFFECT_SIZE_Z))

#define LIGHT_EFFECT_RADIAN			(25.0f)		// ���s�̃T�C�Y
#define LIGHT_EFFECT_RADIAN_INTER	(2.0f)		// ���s�̃T�C�Y
#define LIGHT_EFFECT_LIFE			(2)			// ���C�t

//=========================================================================
// ���̃��C�g�G�t�F�N�g�N���X
//=========================================================================
class CLightEffect :public CModel
{
public:
	CLightEffect(PRIORITY Priority = PRIORITY_EFFECT);	// �R���X�g���N�^
	~CLightEffect();									// �f�X�g���N�^

	static CLightEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
private:
	int m_nLife;		// �̗�
};
#endif