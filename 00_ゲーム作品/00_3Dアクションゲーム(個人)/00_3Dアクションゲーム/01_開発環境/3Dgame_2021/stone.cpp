//=============================================================================
//
// ��̃N���X [stone.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "stone.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define STONE_GRAVITY_POWAR			(1.0f)			// �d�͂̋���
#define STONE_GROUND_RIMIT			(0.0f)			// �n�ʂ̐���
#define STONE_SUB_ALPHA_SPEED		(0.05f)			// �����x�̑��x

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStone::CStone(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStone::~CStone()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CStone * CStone::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CStoneEffect::STONE stone, CXfile::XFILE_NUM StoneNum)
{
	//3D�|���S���N���X�̃|�C���^�ϐ�
	CStone *pStone = new CStone;

	//���������m�ۂł��Ă�����
	if (pStone != nullptr)
	{
		// �����̐ݒ�
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)stone.Distance.x + rand() % (int)stone.Distance.x - rand() % (int)stone.Distance.x - rand() % (int)stone.Distance.x),
			(float)(rand() % (int)stone.Distance.y + rand() % (int)stone.Distance.y),
			(float)(rand() % (int)stone.Distance.z + rand() % (int)stone.Distance.z - rand() % (int)stone.Distance.z - rand() % (int)stone.Distance.z));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y + 100.0f,
			pos.z + Distance.z);

		//�����������Ăяo��
		pStone->Init(TargetPos, stone.size);

		// �ړ��ʂ������_���Ō��߂�
		D3DXVECTOR3 RandMove = D3DXVECTOR3(
		(float)(move.x * ((rand() % (int)stone.move.x + rand() % (int)stone.move.x - rand() % (int)stone.move.x))),
			(float)(rand() % (int)stone.move.y + rand() % (int)stone.move.y + rand() % (int)stone.move.y),
			(float)((move.z * (rand() % (int)stone.move.z + rand() % (int)stone.move.z - rand() % (int)stone.move.z))));

		// X�t�@�C���̃|�C���^
		CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	// ���f���̓ǂݍ���
		pStone->BindModel(pXFile->GetXfile(StoneNum));
		pStone->BindTexture(pXFile->GetXfileTexture(StoneNum));

		// �ړ��ʂ̐ݒ�
		pStone->SetMove(RandMove);

		// ���C�t�̐ݒ�
		int nLife = stone.nLife;
		pStone->SetLife(nLife);

		// �J���[�̐ݒ�
		pStone->SetColor(stone.color);
	}

	return pStone;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStone::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CModel::Init(pos, size);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStone::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStone::Update(void)
{
	// �X�V����
	CModel::Update();

	// ���n�̏���
	if (GetPos().y <= STONE_GROUND_RIMIT)
	{
		// �ړ���0�ɂ���
		SetMove(ZeroVector3);

		// ���W��߂�
		SetPos(D3DXVECTOR3(GetPos().x, STONE_GROUND_RIMIT, GetPos().z));

		// �����ɂ��Ă���
		SubAlpha(STONE_SUB_ALPHA_SPEED);
	}
	else
	{
		// �d�͂�������
		SetMove(D3DXVECTOR3(GetMove().x, GetMove().y - STONE_GRAVITY_POWAR, GetMove().z));
	}

	// ���C�t��0�����������
	if (GetLife() <= 0 || GetAlphaNum() >= 1.0f)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CStone::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}