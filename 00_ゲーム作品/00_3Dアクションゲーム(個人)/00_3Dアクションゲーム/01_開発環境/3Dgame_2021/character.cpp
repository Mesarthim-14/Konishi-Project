//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "life_bar.h"
#include "life_frame.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "particle.h"
#include "effect_factory.h"
#include "stone_effect.h"
#include "stone.h"
#include "texture.h"
#include "guard_effect.h"
#include "number_3d.h"
#include "combo.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���

//=============================================================================
// static����������
//=============================================================================
 int CCharacter::m_nAllNum = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
{
	 m_pos = ZeroVector3;
	 m_posOld = ZeroVector3;
	 m_move = ZeroVector3;
	 m_rot = ZeroVector3;
	 m_state = STATE_NONE;
	 m_Ctype = CHARACTER_TYPE_NONE;
	 m_nLife = 0;
	 m_nAttack = 0;
	 m_nCharaNum = m_nAllNum++;
	 m_nWeaponTipNum = 0;
	 m_fAngle = 0.0f;
	 m_fSpeed = 0.0f;
	 m_bJump = false;
	 m_pLifeBar = nullptr;
	 m_pLifeFrame = nullptr;
	 m_fRadius = 0.0f;
	 m_fWeaponRadius = 0.0f;
	 m_bArmor = false;
	 memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	 m_nStateCounter = 0;
	 m_nAttackPowar = 0;
	 m_nMaxLife = 0;
	 m_nHitNumber = 0;
	 m_pMotion = nullptr;
	 m_nParts = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �����̑��
	m_pos = pos;	// ���W�̐ݒ�
	m_rot = rot;	// �p�x�̐ݒ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		// !nullcheck
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//�������̍폜
			delete m_apModelAnime[nCntModelNum];

			//�������̃N���A
			m_apModelAnime[nCntModelNum] = nullptr;
		}
	}

	// !nullcheck
	if (m_pMotion != nullptr)
	{
		//�������̍폜
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���C�t�̘g
	if (m_pLifeFrame != nullptr)
	{
		// �������̃N���A
		m_pLifeFrame->Uninit();
		m_pLifeFrame = nullptr;
	}

	// ���C�t�̘g
	if (m_pLifeBar != nullptr)
	{
		// �������̃N���A
		m_pLifeBar->Uninit();
		m_pLifeBar = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCharacter::Update()
{
	//�A�j���[�V�����̍X�V����
	ModelAnimeUpdate();

	// �d��
	Gravity();

	// ���n�̏���
	if (m_pos.y <= GROUND_RIMIT)
	{
		Landing(GROUND_RIMIT);
	}

	// �ړ��ʉ��Z
	m_pos += m_move;

	// �����蔻��
	BodyCollision();

	// ���G���Ԃ̂Ƃ�
	if (m_bArmor == true)
	{
		// �J�E���^�[��i�߂�
		m_nStateCounter++;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCharacter::Draw()
{
	// �`�揈��
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��i�����j���J�����O

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
}

//=============================================================================
// ���n�̏���
//=============================================================================
void CCharacter::Landing(float fPosY)
{
	m_move.y = 0.0f;
	m_pos.y = fPosY;
	m_bJump = false;

	// ���n�̏��
	if (m_bLanding == false)
	{
		m_bLanding = true;
	}
}

//=============================================================================
// �d��
//=============================================================================
void CCharacter::Gravity(void)
{
	// �d�͂�������
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// ����
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CCharacter::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFile�̃|�C���^�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���p�[�c�̐ݒ�
		m_nParts = pXfile->GetModelParts(FileNum);

		//���f���p�[�c�����J��Ԃ�
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);

			if (m_apModelAnime[nCntModel] == nullptr)
			{
				// ����������
				m_apModelAnime[nCntModel] = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot);

				// ���f���̏��擾
				std::vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

				// ���f���̐���
				m_apModelAnime[nCntModel]->SetModel(model.at(nCntModel));
			}

			//�e�q�\���̐ݒ�
			if (m_apModelAnime[nCntModel] != nullptr)
			{
				//�e���f���̏ꍇ
				if (nCntModel == 0)
				{
					m_apModelAnime[nCntModel]->SetParent(nullptr);
				}
				//�q���f���̏ꍇ
				else
				{
					//�����̐e����ݒ肷��
					m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[ModelFile.nParent]);
				}
			}
		}

		// nullcheck
		if (m_pMotion == nullptr)
		{
			// �C���X�^���X����
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// ���f���A�j���[�V����
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// ���[�V�����̍X�V����
	if (m_pMotion != nullptr)
	{
		// ���[�V�����̍X�V
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != nullptr)
	{
		// ���[�V�����̍X�V
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// �̗̓o�[�̐����֐�
//=============================================================================
void CCharacter::LifeBarCreate(D3DXVECTOR3 posFrame, D3DXVECTOR3 sizeFrame,
	D3DXVECTOR3 posBar, D3DXVECTOR3 sizeBar, D3DXCOLOR color, int nLife)
{
	// �����̑��
	m_nLife = nLife;		// ���C�t�̐ݒ�
	m_nMaxLife = nLife;		// ���C�t�̍ő吔�ݒ�

	// ���C�t�̃t���[��
	if (m_pLifeFrame == nullptr)
	{
		m_pLifeFrame = CLifeFrame::Create(posFrame, sizeFrame);
	}

	// HP�o�[�̐���
	if (m_pLifeBar == nullptr)
	{
		// �̗̓o�[
		m_pLifeBar = CLifeBar::Create(posBar, sizeBar,
			color, m_Ctype, nLife);
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
void CCharacter::BodyCollision(void)
{
	// �L�����N�^�[�̃|�C���^
	CCharacter *pCharacter = (CCharacter*)GetTop(PRIORITY_CHARACTER);

	while (pCharacter != nullptr)
	{
		// �����̔ԍ�����Ȃ��Ƃ�
		if (pCharacter->m_nCharaNum != m_nCharaNum)
		{
			// �~�`�Ɖ~�`�̓����蔻��
			if (CCollision::CollisionCircularAndCircular(
				m_pos, pCharacter->m_pos,
				m_fRadius, pCharacter->m_fRadius) == true)
			{
				if (pCharacter->m_Ctype == CHARACTER_TYPE_PLAYER)
				{
					// �O�ɉ����o��
					D3DXVECTOR3 vec = (pCharacter->GetPos() - m_pos);
					D3DXVec3Normalize(&vec, &vec);
					vec *= (pCharacter->m_fRadius + m_fRadius);

					D3DXVECTOR3 pos = pCharacter->GetPos();
					pCharacter->SetPos(GetPos() + vec);
				}
				else
				{
					// �O�ɉ����o��
					D3DXVECTOR3 vec = (m_pos - pCharacter->GetPos());
					D3DXVec3Normalize(&vec, &vec);
					vec *= (m_fRadius + pCharacter->m_fRadius);

					D3DXVECTOR3 pos = GetPos();
					SetPos(pCharacter->GetPos() + vec);
				}
			}
		}

		// ���̃|�C���^
		pCharacter = (CCharacter*)pCharacter->GetNext();
	}
}

//=============================================================================
// �U�����̓����蔻��
//=============================================================================
bool CCharacter::AttackCollision(void)
{
	switch (this->GetCType())
	{
	case CHARACTER_TYPE_PLAYER:
		// �v���C���[�̎�
	{
		// �L�����N�^�[�̃|�C���^
		CCharacter *pCharacter = (CCharacter*)GetTop(PRIORITY_CHARACTER);

		while (pCharacter != nullptr)
		{
			// �����̔ԍ�����Ȃ��Ƃ�
			if (pCharacter->m_Ctype == CHARACTER_TYPE_ENEMY)
			{
				// ���ꔻ��p�[�c���W�擾
				D3DXVECTOR3 pos = D3DXVECTOR3(
					pCharacter->GetModelAnime(pCharacter->GetHitNumber())->GetMtxWorld()._41,
					pCharacter->GetModelAnime(pCharacter->GetHitNumber())->GetMtxWorld()._42,
					pCharacter->GetModelAnime(pCharacter->GetHitNumber())->GetMtxWorld()._43);

				// �~�`�Ɖ~�`�̓����蔻��
				if (CCollision::CollisionCircularAndCircular(
					m_pos, pos,
					m_fWeaponRadius, pCharacter->m_fRadius) == true)
				{
					if (pCharacter->m_state != STATE_DAMAGE)
					{
						// �\�[�h�X�L��
						CEffectFactory::CreateEffect(pCharacter->m_pos,
							CEffectFactory::EFFECT_NUM_EXPLOSION);

						// �q�b�g�G�t�F�N�g
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_EFFECT);

						// �q�b�g�G�t�F�N�g
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_EXPLOSION);

						// �q�b�g�G�t�F�N�g
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_IMPACT);

						int nDamage = 0;

						// �\�[�h�X�L��
						if (m_pMotion->GetMotionState() == (int)(CPlayer::MOTION_SWORD_SKILL_000))
						{
							// �_���[�W�̒l
							nDamage = PLAYER_SKILL_ATTACK_DAMAGE;
						}
						else
						{
							// �_���[�W�̒l
							nDamage = PLAYER_ATTACK_DAMAGE;
						}

						// �_���[�W
						nDamage += rand() % PLAYER_ATTACK_RAND_DAMAGE - rand() % PLAYER_ATTACK_RAND_DAMAGE;

						// ������
						CPlayer *pPlayer = CGame::GetPlayer();

						int nNum = 0;

						if (pPlayer != nullptr)
						{
							// �R���{�̔{�������߂�
							nNum = (float)nDamage + ((float)pPlayer->GetCombo()->GetComboNum() * DAMAGE_MAG);

						}

						// ���̃L�����N�^�[�Ƀ_���[�W��^����
						pCharacter->AddDamage(nNum);

						// ��������
						CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
						pSound->Play(CSound::SOUND_LABEL_SE_SLASH);

						if (pPlayer->GetCombo() != nullptr)
						{
							// �R���{���̊֐�
							pPlayer->GetCombo()->Combo(nNum);
						}

						// �_���[�W�̏Ռ�
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_IMPACT_000);

						CNumber3d::Create(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponRootNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponRootNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponRootNum]->GetMtxWorld()._43),
							DAMAGE_NUM_SIZE, nNum);

						return true;
					}
				}
			}

			// ���̃|�C���^
			pCharacter = (CCharacter*)pCharacter->GetNext();
		}
	}
	break;

	case CHARACTER_TYPE_ENEMY:
	{
		// �G�l�~�[�̎�
		CPlayer *pPlayer = CGame::GetPlayer();

		D3DXVECTOR3 WorldPos = D3DXVECTOR3(
			m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
			m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
			m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43);

		// nullcheck
		if (pPlayer != nullptr)
		{
			// �~�`�Ɖ~�`�̓����蔻��
			if (CCollision::CollisionCircularAndCircular(
				WorldPos, pPlayer->m_pos,
				m_fWeaponRadius, pPlayer->m_fRadius) == true)
			{
				// ���G��Ԃ���Ȃ�������
				if (pPlayer->GetArmor() == false)
				{
					if (pPlayer->m_pMotion->GetMotionState() == CPlayer::MOTION_GUARD)
					{
						// �v���C���[�Ƀ_���[�W��^����
						pPlayer->AddDamage(m_nAttackPowar / PLAYER_GUARD_CUT_DAMAGE);

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
						pPlayer->AddDamage(m_nAttackPowar);
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

					return true;
				}
			}
		}
	}
	break;

	default:
		break;
	}

	return false;
}

//=============================================================================
// �_���[�W�̉��Z
//=============================================================================
void CCharacter::AddDamage(int nDamage)
{
	// 0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		m_nLife = 0;
	}
	else
	{
		m_nLife -= nDamage;
		SetState(STATE_DAMAGE);
		m_bArmor = true;

		// �������C�t�o�[���g���Ă�����
		if (m_pLifeBar != nullptr)
		{
			// ���C�t�o�[�̐ݒ�֐�
			m_pLifeBar->SubGage(nDamage);
		}
	}
}

//=============================================================================
// �񕜂̏���
//=============================================================================
void CCharacter::HeelLife(int nHeelNum)
{
	// 0�ȉ��ɂȂ�����
	if (m_nLife >= m_nMaxLife)
	{
		m_nLife = m_nMaxLife;
	}
	else
	{
		m_nLife += nHeelNum;
		SetState(STATE_DAMAGE);
		m_bArmor = true;

		// �������C�t�o�[���g���Ă�����
		if (m_pLifeBar != nullptr)
		{
			// ���C�t�o�[�̐ݒ�֐�
			m_pLifeBar->HealGage(nHeelNum);
		}
	}
}

//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �Â����W�̐ݒ�
//=============================================================================
void CCharacter::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
void CCharacter::SetState(STATE state)
{
	m_state = state;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �̗͂̐ݒ�
//=============================================================================
void CCharacter::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// �W�����v�̐ݒ�
//=============================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// �n�ʂɂ���t���O�ݒ�
//=============================================================================
void CCharacter::SetLanding(bool bLanding)
{
	m_bLanding = bLanding;
}

//=============================================================================
// ���a�̐ݒ�
//=============================================================================
void CCharacter::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

//=============================================================================
// �L�����N�^�[�̃^�C�v�ݒ�
//=============================================================================
void CCharacter::SetCType(CHARACTER_TYPE Ctype)
{
	m_Ctype = Ctype;
}

//=============================================================================
// �L�����N�^�[�̑��x�ݒ�
//=============================================================================
void CCharacter::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// ����̃p�[�c�ԍ��ݒ�
//=============================================================================
void CCharacter::SetWeaponTipNum(int nWeaponTipNum)
{
	m_nWeaponTipNum = nWeaponTipNum;
}

//=============================================================================
// ���̍��{�̃p�[�c�ԍ��ݒ�
//=============================================================================
void CCharacter::SetWeaponRootNum(int nWeaponRootNum)
{
	m_nWeaponRootNum = nWeaponRootNum;
}

//=============================================================================
// ����̔��a
//=============================================================================
void CCharacter::SetWeaponRadius(float fWeaponRadius)
{
	m_fWeaponRadius = fWeaponRadius;
}

//=============================================================================
// ���G�t���O�ݒ�
//=============================================================================
void CCharacter::SetArmor(bool bArmor)
{
	m_bArmor = bArmor;
}

//=============================================================================
// ��ԃJ�E���^�[�̐ݒ�
//=============================================================================
void CCharacter::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}

//=============================================================================
// �U���͂̐ݒ�
//=============================================================================
void CCharacter::SetAttackPower(int nAttackPowar)
{
	m_nAttackPowar = nAttackPowar;
}

//=============================================================================
// ���ꔻ��̐ݒ�
//=============================================================================
void CCharacter::SetHitNumber(int nHitNumber)
{
	m_nHitNumber = nHitNumber;
}