//=============================================================================
//
// エフェクト生成クラス [effect_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define EFFECT_TEXTURE_NAME	("data/Text/effect.txt")

//=============================================================================
// static初期化
//=============================================================================
CEffectFactory::EFFECT CEffectFactory::m_Effect[EFFECT_NUM_MAX] = {};			// 構造体情報

//=============================================================================
// コンストラクタ
//=============================================================================
CEffectFactory::CEffectFactory()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CEffectFactory::~CEffectFactory()
{
}

//=============================================================================
// パーティクルの生成
//=============================================================================
void CEffectFactory::CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type)
{
	switch (type)
	{
	case EFFECT_NUM_EXPLOSION:
		// 爆発生成時のパーティクル生成
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSION].nNum; nCount++)
		{
			CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSION],
				CTexture::TEXTURE_NUM_PARTICLE);
		}
		break;

	case EFFECT_NUM_SWORD_SKILL:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SWORD_SKILL].nNum; nCount++)
		{
			// ソードスキル発生時のパーティクル生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 200.0f, pos.z), m_Effect[EFFECT_NUM_SWORD_SKILL],
				CTexture::TEXTURE_NUM_SKILL_START);
		}
		break;

	case EFFECT_NUM_SKILL_BLADE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SKILL_BLADE].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_SKILL_BLADE],
				CTexture::TEXTURE_NUM_SKILL_START);
		}
		break;

	case EFFECT_NUM_SHARP_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SHARP_EFFECT].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_SHARP_EFFECT],
				CTexture::SEPARATE_TEX_SHARP);
		}
		break;

	case EFFECT_NUM_ELECTRICITY_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ELECTRICITY_EFFECT].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_ELECTRICITY_EFFECT],
				CTexture::SEPARATE_TEX_ELECTRICITY);
		}
		break;

	case EFFECT_NUM_SMOKE_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SMOKE_EFFECT].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_SMOKE_EFFECT],
				CTexture::SEPARATE_TEX_SMOKE);
		}
		break;
	case EFFECT_NUM_HIT_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_EFFECT].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_HIT_EFFECT],
				CTexture::SEPARATE_TEX_HIT_EFFECT);
		}
		break;
	case EFFECT_NUM_HIT_EXPLOSION:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_EXPLOSION].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_HIT_EXPLOSION],
				CTexture::TEXTURE_NUM_PARTICLE);
		}
		break;

	case EFFECT_NUM_HIT_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_IMPACT].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(pos, m_Effect[EFFECT_NUM_HIT_IMPACT],
				CTexture::SEPARATE_TEX_HIT_IMPACT);
		}
		break;

	case EFFECT_NUM_SAND_SMOKE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SAND_SMOKE].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 200.0f, pos.z), m_Effect[EFFECT_NUM_SAND_SMOKE],
				CTexture::SEPARATE_TEX_SAND_SMOKE);
		}
		break;

	case EFFECT_NUM_CIRCLE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_CIRCLE].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect3D::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), m_Effect[EFFECT_NUM_CIRCLE],
				CTexture::SEPARATE_TEX_CIRCLE);
		}
		break;

	case EFFECT_NUM_ATTACK_LIGHT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ATTACK_LIGHT].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ATTACK_LIGHT],
				CTexture::SEPARATE_TEX_ATTACK_LIGHT);
		}
		break;

	case EFFECT_NUM_KOBOLD_SMOKE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_KOBOLD_SMOKE].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_KOBOLD_SMOKE],
				CTexture::SEPARATE_TEX_KOBOLD_SMOKE);
		}
		break;

	case EFFECT_NUM_JUMP_SMOKE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_JUMP_SMOKE].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_JUMP_SMOKE],
				CTexture::SEPARATE_TEX_JUMP_SMOKE);
		}
		break;

	case EFFECT_NUM_ATTACK_CIRCLE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ATTACK_CIRCLE].nNum; nCount++)
		{
			// 攻撃時のサークル
			CEffect3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ATTACK_CIRCLE],
				CTexture::SEPARATE_TEX_ATTACK_CIRCLE);
		}
		break;
	case EFFECT_NUM_JUMP_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_JUMP_IMPACT].nNum; nCount++)
		{
			// ジャンプ時のエフェクト
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y+5.0f, pos.z), m_Effect[EFFECT_NUM_JUMP_IMPACT],
				CTexture::TEXTURE_NUM_JUMP_IMPACT, false, IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_ROAR_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_IMPACT].nNum; nCount++)
		{
			// 咆哮時の衝撃
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_IMPACT],
				CTexture::TEXTURE_NUM_ROAR_IMPACT, false, IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_HIT_IMPACT_000:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_HIT_IMPACT_000].nNum; nCount++)
		{
			// ヒット時の衝撃
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_HIT_IMPACT_000],
				CTexture::TEXTURE_NUM_HIT_IMPACT_000, true, ATTACK_IMPACT_SCALE_NUM);
		}
		break;
	case EFFECT_NUM_ROAR_CIRCLE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_CIRCLE].nNum; nCount++)
		{
			// 咆哮時のサークル
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_CIRCLE],
				CTexture::SEPARATE_TEX_ATTACK_CIRCLE, false, IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_ARM_LIGHT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ARM_LIGHT].nNum; nCount++)
		{
			// 右手の光
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ARM_LIGHT],
				CTexture::SEPARATE_TEX_ARM_LIGHT);
		}
		break;

	case EFFECT_NUM_GUARD_PARTICLE:
		// 爆発生成時のパーティクル生成
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_GUARD_PARTICLE].nNum; nCount++)
		{
			CEffect::Create(pos, m_Effect[EFFECT_NUM_GUARD_PARTICLE],
				CTexture::TEXTURE_NUM_PARTICLE);
		}
		break;

	case EFFECT_NUM_DUSH_IMPACT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_DUSH_IMPACT].nNum; nCount++)
		{
			// ダッシュの衝撃
			CImpact::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, pos.z), m_Effect[EFFECT_NUM_DUSH_IMPACT],
				CTexture::TEXTURE_NUM_DUSH_IMPACT, false, DUSH_IMPACT_SCALE_NUM);
		}
		break;

	case EFFECT_NUM_DAMAGE_EFFECT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_DAMAGE_EFFECT].nNum; nCount++)
		{
			// ダメージ時のエフェクト
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_DAMAGE_EFFECT],
				CTexture::SEPARATE_TEX_DAMAGE_EFFECT);
		}
		break;

	case EFFECT_NUM_ROAR_FIRE:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_FIRE].nNum; nCount++)
		{
			// 咆哮時の炎
			CRoarFire::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_FIRE].size);
		}
		break;

	case EFFECT_NUM_ROAR_LIGHT:
		for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_ROAR_LIGHT].nNum; nCount++)
		{
			// ダメージ時のエフェクト
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), m_Effect[EFFECT_NUM_ROAR_LIGHT],
				CTexture::SEPARATE_TEX_ROAR_LIGHT);
		}
		break;
	}
}

//=============================================================================
// ファイルの読み込み
//=============================================================================
HRESULT CEffectFactory::ReadFile(void)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// モデルのインデックス

	// ファイルオープン
	pFile = fopen(EFFECT_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "PARTICLESET") == 0)
			{
				//インデックスを最初に戻す
				nParticleIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aParticleName, "END_PARTICLESET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "EFFECTSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aParticleName, "END_EFFECTSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].size.x,
									&m_Effect[nParticleIndex].size.y,
									&m_Effect[nParticleIndex].size.z);
							}
							if (strcmp(aParticleName, "MOVE") == 0)
							{
								// 移動量
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].move.x,
									&m_Effect[nParticleIndex].move.y,
									&m_Effect[nParticleIndex].move.z);
							}
							if (strcmp(aParticleName, "DISTANCE") == 0)
							{
								// 距離
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].Distance.x,
									&m_Effect[nParticleIndex].Distance.y, 
									&m_Effect[nParticleIndex].Distance.z);
							}
							if (strcmp(aParticleName, "LIFE") == 0)
							{
								// 体力
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nLife);
							}
							if (strcmp(aParticleName, "NUM") == 0)
							{
								// 数
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nNum);
							}
							if (strcmp(aParticleName, "COLOR") == 0)
							{
								// 色
								sscanf(aHeadData, "%*s %*s %f %f %f %f", 
									&m_Effect[nParticleIndex].color.r,
									&m_Effect[nParticleIndex].color.g, 
									&m_Effect[nParticleIndex].color.b,
									&m_Effect[nParticleIndex].color.a);
							}
							if (strcmp(aParticleName, "GRAVITY") == 0)
							{
								// 重力
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bGravity);
							}
							if (strcmp(aParticleName, "ALPHA") == 0)
							{
								// 透明にするか
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bAlpha);
							}
							if (strcmp(aParticleName, "ALPHANUM") == 0)
							{
								// アルファテストの値
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].nAlphaNum);
							}
							if (strcmp(aParticleName, "ANIMATION") == 0)
							{
								// アニメーション
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bAnimation);
							}
							if (strcmp(aParticleName, "BLEND") == 0)
							{
								// アニメーション
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}
							if (strcmp(aParticleName, "PRIORITY") == 0)
							{
								// アニメーション
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}

							
						}

						//インデックスを１つ進める
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//失敗した場合メッセージボックスを表示
		MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}