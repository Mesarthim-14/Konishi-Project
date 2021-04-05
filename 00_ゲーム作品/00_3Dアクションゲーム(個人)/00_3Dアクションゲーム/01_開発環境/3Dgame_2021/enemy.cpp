//=============================================================================
//
// �G�l�~�[�N���X [enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "effect_factory.h"
#include "fade.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority)
{
	m_nMotionState = 0;
	m_bActive = false;
	m_bAttack = false;
	m_bRange = false;
	m_nAttackInter = 0;
	m_nAttackFlameCnt = 0;
	m_nArmorFlame = 0;
	m_bPerception = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �������m��
	CEnemy *pEnemy = new CEnemy;

	// ����������
	pEnemy->Init(pos, rot);

	return pEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CCharacter::Init(pos, rot);			// ���W�A�p�x
	SetCType(CHARACTER_TYPE_ENEMY);		// �L�����N�^�[�̃^�C�v

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �X�V����
	CCharacter::Update();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[��G������G
	if (m_bActive == true)
	{
		// ���m�̏���
		Perception();
	}

	// �U���̊Ԋu��i�߂�
	m_nAttackFlameCnt++;

	// �U���͈͓��̂Ƃ�
	if (m_bRange == true)
	{
		// �U���̊Ԋu�Ɏ�������
		if (m_nAttackFlameCnt >= m_nAttackInter)
		{
			// �U���̏���
			Attack();

			// �t���[���̃J�E���g��߂�
			m_nAttackFlameCnt = 0;
		}
	}

	// �̗͂̐ݒ�
	if (GetLife() <= 0)
	{
		// ���S���̏���
		Death();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=============================================================================
// �G�l�~�[�̏��
//=============================================================================
void CEnemy::UpdateState(void)
{
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	STATE state = GetState();

	switch (state)
	{
	case STATE_NORMAL:
		break;

	case STATE_DAMAGE:
	{
		// ��ԃJ�E���^�[�擾
		int nStateCounter = GetStateCounter();

		// ��莞�Ԍo�߂�����
		if (nStateCounter >= m_nArmorFlame)
		{
			SetState(STATE_NORMAL);		// �ʏ��Ԃɖ߂�
			SetArmor(false);			// ���G��ԉ���
			SetStateCounter(0);			// ��ԃJ�E���^�[���Z�b�g
		}
	}
		break;

	default:
		break;
	}
}

//=============================================================================
// �v���C���[�����m
//=============================================================================
void CEnemy::Perception(void)
{
	// �Ǐ]�̃t���O
	if (m_bPerception == true)
	{
		// �v���C���[�̏��
		CPlayer *pPlayer = CGame::GetPlayer();		// �������m��
		D3DXVECTOR3 Ppos = pPlayer->GetPos();		// ���W�擾

		// ���������̐���
		float fDisLimit = GetRadius() + pPlayer->GetRadius() + 100.0f;

		//���@���擾����
		float fPposX = Ppos.x, fPposZ = Ppos.z;			// ���@�̍��W
		float fEposX = GetPos().x, fEposZ = GetPos().z;	// �G�̍��W
		float fAngle;									// �p�x

		fAngle = atan2f((fEposX - fPposX), (fEposZ - fPposZ));			//�p�x�����߂�

		//���@�ƓG�̋���
		float fDistance = sqrtf(
			powf((Ppos.x - GetPos().x), 2) +
			powf((Ppos.z - GetPos().z), 2));

		// ����Ă�����
		if (fDisLimit <= fDistance)
		{
			// �����ȓG�̈ړ�
			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
				(sinf(fAngle)*-GetSpeed()),
				0.0f, cosf(fAngle)*-GetSpeed());

			// �ړ��ʂ̐ݒ�
			SetMove(FollowMove);

			// �p�x�̐ݒ�
			D3DXVECTOR3 rot = GetRot();
			SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));

			// ���[�V�����̐ݒ�
			SetMotion(ENEMY_MOTION_WALK);

			// �͂��Ȃ�
			if (m_bRange == true)
			{
				m_bRange = false;
			}
		}
		else
		{
			// �ړ��ʂ̐ݒ�
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// �͂�
			if (m_bRange == false)
			{
				m_bRange = true;
			}

			// �p�x�̐ݒ�
			D3DXVECTOR3 rot = GetRot();

			SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));

			// ���[�V�����̐ݒ�
			SetMotion(ENEMY_MOTION_IDOL);
		}

	}
}

//=============================================================================
// ���񂾂Ƃ��̏���
//=============================================================================
void CEnemy::Death(void)
{
	// �I������
	Uninit();

	// ���U���g��ʂ֑J��
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_TITLE);
}

//=============================================================================
// �U���̏���
//=============================================================================
void CEnemy::Attack(void)
{
	// �v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();		// �������m��
	D3DXVECTOR3 Ppos = pPlayer->GetPos();		// ���W�擾

	// ���������̐���
	float fDisLimit = GetRadius() + pPlayer->GetRadius() + 100.0f;

	//���@���擾����
	float fPposX = Ppos.x, fPposZ = Ppos.z;			// ���@�̍��W
	float fEposX = GetPos().x, fEposZ = GetPos().z;	// �G�̍��W
	float fAngle;									// �p�x

	//�p�x�����߂�
	fAngle = atan2f((fEposX - fPposX), (fEposZ - fPposZ));

	// �p�x�̐ݒ�
	D3DXVECTOR3 rot = GetRot();
	SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));

	// �U�����[�V����
	SetMotion(ENEMY_MOTION_ATTACK);
	m_nAttackFlameCnt = 0;
}

//=============================================================================
// ���[�V������Ԃ̍X�V
//=============================================================================
void CEnemy::UpdateMotionState(void)
{
}

//=============================================================================
// �v���C���[���m�̐ݒ�
//=============================================================================
void CEnemy::SetActive(bool bActive)
{
	m_bActive = bActive;
}

//=============================================================================
// �U���̊Ԋu�ݒ�
//=============================================================================
void CEnemy::SetAttackInter(int nAttackInter)
{
	m_nAttackInter = nAttackInter;
}

//=============================================================================
// ���G��Ԃ̃t���[���ݒ�
//=============================================================================
void CEnemy::SetArmorFlame(int nArmorFlame)
{
	m_nArmorFlame = nArmorFlame;
}

//=============================================================================
// �Ǐ]�̃t���O�ݒ�
//=============================================================================
void CEnemy::SetPerception(bool bPerception)
{
	m_bPerception = bPerception;
}

//=============================================================================
// �U���J�E���g�̐ݒ�
//=============================================================================
void CEnemy::SetAttackCnt(int nAttackCnt)
{
	m_nAttackFlameCnt = nAttackCnt;
}