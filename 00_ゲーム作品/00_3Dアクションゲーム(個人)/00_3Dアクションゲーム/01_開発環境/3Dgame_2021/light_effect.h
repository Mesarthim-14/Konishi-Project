#ifndef _LIGHT_EFFECT_H_
#define _LIGHT_EFFECT_H_
//=============================================================================
//
// ライトエフェクトのクラスヘッダー [light_effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// マクロ定義
//=========================================================================
#define LIGHT_EFFECT_SIZE_X (25.0f)				// 横のサイズ
#define LIGHT_EFFECT_SIZE_Y (25.0f)				// 縦のサイズ
#define LIGHT_EFFECT_SIZE_Z (25.0f)				// 奥行のサイズ

#define LIGHT_EFFECT_SIZE (D3DXVECTOR3(LIGHT_EFFECT_SIZE_X, LIGHT_EFFECT_SIZE_Y, LIGHT_EFFECT_SIZE_Z))

#define LIGHT_EFFECT_RADIAN			(25.0f)		// 奥行のサイズ
#define LIGHT_EFFECT_RADIAN_INTER	(2.0f)		// 奥行のサイズ
#define LIGHT_EFFECT_LIFE			(2)			// ライフ

//=========================================================================
// 剣のライトエフェクトクラス
//=========================================================================
class CLightEffect :public CModel
{
public:
	CLightEffect(PRIORITY Priority = PRIORITY_EFFECT);	// コンストラクタ
	~CLightEffect();									// デストラクタ

	static CLightEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
private:
	int m_nLife;		// 体力
};
#endif