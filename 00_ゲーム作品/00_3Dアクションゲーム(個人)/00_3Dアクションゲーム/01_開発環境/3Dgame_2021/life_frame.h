#ifndef _LIFE_FRAME_H_
#define _LIFE_FRAME_H_

//=============================================================================
//
// ライフゲージのわくクラスヘッダー	[life_frame.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "ui.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_LIFE_FLAME_POS_X		(SCREEN_WIDTH / 2)		// 横の位置
#define PLAYER_LIFE_FLAME_POS_Y		(600.0f)				// 縦の位置
#define PLAYER_LIFE_FLAME_SIZE_X	(225.0f)				// 横の大きさ
#define PLAYER_LIFE_FLAME_SIZE_Y	(5.0f)					// 縦の大きさ
#define PLAYER_LIFE_FRAME_POS		(D3DXVECTOR3(PLAYER_LIFE_FLAME_POS_X, PLAYER_LIFE_FLAME_POS_Y, 0.0f))
#define PLAYER_LIFE_FRAME_SIZE		(D3DXVECTOR3(PLAYER_LIFE_FLAME_SIZE_X+1.0f, PLAYER_LIFE_FLAME_SIZE_Y+1.0f, 0.0f))

#define ENEMY_LIFE_FLAME_POS_X		(SCREEN_WIDTH / 2)		// 横の位置
#define ENEMY_LIFE_FLAME_POS_Y		(80.0f)					// 縦の位置
#define ENEMY_LIFE_FLAME_SIZE_X		(400.0f)				// 横の大きさ
#define ENEMY_LIFE_FLAME_SIZE_Y		(5.0f)					// 縦の大きさ
#define ENEMY_LIFE_FRAME_POS		(D3DXVECTOR3(ENEMY_LIFE_FLAME_POS_X, ENEMY_LIFE_FLAME_POS_Y, 0.0f))
#define ENEMY_LIFE_FRAME_SIZE		(D3DXVECTOR3(ENEMY_LIFE_FLAME_SIZE_X+1.0f, ENEMY_LIFE_FLAME_SIZE_Y+1.0f, 0.0f))

//=============================================================================
// ライフフレームクラス
//=============================================================================
class CLifeFrame : public CUi
{
public:
	CLifeFrame(PRIORITY Priority = PRIORITY_1);			// コンストラクタ
	~CLifeFrame();										// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理

	static CLifeFrame * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ポリゴン生成

private:
};

#endif