#ifndef _UI_OPERATION_H_
#define _UI_OPERATION_H_
//=============================================================================
//
// 操作のUIクラスヘッダー [ui_operation.h]
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
#define UI_OPERATION_POS_X		(1100.0f)	// X座標
#define UI_OPERATION_POS_Y		(520.0f)	// Y座標
#define UI_OPERATION_SIZE_X		(95.0f)		// Xサイズ
#define UI_OPERATION_SIZE_Y		(95.0f)		// Yサイズ

#define UI_OPERATION_POS		(D3DXVECTOR3(UI_OPERATION_POS_X, UI_OPERATION_POS_Y, 0.0f))		// 座標
#define UI_OPERATION_SIZE		(D3DXVECTOR3(UI_OPERATION_SIZE_X, UI_OPERATION_SIZE_Y, 0.0f))	// サイズ

//=============================================================================
// スキルのUIクラス宣言
//=============================================================================
class CUiOperation : public CUi
{
public:
	CUiOperation();		// コンストラクタ
	~CUiOperation();	// デストラクタ

	static CUiOperation *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bUse);	// オブジェクト生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
private:
};

#endif
