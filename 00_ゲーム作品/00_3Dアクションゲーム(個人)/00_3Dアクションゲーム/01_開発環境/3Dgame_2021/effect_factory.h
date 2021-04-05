#ifndef _EFFECT_FACTORY_H_
#define _EFFECT_FACTORY_H_
//=============================================================================
//
// パーティクル生成クラスヘッダー [effect_factory.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// エフェクト生成
//=============================================================================
class CEffectFactory
{
public:
	// パーティクルの構造体
	typedef struct
	{
		D3DXVECTOR3 size;		// サイズ
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 Distance;	// 距離
		int nLife;				// ライフ
		int nNum;				// 数
		D3DXCOLOR color;		// 色
		bool bGravity;			// 重力
		bool bAlpha;			// アルファテスト
		int nAlphaNum;			// アルファテストの値
		bool bAnimation;		// アニメーションをするかどうか
		bool bBlend;			// 加算合成
		int nPriority;			// 描画優先順位
	}EFFECT;

	// テクスチャの番号の列挙型
	typedef enum
	{
		EFFECT_NUM_NONE = -1,			// 初期値
		EFFECT_NUM_EXPLOSION,			// ダメージを受けたとき
		EFFECT_NUM_SWORD_SKILL,			// スキルの待機時間中
		EFFECT_NUM_SKILL_BLADE,			// スキル時の刀身
		EFFECT_NUM_SHARP_EFFECT,		// 鋭いエフェクト
		EFFECT_NUM_ELECTRICITY_EFFECT,	// 電撃エフェクト
		EFFECT_NUM_SMOKE_EFFECT,		// 煙のエフェクト
		EFFECT_NUM_HIT_EFFECT,			// ヒットエフェクト
		EFFECT_NUM_HIT_EXPLOSION,		// ヒット時の爆発エフェクト
		EFFECT_NUM_HIT_IMPACT,			// ヒット時の衝撃エフェクト
		EFFECT_NUM_SAND_SMOKE,			// 土煙
		EFFECT_NUM_CIRCLE,				// サークルエフェクト
		EFFECT_NUM_ATTACK_LIGHT,		// 攻撃時のライト
		EFFECT_NUM_KOBOLD_SMOKE,		// コボルトの煙
		EFFECT_NUM_JUMP_SMOKE,			// ジャンプの煙
		EFFECT_NUM_ATTACK_CIRCLE,		// 攻撃時のサークル
		EFFECT_NUM_JUMP_IMPACT,			// ジャンプ時のサークル
		EFFECT_NUM_ROAR_IMPACT,			// 咆哮時の衝撃
		EFFECT_NUM_HIT_IMPACT_000,		// ヒット時の衝撃
		EFFECT_NUM_ROAR_CIRCLE,			// 咆哮時の小さいサークル
		EFFECT_NUM_ARM_LIGHT,			// 手の光
		EFFECT_NUM_GUARD_PARTICLE,		// ガード時のパーティクル
		EFFECT_NUM_DUSH_IMPACT,			// ダッシュの衝撃
		EFFECT_NUM_DAMAGE_EFFECT,		// ダメージ時のエフェクト
		EFFECT_NUM_ROAR_FIRE,			// 咆哮時の炎
		EFFECT_NUM_ROAR_LIGHT,			// 咆哮時の光
		EFFECT_NUM_MAX
	}EFFECT_TYPE;

	CEffectFactory();												// コンストラクタ
	~CEffectFactory();												// デストラクタ

	static HRESULT ReadFile(void);									// ファイルの読み込み
	static void CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type);	// パーティクルのクラス
private:
	static EFFECT m_Effect[EFFECT_NUM_MAX];							// パーティクル
};
#endif
