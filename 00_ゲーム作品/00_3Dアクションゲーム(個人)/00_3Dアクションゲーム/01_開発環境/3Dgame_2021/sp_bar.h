#ifndef _SP_BAR_H_
#define _SP_BAR_H_
//=========================================================
//
// 体力バークラスヘッダー	[sp_bar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "gage.h"
#include "life_frame.h"
#include "life_bar.h"

//=========================================================
// マクロ定義
//=========================================================
#define PLAYER_SP_BAR_SIZE_X	(75.0f)		// SPバーの横幅
#define PLAYER_SP_BAR_POS		(D3DXVECTOR3(PLAYER_LIFE_FLAME_POS_X -PLAYER_LIFE_FLAME_SIZE_X + PLAYER_LIFE_BAR_SIZE_X*2 , PLAYER_LIFE_FLAME_POS_Y, 0.0f))		// 体力バーの座標
#define PLAYER_SP_BAR_SIZE		(D3DXVECTOR3(PLAYER_SP_BAR_SIZE_X, PLAYER_LIFE_FLAME_SIZE_Y, 0.0f))						// 体力バーの大きさ

//=========================================================
// SPバークラス
//=========================================================
class CSpBar : public CGage
{
public:
	CSpBar(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CSpBar();									// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

	static CSpBar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSp);		// ポリゴン生成
	void SpRegene(void);													// SPのリジェネ処理

private:
	int m_nRegeneCnt;		// リジェネのフレームカウント
};
#endif