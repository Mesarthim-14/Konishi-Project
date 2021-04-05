#ifndef _GUARD_EFFECT_H_
#define _GUARD_EFFECT_H_
//=============================================================================
//
// ガードエフェクトのクラスヘッダー [guard_effect.h]
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
#define GUARD_EFFECT_SIZE_X (6.0f)		// 横のサイズ
#define GUARD_EFFECT_SIZE_Y (6.0f)		// 縦のサイズ
#define GUARD_EFFECT_SIZE_Z (6.0f)		// 奥行のサイズ

#define GUARD_EFFECT_SIZE (D3DXVECTOR3(GUARD_EFFECT_SIZE_X, GUARD_EFFECT_SIZE_Y, GUARD_EFFECT_SIZE_Z))

//=========================================================================
// ガードエフェクトクラス
//=========================================================================
class CGuardEffect :public CModel
{
public:
	CGuardEffect(PRIORITY Priority = PRIORITY_EFFECT);	// コンストラクタ
	~CGuardEffect();									// デストラクタ

	static CGuardEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	void Luminous(void);								// 発光の処理

private:
	float m_fSubNum;									// 減算の値
	bool m_bLuminous;									// 発光しているフラグ
	D3DXCOLOR m_Emissive;								// 発光の値
};
#endif