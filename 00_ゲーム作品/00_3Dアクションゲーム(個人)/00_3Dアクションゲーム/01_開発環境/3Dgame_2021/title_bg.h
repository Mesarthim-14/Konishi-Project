#ifndef _TITLEBG_H_
#define _TITLEBG_H_
//=============================================================================
//
// タイトル背景の処理 [titlebg.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene2d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define TITLE_BG_POS_X		(SCREEN_WIDTH / 2)		// タイトルのX座標
#define TITLE_BG_POS_Y		(SCREEN_HEIGHT / 2)		// タイトルのY座標
#define TITLE_BG_SIZE_X		(SCREEN_WIDTH / 2)		// タイトルのXサイズ
#define TITLE_BG_SIZE_Y		(SCREEN_HEIGHT / 2)		// タイトルのYサイズ

#define TITLE_BG_POS		(D3DXVECTOR3(TITLE_BG_POS_X, TITLE_BG_POS_Y, 0.0f))		// タイトル背景の座標
#define TITLE_BG_SIZE		(D3DXVECTOR3(TITLE_BG_SIZE_X, TITLE_BG_SIZE_Y, 0.0f))		// タイトル背景の座標

//=============================================================================
//クラス宣言
//=============================================================================
class CTitleBg : public CScene2D
{
public:
	CTitleBg();		// コンストラクタ
	~CTitleBg();	// デストラクタ

	static CTitleBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// オブジェクト生成関数

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
};
#endif // ! _TITLEBG_H_
