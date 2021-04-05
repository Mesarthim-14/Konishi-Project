#ifndef _GAGE_H_
#define _GAGE_H_
//=========================================================
//
// �̗̓o�[�N���X�w�b�_�[	[gage.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "scene.h"

//=========================================================
// �}�N����`
//=========================================================

//=========================================================
// �Q�[�W�o�[�N���X
//=========================================================
class CGage : public CScene
{
public:
	CGage(PRIORITY Priority = PRIORITY_1);						// �R���X�g���N�^
	~CGage();													// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��

	// Set�֐�
	void SubGage(int nGage);									// HP�o�[�̐ݒ�
	void SetMaxGage(int nMaxGage);								// ���C�t�̍ő�l�ݒ�
	void SetGage(int nGage);									// ���C�t�̐ݒ�
	void SetColor(D3DXCOLOR color);								// �F�̐ݒ�	
	void SetSubNum(int nSubNum);								// �_���[�W�l�̐ݒ�
	void AddSubNum(int nAddNum);								// �_���[�W�l�̉��Z
	void HealGage(int nHealGage);								// �Q�[�W�̉�

	// Get�֐�
	int GetGage(void) { return m_nGage; }						// �̗͂̏��
	int GetMaxGage(void) { return m_nMaxGage; }					// �̗͂̍ő吔���
	int GetSubGage(void) { return m_nSubNum; }					// �_���[�W�̒l���
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// �o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_Pos;						// ���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR m_color;						// �F
	int m_nMaxGage;							// �̗͂̍ő�l
	int m_nGage;							// �̗�
	int m_nSubNum;							// �_���[�W�̒l
};
#endif