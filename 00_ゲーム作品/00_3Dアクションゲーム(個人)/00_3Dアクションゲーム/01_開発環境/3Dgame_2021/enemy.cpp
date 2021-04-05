//=============================================================================
//
// エネミークラス [enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "effect_factory.h"
#include "fade.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority)
{
	m_nMotionState = 0;
	m_bActive = false;
	m_bAttack = false;
	m_bRange = false;
	m_nAttackInter = 0;
	m_nAttackFlameCnt = 0;
	m_nArmorFlame = 0;
	m_bPerception = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// オブジェクト生成
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// メモリ確保
	CEnemy *pEnemy = new CEnemy;

	// 初期化処理
	pEnemy->Init(pos, rot);

	return pEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CCharacter::Init(pos, rot);			// 座標、角度
	SetCType(CHARACTER_TYPE_ENEMY);		// キャラクターのタイプ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// 更新処理
	CCharacter::Update();

	// モーション状態
	UpdateMotionState();

	// プレイヤーを敵視する敵
	if (m_bActive == true)
	{
		// 感知の処理
		Perception();
	}

	// 攻撃の間隔を進める
	m_nAttackFlameCnt++;

	// 攻撃範囲内のとき
	if (m_bRange == true)
	{
		// 攻撃の間隔に至ったら
		if (m_nAttackFlameCnt >= m_nAttackInter)
		{
			// 攻撃の処理
			Attack();

			// フレームのカウントを戻す
			m_nAttackFlameCnt = 0;
		}
	}

	// 体力の設定
	if (GetLife() <= 0)
	{
		// 死亡時の処理
		Death();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=============================================================================
// エネミーの状態
//=============================================================================
void CEnemy::UpdateState(void)
{
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	STATE state = GetState();

	switch (state)
	{
	case STATE_NORMAL:
		break;

	case STATE_DAMAGE:
	{
		// 状態カウンター取得
		int nStateCounter = GetStateCounter();

		// 一定時間経過したら
		if (nStateCounter >= m_nArmorFlame)
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
// プレイヤーを感知
//=============================================================================
void CEnemy::Perception(void)
{
	// 追従のフラグ
	if (m_bPerception == true)
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

		fAngle = atan2f((fEposX - fPposX), (fEposZ - fPposZ));			//角度を決める

		//自機と敵の距離
		float fDistance = sqrtf(
			powf((Ppos.x - GetPos().x), 2) +
			powf((Ppos.z - GetPos().z), 2));

		// 離れていたら
		if (fDisLimit <= fDistance)
		{
			// 透明な敵の移動
			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
				(sinf(fAngle)*-GetSpeed()),
				0.0f, cosf(fAngle)*-GetSpeed());

			// 移動量の設定
			SetMove(FollowMove);

			// 角度の設定
			D3DXVECTOR3 rot = GetRot();
			SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));

			// モーションの設定
			SetMotion(ENEMY_MOTION_WALK);

			// 届かない
			if (m_bRange == true)
			{
				m_bRange = false;
			}
		}
		else
		{
			// 移動量の設定
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// 届く
			if (m_bRange == false)
			{
				m_bRange = true;
			}

			// 角度の設定
			D3DXVECTOR3 rot = GetRot();

			SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));

			// モーションの設定
			SetMotion(ENEMY_MOTION_IDOL);
		}

	}
}

//=============================================================================
// 死んだときの処理
//=============================================================================
void CEnemy::Death(void)
{
	// 終了処理
	Uninit();

	// リザルト画面へ遷移
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_TITLE);
}

//=============================================================================
// 攻撃の処理
//=============================================================================
void CEnemy::Attack(void)
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

	// 攻撃モーション
	SetMotion(ENEMY_MOTION_ATTACK);
	m_nAttackFlameCnt = 0;
}

//=============================================================================
// モーション状態の更新
//=============================================================================
void CEnemy::UpdateMotionState(void)
{
}

//=============================================================================
// プレイヤー感知の設定
//=============================================================================
void CEnemy::SetActive(bool bActive)
{
	m_bActive = bActive;
}

//=============================================================================
// 攻撃の間隔設定
//=============================================================================
void CEnemy::SetAttackInter(int nAttackInter)
{
	m_nAttackInter = nAttackInter;
}

//=============================================================================
// 無敵状態のフレーム設定
//=============================================================================
void CEnemy::SetArmorFlame(int nArmorFlame)
{
	m_nArmorFlame = nArmorFlame;
}

//=============================================================================
// 追従のフラグ設定
//=============================================================================
void CEnemy::SetPerception(bool bPerception)
{
	m_bPerception = bPerception;
}

//=============================================================================
// 攻撃カウントの設定
//=============================================================================
void CEnemy::SetAttackCnt(int nAttackCnt)
{
	m_nAttackFlameCnt = nAttackCnt;
}