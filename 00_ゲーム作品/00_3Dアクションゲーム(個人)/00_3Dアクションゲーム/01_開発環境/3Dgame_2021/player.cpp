//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include <stdio.h>
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "life_bar.h"
#include "life_frame.h"
#include "collision.h"
#include "fade.h"
#include "sp_bar.h"
#include "ui_skill.h"
#include "light_effect.h"
#include "locus.h"
#include "particle.h"
#include "effect_factory.h"
#include "slashing_effect.h"
#include "guard_effect.h"
#include "ui_operation.h"
#include "texture.h"
#include "resource_manager.h"
#include "combo.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// �v���C���[�̈ړ���
#define PLAYER_AVOID_SPEED				(30.0f)				// �v���C���[�̉���
#define PLAYER_JUMP						(17.0f)				// �W�����v�̏���
#define STICK_SENSITIVITY				(50.0f)				// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)				// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS					(50.0f)				// ���a�̑傫��
#define PLAYER_WEAPON_RADIUS			(350.0f)			// ����̔��a
#define PLAYER_PARTS					(22)				// �v���C���[�̃p�[�c��
#define PLAYER_ARMOR_TIME				(150)				// ���G����
#define GAME_END_FLAME					(100)				// �Q�[�����I���t���[��
#define MAX_SP_NUM						(300)				// SP�̍ő吔
#define SKILL_SP_NUM					(100)				// �X�L���̏���Q�[�W
#define BLADE_EFFECT_INTER				(190)				// ���g�̃p�[�e�B�N���̊Ԋu
#define WEAPON_TIP_NUM					(20)				// ����̃p�[�c�ԍ�
#define WEAPON_ROOT_NUM					(21)				// ���̍����̃p�[�c�ԍ�
#define PLAYER_AVOID_FLAME				(20)				// �������
#define PLAYER_AVOID_END_FLAME			(15)				// ����̉�������
#define PLAYER_HP_REGENE_NUM			(5)					// �񕜂̒l
#define PLAYER_HP_REGENE_FLAME			(300)				// �񕜂̃t���[��
#define PLAYER_HIT_SP_HEAL_NUM			(10)				// SP�̉�

// �U�����[�V�����̏��
#define PLAYER_STAND_ATTACK_KEY_000		(2)					// ��i�ڂ̍U�����L���ȃL�[
#define PLAYER_NEXT_ATTACK_KEY_000		(3)					// ���̍U�����\�ȃL�[
#define PLAYER_ATTACK_SPEED_000			(40.0f)				// �U�����̈ړ�
#define PLAYER_ATTACK_SPEED_001			(30.0f)				// �U�����̈ړ�
#define PLAYER_STAND_ATTACK_KEY_001		(2)					// 2�i�ڂ̍U�����L���ȃL�[
#define PLAYER_NEXT_ATTACK_KEY_001		(2)					// ���̍U�����\�ȃL�[
#define PLAYER_STAND_ATTACK_KEY_002		(2)					// 3�i�ڂ̍U�����\�ȃL�[
#define PLAYER_SKILL_ATTACK_KEY_000		(5)					// �\�[�h�X�L���̍U�����L���ȃL�[
#define PLAYER_CIRCLE_EFFECT_INTER		(80)				// CIRCLE�G�t�F�N�g�̊Ԋu
#define PLAYER_SKILL_MOVE_000			(7.0f)				// �\�[�h�X�L�����̈ړ���
#define PLAYER_NEXT_ATTACK_KEY_002		(3)					// ���̍U���̔h���L�[

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ����������
		pPlayer->Init(pos, size);
	}

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bWalk = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_pSpBar = nullptr;
	m_pUiSkill = nullptr;
	m_pUiOperation = nullptr;
	m_bUseLocusEffect = true;
	m_bAvoid = false;
	m_bArmor = false;
	m_nAvoidCounter = 0;
	m_pGuardEffect = nullptr;
	m_bCircleEffect = false;
	m_nCircleInter = 0;
	m_nRegeneCounter = 0;
	m_pCombo = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter::Init(pos, rot);												// ���W�@�p�x
	SetRadius(PLAYER_RADIUS);												// ���a�̐ݒ�
	SetWeaponRadius(PLAYER_WEAPON_RADIUS);									// �U���͈�
	SetCType(CHARACTER_TYPE_PLAYER);										// �L�����N�^�[�̃^�C�v
	SetSpeed(PLAYER_SPEED);													// ���x�̐ݒ�
	SetWeaponTipNum(PARTS_NUM_COLLISION);									// ����̃p�[�c�ԍ�
	SetWeaponRootNum(PARTS_NUM_ROOT);										// ���̍��{�̃p�[�c�ԍ�
	LifeBarCreate(PLAYER_LIFE_FRAME_POS, PLAYER_LIFE_FRAME_SIZE,
		PLAYER_LIFE_BAR_POS, PLAYER_LIFE_BAR_SIZE,
		PLAYER_LIFE_BAR_COLOR, PLAYER_LIFE_NUM);							// ���C�t�o�[�̐���

	// SP�o�[�̐���
	if (m_pSpBar == nullptr)
	{
		m_pSpBar = CSpBar::Create(PLAYER_SP_BAR_POS, PLAYER_SP_BAR_SIZE, MAX_SP_NUM);
	}

	// �X�L����UI
	if (m_pUiSkill == nullptr)
	{
		m_pUiSkill = CUiSkill::Create(UI_SKILL_POS, UI_SKILL_SIZE, false);
	}

	// ������@��UI
	if (m_pUiOperation == nullptr)
	{
		m_pUiOperation = CUiOperation::Create(UI_OPERATION_POS, UI_OPERATION_SIZE, true);
	}

	// �R���{�̃|�C���^
	if (m_pCombo == nullptr)
	{
		// �R���{�̐���
		m_pCombo = CCombo::Create();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	// !nullcheck
	if (m_pCombo != nullptr)
	{
		// �R���{�̏I������
		m_pCombo->Uninit();
		delete m_pCombo;
		m_pCombo = nullptr;
	}

	// !nullcheck
	if (m_pSpBar != nullptr)
	{
		// Sp�o�[�I������
		m_pSpBar->Uninit();
		m_pSpBar = nullptr;
	}

	// !nullcheck
	if (m_pUiSkill != nullptr)
	{
		m_pUiSkill->Uninit();
		m_pUiSkill = nullptr;
	}

	// !nullcheck
	if (m_pUiOperation != nullptr)
	{
		// ����UI�̏I������
		m_pUiOperation->Uninit();
		m_pUiOperation = nullptr;
	}

	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// ����łȂ��Ƃ�
	if (m_bDraw == true)
	{
		// �L�[�{�[�h�X�V
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		// ���W���
		D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
		SetPosOld(pos);				// �Â����W�ۑ�

		// �v���C���[�̏��
		UpdateState();

		// ���[�V�������
		UpdateMotionState();

		// HP�̃��W�F�l����
		HpRegene();

		// �v���C���[�̐���
		PlayerControl();

		// �p�x�̍X�V����
		UpdateRot();

		// �����Ă���|�C���^�̍X�V����
		HasPtrUpdate();

		// �e�N���X�̍X�V����
		CCharacter::Update();

		// �T�[�N���̃G�t�F�N�g���g���Ă�����
		if (m_bCircleEffect == true)
		{
			m_nCircleInter++;
		}

		// ���ȏ��
		if (m_nCircleInter >= PLAYER_CIRCLE_EFFECT_INTER)
		{
			m_nCircleInter = 0;
			m_bCircleEffect = false;
		}

		// �}�b�v�̐���
		MapLimit();

		// �̗͂�0�ɂȂ�����
		if (GetLife() <= 0)
		{
			// ���񂾂Ƃ�
			Death();
		}
	}
	else
	{
		m_nEndCounter++;

		// �Q�[���I���̃t���[��
		if (m_nEndCounter >= GAME_END_FLAME)
		{
			// ���U���g��ʂ�
			CManager::GetFade()->SetFade(CManager::MODE_TYPE_TITLE);
			m_nEndCounter = 0;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	if (m_bDraw == true)
	{
		// �`�揈��
		CCharacter::Draw();
	}
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::UpdateState(void)
{
	STATE state = GetState();

	switch (state)
	{
	case STATE_NORMAL:
		// �ʏ���

		break;

	case STATE_DAMAGE:
	{// �_���[�W��Ԃ̎�

		// ��ԃJ�E���^�[�擾
		int nStateCounter = GetStateCounter();

		// ��莞�Ԍo�߂�����
		if (nStateCounter >= PLAYER_ARMOR_TIME)
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
// ���[�V�������
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// ���[�V�������
	switch (MotionState)
	{
	case MOTION_IDOL:
		// �ʏ���

		// ���G��ԉ���
		SetArmor(false);
		break;

	case MOTION_ATTACK:
		// �U�����[�V������

		// ���̃G�t�F�N�g
		SwordLight();

		// ���̋O��
		SwordLocus();

		// �U�����[�V����
		if (nKey == PLAYER_STAND_ATTACK_KEY_000)
		{
			if (m_bUseLocusEffect == false)
			{
				// ����̌��ݍ��W
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// �O�Ղ̃G�t�F�N�g����
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// �U�����̓����蔻��
			if (AttackCollision() == true)
			{
				if (m_pSpBar != nullptr)
				{
					// SP�̉�
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}
			}
		}
		break;
		
	case MOTION_JUMP:
		// �W�����v���[�V�����̎�

		// ���n���Ă���Ƃ�
		if (GetLanding() == true)
		{
			// �ʏ�ɖ߂�
			SetMotion(MOTION_IDOL);
		}
		break;

	case MOTION_ATTACK_000:
		// ��i�ڂ̍U��

		// ���̃G�t�F�N�g
		SwordLight();

		// ���݂̃L�[
		if (nKey == 0)
		{
			// �ړ��ʉ��Z
			AttackMove(PLAYER_ATTACK_SPEED_000);
		}

		if (nKey >= 1)
		{
			// ���̋O��
			SwordLocus();

			// �ړ��ʐݒ�
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));
		}

		// �U�����[�V����
		if (nKey == PLAYER_STAND_ATTACK_KEY_000)
		{
			// �O�Ղ̃G�t�F�N�g���g���Ă��Ȃ�������
			if (m_bUseLocusEffect == false)
			{
				// ����̌��ݍ��W
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// �O�Ղ̃G�t�F�N�g����
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;			// �t���O��ON
			}

			// �U�����̓����蔻��
			if (AttackCollision() == true)
			{
				// !nullcheck
				if (m_pSpBar != nullptr)
				{
					// SP�̉�
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}

			}
		}

		// ��i�ڂ̍U�����\�ȃL�[
		if (nKey == PLAYER_NEXT_ATTACK_KEY_000)
		{
			// ��i�ڂ̍U������
			Attack2();

			// ����̏���
			Avoid();
		}
		break;

	case MOTION_ATTACK_001:
		// ��i�ڂ̍U��

		// ���̃G�t�F�N�g
		SwordLight();

		// ���̋O��
		SwordLocus();

		if (nKey == 0)
		{
			// �ړ��ʉ��Z
			AttackMove(PLAYER_ATTACK_SPEED_001);
		}

		// �U�����[�V����
		if (nKey == PLAYER_STAND_ATTACK_KEY_001)
		{
			// �ړ��ʐݒ�
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

			// �O�Ղ̃G�t�F�N�g���g���Ă��Ȃ�������
			if (m_bUseLocusEffect == false)
			{
				// ����̌��ݍ��W
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// �O�Ղ̃G�t�F�N�g����
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// �U�����̓����蔻��
			if (AttackCollision() == true)
			{
				if (m_pSpBar != nullptr)
				{
					// SP�̉�
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}
			}

			// 3�i�ڂ̍U�����\�ȃL�[
			if (nKey >= PLAYER_NEXT_ATTACK_KEY_001)
			{
				// 3�i�ڂ̍U������
				Attack3();

				// ����̏���
				Avoid();
			}
		}
		break;

	case MOTION_ATTACK_002:
		// 3�i�ڂ̍U��

		// 3�i�ڂ̍U�����\�ȃL�[
		if (nKey >= 4)
		{
			if (nKey == 4)
			{
				if (nCountMotion == 0)
				{
					// ��̌��G�t�F�N�g
					CEffectFactory::CreateEffect(D3DXVECTOR3(
						GetModelAnime(PARTS_NUM_RIGHT_HAND)->GetMtxWorld()._41,
						GetModelAnime(PARTS_NUM_RIGHT_HAND)->GetMtxWorld()._42,
						GetModelAnime(PARTS_NUM_RIGHT_HAND)->GetMtxWorld()._43),
						CEffectFactory::EFFECT_NUM_ARM_LIGHT);
				}
			}

			// 
			if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0))
			{
				// !nullcheck
				if (m_pSpBar != nullptr)
				{
					// �Q�[�W�����ʈȏゾ������
					if (m_pSpBar->GetGage() >= SKILL_SP_NUM)
					{
						// �ړ��ʂ̐ݒ�
						SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

						// �U�����[�V����
						SetMotion(MOTION_SWORD_SKILL_000);

						// ���̐ݒ�
						CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
						pSound->Play(CSound::SOUND_LABEL_SE_SWORD_SKILL);

						// SP�o�[�̃Q�[�W�����炷
						m_pSpBar->SubGage(SKILL_SP_NUM);

						return;
					}
				}

			}
			// 3�i�ڂ̍U������
			if (UseSkill() == true)
			{
				return;
			}

			// ����̏���
			Avoid();
		}

		// ���̌�����
		SwordLight();

		// ���̋O��
		SwordLocus();

		if (nKey == 0)
		{
			// �ړ��ʐݒ�
			AttackMove(PLAYER_ATTACK_SPEED_001);
		 }

		// �U�����[�V����
		if (nKey == PLAYER_STAND_ATTACK_KEY_002)
		{
			// �ړ��ʐݒ�
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

			// ��ՃG�t�F�N�g���g���Ă��Ȃ�������
			if (m_bUseLocusEffect == false)
			{
				// ����̌��ݍ��W
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// �O�Ղ̃G�t�F�N�g����
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// �U�����̓����蔻��
			if (AttackCollision() == true)
			{
				// !nullcheck
				if (m_pSpBar != nullptr)
				{
					// SP�̉�
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}
			}
		}
		break;

	case MOTION_GUARD:
		// �K�[�h���[�V����

		// !nullcheck
		if (m_pGuardEffect != nullptr)
		{
			// �K�[�h�G�t�F�N�g�̈ʒu
			m_pGuardEffect->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + PLAYER_BASE_POS_Y, GetPos().z));
		}
		break;

		// �\�[�h�X�L��
	case MOTION_SWORD_SKILL_000:
		
		// ���̃G�t�F�N�g
		SwordLight();

		if (nKey == 0)
		{
			// �T�[�N���G�t�F�N�g���g���Ă��Ȃ��Ƃ�
			if (m_bCircleEffect == false)
			{
				// �T�[�N���G�t�F�N�g
				CEffectFactory::CreateEffect(GetPos(), CEffectFactory::EFFECT_NUM_CIRCLE);

				// �t���O��ON
				m_bCircleEffect = true;
			}
		}

		if (nKey >= 3)
		{
			// ���̋O��
			SwordLocus();

			if (nKey == 3)
			{
				// �ړ��ʐݒ�
				AttackMove(PLAYER_ATTACK_SPEED_000);
			}

			// �ړ��̏I���
			if (nKey == 6)
			{
				// �ړ��ʐݒ�
				SetMove(ZeroVector3);
			}
		}
		else
		{
			// �\�[�h�X�L���������̃p�[�e�B�N��
			CEffectFactory::CreateEffect(GetPos(),
				CEffectFactory::EFFECT_NUM_SWORD_SKILL);
		}

		// �U�����[�V����
		if (nKey == PLAYER_SKILL_ATTACK_KEY_000)
		{
			// ��ՃG�t�F�N�g���g���Ă��Ȃ�������
			if (m_bUseLocusEffect == false)
			{
				// ����̌��ݍ��W
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// �O�Ղ̃G�t�F�N�g����
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// �U�����̓����蔻��
			if (AttackCollision() == true)
			{

			}
		}
		break;

	case MOTION_DAMAGE:
		// ���ꃂ�[�V�����̎�
		if (GetArmor() == false)
		{
			// ���G���
			SetArmor(true);
		}

		// �ړ��ʐݒ�
		SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

		break;

	case MOTION_AVOID_STEP:
		// ������[�V����

		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	MOTION_STATE state = (MOTION_STATE)GetState();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	// �����Ԃ���Ȃ��Ƃ�
	if (state != MOTION_DAMAGE)
	{
		// �v���C���[�̈ړ�����
		Walk();

		// �K�[�h�̏���
		Guard();

		if (MotionState != MOTION_ATTACK && MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001
			&& MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000&& MotionState != MOTION_GUARD)
		{
			// �X�L���̏���
			UseSkill();
		}

		// !nullcheck
		if (m_pUiSkill != nullptr)
		{
			// �g���Ă��Ȃ�������
			if (m_pUiSkill->GetUse() == false)
			{
				// �W�����v�̏���
				Jump();

				// �U���̏���
				Attack();

				if (MotionState != MOTION_ATTACK && MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001 && MotionState != MOTION_DAMAGE
					&& MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000 && MotionState != MOTION_GUARD)
				{
					// ����̏���
					Avoid();
				}
			}
		}
	}

#ifdef _DEBUG
	// �f�o�b�O�R�}���h
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h�X�V

	// L�{�^���̎�
	if (pKeyboard->GetTrigger(DIK_L))
	{
		// �_���[�W��^����
		AddDamage(20);
	}

#endif
}

//=============================================================================
// �p�x�̍X�V����
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// �p�x�̐ݒ�
	SetRot(rot);
}

//=============================================================================
// �������Ă���|�C���^�̍X�V����
//=============================================================================
void CPlayer::HasPtrUpdate(void)
{
	// �R���{�̃|�C���^
	if (m_pCombo != nullptr)
	{
		// �R���{�̐���
		m_pCombo->Update();
	}

	// ����Ui�̐؂�ւ�
	if (m_pUiSkill != nullptr)
	{
		if (m_pUiSkill->GetUse() == true)
		{
			// �����UI������Ƃ�
			if (m_pUiOperation != nullptr)
			{
				m_pUiOperation->SetUse(false);
			}
		}
		else
		{
			// �����UI������Ƃ�
			if (m_pUiOperation != nullptr)
			{
				m_pUiOperation->SetUse(true);
			}
		}
	}
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	// ���[�J���ϐ�
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// �T�E���h�̃|�C���^
	float fAngle = CGame::GetCamera()->Get��();								// �J�����̊p�x
	D3DXVECTOR3 pos = GetPos();												// ���W
	D3DXVECTOR3 rot = GetRot();												// �p�x
	float fSpeed = GetSpeed();												// �X�s�[�h
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// ���[�V�����̏��

	if (MotionState != MOTION_ATTACK && MotionState != MOTION_GUARD && MotionState != MOTION_DAMAGE && m_bAvoid != true
		&& MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001 && MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000)
	{
		//���͂����݂���
		if ((js.lX != 0.0f || js.lY != 0.0f))
		{
			//�_���[�W���󂯂Ă��Ȃ��Ƃ��݈̂ړ�����
				bool bJump = GetJump();

				//�W�����v���Ă��Ȃ��Ƃ�
				if (bJump == false)
				{
					// ������Ԃɂ���
					m_bWalk = true;

					//���s���[�V�����̍Đ�
					SetMotion(MOTION_WALK);
				}

				float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
				float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

				// �ړ��ʐݒ�
				pos.x += sinf(fAngle + (fAngle2))* fSpeed;
				pos.z += cosf(fAngle + (fAngle2))* fSpeed;

				// �p�x�̐ݒ�
				m_rotDest.y = fAngle + (fAngle3);
		}
		else
		{
			// �����Ă�����
			if (m_bWalk == true)
			{
				//�ҋ@���[�V�������Đ�
				SetMotion(MOTION_IDOL);
				m_bWalk = false;
			}
		}

		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_W))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			// �ړ��ʁE�p�x�̐ݒ�
			pos.x -= sinf(fAngle)*fSpeed;
			pos.z -= cosf(fAngle)*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_S))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			// �ړ��ʁE�p�x�̐ݒ�
			pos.x += sinf((fAngle))*fSpeed;
			pos.z += cosf((fAngle))*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));

		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_A))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			// �ړ��ʁE�p�x�̐ݒ�
			pos.x += sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
			pos.z += cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));

		}
		// �E�Ɉړ�
		if (pKeyboard->GetPress(DIK_D))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			// �ړ��ʁE�p�x�̐ݒ�
			pos.x += sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
			pos.z += cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));

		}

		// ���W�ݒ�
		SetPos(pos);

		// �Â����W�擾
		D3DXVECTOR3 OldPos = GetOldPos();

		// �����Ă��Ȃ�������
		if (OldPos == pos)
		{
			// �ʏ탂�[�V����
			SetMotion(MOTION_IDOL);
		}
	}
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK && MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001 && m_bAvoid == false
		&& MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000 && MotionState != MOTION_GUARD && MotionState != MOTION_DAMAGE)
	{
		// �L�[�{�[�h���
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();
		
		bool bJump = GetJump();

		// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && bJump == false
			|| pKeyboard->GetTrigger(DIK_SPACE) && bJump == false)
		{
			// �ړ��ʐݒ�
			D3DXVECTOR3 move = GetMove();
			move.y = PLAYER_JUMP;
			SetMove(move);
			SetJump(true);
			m_bWalk = false;

			//�W�����v���[�V�����̍Đ�
			SetMotion(MOTION_JUMP);
			SetLanding(false);
		}
	}
}

//=============================================================================
// ���񂾂Ƃ��̏���
//=============================================================================
void CPlayer::Death(void)
{
	m_bDraw = false;
}

//=============================================================================
// �U���̏���
//=============================================================================
void CPlayer::Attack(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK_000 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK && m_bAvoid == false
		&& MotionState != MOTION_ATTACK_001 && MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000)
	{
		// ENTER�L�[���������Ƃ��E�R���g���[����X���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0)
			|| pKeyboard->GetTrigger(DIK_RETURN))
		{

			// �U�����[�V����
			SetMotion(MOTION_ATTACK_000);
		}
	}
}

//=============================================================================
// ��i�ڂ̍U���̏���
//=============================================================================
void CPlayer::Attack2(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK_001 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK && MotionState != MOTION_SWORD_SKILL_000)
	{
		// ENTER�L�[���������Ƃ��E�R���g���[����X���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0)
			|| pKeyboard->GetTrigger(DIK_RETURN))
		{
			// ��i�ڍU�����[�V����
			SetMotion(MOTION_ATTACK_001);

			// �ړ��ʂ̐ݒ�
			SetMove(ZeroVector3);
		}
	}
}

//=============================================================================
// 3�i�ڂ̍U���̏���
//=============================================================================
void CPlayer::Attack3(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK_002 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK&& MotionState != MOTION_SWORD_SKILL_000)
	{
		// ENTER�L�[���������Ƃ��E�R���g���[����X���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0)
			|| pKeyboard->GetTrigger(DIK_RETURN))
		{
			// ��i�ڍU�����[�V����
			SetMotion(MOTION_ATTACK_002);
		}
	}
}

//=============================================================================
// �K�[�h�̏���
//=============================================================================
void CPlayer::Guard(void)
{
		// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	// �K�[�h�̏���
	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_Y, 0) 
		|| pKeyboard->GetPress(DIK_G))
	{
		if (MotionState != MOTION_ATTACK_000 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK && m_bAvoid == false
			&& MotionState != MOTION_ATTACK_001 && MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000)
		{
			if (m_pUiSkill->GetUse() == false)
			{
				// �K�[�h���[�V����
				SetMotion(MOTION_GUARD);

				// �K�[�h�G�t�F�N�g���g���Ă��Ȃ�������
				if (m_pGuardEffect == nullptr)
				{
					// �K�[�h�G�t�F�N�g����
					m_pGuardEffect = CGuardEffect::Create(D3DXVECTOR3(GetPos().x, GetPos().y + PLAYER_BASE_POS_Y, GetPos().z), GUARD_EFFECT_SIZE);
				}
			}
		}
	}
	else
	{
		// !nullcheck
		if (m_pGuardEffect != nullptr)
		{
			// �K�[�h�G�t�F�N�g�I������
			m_pGuardEffect->Uninit();
			m_pGuardEffect = nullptr;
		}

		if (MotionState == MOTION_GUARD)
		{
			// �K�[�h���[�V����
			SetMotion(MOTION_IDOL);
		}
	}
}

//=============================================================================
// ����̏���
//=============================================================================
void CPlayer::Avoid(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
		|| pKeyboard->GetTrigger(DIK_T))
	{
		// ��������g�p�Ȃ�
		if (m_bAvoid == false)
		{
			// �U�����̓���
			AttackMove(PLAYER_ATTACK_SPEED_000);

			// ����̃X�e�b�v
			SetMotion(MOTION_AVOID_STEP);

			// �_�b�V��
			CEffectFactory::CreateEffect(GetPos(), CEffectFactory::EFFECT_NUM_DUSH_IMPACT);

			m_bAvoid = true;	// ���
			SetArmor(true);		// ���G����
		}
	}

	// ������g��ꂽ�Ƃ�
	if (m_bAvoid == true)
	{
		m_nAvoidCounter++;

		// ����̎���
		if (m_nAvoidCounter >= PLAYER_AVOID_FLAME)
		{
			m_nAvoidCounter = 0;
			m_bAvoid = false;
			SetMotion(MOTION_IDOL);
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));
		}
	}

	// ���G���ԉ���
	if (m_nAvoidCounter == PLAYER_AVOID_END_FLAME)
	{
		// ���G�̉���
		SetArmor(false);
	}
}

//=============================================================================
// ���̃G�t�F�N�g�̏���
//=============================================================================
void CPlayer::SwordLight(void)
{
	// ���̍��{�ƌ���̃��[���h���W�擾
	D3DXVECTOR3 Root = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	D3DXVECTOR3 Tip = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	//==========================================================
	// �x�N�g�����߂�
	//==========================================================
	// 2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
	D3DXVECTOR3 Vector = Tip - Root;

	// �x�N�g���̑傫�������߂�(��c^2 = a^2 * b^2)	����
	float fVectorSize = D3DXVec3Length(&Vector);
	
	for (int nCount = 0; nCount < fVectorSize / LIGHT_EFFECT_RADIAN_INTER; nCount++)
	{
		// ��������̃x�N�g����nCount�ŕ�����
		D3DXVECTOR3 pos = Root + (Vector / (fVectorSize / LIGHT_EFFECT_RADIAN_INTER)) * (float)nCount;

		if (int nNum = rand() % BLADE_EFFECT_INTER == 0)
		{
			// �\�[�h�X�L�����̓��g�p�[�e�B�N��
			CEffectFactory::CreateEffect(pos,
				CEffectFactory::EFFECT_NUM_SKILL_BLADE);
		}

		// �\�[�h�G�t�F�N�g
		CLightEffect::Create(pos, LIGHT_EFFECT_SIZE, LIGHT_EFFECT_LIFE);
	}
}

//=============================================================================
// ���̋O��
//=============================================================================
void CPlayer::SwordLocus(void)
{
	// ���_�̌Â����W�擾
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._43);

	// ����̌Â����W
	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._43);

	// ���_�̌��ݍ��W
	D3DXVECTOR3 Origin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	// ����̌��ݍ��W
	D3DXVECTOR3 Top = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	
	// �O�Ղ̐���
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		GetRot(), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE, pTexture->GetTexture(CTexture::TEXTURE_NUM_SWORD_LOCUS));
}

//=============================================================================
// �A�^�b�N���̓���
//=============================================================================
void CPlayer::AttackMove(float fSpeed)
{
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// �W���C�p�b�h�̎擾

	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);
	float fAngle = CGame::GetCamera()->Get��();

	// �X�e�B�b�N�����͂���Ă�����
	if (js.lY != 0 || js.lX != 0)
	{
		// �ړ��ʂ̏�����
		SetMove(ZeroVector3);

		// �ړ��ʂ̐ݒ�
		SetMove(D3DXVECTOR3(
			sinf(fAngle + (fAngle2))*fSpeed,
			0.0f,
			cosf(fAngle + (fAngle2))*fSpeed));

		// �p�x�̐ݒ�
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{
		// �ړ��ʂ̏�����
		SetMove(ZeroVector3);

		// �ړ��ʐݒ�
		SetMove(D3DXVECTOR3(
			-sinf(m_rotDest.y)*fSpeed,
			0.0f,
			-cosf(m_rotDest.y)*fSpeed));

		// �p�x�̐ݒ�
		m_rotDest.y = fAngle;
	}
}

//=============================================================================
// HP�̃��W�F�l����
//=============================================================================
void CPlayer::HpRegene(void)
{
	// �J�E���^�[��i�߂�
	m_nRegeneCounter++;

	// ���ʈȏゾ������
	if (m_nRegeneCounter >= PLAYER_HP_REGENE_FLAME)
	{
		// ���C�t�o�[���g���Ă�����
		if (GetLifeBar() != nullptr)
		{
			// ���Z
			HeelLife(PLAYER_HP_REGENE_NUM);
			m_nRegeneCounter = 0;
		}
	}
}

//=============================================================================
// �X�L���̎g�p����
//=============================================================================
bool CPlayer::UseSkill(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// K�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_R_TRIGGER, 0)
		|| pKeyboard->GetPress(DIK_RSHIFT))
	{
		// !nullcheck
		if (m_pUiSkill != nullptr)
		{
			// �g���ĂȂ�������
			if (m_pUiSkill->GetUse() == false)
			{
				// �X�L����UI��`�悷��
				m_pUiSkill->SetUse(true);
			}
		}

		// K�L�[���������Ƃ��E�R���g���[����B���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
			|| pKeyboard->GetTrigger(DIK_1))
		{
			// !nullcheck
			if (m_pSpBar != nullptr)
			{
				// �Q�[�W�����ʈȏゾ������
				if (m_pSpBar->GetGage() >= SKILL_SP_NUM)
				{
					// �ړ��ʂ̐ݒ�
					SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

					// �U�����[�V����
					SetMotion(MOTION_SWORD_SKILL_000);

					// ���̐ݒ�
					CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
					pSound->Play(CSound::SOUND_LABEL_SE_SWORD_SKILL);

					// SP�o�[�̃Q�[�W�����炷
					m_pSpBar->SubGage(SKILL_SP_NUM);
				}
			}
		}

		return true;
	}
	else
	{
		// !nullcheck
		if (m_pUiSkill != nullptr)
		{
			// �g���Ă���
			if (m_pUiSkill->GetUse() == true)
			{
				// �X�L����UI��`�悷��
				m_pUiSkill->SetUse(false);
			}
		}

	}
	return false;
}

//=============================================================================
// �͈͊O�ɍs���Ȃ��悤�ɂ��鏈��
//=============================================================================
void CPlayer::MapLimit(void)
{
	// ���W�擾
	D3DXVECTOR3 pos = GetPos();

	//�E
	if (pos.x > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(MAP_LIMIT, pos.y, pos.z));
	}

	//��
	if (pos.x <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(-MAP_LIMIT, pos.y, pos.z));
	}

	//��
	if (pos.z > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, MAP_LIMIT));
	}

	//��O
	if (pos.z <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, -MAP_LIMIT));
	}
}