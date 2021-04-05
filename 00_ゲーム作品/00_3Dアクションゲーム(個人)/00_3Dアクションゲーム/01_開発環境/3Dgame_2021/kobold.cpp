//=============================================================================
//
// �R�{���g�G�l�~�[�N���X [kobold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "kobold.h"
#include "manager.h"
#include "renderer.h"
#include "life_frame.h"
#include "life_bar.h"
#include "player.h"
#include "game.h"
#include "effect_factory.h"
#include "stone_effect.h"
#include "collision.h"
#include "texture.h"
#include "guard_effect.h"
#include "locus.h"
#include "combo.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define KOBOLD_LIFE					(15000)						// �R�{���g�̗̑�
#define KOBOLD_RADIUS				(500.0f)					// �R�{���g�̑傫��
#define KOBOLD_SPEED				(13.0f)						// �R�{���g�̑���
#define KOBOLD_ATTACK_INTER			(300)						// �U���̊Ԋu
#define KOBOLD_ATTACK_PARTS_NUM		(12)						// �U���̃p�[�c�ԍ�
#define KOBOLD_WEAPON_RADIUS		(600.0f)					// ����̔��a
#define KOBOLD_ARMOR_FLAME			(9)							// ���G���Ԃ̃t���[��
#define KOBOLD_ATTACK_POWAR			(20)						// �U����
#define KOBOLD_JUMP_POWER			(40.0f)						// �W�����v�̋���
#define KOBOLD_SMOKE_INTER			(5)							// �����o���Ԋu
#define KOBOLD_JUMP_CIRCLE			(2500)						// �����蔻��
#define KOBOLD_ROAR_CIRCLE_INTER	(30)						// �������~���o���Ԋu
#define KOBOLD_ROAR_CIRCLE_DIS		(4500)						// �������~���o������
#define KOBOLD_JUMP_EFFECT_FLAME	(17)						// �W�����v���̃G�t�F�N�g���o���t���[��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKobold::CKobold(PRIORITY nPriority)
{
	m_nSmokeCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKobold::~CKobold()
{
}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CKobold * CKobold::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �������m��
	CKobold *pKobold = new CKobold;

	// ����������
	pKobold->Init(pos, rot);

	return pKobold;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKobold::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	// ���f�����擾
	CXfile *pXfile = GET_XFILE_PTR;

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_KOBOLD);
	}

	CEnemy::Init(pos, rot);													// ����������
	SetLife(KOBOLD_LIFE);													// ���C�t�̐���
	SetRadius(KOBOLD_RADIUS);												// ���a�̐ݒ�
	SetSpeed(KOBOLD_SPEED);													// �����̐ݒ�
	SetActive(true);														// �G�����邩�̐ݒ�
	SetAttackInter(KOBOLD_ATTACK_INTER);									// �U���̊Ԋu��ݒ�
	SetWeaponTipNum(KOBOLD_ATTACK_PARTS_NUM);								// �U���p�[�c�̔ԍ���ݒ�
	SetWeaponRadius(KOBOLD_WEAPON_RADIUS);									// ����̔��a
	SetArmorFlame(KOBOLD_ARMOR_FLAME);										// ���G���Ԃ̐ݒ�
	SetAttackPower(KOBOLD_ATTACK_POWAR);									// �U���͂̐ݒ�
	SetHitNumber((int)KOBOLD_PARTS_NUM_BODY_COLLISION);						// ���ꔻ��̃p�[�c
	LifeBarCreate(ENEMY_LIFE_FRAME_POS, ENEMY_LIFE_FRAME_SIZE,				// ���C�t�o�[�̐���
		ENEMY_LIFE_BAR_POS, ENEMY_LIFE_BAR_SIZE,
		ENEMY_LIFE_BAR_COLOR, KOBOLD_LIFE);	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKobold::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CKobold::Update(void)
{
	// ���̃J�E���^�[��i�߂�
	m_nSmokeCounter++;

	if (m_nSmokeCounter % KOBOLD_SMOKE_INTER == 0)
	{
		// ���̃G�t�F�N�g
		CEffectFactory::CreateEffect(D3DXVECTOR3(
			GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
			GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42 - 800.0f,
			GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
			CEffectFactory::EFFECT_NUM_KOBOLD_SMOKE);
	}

	// ��ԍX�V
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �X�V����
	CEnemy::Update();

	// ���W���
	D3DXVECTOR3 pos = GetPos();		// ���݂̍��W�擾
	SetPosOld(pos);					// �Â����W�ۑ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void CKobold::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}


//=============================================================================
// ���[�V�������
//=============================================================================
void CKobold::UpdateMotionState(void)
{
	// ���[�V�������
	KOBOLD_MOTION MotionState = (KOBOLD_MOTION)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	switch (MotionState)
	{
		// �ʏ���
	case KOBOLD_MOTION_IDOL:

		// ���m�I�t�̎�
		if (GetPerception() == false)
		{
			// �ړ��ł���悤�ɂ���
			SetPerception(true);
		}
		break;

		// �W�����v�U��
	case KOBOLD_MOTION_JUMP_ATTACK:

		// ���݂̃L�[
		if (nKey == 0)
		{
			// ���݂̃��[�V�����J�E���g
			if (nCountMotion == 0)
			{	
				// ���̃G�t�F�N�g
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_ATTACK_CIRCLE);

				// ���̃G�t�F�N�g
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}

		// ���݂̃L�[
		if (nKey == 2)
		{
			// ���݂̃��[�V�����J�E���g
			if (nCountMotion == KOBOLD_JUMP_EFFECT_FLAME)
			{
				// �W�����v�̉�
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_JUMP_SMOKE);

				// �W�����v�̏Ռ��G�t�F�N�g
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_JUMP_IMPACT);
			}
		}

		// ���݂̃L�[
		if (nKey == 5)
		{
			// ���݂̃��[�V�����J�E���g
			if (nCountMotion == 0)
			{
				// �v���C���[���
				CPlayer *pPlayer = CGame::GetPlayer();

				// nullchack
				if (pPlayer != nullptr)
				{
					// �����蔻��
					if (CCollision::CollisionCircularAndCircular(D3DXVECTOR3(
						GetModelAnime(KOBOLD_PARTS_NUM_BODY_COLLISION)->GetMtxWorld()._41,
						GetModelAnime(KOBOLD_PARTS_NUM_BODY_COLLISION)->GetMtxWorld()._42,
						GetModelAnime(KOBOLD_PARTS_NUM_BODY_COLLISION)->GetMtxWorld()._43),
						pPlayer->GetPos(),
						KOBOLD_JUMP_CIRCLE, pPlayer->GetRadius()) == true)
					{
						// ���G��Ԃ���Ȃ�������
						if (pPlayer->GetArmor() == false && pPlayer->GetJump() == false)
						{
							// �K�[�h��ԂȂ�
							if (pPlayer->GetMotion()->GetMotionState() == CPlayer::MOTION_GUARD)
							{
								// �v���C���[�Ƀ_���[�W��^����
								pPlayer->AddDamage(GetAttackPower() / PLAYER_GUARD_CUT_DAMAGE);

								// �K�[�h���̃p�[�e�B�N��
								CEffectFactory::CreateEffect(D3DXVECTOR3(
									pPlayer->GetPos().x,
									pPlayer->GetPos().y,
									pPlayer->GetPos().z),
									CEffectFactory::EFFECT_NUM_GUARD_PARTICLE);

								if (pPlayer->GetGuardEffect() != nullptr)
								{
									// �K�[�h�̔���
									pPlayer->GetGuardEffect()->Luminous();
								}
							}
							else
							{
								// �v���C���[�Ƀ_���[�W��^����
								pPlayer->AddDamage(GetAttackPower());
								pPlayer->SetMotion(CPlayer::MOTION_DAMAGE);

								// �_���[�W�G�t�F�N�g
								CEffectFactory::CreateEffect(D3DXVECTOR3(
									pPlayer->GetPos().x,
									pPlayer->GetPos().y + PLAYER_BASE_POS_Y,
									pPlayer->GetPos().z),
									CEffectFactory::EFFECT_NUM_DAMAGE_EFFECT);

								// �R���{�̏I��
								pPlayer->GetCombo()->ComboBreak();
							}
						}
					}
				}

				// ��̃G�t�F�N�g
				CStoneEffect::CreateStone(GetPos());
			}
		}

		break;

		// �@�����U��
	case KOBOLD_MOTION_SMASH:

		// ���݂̃L�[
		if (nKey == 0)
		{
			// ���݂̃��[�V�����J�E���g
			if (nCountMotion == 0)
			{
				// ���̃G�t�F�N�g
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}

		// ���݂̃L�[
		if (nKey == 2)
		{
			// �����蔻��
			if (AttackCollision() == true)
			{

			}
		}

		// ���݂̃L�[
		if (nKey == 3)
		{
			if (nCountMotion == 0)
			{
				// ���G�t�F�N�g
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_JUMP_SMOKE);

				// �@�����̉�
				CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
				pSound->Play(CSound::SOUND_LABEL_SE_STOMP);
			}
		}

		break;

		// �ガ�����U��
	case KOBOLD_MOTION_WIPE:

		// ���݂̃L�[
		if (nKey == 0)
		{
			// ���݂̃��[�V�����J�E���g
			if (nCountMotion == 0)
			{
				// ���̃G�t�F�N�g
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}
		else
		{
			// �O�Ղ��o��
			Locus();
		}

		// ���݂̃L�[
		if (nKey == 2)
		{
			// �����蔻��
			if (AttackCollision() == true)
			{

			}
		}
		break;

		// ���ѐ��̍U��
	case KOBOLD_MOTION_ROAR:

		// �J�E���^�[
		m_nRoarAttackCounter++;

		// �J�E���^�[����萔�ȏ��
		if (m_nRoarAttackCounter >= KOBOLD_ROAR_CIRCLE_INTER)
		{
			// �ϐ��錾
			int nNum = rand() % 360;					// �p�x�̐ݒ�
			int nDis = rand() % KOBOLD_ROAR_CIRCLE_DIS;	// �����̐ݒ�

			// ���ѐ��̍U���T�[�N��
			CEffectFactory::CreateEffect(D3DXVECTOR3(
				GetPos().x + float(nDis *cosf(D3DXToRadian(nNum))),
				GetPos().y, 
				GetPos().z + float(nDis * sinf(D3DXToRadian(nNum)))),
				CEffectFactory::EFFECT_NUM_ROAR_CIRCLE);

			// �Β��𐶐�
			CEffectFactory::CreateEffect(D3DXVECTOR3(
				GetPos().x + float(nDis *cosf(D3DXToRadian(nNum))),
				GetPos().y,
				GetPos().z + float(nDis * sinf(D3DXToRadian(nNum)))),
				CEffectFactory::EFFECT_NUM_ROAR_FIRE);

			// �J�E���^�[��0�ɂ���
			m_nRoarAttackCounter = 0;
		}

		// ���݂̃L�[
		if (nKey == 0)
		{
			// ���݂̃��[�V�����J�E���^�[
			if (nCountMotion == 0)
			{
				// ���̏���
				CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
				pSound->Play(CSound::SOUND_LABEL_SE_ROAR_CRY);

				// �U�������̃G�t�F�N�g
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);

				// ���ѐ����̐Ԃ��Ռ�
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_ROAR_IMPACT);

			}
		}
		break;

		// ���ꃂ�[�V�������
	case KOBOLD_MOTION_DAMAGE:

		// ���݂̃L�[
		if (nKey == 0)
		{
			// ���݂̃��[�V�����J�E���g
			if (nCountMotion == 0)
			{
				// ���̃G�t�F�N�g
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}

		break;
	}
}


//=============================================================================
// �U���̏���
//=============================================================================
void CKobold::Attack(void)
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

	// �U���𗐐��Ō��߂�
	switch (int nNum = rand() % 4)
	{
	case 0:
		// �U�����[�V����
		SetMotion(KOBOLD_MOTION_JUMP_ATTACK);
		break;

	case 1:
		// �U�����[�V����
		SetMotion(KOBOLD_MOTION_SMASH);
		break;

	case 2:
		// �U�����[�V����
		SetMotion(KOBOLD_MOTION_WIPE);
		break;

	case 3:
		// �U�����[�V����
	SetMotion(KOBOLD_MOTION_ROAR);
		break;
	}

	// �ړ��ł��Ȃ��悤�ɂ���
	SetPerception(false);
}

//=============================================================================
// �O��
//=============================================================================
void CKobold::Locus(void)
{
	// ���_�̌Â����W�擾
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetOldMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetOldMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetOldMtxWorld()._43);

	// ����̌Â����W
	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetOldMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetOldMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetOldMtxWorld()._43);

	// ���_�̌��ݍ��W
	D3DXVECTOR3 Origin = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetMtxWorld()._43);

	// ����̌��ݍ��W
	D3DXVECTOR3 Top = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._43);
	
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// �O�Ղ̐���
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		GetRot(), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE, pTexture->GetTexture(CTexture::TEXTURE_NUM_ENEMY_LOCUS));
}