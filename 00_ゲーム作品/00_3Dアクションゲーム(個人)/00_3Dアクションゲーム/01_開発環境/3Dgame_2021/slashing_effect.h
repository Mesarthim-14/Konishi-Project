#ifndef _SLASHING_EFFECT_H_
#define _SLASHING_EFFECT_H_
//=============================================================================
//
// 斬撃エフェクトのクラスヘッダー [slashing_effect.h]
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
#define SLASHING_EFFECT_SIZE_X (5.0f)		// 横のサイズ
#define SLASHING_EFFECT_SIZE_Y (7.0f)		// 縦のサイズ
#define SLASHING_EFFECT_SIZE_Z (5.0f)		// 奥行のサイズ

#define SLASHING_EFFECT_SIZE (D3DXVECTOR3(SLASHING_EFFECT_SIZE_X, SLASHING_EFFECT_SIZE_Y, SLASHING_EFFECT_SIZE_Z))

//=========================================================================
// 斬撃エフェクトクラス
//=========================================================================
class CSlashingEffect :public CModel
{
public:
	CSlashingEffect(PRIORITY Priority = PRIORITY_EFFECT);	// コンストラクタ
	~CSlashingEffect();										// デストラクタ

	static CSlashingEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
private:
};
#endif