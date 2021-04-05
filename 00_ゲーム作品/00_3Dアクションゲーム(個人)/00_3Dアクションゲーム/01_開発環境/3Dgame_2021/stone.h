#ifndef _STONE_H_
#define _STONE_H_
//=============================================================================
//
// 岩のクラスヘッダー [stone.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"
#include "stone_effect.h"

//=========================================================================
// マクロ定義
//=========================================================================
#define STONE_SIZE_X (6.0f)				// 横のサイズ
#define STONE_SIZE_Y (6.0f)				// 縦のサイズ
#define STONE_SIZE_Z (6.0f)				// 奥行のサイズ

#define STONE_SIZE (D3DXVECTOR3(GUARD_EFFECT_SIZE_X, GUARD_EFFECT_SIZE_Y, GUARD_EFFECT_SIZE_Z))

#define STONE_RADIAN		(25.0f)		// 奥行のサイズ
#define STONE_RADIAN_INTER	(2.0f)		// 奥行のサイズ
#define STONE_LIFE			(2)			// ライフ

//=========================================================================
// 3Dポリゴンクラス
//=========================================================================
class CStone :public CModel
{
public:
	CStone(PRIORITY Priority = PRIORITY_EFFECT);	// コンストラクタ
	~CStone();										// デストラクタ

	static CStone *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
		CStoneEffect::STONE stone, CXfile::XFILE_NUM StoneNum);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
private:
};
#endif