//=============================================================================
//
// コボルトエネミークラス [kobold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define KOBOLD_LIFE					(15000)						// コボルトの体力
#define KOBOLD_RADIUS				(500.0f)					// コボルトの大きさ
#define KOBOLD_SPEED				(13.0f)						// コボルトの速さ
#define KOBOLD_ATTACK_INTER			(300)						// 攻撃の間隔
#define KOBOLD_ATTACK_PARTS_NUM		(12)						// 攻撃のパーツ番号
#define KOBOLD_WEAPON_RADIUS		(600.0f)					// 武器の半径
#define KOBOLD_ARMOR_FLAME			(9)							// 無敵時間のフレーム
#define KOBOLD_ATTACK_POWAR			(20)						// 攻撃力
#define KOBOLD_JUMP_POWER			(40.0f)						// ジャンプの強さ
#define KOBOLD_SMOKE_INTER			(5)							// 煙を出す間隔
#define KOBOLD_JUMP_CIRCLE			(2500)						// 当たり判定
#define KOBOLD_ROAR_CIRCLE_INTER	(30)						// 小さい円を出す間隔
#define KOBOLD_ROAR_CIRCLE_DIS		(4500)						// 小さい円を出す距離
#define KOBOLD_JUMP_EFFECT_FLAME	(17)						// ジャンプ時のエフェクトを出すフレーム

//=============================================================================
// コンストラクタ
//=============================================================================
CKobold::CKobold(PRIORITY nPriority)
{
	m_nSmokeCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CKobold::~CKobold()
{
}

//=============================================================================
// オブジェクト生成
//=============================================================================
CKobold * CKobold::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// メモリ確保
	CKobold *pKobold = new CKobold;

	// 初期化処理
	pKobold->Init(pos, rot);

	return pKobold;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CKobold::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	// モデル情報取得
	CXfile *pXfile = GET_XFILE_PTR;

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_KOBOLD);
	}

	CEnemy::Init(pos, rot);													// 初期化処理
	SetLife(KOBOLD_LIFE);													// ライフの生成
	SetRadius(KOBOLD_RADIUS);												// 半径の設定
	SetSpeed(KOBOLD_SPEED);													// 速さの設定
	SetActive(true);														// 敵視するかの設定
	SetAttackInter(KOBOLD_ATTACK_INTER);									// 攻撃の間隔を設定
	SetWeaponTipNum(KOBOLD_ATTACK_PARTS_NUM);								// 攻撃パーツの番号を設定
	SetWeaponRadius(KOBOLD_WEAPON_RADIUS);									// 武器の半径
	SetArmorFlame(KOBOLD_ARMOR_FLAME);										// 無敵時間の設定
	SetAttackPower(KOBOLD_ATTACK_POWAR);									// 攻撃力の設定
	SetHitNumber((int)KOBOLD_PARTS_NUM_BODY_COLLISION);						// やられ判定のパーツ
	LifeBarCreate(ENEMY_LIFE_FRAME_POS, ENEMY_LIFE_FRAME_SIZE,				// ライフバーの生成
		ENEMY_LIFE_BAR_POS, ENEMY_LIFE_BAR_SIZE,
		ENEMY_LIFE_BAR_COLOR, KOBOLD_LIFE);	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CKobold::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CKobold::Update(void)
{
	// 煙のカウンターを進める
	m_nSmokeCounter++;

	if (m_nSmokeCounter % KOBOLD_SMOKE_INTER == 0)
	{
		// 光のエフェクト
		CEffectFactory::CreateEffect(D3DXVECTOR3(
			GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
			GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42 - 800.0f,
			GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
			CEffectFactory::EFFECT_NUM_KOBOLD_SMOKE);
	}

	// 状態更新
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// 更新処理
	CEnemy::Update();

	// 座標代入
	D3DXVECTOR3 pos = GetPos();		// 現在の座標取得
	SetPosOld(pos);					// 古い座標保存
}

//=============================================================================
// 描画処理
//=============================================================================
void CKobold::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}


//=============================================================================
// モーション状態
//=============================================================================
void CKobold::UpdateMotionState(void)
{
	// モーション情報
	KOBOLD_MOTION MotionState = (KOBOLD_MOTION)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	switch (MotionState)
	{
		// 通常状態
	case KOBOLD_MOTION_IDOL:

		// 感知オフの時
		if (GetPerception() == false)
		{
			// 移動できるようにする
			SetPerception(true);
		}
		break;

		// ジャンプ攻撃
	case KOBOLD_MOTION_JUMP_ATTACK:

		// 現在のキー
		if (nKey == 0)
		{
			// 現在のモーションカウント
			if (nCountMotion == 0)
			{	
				// 光のエフェクト
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_ATTACK_CIRCLE);

				// 光のエフェクト
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}

		// 現在のキー
		if (nKey == 2)
		{
			// 現在のモーションカウント
			if (nCountMotion == KOBOLD_JUMP_EFFECT_FLAME)
			{
				// ジャンプの煙
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_JUMP_SMOKE);

				// ジャンプの衝撃エフェクト
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_JUMP_IMPACT);
			}
		}

		// 現在のキー
		if (nKey == 5)
		{
			// 現在のモーションカウント
			if (nCountMotion == 0)
			{
				// プレイヤー情報
				CPlayer *pPlayer = CGame::GetPlayer();

				// nullchack
				if (pPlayer != nullptr)
				{
					// 当たり判定
					if (CCollision::CollisionCircularAndCircular(D3DXVECTOR3(
						GetModelAnime(KOBOLD_PARTS_NUM_BODY_COLLISION)->GetMtxWorld()._41,
						GetModelAnime(KOBOLD_PARTS_NUM_BODY_COLLISION)->GetMtxWorld()._42,
						GetModelAnime(KOBOLD_PARTS_NUM_BODY_COLLISION)->GetMtxWorld()._43),
						pPlayer->GetPos(),
						KOBOLD_JUMP_CIRCLE, pPlayer->GetRadius()) == true)
					{
						// 無敵状態じゃなかったら
						if (pPlayer->GetArmor() == false && pPlayer->GetJump() == false)
						{
							// ガード状態なら
							if (pPlayer->GetMotion()->GetMotionState() == CPlayer::MOTION_GUARD)
							{
								// プレイヤーにダメージを与える
								pPlayer->AddDamage(GetAttackPower() / PLAYER_GUARD_CUT_DAMAGE);

								// ガード時のパーティクル
								CEffectFactory::CreateEffect(D3DXVECTOR3(
									pPlayer->GetPos().x,
									pPlayer->GetPos().y,
									pPlayer->GetPos().z),
									CEffectFactory::EFFECT_NUM_GUARD_PARTICLE);

								if (pPlayer->GetGuardEffect() != nullptr)
								{
									// ガードの発光
									pPlayer->GetGuardEffect()->Luminous();
								}
							}
							else
							{
								// プレイヤーにダメージを与える
								pPlayer->AddDamage(GetAttackPower());
								pPlayer->SetMotion(CPlayer::MOTION_DAMAGE);

								// ダメージエフェクト
								CEffectFactory::CreateEffect(D3DXVECTOR3(
									pPlayer->GetPos().x,
									pPlayer->GetPos().y + PLAYER_BASE_POS_Y,
									pPlayer->GetPos().z),
									CEffectFactory::EFFECT_NUM_DAMAGE_EFFECT);

								// コンボの終了
								pPlayer->GetCombo()->ComboBreak();
							}
						}
					}
				}

				// 岩のエフェクト
				CStoneEffect::CreateStone(GetPos());
			}
		}

		break;

		// 叩きつけ攻撃
	case KOBOLD_MOTION_SMASH:

		// 現在のキー
		if (nKey == 0)
		{
			// 現在のモーションカウント
			if (nCountMotion == 0)
			{
				// 光のエフェクト
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}

		// 現在のキー
		if (nKey == 2)
		{
			// 当たり判定
			if (AttackCollision() == true)
			{

			}
		}

		// 現在のキー
		if (nKey == 3)
		{
			if (nCountMotion == 0)
			{
				// 煙エフェクト
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_JUMP_SMOKE);

				// 叩きつけの音
				CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
				pSound->Play(CSound::SOUND_LABEL_SE_STOMP);
			}
		}

		break;

		// 薙ぎ払い攻撃
	case KOBOLD_MOTION_WIPE:

		// 現在のキー
		if (nKey == 0)
		{
			// 現在のモーションカウント
			if (nCountMotion == 0)
			{
				// 光のエフェクト
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);
			}
		}
		else
		{
			// 軌跡を出す
			Locus();
		}

		// 現在のキー
		if (nKey == 2)
		{
			// 当たり判定
			if (AttackCollision() == true)
			{

			}
		}
		break;

		// 叫び声の攻撃
	case KOBOLD_MOTION_ROAR:

		// カウンター
		m_nRoarAttackCounter++;

		// カウンターが一定数以上で
		if (m_nRoarAttackCounter >= KOBOLD_ROAR_CIRCLE_INTER)
		{
			// 変数宣言
			int nNum = rand() % 360;					// 角度の設定
			int nDis = rand() % KOBOLD_ROAR_CIRCLE_DIS;	// 距離の設定

			// 叫び声の攻撃サークル
			CEffectFactory::CreateEffect(D3DXVECTOR3(
				GetPos().x + float(nDis *cosf(D3DXToRadian(nNum))),
				GetPos().y, 
				GetPos().z + float(nDis * sinf(D3DXToRadian(nNum)))),
				CEffectFactory::EFFECT_NUM_ROAR_CIRCLE);

			// 火柱を生成
			CEffectFactory::CreateEffect(D3DXVECTOR3(
				GetPos().x + float(nDis *cosf(D3DXToRadian(nNum))),
				GetPos().y,
				GetPos().z + float(nDis * sinf(D3DXToRadian(nNum)))),
				CEffectFactory::EFFECT_NUM_ROAR_FIRE);

			// カウンターを0にする
			m_nRoarAttackCounter = 0;
		}

		// 現在のキー
		if (nKey == 0)
		{
			// 現在のモーションカウンター
			if (nCountMotion == 0)
			{
				// 音の処理
				CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
				pSound->Play(CSound::SOUND_LABEL_SE_ROAR_CRY);

				// 攻撃時光のエフェクト
				CEffectFactory::CreateEffect(D3DXVECTOR3(
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._41,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._42,
					GetModelAnime(KOBOLD_PARTS_NUM_BODY)->GetMtxWorld()._43),
					CEffectFactory::EFFECT_NUM_ATTACK_LIGHT);

				// 叫び声時の赤い衝撃
				CEffectFactory::CreateEffect(GetPos(),
					CEffectFactory::EFFECT_NUM_ROAR_IMPACT);

			}
		}
		break;

		// やられモーション状態
	case KOBOLD_MOTION_DAMAGE:

		// 現在のキー
		if (nKey == 0)
		{
			// 現在のモーションカウント
			if (nCountMotion == 0)
			{
				// 光のエフェクト
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
// 攻撃の処理
//=============================================================================
void CKobold::Attack(void)
{
	// プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();		// メモリ確保
	D3DXVECTOR3 Ppos = pPlayer->GetPos();		// 座標取得

	// 直線距離の制限
	float fDisLimit = GetRadius() + pPlayer->GetRadius() + 100.0f;

	//自機を取得する
	float fPposX = Ppos.x, fPposZ = Ppos.z;			// 自機の座標
	float fEposX = GetPos().x, fEposZ = GetPos().z;	// 敵の座標
	float fAngle;									// 角度

	//角度を決める
	fAngle = atan2f((fEposX - fPposX), (fEposZ - fPposZ));

	// 角度の設定
	D3DXVECTOR3 rot = GetRot();
	SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));

	// 攻撃を乱数で決める
	switch (int nNum = rand() % 4)
	{
	case 0:
		// 攻撃モーション
		SetMotion(KOBOLD_MOTION_JUMP_ATTACK);
		break;

	case 1:
		// 攻撃モーション
		SetMotion(KOBOLD_MOTION_SMASH);
		break;

	case 2:
		// 攻撃モーション
		SetMotion(KOBOLD_MOTION_WIPE);
		break;

	case 3:
		// 攻撃モーション
	SetMotion(KOBOLD_MOTION_ROAR);
		break;
	}

	// 移動できないようにする
	SetPerception(false);
}

//=============================================================================
// 軌跡
//=============================================================================
void CKobold::Locus(void)
{
	// 原点の古い座標取得
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetOldMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetOldMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetOldMtxWorld()._43);

	// 剣先の古い座標
	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetOldMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetOldMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetOldMtxWorld()._43);

	// 原点の現在座標
	D3DXVECTOR3 Origin = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE)->GetMtxWorld()._43);

	// 剣先の現在座標
	D3DXVECTOR3 Top = D3DXVECTOR3(
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._41,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._42,
		GetModelAnime(KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE)->GetMtxWorld()._43);
	
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// 軌跡の生成
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		GetRot(), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE, pTexture->GetTexture(CTexture::TEXTURE_NUM_ENEMY_LOCUS));
}