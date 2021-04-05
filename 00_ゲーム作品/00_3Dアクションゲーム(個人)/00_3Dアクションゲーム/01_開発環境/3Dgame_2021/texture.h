#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
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
using TEXTURE_LIST = std::vector<std::string>;

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:
	// テクスチャの番号の列挙型
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,		// 初期値
		TEXTURE_NUM_FIRE,			// 炎
		TEXTURE_NUM_GAGEFLAME,		// ライフの枠
		TEXTURE_NUM_GAGEBAR,		// ライフのゲージ
		TEXTURE_NUM_TITLE_BG,		// タイトルの背景
		TEXTURE_NUM_PARTICLE,		// パーティクル
		TEXTURE_NUM_SKILL_UI,		// スキルのUI
		TEXTURE_NUM_SWORD_LOCUS,	// 剣の奇跡
		TEXTURE_NUM_SLASH_EFFECT,	// 斬撃のエフェクト
		TEXTURE_NUM_SKILL_START,	// スキルの待機時
		TEXTURE_NUM_QUEST_START,	// クエストの始まり
		TEXTURE_NUM_OPERATION,		// 操作のUI
		TEXTURE_NUM_JUMP_IMPACT,	// ジャンプの衝撃
		TEXTURE_NUM_ROAR_IMPACT,	// 咆哮の衝撃
		TEXTURE_NUM_HIT_IMPACT_000,	// 攻撃ヒット時のエフェクト
		TEXTURE_NUM_FLOOR,			// 床のテクスチャ
		TEXTURE_NUM_DUSH_IMPACT,	// ダッシュのエフェクト
		TEXTURE_NUM_ENEMY_LOCUS,	// 敵の攻撃の軌跡
		TEXTURE_NUM_HIT_UI,			// HITのUI
		TEXTURE_NUM_DAMAGE_UI,		// DamageのUI
		TEXTURE_NUM_MAX
	};

	// アニメーションを行うテクスチャの列挙型
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// 初期値
		SEPARATE_TEX_SHARP,				// 鋭いエフェクト
		SEPARATE_TEX_ELECTRICITY,		// 電撃エフェクト
		SEPARATE_TEX_SMOKE,				// 煙のエフェクト
		SEPARATE_TEX_HIT_EFFECT,		// ヒット時のエフェクト
		SEPARATE_TEX_HIT_IMPACT,		// ヒット時の衝撃
		SEPARATE_TEX_SAND_SMOKE,		// 土煙
		SEPARATE_TEX_CIRCLE,			// サークルエフェクト	
		SEPARATE_TEX_ATTACK_LIGHT,		// 攻撃時の光
		SEPARATE_TEX_KOBOLD_SMOKE,		// コボルトの煙
		SEPARATE_TEX_JUMP_SMOKE,		// ジャンプ時の煙
		SEPARATE_TEX_ATTACK_CIRCLE,		// 攻撃の円
		SEPARATE_TEX_DAMAGE_NUMBER,		// ダメージのテクスチャ
		SEPARATE_TEX_ARM_LIGHT,			// 手の光
		SEPARATE_TEX_DAMAGE_EFFECT,		// ダメージのエフェクト
		SEPARATE_TEX_ROAR_FIRE,			// 炎のエフェクト
		SEPARATE_TEX_ROAR_LIGHT,		// 咆哮のライト
		SEPARATE_TEX_COMBO_NUMBER,		// コンボのナンバー
		SEPARATE_TEX_COMBO_NUMBER_000,	// コンボのダメージナンバー
		SEPARATE_TEX_MAX				// 最大値
	};

	// アニメーションを行うテクスチャの構造体情報
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// 分割テクスチャへのポインタ
		SEPARATE_TEX_TYPE type;						// テクスチャの種類
		D3DXVECTOR2 m_TexInfo;						// テクスチャの分割数、速さ
		bool bLoop;									// ループするか
	};

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	static CTexture *Create(void);												// インスタンス生成

	 HRESULT Load(void);														// テクスチャロード
	 void UnLoad(void);															// テクスチャアンロード
	 HRESULT SeparateTexLoad(void);												// 分割テクスチャロード
	 void SeparateTexUnLoad(void);												// 分割テクスチャアンロード

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// テクスチャの情報

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// 分割テクスチャ情報
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// 分割テクスチャ　UVの枚数取得
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ループするか

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// テクスチャのポインタ
	std::vector<std::string> m_aTexFileName;									// 通常テクスチャのファイル名

	// 分割テクスチャ用変数
	std::vector<std::string> m_aSparateTexFileName;								// 分割テクスチャのファイル名

	// 分割テクスチャの構造体
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_SHARP, D3DXVECTOR2(5, 5), false,
		nullptr, CTexture::SEPARATE_TEX_ELECTRICITY, D3DXVECTOR2(8, 5), false,
		nullptr, CTexture::SEPARATE_TEX_SMOKE, D3DXVECTOR2(10, 4), false,
		nullptr, CTexture::SEPARATE_TEX_HIT_EFFECT, D3DXVECTOR2(9, 2), false,
		nullptr, CTexture::SEPARATE_TEX_HIT_IMPACT, D3DXVECTOR2(6, 3), false,
		nullptr, CTexture::SEPARATE_TEX_SAND_SMOKE, D3DXVECTOR2(8, 10), false,
		nullptr, CTexture::SEPARATE_TEX_CIRCLE, D3DXVECTOR2(6, 4), false,
		nullptr, CTexture::SEPARATE_TEX_ATTACK_LIGHT, D3DXVECTOR2(8, 4), false,
		nullptr, CTexture::SEPARATE_TEX_KOBOLD_SMOKE, D3DXVECTOR2(8, 6), false,
		nullptr, CTexture::SEPARATE_TEX_JUMP_SMOKE, D3DXVECTOR2(10, 3), false,
		nullptr, CTexture::SEPARATE_TEX_ATTACK_CIRCLE, D3DXVECTOR2(2, 20), true,
		nullptr, CTexture::SEPARATE_TEX_DAMAGE_NUMBER, D3DXVECTOR2(10, 20), false,
		nullptr, CTexture::SEPARATE_TEX_ARM_LIGHT, D3DXVECTOR2(6, 2), false,
		nullptr, CTexture::SEPARATE_TEX_DAMAGE_EFFECT, D3DXVECTOR2(5, 4), false,
		nullptr, CTexture::SEPARATE_TEX_ROAR_FIRE, D3DXVECTOR2(12, 4), false,
		nullptr, CTexture::SEPARATE_TEX_ROAR_LIGHT, D3DXVECTOR2(6, 4), false,
		nullptr, CTexture::SEPARATE_TEX_COMBO_NUMBER, D3DXVECTOR2(10, 20), false,
		nullptr, CTexture::SEPARATE_TEX_COMBO_NUMBER_000, D3DXVECTOR2(10, 20), false,
	};
};
#endif
