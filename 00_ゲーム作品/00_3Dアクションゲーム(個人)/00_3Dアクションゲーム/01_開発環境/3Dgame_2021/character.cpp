//=============================================================================
//
// キャラクタークラス [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限

//=============================================================================
// static初期化処理
//=============================================================================
 int CCharacter::m_nAllNum = 0;

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 引数の代入
	m_pos = pos;	// 座標の設定
	m_rot = rot;	// 角度の設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		// !nullcheck
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//メモリの削除
			delete m_apModelAnime[nCntModelNum];

			//メモリのクリア
			m_apModelAnime[nCntModelNum] = nullptr;
		}
	}

	// !nullcheck
	if (m_pMotion != nullptr)
	{
		//メモリの削除
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ライフの枠
	if (m_pLifeFrame != nullptr)
	{
		// メモリのクリア
		m_pLifeFrame->Uninit();
		m_pLifeFrame = nullptr;
	}

	// ライフの枠
	if (m_pLifeBar != nullptr)
	{
		// メモリのクリア
		m_pLifeBar->Uninit();
		m_pLifeBar = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter::Update()
{
	//アニメーションの更新処理
	ModelAnimeUpdate();

	// 重力
	Gravity();

	// 着地の処理
	if (m_pos.y <= GROUND_RIMIT)
	{
		Landing(GROUND_RIMIT);
	}

	// 移動量加算
	m_pos += m_move;

	// 当たり判定
	BodyCollision();

	// 無敵時間のとき
	if (m_bArmor == true)
	{
		// カウンターを進める
		m_nStateCounter++;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacter::Draw()
{
	// 描画処理
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 裏面を（左回り）をカリング

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//階層モデルクラスの描画処理
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
}

//=============================================================================
// 着地の処理
//=============================================================================
void CCharacter::Landing(float fPosY)
{
	m_move.y = 0.0f;
	m_pos.y = fPosY;
	m_bJump = false;

	// 着地の状態
	if (m_bLanding == false)
	{
		m_bLanding = true;
	}
}

//=============================================================================
// 重力
//=============================================================================
void CCharacter::Gravity(void)
{
	// 重力をかける
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// 落下
}

//=============================================================================
// モデルの生成
//=============================================================================
void CCharacter::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFileのポインタ取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルパーツの設定
		m_nParts = pXfile->GetModelParts(FileNum);

		//モデルパーツ数分繰り返す
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);

			if (m_apModelAnime[nCntModel] == nullptr)
			{
				// 初期化処理
				m_apModelAnime[nCntModel] = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot);

				// モデルの情報取得
				std::vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

				// モデルの生成
				m_apModelAnime[nCntModel]->SetModel(model.at(nCntModel));
			}

			//親子構造の設定
			if (m_apModelAnime[nCntModel] != nullptr)
			{
				//親モデルの場合
				if (nCntModel == 0)
				{
					m_apModelAnime[nCntModel]->SetParent(nullptr);
				}
				//子モデルの場合
				else
				{
					//自分の親情報を設定する
					m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[ModelFile.nParent]);
				}
			}
		}

		// nullcheck
		if (m_pMotion == nullptr)
		{
			// インスタンス生成
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// モデルアニメーション
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// モーションの更新処理
	if (m_pMotion != nullptr)
	{
		// モーションの更新
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// モーションの設定
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != nullptr)
	{
		// モーションの更新
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 体力バーの生成関数
//=============================================================================
void CCharacter::LifeBarCreate(D3DXVECTOR3 posFrame, D3DXVECTOR3 sizeFrame,
	D3DXVECTOR3 posBar, D3DXVECTOR3 sizeBar, D3DXCOLOR color, int nLife)
{
	// 引数の代入
	m_nLife = nLife;		// ライフの設定
	m_nMaxLife = nLife;		// ライフの最大数設定

	// ライフのフレーム
	if (m_pLifeFrame == nullptr)
	{
		m_pLifeFrame = CLifeFrame::Create(posFrame, sizeFrame);
	}

	// HPバーの生成
	if (m_pLifeBar == nullptr)
	{
		// 体力バー
		m_pLifeBar = CLifeBar::Create(posBar, sizeBar,
			color, m_Ctype, nLife);
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CCharacter::BodyCollision(void)
{
	// キャラクターのポインタ
	CCharacter *pCharacter = (CCharacter*)GetTop(PRIORITY_CHARACTER);

	while (pCharacter != nullptr)
	{
		// 自分の番号じゃないとき
		if (pCharacter->m_nCharaNum != m_nCharaNum)
		{
			// 円形と円形の当たり判定
			if (CCollision::CollisionCircularAndCircular(
				m_pos, pCharacter->m_pos,
				m_fRadius, pCharacter->m_fRadius) == true)
			{
				if (pCharacter->m_Ctype == CHARACTER_TYPE_PLAYER)
				{
					// 外に押し出す
					D3DXVECTOR3 vec = (pCharacter->GetPos() - m_pos);
					D3DXVec3Normalize(&vec, &vec);
					vec *= (pCharacter->m_fRadius + m_fRadius);

					D3DXVECTOR3 pos = pCharacter->GetPos();
					pCharacter->SetPos(GetPos() + vec);
				}
				else
				{
					// 外に押し出す
					D3DXVECTOR3 vec = (m_pos - pCharacter->GetPos());
					D3DXVec3Normalize(&vec, &vec);
					vec *= (m_fRadius + pCharacter->m_fRadius);

					D3DXVECTOR3 pos = GetPos();
					SetPos(pCharacter->GetPos() + vec);
				}
			}
		}

		// 次のポインタ
		pCharacter = (CCharacter*)pCharacter->GetNext();
	}
}

//=============================================================================
// 攻撃時の当たり判定
//=============================================================================
bool CCharacter::AttackCollision(void)
{
	switch (this->GetCType())
	{
	case CHARACTER_TYPE_PLAYER:
		// プレイヤーの時
	{
		// キャラクターのポインタ
		CCharacter *pCharacter = (CCharacter*)GetTop(PRIORITY_CHARACTER);

		while (pCharacter != nullptr)
		{
			// 自分の番号じゃないとき
			if (pCharacter->m_Ctype == CHARACTER_TYPE_ENEMY)
			{
				// やられ判定パーツ座標取得
				D3DXVECTOR3 pos = D3DXVECTOR3(
					pCharacter->GetModelAnime(pCharacter->GetHitNumber())->GetMtxWorld()._41,
					pCharacter->GetModelAnime(pCharacter->GetHitNumber())->GetMtxWorld()._42,
					pCharacter->GetModelAnime(pCharacter->GetHitNumber())->GetMtxWorld()._43);

				// 円形と円形の当たり判定
				if (CCollision::CollisionCircularAndCircular(
					m_pos, pos,
					m_fWeaponRadius, pCharacter->m_fRadius) == true)
				{
					if (pCharacter->m_state != STATE_DAMAGE)
					{
						// ソードスキル
						CEffectFactory::CreateEffect(pCharacter->m_pos,
							CEffectFactory::EFFECT_NUM_EXPLOSION);

						// ヒットエフェクト
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_EFFECT);

						// ヒットエフェクト
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_EXPLOSION);

						// ヒットエフェクト
						CEffectFactory::CreateEffect(D3DXVECTOR3(
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
							this->m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43),
							CEffectFactory::EFFECT_NUM_HIT_IMPACT);

						int nDamage = 0;

						// ソードスキル
						if (m_pMotion->GetMotionState() == (int)(CPlayer::MOTION_SWORD_SKILL_000))
						{
							// ダメージの値
							nDamage = PLAYER_SKILL_ATTACK_DAMAGE;
						}
						else
						{
							// ダメージの値
							nDamage = PLAYER_ATTACK_DAMAGE;
						}

						// ダメージ
						nDamage += rand() % PLAYER_ATTACK_RAND_DAMAGE - rand() % PLAYER_ATTACK_RAND_DAMAGE;

						// メモリ
						CPlayer *pPlayer = CGame::GetPlayer();

						int nNum = 0;

						if (pPlayer != nullptr)
						{
							// コンボの倍率を決める
							nNum = (float)nDamage + ((float)pPlayer->GetCombo()->GetComboNum() * DAMAGE_MAG);

						}

						// そのキャラクターにダメージを与える
						pCharacter->AddDamage(nNum);

						// 音を入れる
						CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
						pSound->Play(CSound::SOUND_LABEL_SE_SLASH);

						if (pPlayer->GetCombo() != nullptr)
						{
							// コンボ時の関数
							pPlayer->GetCombo()->Combo(nNum);
						}

						// ダメージの衝撃
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

			// 次のポインタ
			pCharacter = (CCharacter*)pCharacter->GetNext();
		}
	}
	break;

	case CHARACTER_TYPE_ENEMY:
	{
		// エネミーの時
		CPlayer *pPlayer = CGame::GetPlayer();

		D3DXVECTOR3 WorldPos = D3DXVECTOR3(
			m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._41,
			m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._42,
			m_apModelAnime[m_nWeaponTipNum]->GetMtxWorld()._43);

		// nullcheck
		if (pPlayer != nullptr)
		{
			// 円形と円形の当たり判定
			if (CCollision::CollisionCircularAndCircular(
				WorldPos, pPlayer->m_pos,
				m_fWeaponRadius, pPlayer->m_fRadius) == true)
			{
				// 無敵状態じゃなかったら
				if (pPlayer->GetArmor() == false)
				{
					if (pPlayer->m_pMotion->GetMotionState() == CPlayer::MOTION_GUARD)
					{
						// プレイヤーにダメージを与える
						pPlayer->AddDamage(m_nAttackPowar / PLAYER_GUARD_CUT_DAMAGE);

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
						pPlayer->AddDamage(m_nAttackPowar);
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
// ダメージの加算
//=============================================================================
void CCharacter::AddDamage(int nDamage)
{
	// 0以下になったら
	if (m_nLife <= 0)
	{
		m_nLife = 0;
	}
	else
	{
		m_nLife -= nDamage;
		SetState(STATE_DAMAGE);
		m_bArmor = true;

		// もしライフバーが使われていたら
		if (m_pLifeBar != nullptr)
		{
			// ライフバーの設定関数
			m_pLifeBar->SubGage(nDamage);
		}
	}
}

//=============================================================================
// 回復の処理
//=============================================================================
void CCharacter::HeelLife(int nHeelNum)
{
	// 0以下になったら
	if (m_nLife >= m_nMaxLife)
	{
		m_nLife = m_nMaxLife;
	}
	else
	{
		m_nLife += nHeelNum;
		SetState(STATE_DAMAGE);
		m_bArmor = true;

		// もしライフバーが使われていたら
		if (m_pLifeBar != nullptr)
		{
			// ライフバーの設定関数
			m_pLifeBar->HealGage(nHeelNum);
		}
	}
}

//=============================================================================
// 座標の設定
//=============================================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 古い座標の設定
//=============================================================================
void CCharacter::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//=============================================================================
// 状態の設定
//=============================================================================
void CCharacter::SetState(STATE state)
{
	m_state = state;
}

//=============================================================================
// 移動量の設定
//=============================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 角度の設定
//=============================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 体力の設定
//=============================================================================
void CCharacter::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ジャンプの設定
//=============================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// 地面にいるフラグ設定
//=============================================================================
void CCharacter::SetLanding(bool bLanding)
{
	m_bLanding = bLanding;
}

//=============================================================================
// 半径の設定
//=============================================================================
void CCharacter::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

//=============================================================================
// キャラクターのタイプ設定
//=============================================================================
void CCharacter::SetCType(CHARACTER_TYPE Ctype)
{
	m_Ctype = Ctype;
}

//=============================================================================
// キャラクターの速度設定
//=============================================================================
void CCharacter::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// 剣先のパーツ番号設定
//=============================================================================
void CCharacter::SetWeaponTipNum(int nWeaponTipNum)
{
	m_nWeaponTipNum = nWeaponTipNum;
}

//=============================================================================
// 剣の根本のパーツ番号設定
//=============================================================================
void CCharacter::SetWeaponRootNum(int nWeaponRootNum)
{
	m_nWeaponRootNum = nWeaponRootNum;
}

//=============================================================================
// 武器の半径
//=============================================================================
void CCharacter::SetWeaponRadius(float fWeaponRadius)
{
	m_fWeaponRadius = fWeaponRadius;
}

//=============================================================================
// 無敵フラグ設定
//=============================================================================
void CCharacter::SetArmor(bool bArmor)
{
	m_bArmor = bArmor;
}

//=============================================================================
// 状態カウンターの設定
//=============================================================================
void CCharacter::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}

//=============================================================================
// 攻撃力の設定
//=============================================================================
void CCharacter::SetAttackPower(int nAttackPowar)
{
	m_nAttackPowar = nAttackPowar;
}

//=============================================================================
// やられ判定の設定
//=============================================================================
void CCharacter::SetHitNumber(int nHitNumber)
{
	m_nHitNumber = nHitNumber;
}