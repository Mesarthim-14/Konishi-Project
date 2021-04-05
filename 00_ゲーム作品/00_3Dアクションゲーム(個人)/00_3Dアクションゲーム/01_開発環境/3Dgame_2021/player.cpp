//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// プレイヤーの移動量
#define PLAYER_AVOID_SPEED				(30.0f)				// プレイヤーの回避量
#define PLAYER_JUMP						(17.0f)				// ジャンプの処理
#define STICK_SENSITIVITY				(50.0f)				// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)				// キャラクターの回転する速度
#define PLAYER_RADIUS					(50.0f)				// 半径の大きさ
#define PLAYER_WEAPON_RADIUS			(350.0f)			// 武器の半径
#define PLAYER_PARTS					(22)				// プレイヤーのパーツ数
#define PLAYER_ARMOR_TIME				(150)				// 無敵時間
#define GAME_END_FLAME					(100)				// ゲームが終わるフレーム
#define MAX_SP_NUM						(300)				// SPの最大数
#define SKILL_SP_NUM					(100)				// スキルの消費ゲージ
#define BLADE_EFFECT_INTER				(190)				// 刀身のパーティクルの間隔
#define WEAPON_TIP_NUM					(20)				// 剣先のパーツ番号
#define WEAPON_ROOT_NUM					(21)				// 剣の根元のパーツ番号
#define PLAYER_AVOID_FLAME				(20)				// 回避時間
#define PLAYER_AVOID_END_FLAME			(15)				// 回避の解除時間
#define PLAYER_HP_REGENE_NUM			(5)					// 回復の値
#define PLAYER_HP_REGENE_FLAME			(300)				// 回復のフレーム
#define PLAYER_HIT_SP_HEAL_NUM			(10)				// SPの回復

// 攻撃モーションの情報
#define PLAYER_STAND_ATTACK_KEY_000		(2)					// 一段目の攻撃が有効なキー
#define PLAYER_NEXT_ATTACK_KEY_000		(3)					// 次の攻撃が可能なキー
#define PLAYER_ATTACK_SPEED_000			(40.0f)				// 攻撃時の移動
#define PLAYER_ATTACK_SPEED_001			(30.0f)				// 攻撃時の移動
#define PLAYER_STAND_ATTACK_KEY_001		(2)					// 2段目の攻撃が有効なキー
#define PLAYER_NEXT_ATTACK_KEY_001		(2)					// 次の攻撃が可能なキー
#define PLAYER_STAND_ATTACK_KEY_002		(2)					// 3段目の攻撃が可能なキー
#define PLAYER_SKILL_ATTACK_KEY_000		(5)					// ソードスキルの攻撃が有効なキー
#define PLAYER_CIRCLE_EFFECT_INTER		(80)				// CIRCLEエフェクトの間隔
#define PLAYER_SKILL_MOVE_000			(7.0f)				// ソードスキル時の移動量
#define PLAYER_NEXT_ATTACK_KEY_002		(3)					// 次の攻撃の派生キー

//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 初期化処理
		pPlayer->Init(pos, size);
	}

	return pPlayer;
}

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter::Init(pos, rot);												// 座標　角度
	SetRadius(PLAYER_RADIUS);												// 半径の設定
	SetWeaponRadius(PLAYER_WEAPON_RADIUS);									// 攻撃範囲
	SetCType(CHARACTER_TYPE_PLAYER);										// キャラクターのタイプ
	SetSpeed(PLAYER_SPEED);													// 速度の設定
	SetWeaponTipNum(PARTS_NUM_COLLISION);									// 剣先のパーツ番号
	SetWeaponRootNum(PARTS_NUM_ROOT);										// 剣の根本のパーツ番号
	LifeBarCreate(PLAYER_LIFE_FRAME_POS, PLAYER_LIFE_FRAME_SIZE,
		PLAYER_LIFE_BAR_POS, PLAYER_LIFE_BAR_SIZE,
		PLAYER_LIFE_BAR_COLOR, PLAYER_LIFE_NUM);							// ライフバーの生成

	// SPバーの生成
	if (m_pSpBar == nullptr)
	{
		m_pSpBar = CSpBar::Create(PLAYER_SP_BAR_POS, PLAYER_SP_BAR_SIZE, MAX_SP_NUM);
	}

	// スキルのUI
	if (m_pUiSkill == nullptr)
	{
		m_pUiSkill = CUiSkill::Create(UI_SKILL_POS, UI_SKILL_SIZE, false);
	}

	// 操作方法のUI
	if (m_pUiOperation == nullptr)
	{
		m_pUiOperation = CUiOperation::Create(UI_OPERATION_POS, UI_OPERATION_SIZE, true);
	}

	// コンボのポインタ
	if (m_pCombo == nullptr)
	{
		// コンボの生成
		m_pCombo = CCombo::Create();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	// !nullcheck
	if (m_pCombo != nullptr)
	{
		// コンボの終了処理
		m_pCombo->Uninit();
		delete m_pCombo;
		m_pCombo = nullptr;
	}

	// !nullcheck
	if (m_pSpBar != nullptr)
	{
		// Spバー終了処理
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
		// 操作UIの終了処理
		m_pUiOperation->Uninit();
		m_pUiOperation = nullptr;
	}

	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 死んでないとき
	if (m_bDraw == true)
	{
		// キーボード更新
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		// 座標代入
		D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
		SetPosOld(pos);				// 古い座標保存

		// プレイヤーの状態
		UpdateState();

		// モーション状態
		UpdateMotionState();

		// HPのリジェネ処理
		HpRegene();

		// プレイヤーの制御
		PlayerControl();

		// 角度の更新処理
		UpdateRot();

		// 持っているポインタの更新処理
		HasPtrUpdate();

		// 親クラスの更新処理
		CCharacter::Update();

		// サークルのエフェクトが使われていたら
		if (m_bCircleEffect == true)
		{
			m_nCircleInter++;
		}

		// 一定以上で
		if (m_nCircleInter >= PLAYER_CIRCLE_EFFECT_INTER)
		{
			m_nCircleInter = 0;
			m_bCircleEffect = false;
		}

		// マップの制限
		MapLimit();

		// 体力が0になったら
		if (GetLife() <= 0)
		{
			// 死んだとき
			Death();
		}
	}
	else
	{
		m_nEndCounter++;

		// ゲーム終了のフレーム
		if (m_nEndCounter >= GAME_END_FLAME)
		{
			// リザルト画面へ
			CManager::GetFade()->SetFade(CManager::MODE_TYPE_TITLE);
			m_nEndCounter = 0;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	if (m_bDraw == true)
	{
		// 描画処理
		CCharacter::Draw();
	}
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer::UpdateState(void)
{
	STATE state = GetState();

	switch (state)
	{
	case STATE_NORMAL:
		// 通常状態

		break;

	case STATE_DAMAGE:
	{// ダメージ状態の時

		// 状態カウンター取得
		int nStateCounter = GetStateCounter();

		// 一定時間経過したら
		if (nStateCounter >= PLAYER_ARMOR_TIME)
		{
			SetState(STATE_NORMAL);		// 通常状態に戻す
			SetArmor(false);			// 無敵状態解除
			SetStateCounter(0);			// 状態カウンターリセット
		}
	}

		break;
	default:
		break;
	}
}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// モーション情報
	switch (MotionState)
	{
	case MOTION_IDOL:
		// 通常状態

		// 無敵状態解除
		SetArmor(false);
		break;

	case MOTION_ATTACK:
		// 攻撃モーション時

		// 剣のエフェクト
		SwordLight();

		// 剣の軌跡
		SwordLocus();

		// 攻撃モーション
		if (nKey == PLAYER_STAND_ATTACK_KEY_000)
		{
			if (m_bUseLocusEffect == false)
			{
				// 剣先の現在座標
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// 軌跡のエフェクト生成
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// 攻撃時の当たり判定
			if (AttackCollision() == true)
			{
				if (m_pSpBar != nullptr)
				{
					// SPの回復
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}
			}
		}
		break;
		
	case MOTION_JUMP:
		// ジャンプモーションの時

		// 着地しているとき
		if (GetLanding() == true)
		{
			// 通常に戻す
			SetMotion(MOTION_IDOL);
		}
		break;

	case MOTION_ATTACK_000:
		// 一段目の攻撃

		// 剣のエフェクト
		SwordLight();

		// 現在のキー
		if (nKey == 0)
		{
			// 移動量加算
			AttackMove(PLAYER_ATTACK_SPEED_000);
		}

		if (nKey >= 1)
		{
			// 剣の軌跡
			SwordLocus();

			// 移動量設定
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));
		}

		// 攻撃モーション
		if (nKey == PLAYER_STAND_ATTACK_KEY_000)
		{
			// 軌跡のエフェクトが使われていなかったら
			if (m_bUseLocusEffect == false)
			{
				// 剣先の現在座標
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// 軌跡のエフェクト生成
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;			// フラグをON
			}

			// 攻撃時の当たり判定
			if (AttackCollision() == true)
			{
				// !nullcheck
				if (m_pSpBar != nullptr)
				{
					// SPの回復
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}

			}
		}

		// 二段目の攻撃が可能なキー
		if (nKey == PLAYER_NEXT_ATTACK_KEY_000)
		{
			// 二段目の攻撃処理
			Attack2();

			// 回避の処理
			Avoid();
		}
		break;

	case MOTION_ATTACK_001:
		// 二段目の攻撃

		// 剣のエフェクト
		SwordLight();

		// 剣の軌跡
		SwordLocus();

		if (nKey == 0)
		{
			// 移動量加算
			AttackMove(PLAYER_ATTACK_SPEED_001);
		}

		// 攻撃モーション
		if (nKey == PLAYER_STAND_ATTACK_KEY_001)
		{
			// 移動量設定
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

			// 軌跡のエフェクトが使われていなかったら
			if (m_bUseLocusEffect == false)
			{
				// 剣先の現在座標
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// 軌跡のエフェクト生成
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// 攻撃時の当たり判定
			if (AttackCollision() == true)
			{
				if (m_pSpBar != nullptr)
				{
					// SPの回復
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}
			}

			// 3段目の攻撃が可能なキー
			if (nKey >= PLAYER_NEXT_ATTACK_KEY_001)
			{
				// 3段目の攻撃処理
				Attack3();

				// 回避の処理
				Avoid();
			}
		}
		break;

	case MOTION_ATTACK_002:
		// 3段目の攻撃

		// 3段目の攻撃が可能なキー
		if (nKey >= 4)
		{
			if (nKey == 4)
			{
				if (nCountMotion == 0)
				{
					// 手の光エフェクト
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
					// ゲージが一定量以上だったら
					if (m_pSpBar->GetGage() >= SKILL_SP_NUM)
					{
						// 移動量の設定
						SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

						// 攻撃モーション
						SetMotion(MOTION_SWORD_SKILL_000);

						// 音の設定
						CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
						pSound->Play(CSound::SOUND_LABEL_SE_SWORD_SKILL);

						// SPバーのゲージを減らす
						m_pSpBar->SubGage(SKILL_SP_NUM);

						return;
					}
				}

			}
			// 3段目の攻撃処理
			if (UseSkill() == true)
			{
				return;
			}

			// 回避の処理
			Avoid();
		}

		// 剣の光生成
		SwordLight();

		// 剣の軌跡
		SwordLocus();

		if (nKey == 0)
		{
			// 移動量設定
			AttackMove(PLAYER_ATTACK_SPEED_001);
		 }

		// 攻撃モーション
		if (nKey == PLAYER_STAND_ATTACK_KEY_002)
		{
			// 移動量設定
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

			// 奇跡エフェクトが使われていなかったら
			if (m_bUseLocusEffect == false)
			{
				// 剣先の現在座標
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// 軌跡のエフェクト生成
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// 攻撃時の当たり判定
			if (AttackCollision() == true)
			{
				// !nullcheck
				if (m_pSpBar != nullptr)
				{
					// SPの回復
					m_pSpBar->HealGage(PLAYER_HIT_SP_HEAL_NUM);
				}
			}
		}
		break;

	case MOTION_GUARD:
		// ガードモーション

		// !nullcheck
		if (m_pGuardEffect != nullptr)
		{
			// ガードエフェクトの位置
			m_pGuardEffect->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + PLAYER_BASE_POS_Y, GetPos().z));
		}
		break;

		// ソードスキル
	case MOTION_SWORD_SKILL_000:
		
		// 剣のエフェクト
		SwordLight();

		if (nKey == 0)
		{
			// サークルエフェクトが使われていないとき
			if (m_bCircleEffect == false)
			{
				// サークルエフェクト
				CEffectFactory::CreateEffect(GetPos(), CEffectFactory::EFFECT_NUM_CIRCLE);

				// フラグをON
				m_bCircleEffect = true;
			}
		}

		if (nKey >= 3)
		{
			// 剣の軌跡
			SwordLocus();

			if (nKey == 3)
			{
				// 移動量設定
				AttackMove(PLAYER_ATTACK_SPEED_000);
			}

			// 移動の終わり
			if (nKey == 6)
			{
				// 移動量設定
				SetMove(ZeroVector3);
			}
		}
		else
		{
			// ソードスキル発生時のパーティクル
			CEffectFactory::CreateEffect(GetPos(),
				CEffectFactory::EFFECT_NUM_SWORD_SKILL);
		}

		// 攻撃モーション
		if (nKey == PLAYER_SKILL_ATTACK_KEY_000)
		{
			// 奇跡エフェクトが使われていなかったら
			if (m_bUseLocusEffect == false)
			{
				// 剣先の現在座標
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// 軌跡のエフェクト生成
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}

			// 攻撃時の当たり判定
			if (AttackCollision() == true)
			{

			}
		}
		break;

	case MOTION_DAMAGE:
		// やられモーションの時
		if (GetArmor() == false)
		{
			// 無敵状態
			SetArmor(true);
		}

		// 移動量設定
		SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

		break;

	case MOTION_AVOID_STEP:
		// 回避モーション

		break;
	}
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	MOTION_STATE state = (MOTION_STATE)GetState();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	// やられ状態じゃないとき
	if (state != MOTION_DAMAGE)
	{
		// プレイヤーの移動処理
		Walk();

		// ガードの処理
		Guard();

		if (MotionState != MOTION_ATTACK && MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001
			&& MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000&& MotionState != MOTION_GUARD)
		{
			// スキルの処理
			UseSkill();
		}

		// !nullcheck
		if (m_pUiSkill != nullptr)
		{
			// 使われていなかったら
			if (m_pUiSkill->GetUse() == false)
			{
				// ジャンプの処理
				Jump();

				// 攻撃の処理
				Attack();

				if (MotionState != MOTION_ATTACK && MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001 && MotionState != MOTION_DAMAGE
					&& MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000 && MotionState != MOTION_GUARD)
				{
					// 回避の処理
					Avoid();
				}
			}
		}
	}

#ifdef _DEBUG
	// デバッグコマンド
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新

	// Lボタンの時
	if (pKeyboard->GetTrigger(DIK_L))
	{
		// ダメージを与える
		AddDamage(20);
	}

#endif
}

//=============================================================================
// 角度の更新処理
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 角度の設定
	SetRot(rot);
}

//=============================================================================
// 所持しているポインタの更新処理
//=============================================================================
void CPlayer::HasPtrUpdate(void)
{
	// コンボのポインタ
	if (m_pCombo != nullptr)
	{
		// コンボの生成
		m_pCombo->Update();
	}

	// 操作Uiの切り替え
	if (m_pUiSkill != nullptr)
	{
		if (m_pUiSkill->GetUse() == true)
		{
			// 操作のUIがあるとき
			if (m_pUiOperation != nullptr)
			{
				m_pUiOperation->SetUse(false);
			}
		}
		else
		{
			// 操作のUIがあるとき
			if (m_pUiOperation != nullptr)
			{
				m_pUiOperation->SetUse(true);
			}
		}
	}
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	// ローカル変数
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// サウンドのポインタ
	float fAngle = CGame::GetCamera()->Getφ();								// カメラの角度
	D3DXVECTOR3 pos = GetPos();												// 座標
	D3DXVECTOR3 rot = GetRot();												// 角度
	float fSpeed = GetSpeed();												// スピード
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// モーションの状態

	if (MotionState != MOTION_ATTACK && MotionState != MOTION_GUARD && MotionState != MOTION_DAMAGE && m_bAvoid != true
		&& MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001 && MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000)
	{
		//入力が存在する
		if ((js.lX != 0.0f || js.lY != 0.0f))
		{
			//ダメージを受けていないときのみ移動する
				bool bJump = GetJump();

				//ジャンプしていないとき
				if (bJump == false)
				{
					// 歩き状態にする
					m_bWalk = true;

					//歩行モーションの再生
					SetMotion(MOTION_WALK);
				}

				float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
				float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度

				// 移動量設定
				pos.x += sinf(fAngle + (fAngle2))* fSpeed;
				pos.z += cosf(fAngle + (fAngle2))* fSpeed;

				// 角度の設定
				m_rotDest.y = fAngle + (fAngle3);
		}
		else
		{
			// 歩いていたら
			if (m_bWalk == true)
			{
				//待機モーションを再生
				SetMotion(MOTION_IDOL);
				m_bWalk = false;
			}
		}

		// 前に移動
		if (pKeyboard->GetPress(DIK_W))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			// 移動量・角度の設定
			pos.x -= sinf(fAngle)*fSpeed;
			pos.z -= cosf(fAngle)*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
		}
		// 後ろに移動
		if (pKeyboard->GetPress(DIK_S))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			// 移動量・角度の設定
			pos.x += sinf((fAngle))*fSpeed;
			pos.z += cosf((fAngle))*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));

		}
		// 左に移動
		if (pKeyboard->GetPress(DIK_A))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			// 移動量・角度の設定
			pos.x += sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
			pos.z += cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));

		}
		// 右に移動
		if (pKeyboard->GetPress(DIK_D))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			// 移動量・角度の設定
			pos.x += sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
			pos.z += cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
			m_rotDest.y = fAngle;
			SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));

		}

		// 座標設定
		SetPos(pos);

		// 古い座標取得
		D3DXVECTOR3 OldPos = GetOldPos();

		// 動いていなかったら
		if (OldPos == pos)
		{
			// 通常モーション
			SetMotion(MOTION_IDOL);
		}
	}
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK && MotionState != MOTION_ATTACK_000 && MotionState != MOTION_ATTACK_001 && m_bAvoid == false
		&& MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000 && MotionState != MOTION_GUARD && MotionState != MOTION_DAMAGE)
	{
		// キーボード情報
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();
		
		bool bJump = GetJump();

		// SPACEキーを押したとき・コントローラのYを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && bJump == false
			|| pKeyboard->GetTrigger(DIK_SPACE) && bJump == false)
		{
			// 移動量設定
			D3DXVECTOR3 move = GetMove();
			move.y = PLAYER_JUMP;
			SetMove(move);
			SetJump(true);
			m_bWalk = false;

			//ジャンプモーションの再生
			SetMotion(MOTION_JUMP);
			SetLanding(false);
		}
	}
}

//=============================================================================
// 死んだときの処理
//=============================================================================
void CPlayer::Death(void)
{
	m_bDraw = false;
}

//=============================================================================
// 攻撃の処理
//=============================================================================
void CPlayer::Attack(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK_000 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK && m_bAvoid == false
		&& MotionState != MOTION_ATTACK_001 && MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000)
	{
		// ENTERキーを押したとき・コントローラのXを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0)
			|| pKeyboard->GetTrigger(DIK_RETURN))
		{

			// 攻撃モーション
			SetMotion(MOTION_ATTACK_000);
		}
	}
}

//=============================================================================
// 二段目の攻撃の処理
//=============================================================================
void CPlayer::Attack2(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK_001 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK && MotionState != MOTION_SWORD_SKILL_000)
	{
		// ENTERキーを押したとき・コントローラのXを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0)
			|| pKeyboard->GetTrigger(DIK_RETURN))
		{
			// 二段目攻撃モーション
			SetMotion(MOTION_ATTACK_001);

			// 移動量の設定
			SetMove(ZeroVector3);
		}
	}
}

//=============================================================================
// 3段目の攻撃の処理
//=============================================================================
void CPlayer::Attack3(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	if (MotionState != MOTION_ATTACK_002 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK&& MotionState != MOTION_SWORD_SKILL_000)
	{
		// ENTERキーを押したとき・コントローラのXを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0)
			|| pKeyboard->GetTrigger(DIK_RETURN))
		{
			// 二段目攻撃モーション
			SetMotion(MOTION_ATTACK_002);
		}
	}
}

//=============================================================================
// ガードの処理
//=============================================================================
void CPlayer::Guard(void)
{
		// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	// ガードの処理
	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_Y, 0) 
		|| pKeyboard->GetPress(DIK_G))
	{
		if (MotionState != MOTION_ATTACK_000 && MotionState != MOTION_DAMAGE && MotionState != MOTION_ATTACK && m_bAvoid == false
			&& MotionState != MOTION_ATTACK_001 && MotionState != MOTION_ATTACK_002 && MotionState != MOTION_SWORD_SKILL_000)
		{
			if (m_pUiSkill->GetUse() == false)
			{
				// ガードモーション
				SetMotion(MOTION_GUARD);

				// ガードエフェクトが使われていなかったら
				if (m_pGuardEffect == nullptr)
				{
					// ガードエフェクト生成
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
			// ガードエフェクト終了処理
			m_pGuardEffect->Uninit();
			m_pGuardEffect = nullptr;
		}

		if (MotionState == MOTION_GUARD)
		{
			// ガードモーション
			SetMotion(MOTION_IDOL);
		}
	}
}

//=============================================================================
// 回避の処理
//=============================================================================
void CPlayer::Avoid(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
		|| pKeyboard->GetTrigger(DIK_T))
	{
		// 回避が未使用なら
		if (m_bAvoid == false)
		{
			// 攻撃時の動き
			AttackMove(PLAYER_ATTACK_SPEED_000);

			// 回避のステップ
			SetMotion(MOTION_AVOID_STEP);

			// ダッシュ
			CEffectFactory::CreateEffect(GetPos(), CEffectFactory::EFFECT_NUM_DUSH_IMPACT);

			m_bAvoid = true;	// 回避
			SetArmor(true);		// 無敵時間
		}
	}

	// 回避が使われたとき
	if (m_bAvoid == true)
	{
		m_nAvoidCounter++;

		// 回避の時間
		if (m_nAvoidCounter >= PLAYER_AVOID_FLAME)
		{
			m_nAvoidCounter = 0;
			m_bAvoid = false;
			SetMotion(MOTION_IDOL);
			SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));
		}
	}

	// 無敵時間解除
	if (m_nAvoidCounter == PLAYER_AVOID_END_FLAME)
	{
		// 無敵の解除
		SetArmor(false);
	}
}

//=============================================================================
// 剣のエフェクトの処理
//=============================================================================
void CPlayer::SwordLight(void)
{
	// 剣の根本と剣先のワールド座標取得
	D3DXVECTOR3 Root = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	D3DXVECTOR3 Tip = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	//==========================================================
	// ベクトル求める
	//==========================================================
	// 2点間のベクトルを求める（終点[目標地点] - 始点[自身の位置]）
	D3DXVECTOR3 Vector = Tip - Root;

	// ベクトルの大きさを求める(√c^2 = a^2 * b^2)	長さ
	float fVectorSize = D3DXVec3Length(&Vector);
	
	for (int nCount = 0; nCount < fVectorSize / LIGHT_EFFECT_RADIAN_INTER; nCount++)
	{
		// 根元からのベクトルをnCountで分ける
		D3DXVECTOR3 pos = Root + (Vector / (fVectorSize / LIGHT_EFFECT_RADIAN_INTER)) * (float)nCount;

		if (int nNum = rand() % BLADE_EFFECT_INTER == 0)
		{
			// ソードスキル時の刀身パーティクル
			CEffectFactory::CreateEffect(pos,
				CEffectFactory::EFFECT_NUM_SKILL_BLADE);
		}

		// ソードエフェクト
		CLightEffect::Create(pos, LIGHT_EFFECT_SIZE, LIGHT_EFFECT_LIFE);
	}
}

//=============================================================================
// 剣の軌跡
//=============================================================================
void CPlayer::SwordLocus(void)
{
	// 原点の古い座標取得
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._43);

	// 剣先の古い座標
	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._43);

	// 原点の現在座標
	D3DXVECTOR3 Origin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	// 剣先の現在座標
	D3DXVECTOR3 Top = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	
	// 軌跡の生成
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		GetRot(), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE, pTexture->GetTexture(CTexture::TEXTURE_NUM_SWORD_LOCUS));
}

//=============================================================================
// アタック時の動き
//=============================================================================
void CPlayer::AttackMove(float fSpeed)
{
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// ジョイパッドの取得

	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);
	float fAngle = CGame::GetCamera()->Getφ();

	// スティックが入力されていたら
	if (js.lY != 0 || js.lX != 0)
	{
		// 移動量の初期化
		SetMove(ZeroVector3);

		// 移動量の設定
		SetMove(D3DXVECTOR3(
			sinf(fAngle + (fAngle2))*fSpeed,
			0.0f,
			cosf(fAngle + (fAngle2))*fSpeed));

		// 角度の設定
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{
		// 移動量の初期化
		SetMove(ZeroVector3);

		// 移動量設定
		SetMove(D3DXVECTOR3(
			-sinf(m_rotDest.y)*fSpeed,
			0.0f,
			-cosf(m_rotDest.y)*fSpeed));

		// 角度の設定
		m_rotDest.y = fAngle;
	}
}

//=============================================================================
// HPのリジェネ処理
//=============================================================================
void CPlayer::HpRegene(void)
{
	// カウンターを進める
	m_nRegeneCounter++;

	// 一定量以上だったら
	if (m_nRegeneCounter >= PLAYER_HP_REGENE_FLAME)
	{
		// ライフバーが使われていたら
		if (GetLifeBar() != nullptr)
		{
			// 加算
			HeelLife(PLAYER_HP_REGENE_NUM);
			m_nRegeneCounter = 0;
		}
	}
}

//=============================================================================
// スキルの使用処理
//=============================================================================
bool CPlayer::UseSkill(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// Kキーを押したとき・コントローラのR1を押したとき
	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_R_TRIGGER, 0)
		|| pKeyboard->GetPress(DIK_RSHIFT))
	{
		// !nullcheck
		if (m_pUiSkill != nullptr)
		{
			// 使われてなかったら
			if (m_pUiSkill->GetUse() == false)
			{
				// スキルのUIを描画する
				m_pUiSkill->SetUse(true);
			}
		}

		// Kキーを押したとき・コントローラのBを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
			|| pKeyboard->GetTrigger(DIK_1))
		{
			// !nullcheck
			if (m_pSpBar != nullptr)
			{
				// ゲージが一定量以上だったら
				if (m_pSpBar->GetGage() >= SKILL_SP_NUM)
				{
					// 移動量の設定
					SetMove(D3DXVECTOR3(0.0f, GetMove().y, 0.0f));

					// 攻撃モーション
					SetMotion(MOTION_SWORD_SKILL_000);

					// 音の設定
					CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
					pSound->Play(CSound::SOUND_LABEL_SE_SWORD_SKILL);

					// SPバーのゲージを減らす
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
			// 使われてたら
			if (m_pUiSkill->GetUse() == true)
			{
				// スキルのUIを描画する
				m_pUiSkill->SetUse(false);
			}
		}

	}
	return false;
}

//=============================================================================
// 範囲外に行かないようにする処理
//=============================================================================
void CPlayer::MapLimit(void)
{
	// 座標取得
	D3DXVECTOR3 pos = GetPos();

	//右
	if (pos.x > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(MAP_LIMIT, pos.y, pos.z));
	}

	//左
	if (pos.x <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(-MAP_LIMIT, pos.y, pos.z));
	}

	//奥
	if (pos.z > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, MAP_LIMIT));
	}

	//手前
	if (pos.z <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, -MAP_LIMIT));
	}
}