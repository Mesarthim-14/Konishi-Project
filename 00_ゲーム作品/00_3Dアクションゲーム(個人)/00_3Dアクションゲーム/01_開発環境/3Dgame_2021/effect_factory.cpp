//=============================================================================
//
// �G�t�F�N�g�����N���X [effect_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect_factory.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "effect_3d.h"
#include "impact.h"
#include "texture.h"
#include "roar_fire.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_TEXTURE_NAME	("data/Text/effect.txt")

//=============================================================================
// static������
//=============================================================================
CEffectFactory::EFFECT CEffectFactory::m_Effect[EFFECT_NUM_MAX] = {};			// �\���̏��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffectFactory::CEffectFactory()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffectFactory::~CEffectFactory()
{
}

//=============================================================================
// �p�[�e�B�N���̐���
//=============================================================================
void CEffectFactory::CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type)
{
	switch (type)
	{
	case EFFECT_NUM_EXPLOSION:
		// �����������̃p�[�e�B�N������
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSION].nNum; nCount++)
		{
			CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSION],
				CTexture::TEXTURE_NUM_PARTICLE);
		}
		break;

	case EFFECT_NUM_SWORD_SKILL:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SWORD_SKILL].nNum; nCount++)
		{
			// �\�[�h�X�L���������̃p�[�e�B�N������
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 200.0f, pos.z), m_Effect[EFFECT_NUM_SWORD_SKILL],
				CTexture::TEXTURE_NUM_SKILL_START);
		}
		break;

	case EFFECT_NUM_SKILL_BLADE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SKILL_BLADE].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_SKILL_BLADE],
				CTexture::TEXTURE_NUM_SKILL_START);
		}
		break;

	case EFFECT_NUM_SHARP_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SHARP_EFFECT].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_SHARP_EFFECT],
				CTexture::SEPARATE_TEX_SHARP);
		}
		break;

	case EFFECT_NUM_ELECTRICITY_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ELECTRICITY_EFFECT].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_ELECTRICITY_EFFECT],
				CTexture::SEPARATE_TEX_ELECTRICITY);
		}
		break;

	case EFFECT_NUM_SMOKE_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SMOKE_EFFECT].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_SMOKE_EFFECT],
				CTexture::SEPARATE_TEX_SMOKE);
		}
		break;
	case EFFECT_NUM_HIT_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_EFFECT].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_HIT_EFFECT],
				CTexture::SEPARATE_TEX_HIT_EFFECT);
		}
		break;
	case EFFECT_NUM_HIT_EXPLOSION:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_EXPLOSION].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_HIT_EXPLOSION],
				CTexture::TEXTURE_NUM_PARTICLE);
		}
		break;

	case EFFECT_NUM_HIT_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_IMPACT].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(pos, m_Effect[EFFECT_NUM_HIT_IMPACT],
				CTexture::SEPARATE_TEX_HIT_IMPACT);
		}
		break;

	case EFFECT_NUM_SAND_SMOKE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SAND_SMOKE].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 200.0f, pos.z), m_Effect[EFFECT_NUM_SAND_SMOKE],
				CTexture::SEPARATE_TEX_SAND_SMOKE);
		}
		break;

	case EFFECT_NUM_CIRCLE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_CIRCLE].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect3D::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), m_Effect[EFFECT_NUM_CIRCLE],
				CTexture::SEPARATE_TEX_CIRCLE);
		}
		break;

	case EFFECT_NUM_ATTACK_LIGHT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ATTACK_LIGHT].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ATTACK_LIGHT],
				CTexture::SEPARATE_TEX_ATTACK_LIGHT);
		}
		break;

	case EFFECT_NUM_KOBOLD_SMOKE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_KOBOLD_SMOKE].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_KOBOLD_SMOKE],
				CTexture::SEPARATE_TEX_KOBOLD_SMOKE);
		}
		break;

	case EFFECT_NUM_JUMP_SMOKE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_JUMP_SMOKE].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_JUMP_SMOKE],
				CTexture::SEPARATE_TEX_JUMP_SMOKE);
		}
		break;

	case EFFECT_NUM_ATTACK_CIRCLE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ATTACK_CIRCLE].nNum; nCount++)
		{
			// �U�����̃T�[�N��
			CEffect3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ATTACK_CIRCLE],
				CTexture::SEPARATE_TEX_ATTACK_CIRCLE);
		}
		break;
	case EFFECT_NUM_JUMP_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_JUMP_IMPACT].nNum; nCount++)
		{
			// �W�����v���̃G�t�F�N�g
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y+5.0f, pos.z), m_Effect[EFFECT_NUM_JUMP_IMPACT],
				CTexture::TEXTURE_NUM_JUMP_IMPACT, false, IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_ROAR_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_IMPACT].nNum; nCount++)
		{
			// ���K���̏Ռ�
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_IMPACT],
				CTexture::TEXTURE_NUM_ROAR_IMPACT, false, IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_HIT_IMPACT_000:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_IMPACT_000].nNum; nCount++)
		{
			// �q�b�g���̏Ռ�
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_HIT_IMPACT_000],
				CTexture::TEXTURE_NUM_HIT_IMPACT_000, true, ATTACK_IMPACT_SCALE_NUM);
		}
		break;
	case EFFECT_NUM_ROAR_CIRCLE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_CIRCLE].nNum; nCount++)
		{
			// ���K���̃T�[�N��
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_CIRCLE],
				CTexture::SEPARATE_TEX_ATTACK_CIRCLE, false, IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_ARM_LIGHT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ARM_LIGHT].nNum; nCount++)
		{
			// �E��̌�
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ARM_LIGHT],
				CTexture::SEPARATE_TEX_ARM_LIGHT);
		}
		break;

	case EFFECT_NUM_GUARD_PARTICLE:
		// �����������̃p�[�e�B�N������
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_GUARD_PARTICLE].nNum; nCount++)
		{
			CEffect::Create(pos, m_Effect[EFFECT_NUM_GUARD_PARTICLE],
				CTexture::TEXTURE_NUM_PARTICLE);
		}
		break;

	case EFFECT_NUM_DUSH_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_DUSH_IMPACT].nNum; nCount++)
		{
			// �_�b�V���̏Ռ�
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, pos.z), m_Effect[EFFECT_NUM_DUSH_IMPACT],
				CTexture::TEXTURE_NUM_DUSH_IMPACT, false, DUSH_IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_DAMAGE_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_DAMAGE_EFFECT].nNum; nCount++)
		{
			// �_���[�W���̃G�t�F�N�g
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_DAMAGE_EFFECT],
				CTexture::SEPARATE_TEX_DAMAGE_EFFECT);
		}
		break;

	case EFFECT_NUM_ROAR_FIRE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_FIRE].nNum; nCount++)
		{
			// ���K���̉�
			CRoarFire::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_FIRE].size);
		}
		break;

	case EFFECT_NUM_ROAR_LIGHT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_LIGHT].nNum; nCount++)
		{
			// �_���[�W���̃G�t�F�N�g
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_LIGHT],
				CTexture::SEPARATE_TEX_ROAR_LIGHT);
		}
		break;
	}
}

//=============================================================================
// �t�@�C���̓ǂݍ���
//=============================================================================
HRESULT CEffectFactory::ReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// ���f���̃C���f�b�N�X

	// �t�@�C���I�[�v��
	pFile = fopen(EFFECT_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "PARTICLESET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
				nParticleIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aParticleName, "END_PARTICLESET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "EFFECTSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aParticleName, "END_EFFECTSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].size.x,
									&m_Effect[nParticleIndex].size.y,
									&m_Effect[nParticleIndex].size.z);
							}
							if (strcmp(aParticleName, "MOVE") == 0)
							{
								// �ړ���
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].move.x,
									&m_Effect[nParticleIndex].move.y,
									&m_Effect[nParticleIndex].move.z);
							}
							if (strcmp(aParticleName, "DISTANCE") == 0)
							{
								// ����
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].Distance.x,
									&m_Effect[nParticleIndex].Distance.y, 
									&m_Effect[nParticleIndex].Distance.z);
							}
							if (strcmp(aParticleName, "LIFE") == 0)
							{
								// �̗�
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nLife);
							}
							if (strcmp(aParticleName, "NUM") == 0)
							{
								// ��
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nNum);
							}
							if (strcmp(aParticleName, "COLOR") == 0)
							{
								// �F
								sscanf(aHeadData, "%*s %*s %f %f %f %f", 
									&m_Effect[nParticleIndex].color.r,
									&m_Effect[nParticleIndex].color.g, 
									&m_Effect[nParticleIndex].color.b,
									&m_Effect[nParticleIndex].color.a);
							}
							if (strcmp(aParticleName, "GRAVITY") == 0)
							{
								// �d��
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bGravity);
							}
							if (strcmp(aParticleName, "ALPHA") == 0)
							{
								// �����ɂ��邩
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bAlpha);
							}
							if (strcmp(aParticleName, "ALPHANUM") == 0)
							{
								// �A���t�@�e�X�g�̒l
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].nAlphaNum);
							}
							if (strcmp(aParticleName, "ANIMATION") == 0)
							{
								// �A�j���[�V����
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bAnimation);
							}
							if (strcmp(aParticleName, "BLEND") == 0)
							{
								// �A�j���[�V����
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}
							if (strcmp(aParticleName, "PRIORITY") == 0)
							{
								// �A�j���[�V����
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}

							
						}

						//�C���f�b�N�X���P�i�߂�
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}