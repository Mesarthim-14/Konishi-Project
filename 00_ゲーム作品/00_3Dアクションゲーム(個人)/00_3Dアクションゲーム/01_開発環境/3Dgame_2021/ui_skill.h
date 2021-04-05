#ifndef _UI_SKILL_H_
#define _UI_SKILL_H_
//=============================================================================
//
// スキルのUIクラスヘッダー [ui_skill.h]
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
#define UI_SKILL_POS_X		(SCREEN_WIDTH / 2)	// X座標
#define UI_SKILL_POS_Y		(500.0f)			// Y座標
#define UI_SKILL_SIZE_X		(200.0f)			// Xサイズ
#define UI_SKILL_SIZE_Y		(25.0f)				// Yサイズ

#define UI_SKILL_POS		(D3DXVECTOR3(UI_SKILL_POS_X, UI_SKILL_POS_Y, 0.0f))		// 座標
#define UI_SKILL_SIZE		(D3DXVECTOR3(UI_SKILL_SIZE_X, UI_SKILL_SIZE_Y, 0.0f))	// サイズ

//=============================================================================
// スキルのUIクラス宣言
//=============================================================================
class CUiSkill : public CUi
{
public:
	CUiSkill();		// コンストラクタ
	~CUiSkill();	// デストラクタ

	static CUiSkill *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bUse);	// オブジェクト生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
private:
};

#endif
