#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクター処理  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// キャラクターのパーツ数
#define MAX_KEYFRAME		(10)	// キーフレームの最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CLifeBar;
class CLifeFrame;
class CMotion;

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter : public CScene
{
public:
	enum STATE
	{
		STATE_NONE = 0,		// 初期値
		STATE_APPEAR,		// 出現
		STATE_NO_ACTIVE,	// 非戦闘状態
		STATE_NORMAL,		// 通常状態
		STATE_DAMAGE,		// ダメージ状態
		STATE_MAX,			// 最大値
	};

	enum CHARACTER_TYPE
	{
		CHARACTER_TYPE_NONE = 0,	// 初期値
		CHARACTER_TYPE_PLAYER,		// プレイヤー
		CHARACTER_TYPE_ENEMY,		// エネミー
		CHARACTER_TYPE_MAX,			// 最大数
	};

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	virtual ~CCharacter();											// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	virtual void Uninit();											// 終了処理
	virtual void Update();											// 更新処理
	virtual void Draw();											// 描画処理

	void AddDamage(int nDamage);									// ダメージの加算
	void HeelLife(int nHeelNum);									// 回復の処理
	void Gravity(void);												// 地面の制限
	void BodyCollision(void);										// 当たり判定
	bool AttackCollision(void);										// 攻撃時の当たり判定
	void LifeBarCreate(D3DXVECTOR3 posFrame, D3DXVECTOR3 sizeFrame,	// 体力バーの設置
		D3DXVECTOR3 posBar, D3DXVECTOR3 sizeBar,
		D3DXCOLOR color, int nLife);								// 体力バーの生成関数

	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// モデルの生成
	void ModelAnimeUpdate(void);									// モデルアニメーション
	void Landing(float fPosY);										// 着地処理

	// 純粋仮想関数
	virtual void UpdateState(void) = 0;								// キャラクター状態
	virtual void UpdateMotionState(void) = 0;						// モーションの状態
	virtual void Attack(void) = 0;									// 攻撃の処理
	virtual void Death(void) = 0;									// 死んだときの処理

	// Set関数
	void SetPos(D3DXVECTOR3 pos);									// 座標の設定
	void SetPosOld(D3DXVECTOR3 posOld);								// 座標の設定
	void SetState(STATE state);										// プレイヤー情報の設定
	void SetMove(D3DXVECTOR3 move);									// 移動量の設定
	void SetRot(D3DXVECTOR3 rot);									// 角度の設定
	void SetLife(int nLife);										// ライフの設定
	void SetCountMotion(int CountMotion);							// モーションのカウント設定
	void SetMotionState(int nMotionState);							// モーションの状態設定
	void SetMotion(int nMotion);									// モーションの設定 
	void SetKey(int nKey);											// キー設定
	void SetJump(bool bJump);										// ジャンプのフラグ
	void SetLanding(bool bLanding);									// 着地の設定
	void SetRadius(float fRadius);									// 半径の設定
	void SetCType(CHARACTER_TYPE Ctype);							// キャラクターのタイプ
	void SetSpeed(float fSpeed);									// 速度の設定
	void SetWeaponTipNum(int nWeaponTipNum);						// 剣先のパーツ番号
	void SetWeaponRootNum(int nWeaponRootNum);						// 剣の根本のパーツ番号
	void SetWeaponRadius(float fWeaponRadius);						// 武器の半径
	void SetArmor(bool bArmor);										// 無敵フラグ設定
	void SetStateCounter(int nStateCounter);						// 状態カウンターの設定
	void SetAttackPower(int m_nAttackPowar);						// 攻撃力の設定
	void SetHitNumber(int nHitNumber);								// やられ判定の設定

	// Get関数
	D3DXVECTOR3 GetPos(void)				{ return m_pos; }						// 現在の座標情報
	D3DXVECTOR3 GetOldPos(void)				{ return m_posOld; }					// 古い座標情報
	D3DXVECTOR3 GetRot(void)				{ return m_rot; }						// 角度情報
	D3DXVECTOR3 GetMove(void)				{ return m_move; }						// 移動量の情報
	STATE GetState(void)					{ return m_state; }						// プレイヤーの状態情報
	CHARACTER_TYPE GetCType(void)			{ return m_Ctype; }						// キャラクターのタイプ
	int GetLife(void)						{ return m_nLife; }						// ライフの情報
	int GetWeaponPartsNum(void)				{ return m_nWeaponTipNum; }				// 剣先のパーツ番号の情報
	int GetWeaponRootNum(void)				{ return m_nWeaponTipNum; }				// 剣先のパーツ番号の情報
	int GetStateCounter(void)				{ return m_nStateCounter; }				// 状態カウンターの情報
	int GetAttackPower(void)				{ return m_nAttackPowar; }				// 攻撃の状態
	int GetHitNumber(void)					{return m_nHitNumber; }					// やられ判定の情報
	float GetSpeed(void)					{ return m_fSpeed; }					// スピードの情報
	float GetRadius(void)					{ return m_fRadius; }					// 半径の情報
	CModelAnime *GetModelAnime(int nCount)	{ return m_apModelAnime[nCount]; }		// モーションのカウント情報
	bool GetJump(void)						{ return m_bJump; }						// ジャンプ
	bool GetLanding(void)					{ return m_bLanding; }					// 着地のフラグ
	bool GetArmor(void)						{ return m_bArmor;}						// 無敵時間
	CLifeBar *GetLifeBar(void)				{ return m_pLifeBar; }					// ライフバーの情報
	CMotion *GetMotion(void)				{ return m_pMotion; }					// モーションのポインタ情報

private:
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// モデルパーツ用のポインタ
	CMotion *m_pMotion;								// モーションクラスのポインタ
	D3DXVECTOR3 m_pos;				// 座標
	D3DXVECTOR3 m_posOld;			// 古い座標
	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_rot;				// 現在の回転
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	STATE m_state;					// キャラクターの状態
	CHARACTER_TYPE m_Ctype;			// キャラクターのタイプ
	int m_nLife;					// 体力
	int m_nMaxLife;					// ライフの最大量
	int m_nAttack;					// 攻撃力
	int m_nCharaNum;				// キャラクターのナンバー
	int m_nWeaponTipNum;			// 剣先のパーツ番号
	int m_nWeaponRootNum;			// 剣の根本のパーツ
	int m_nStateCounter;			// 状態のカウンター
	int m_nAttackPowar;				// 攻撃力
	int m_nHitNumber;				// やられ判定のパーツ番号
	int m_nParts;					// パーツ数
	float m_fSpeed;					// 移動量
	float m_fAngle;					// 角度
	float m_fRadius;				// 半径
	float m_fWeaponRadius;			// 武器の半径
	bool m_bJump;					// ジャンプしているフラグ
	bool m_bLanding;				// 着地のフラグ
	bool m_bArmor;					// 無敵フラグ
	CLifeBar *m_pLifeBar;			// ライフバーのポインタ
	CLifeFrame *m_pLifeFrame;		// ライフバーのフレーム
	// 静的メンバ変数
	static int m_nAllNum;			// キャラクターの総数
};
#endif