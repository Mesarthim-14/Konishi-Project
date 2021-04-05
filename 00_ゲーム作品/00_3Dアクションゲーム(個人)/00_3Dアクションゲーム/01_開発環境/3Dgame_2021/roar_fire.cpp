//=============================================================================
//
// ���K���̉��N���X [roar_fire.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "roar_fire.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "texture.h"
#include "effect_factory.h"
#include "collision.h"
#include "game.h"
#include "combo.h"
#include "guard_effect.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ROAR_FIRE_COUNTER	(25)		// �J�E���^�[
#define ROAR_FIRE_LIFE		(200)		// ���C�t�̐ݒ�
#define ROAR_LIGHT_FLAME	(33)		// ���C�g�̏o��
#define ROAR_ATTACK_CIRCLE	(1000.0f)	// �U���̉~
#define ROAR_ATTACK_NUM		(15)		// �U����

//=============================================================================
// �C���X�^���X����
//=============================================================================
CRoarFire * CRoarFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X����
	CRoarFire *pRoarFire = new CRoarFire;

	if (pRoarFire != nullptr)
	{
		// ����������
		pRoarFire->Init(pos, size);

		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// �e�N�X�`���̐ݒ�
		pRoarFire->BindTexture(pTexture->GetSeparateTexture(pTexture->SEPARATE_TEX_ROAR_FIRE));
		
		// �A�j���[�V�����ݒ�
		pRoarFire->InitAnimation(
			pTexture->GetSparateTexInfo(pTexture->SEPARATE_TEX_ROAR_FIRE),
			pTexture->GetSparateTexLoop(pTexture->SEPARATE_TEX_ROAR_FIRE));
	}

	return pRoarFire;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRoarFire::CRoarFire(PRIORITY Priority):CBillboard(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRoarFire::~CRoarFire()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRoarFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// ���C�t�̐ݒ�
	SetLife(ROAR_FIRE_LIFE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRoarFire::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRoarFire::Update(void)
{
	m_nCounter++;

	// �J�E���^�[
	if (m_nCounter >= ROAR_FIRE_COUNTER)
	{
		// �X�V����
		CBillboard::Update();

	}

	// ���C�g���o���J�E���^�[
	if (m_nCounter == ROAR_LIGHT_FLAME)
	{
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
		pSound->Play(CSound::SOUND_LABEL_SE_ROAR_FIRE);

		D3DXVECTOR3 pos = GetPos();

		// �G�t�F�N�g����
		CEffectFactory::CreateEffect(pos, CEffectFactory::EFFECT_NUM_ROAR_LIGHT);

		// �G�t�F�N�g����
		CEffectFactory::CreateEffect(pos, CEffectFactory::EFFECT_NUM_JUMP_SMOKE);

		// �����蔻��
		Collision();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRoarFire::Draw(void)
{
	// �J�E���^�[
	if (m_nCounter >= ROAR_FIRE_COUNTER)
	{
		// �`�揈��
		CBillboard::Draw();
	}
}

//=============================================================================
// �����蔻��̊֐�
//=============================================================================
void CRoarFire::Collision(void)
{
	// �v���C���[�̃|�C���^
	CPlayer *pPlayer = CGame::GetPlayer();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �~�`�Ɖ~�`�̓����蔻��
		if (CCollision::CollisionCircularAndCircular(
			GetPos(), PlayerPos,
			ROAR_ATTACK_CIRCLE, pPlayer->GetRadius()) == true)
		{
			// ���G��Ԃ���Ȃ�������
			if (pPlayer->GetArmor() == false)
			{
				// �K�[�h���Ă�����
				if (pPlayer->GetMotion()->GetMotionState() == CPlayer::MOTION_GUARD)
				{
					// �v���C���[�Ƀ_���[�W��^����
					pPlayer->AddDamage(ROAR_ATTACK_NUM / PLAYER_GUARD_CUT_DAMAGE);

					// �K�[�h���̃p�[�e�B�N��
					CEffectFactory::CreateEffect(D3DXVECTOR3(
						PlayerPos.x,
						PlayerPos.y,
						PlayerPos.z),
						CEffectFactory::EFFECT_NUM_GUARD_PARTICLE);

					// !nullcheck
					if (pPlayer->GetGuardEffect() != nullptr)
					{
						// �K�[�h�̔���
						pPlayer->GetGuardEffect()->Luminous();
					}
				}
				else
				{

					// �v���C���[�Ƀ_���[�W��^����
					pPlayer->AddDamage(ROAR_ATTACK_NUM);

					// ���ꃂ�[�V�����ւ�
					pPlayer->SetMotion(CPlayer::MOTION_DAMAGE);

					// �_���[�W�G�t�F�N�g
					CEffectFactory::CreateEffect(D3DXVECTOR3(
						PlayerPos.x,
						PlayerPos.y + PLAYER_BASE_POS_Y,
						PlayerPos.z),
						CEffectFactory::EFFECT_NUM_DAMAGE_EFFECT);

					// �R���{�̏I��
					pPlayer->GetCombo()->ComboBreak();
				}
			}
		}
	}
}