#ifndef _LIFE_BAR_H_
#define _LIFE_BAR_H_
//=========================================================
//
// 体力バークラスヘッダー	[life_bar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "gage.h"
#include "life_frame.h"
#include "character.h"

//=========================================================
// マクロ定義
//=========================================================
#define PLAYER_LIFE_BAR_SIZE_X		(150.0f)
#define PLAYER_LIFE_BAR_COLOR		(D3DCOLOR_RGBA(70, 185, 127, 255))
#define PLAYER_LIFE_BAR_POS			(D3DXVECTOR3(PLAYER_LIFE_FLAME_POS_X -PLAYER_LIFE_FLAME_SIZE_X , PLAYER_LIFE_FLAME_POS_Y, 0.0f))							// 体力バーの座標
#define PLAYER_LIFE_BAR_SIZE		(D3DXVECTOR3(PLAYER_LIFE_BAR_SIZE_X, PLAYER_LIFE_FLAME_SIZE_Y, 0.0f))		// 体力バーの大きさ

#define ENEMY_LIFE_BAR_SIZE_X		(ENEMY_LIFE_FLAME_SIZE_X)
#define ENEMY_LIFE_BAR_COLOR		(D3DCOLOR_RGBA(200, 20, 200, 255))
#define ENEMY_LIFE_BAR_POS			(D3DXVECTOR3(ENEMY_LIFE_FLAME_POS_X -ENEMY_LIFE_FLAME_SIZE_X , ENEMY_LIFE_FLAME_POS_Y, 0.0f))							// 体力バーの座標
#define ENEMY_LIFE_BAR_SIZE			(D3DXVECTOR3(ENEMY_LIFE_BAR_SIZE_X, ENEMY_LIFE_FLAME_SIZE_Y, 0.0f))		// 体力バーの大きさ

//=========================================================
// ヒットポイントバークラス
//=========================================================
class CLifeBar : public CGage
{
public:
	CLifeBar(PRIORITY Priority = PRIORITY_1);										// コンストラクタ
	~CLifeBar();																	// デストラクタ

	static CLifeBar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,
		CCharacter::CHARACTER_TYPE Ctype, int nLife);								// ポリゴン生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// 初期化処理
	void Uninit(void);																// 終了処理
	void Update(void);																// 更新処理
	void Draw(void);																// 描画処理

	void ColorChange(void);															// カラーの変更
private:
	CCharacter::CHARACTER_TYPE m_Ctype;		// タイプ
};
#endif