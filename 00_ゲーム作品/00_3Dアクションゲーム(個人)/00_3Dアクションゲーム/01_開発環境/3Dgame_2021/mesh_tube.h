#ifndef _MESH_TUBE_H_
#define _MESH_TUBE_H_
//=====================================================
//
// ���̃��b�V���̐����N���X�w�b�_�[ [mesh_tube.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "mesh_3d.h"

//=============================================================================
// �~���̃N���X
//=============================================================================
class CMeshTube : public CMesh3d
{
public:
	CMeshTube(PRIORITY Priority = PRIORITY_0);			// �R���X�g���N�^
	~CMeshTube();										// �f�X�g���N�^

	 HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	 void Uninit(void);									// �I������
	 void Update(void);									// �X�V����
	 void Draw(void);									// �`�揈��

	static CMeshTube*Create(D3DXVECTOR3 pos,
		MESH_TYPE MeshNum);								// �C���X�^���X����

private:
};

#endif