//=============================================================================
//
// 咆哮時の炎クラス [roar_fire.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define ROAR_FIRE_COUNTER	(25)		// カウンター
#define ROAR_FIRE_LIFE		(200)		// ライフの設定
#define ROAR_LIGHT_FLAME	(33)		// ライトの出現
#define ROAR_ATTACK_CIRCLE	(1000.0f)	// 攻撃の円
#define ROAR_ATTACK_NUM		(15)		// 攻撃力

//=============================================================================
// インスタンス生成
//=============================================================================
CRoarFire * CRoarFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンス生成
	CRoarFire *pRoarFire = new CRoarFire;

	if (pRoarFire != nullptr)
	{
		// 初期化処理
		pRoarFire->Init(pos, size);

		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// テクスチャの設定
		pRoarFire->BindTexture(pTexture->GetSeparateTexture(pTexture->SEPARATE_TEX_ROAR_FIRE));
		
		// アニメーション設定
		pRoarFire->InitAnimation(
			pTexture->GetSparateTexInfo(pTexture->SEPARATE_TEX_ROAR_FIRE),
			pTexture->GetSparateTexLoop(pTexture->SEPARATE_TEX_ROAR_FIRE));
	}

	return pRoarFire;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CRoarFire::CRoarFire(PRIORITY Priority):CBillboard(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRoarFire::~CRoarFire()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRoarFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	// ライフの設定
	SetLife(ROAR_FIRE_LIFE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRoarFire::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRoarFire::Update(void)
{
	m_nCounter++;

	// カウンター
	if (m_nCounter >= ROAR_FIRE_COUNTER)
	{
		// 更新処理
		CBillboard::Update();

	}

	// ライトを出すカウンター
	if (m_nCounter == ROAR_LIGHT_FLAME)
	{
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
		pSound->Play(CSound::SOUND_LABEL_SE_ROAR_FIRE);

		D3DXVECTOR3 pos = GetPos();

		// エフェクト生成
		CEffectFactory::CreateEffect(pos, CEffectFactory::EFFECT_NUM_ROAR_LIGHT);

		// エフェクト生成
		CEffectFactory::CreateEffect(pos, CEffectFactory::EFFECT_NUM_JUMP_SMOKE);

		// 当たり判定
		Collision();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRoarFire::Draw(void)
{
	// カウンター
	if (m_nCounter >= ROAR_FIRE_COUNTER)
	{
		// 描画処理
		CBillboard::Draw();
	}
}

//=============================================================================
// 当たり判定の関数
//=============================================================================
void CRoarFire::Collision(void)
{
	// プレイヤーのポインタ
	CPlayer *pPlayer = CGame::GetPlayer();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// 円形と円形の当たり判定
		if (CCollision::CollisionCircularAndCircular(
			GetPos(), PlayerPos,
			ROAR_ATTACK_CIRCLE, pPlayer->GetRadius()) == true)
		{
			// 無敵状態じゃなかったら
			if (pPlayer->GetArmor() == false)
			{
				// ガードしていたら
				if (pPlayer->GetMotion()->GetMotionState() == CPlayer::MOTION_GUARD)
				{
					// プレイヤーにダメージを与える
					pPlayer->AddDamage(ROAR_ATTACK_NUM / PLAYER_GUARD_CUT_DAMAGE);

					// ガード時のパーティクル
					CEffectFactory::CreateEffect(D3DXVECTOR3(
						PlayerPos.x,
						PlayerPos.y,
						PlayerPos.z),
						CEffectFactory::EFFECT_NUM_GUARD_PARTICLE);

					// !nullcheck
					if (pPlayer->GetGuardEffect() != nullptr)
					{
						// ガードの発光
						pPlayer->GetGuardEffect()->Luminous();
					}
				}
				else
				{

					// プレイヤーにダメージを与える
					pPlayer->AddDamage(ROAR_ATTACK_NUM);

					// やられモーションへの
					pPlayer->SetMotion(CPlayer::MOTION_DAMAGE);

					// ダメージエフェクト
					CEffectFactory::CreateEffect(D3DXVECTOR3(
						PlayerPos.x,
						PlayerPos.y + PLAYER_BASE_POS_Y,
						PlayerPos.z),
						CEffectFactory::EFFECT_NUM_DAMAGE_EFFECT);

					// コンボの終了
					pPlayer->GetCombo()->ComboBreak();
				}
			}
		}
	}
}