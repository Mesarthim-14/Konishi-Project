//=============================================================================
//
// ��̐����N���X [stone_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "stone_effect.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "texture.h"
#include "stone.h"
#include "xfile.h"
#include "effect_factory.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define STONE_TEXTURE_NAME	("data/Text/stone_effect.txt")	// �t�@�C���̖��O
#define STONE_EFFECT_RADIAN	(400.0f)						// ��̃G�t�F�N�g�̔��a

//=============================================================================
// static������
//=============================================================================
CStoneEffect::STONE CStoneEffect::m_Stone[STONE_NUM_MAX] = {};			// �p�[�e�B�N��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStoneEffect::CStoneEffect()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStoneEffect::~CStoneEffect()
{

}

//=============================================================================
// ��̃G�t�F�N�g����
//=============================================================================
void CStoneEffect::CreateStone(D3DXVECTOR3 pos)
{
	// ��̎�ނ�for��
	for (int nStoneCnt = 0; nStoneCnt < STONE_NUM_MAX; nStoneCnt++)
	{
		// ��̌�����
		for (int nCount = 0; nCount < m_Stone[nStoneCnt].nNum; nCount++)
		{
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(
				pos.x + STONE_EFFECT_RADIAN * cosf(D3DXToRadian(nCount * 360 / m_Stone[nStoneCnt].nNum)),
				pos.y,
				pos.z + STONE_EFFECT_RADIAN * sinf(D3DXToRadian(nCount * 360 / m_Stone[nStoneCnt].nNum)));

			D3DXVECTOR3 move = D3DXVECTOR3(
				cosf(D3DXToRadian(360 / m_Stone[nStoneCnt].nNum *nCount)) *m_Stone[nStoneCnt].move.x,
				(float)(rand() % (int)m_Stone[nStoneCnt].move.y + rand() % (int)m_Stone[nStoneCnt].move.y),
				sinf(D3DXToRadian(nCount * (360 / m_Stone[nStoneCnt].nNum)))*m_Stone[nStoneCnt].move.z);

			// ��̐���
			CStone::Create(pos, move, m_Stone[nStoneCnt], (CXfile::XFILE_NUM)((int)CXfile::XFILE_NUM_STONE_000 + nStoneCnt));
		}
	}

	// �y���G�t�F�N�g�̐���
	CEffectFactory::CreateEffect(pos, CEffectFactory::EFFECT_NUM_SAND_SMOKE);
}

//=============================================================================
// ��̃t�@�C���ǂݍ���
//=============================================================================
HRESULT CStoneEffect::ReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aStoneName[1024];
	int nStoneIndex = 0;	// ���f���̃C���f�b�N�X

	// �t�@�C���I�[�v��
	pFile = fopen(STONE_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aStoneName);

			if (strcmp(aStoneName, "STONESET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
				nStoneIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aStoneName, "END_STONESET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aStoneName);

					if (strcmp(aStoneName, "EFFECTSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aStoneName, "END_EFFECTSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aStoneName);

							if (strcmp(aStoneName, "SIZE") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Stone[nStoneIndex].size.x,
									&m_Stone[nStoneIndex].size.y,
									&m_Stone[nStoneIndex].size.z);
							}
							if (strcmp(aStoneName, "RANDMOVE") == 0)
							{
								// �ړ���
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Stone[nStoneIndex].move.x,
									&m_Stone[nStoneIndex].move.y,
									&m_Stone[nStoneIndex].move.z);
							}
							if (strcmp(aStoneName, "DISTANCE") == 0)
							{
								// ����
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Stone[nStoneIndex].Distance.x,
									&m_Stone[nStoneIndex].Distance.y,
									&m_Stone[nStoneIndex].Distance.z);
							}
							if (strcmp(aStoneName, "LIFE") == 0)
							{
								// �̗�
								sscanf(aHeadData, "%*s %*s %d", &m_Stone[nStoneIndex].nLife);
							}
							if (strcmp(aStoneName, "NUM") == 0)
							{
								// ��
								sscanf(aHeadData, "%*s %*s %d", &m_Stone[nStoneIndex].nNum);
							}
							if (strcmp(aStoneName, "COLOR") == 0)
							{
								// �F
								sscanf(aHeadData, "%*s %*s %f %f %f %f",
									&m_Stone[nStoneIndex].color.r,
									&m_Stone[nStoneIndex].color.g,
									&m_Stone[nStoneIndex].color.b,
									&m_Stone[nStoneIndex].color.a);
							}
						}

						//�C���f�b�N�X���P�i�߂�
						nStoneIndex++;
					}
				}
			}

		} while (strcmp(aStoneName, "END_SCRIPT") != 0);

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