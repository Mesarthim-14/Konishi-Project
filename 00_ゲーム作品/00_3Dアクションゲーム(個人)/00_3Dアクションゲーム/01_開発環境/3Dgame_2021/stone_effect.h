#ifndef _STONE_EFFECT_H_
#define _STONE_EFFECT_H_
//=============================================================================
//
// 岩のエフェクトクラスヘッダー [stone_effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//クラス宣言
//=============================================================================
class CStoneEffect
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
	}STONE;

	// テクスチャの番号の列挙型
	typedef enum
	{
		STONE_NUM_NONE = -1,	// 初期値
		STONE_NUM_000,			// 岩の番号
		STONE_NUM_001,			// 岩の番号
		STONE_NUM_002,			// 岩の番号
		STONE_NUM_MAX
	}STONE_TYPE;

	CStoneEffect();			// コンストラクタ
	~CStoneEffect();		// デストラクタ

	static HRESULT ReadFile(void);				// ファイルの読み込み
	static void CreateStone(D3DXVECTOR3 pos);	// 岩の生成クラス
private:
	static STONE m_Stone[STONE_NUM_MAX];		// パーティクル
};
#endif
