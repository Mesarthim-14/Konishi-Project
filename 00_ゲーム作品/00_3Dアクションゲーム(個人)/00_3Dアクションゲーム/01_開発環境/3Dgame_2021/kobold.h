#ifndef _KOBOLD_H_
#define _KOBOLD_H_
//=============================================================================
//
// 蟹エネミークラスヘッダー [kobold.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_KOBOLD_PARTS			(19)		// モデルのパーツの最大数

//=============================================================================
// コボルトクラス
//=============================================================================
class CKobold : public CEnemy
{
public:
	CKobold(PRIORITY Priority = PRIORITY_CHARACTER);	// コンストラクタ
	~CKobold();											// デストラクタ

	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	typedef enum
	{
		KOBOLD_MOTION_NONE = -1,
		KOBOLD_MOTION_IDOL,			// アイドルモーション
		KOBOLD_MOTION_WALK,			// 歩行モーション
		KOBOLD_MOTION_JUMP_ATTACK,	// ジャンプ攻撃モーション
		KOBOLD_MOTION_SMASH,		// 叩きつけモーション
		KOBOLD_MOTION_WIPE,			// 払いモーション
		KOBOLD_MOTION_ROAR,			// 咆哮モーション
		KOBOLD_MOTION_DAMAGE,		// ダメージモーション
		KOBOLD_MOTION_MAX,			// モーション最大数
	}KOBOLD_MOTION;

	//=============================================================================
	//　モーションパーツの列挙型
	//=============================================================================
	typedef enum
	{
		KOBOLD_PARTS_NUM_NONE = -1,
		KOBOLD_PARTS_NUM_BODY,						// [0]体
		KOBOLD_PARTS_NUM_HEAD,						// [1]頭
		KOBOLD_PARTS_NUM_RIGHT_SHOLDER,				// [2]右肩
		KOBOLD_PARTS_NUM_RIGHT_UPPERARM,			// [3]右上腕
		KOBOLD_PARTS_NUM_RIGHT_ARM,					// [4]右腕
		KOBOLD_PARTS_NUM_LEFT_SHOLDER,				// [5]左肩
		KOBOLD_PARTS_NUM_LEFT_UPPERARM,				// [6]左上腕
		KOBOLD_PARTS_NUM_LEFT_ARM,					// [7]左腕
		KOBOLD_PARTS_NUM_RIGHT_LEG,					// [8]右腰
		KOBOLD_PARTS_NUM_RIGHT_FOOT,				// [9]右足
		KOBOLD_PARTS_NUM_LEFT_LEG,					// [10]左腰
		KOBOLD_PARTS_NUM_LEFT_FOOT,					// [11]左足
		KOBOLD_PARTS_NUM_RIGHT_ARM_COLLISION,		// [12]右手当たり判定
		KOBOLD_PARTS_NUM_LEFT_ARM_COLLISION,		// [13]左手当たり判定
		KOBOLD_PARTS_NUM_RIGHT_LEG_COLLISION,		// [14]右足当たり判定
		KOBOLD_PARTS_NUM_LEFT_LEG_COLLISION,		// [15]左足当たり判定
		KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE,			// [16]親指
		KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE,			// [17]小指
		KOBOLD_PARTS_NUM_BODY_COLLISION,			// [18]本体の当たり判定
		KOBOLD_PARTS_NUM_MAX,						// パーツ最大数
	}KOBOLD_PARTS_NUM;

	static CKobold *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void Locus(void);											// 軌跡
	void Attack(void);											// 攻撃の処理
	void UpdateMotionState(void);								// モーション状態

private:
	int m_nSmokeCounter;			// 煙のカウンター
	int m_nRoarAttackCounter = 0;	// 叫び攻撃のカウンター
};
#endif