#ifndef _COMBO_H_
#define _COMBO_H_
//=============================================================================
//
// コンボクラスヘッダー [combo.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NUMBER_NUM		(4)			// 最大の桁数
#define MAX_DAMAGE_NUM		(6)			// ダメージの最大桁数
#define DAMAGE_MAG			(1.05f)		// ダメージ倍率

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber2d;
class CUi;

//=============================================================================
// コンボクラス
//=============================================================================
class CCombo
{
public:
	CCombo();							// コンストラクタ
	~CCombo();							// デストラクタ

	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理

	static CCombo *Create(void);		// インスタンス生成

	void Combo(int nDamage);			// コンボの処理関数
	void UiCreate(void);				// UIの生成
	void UiUninit(void);				// Uiの終了
	void ComboNum(void);				// コンボ数の処理
	void DamageNum(void);				// ダメージの処理
	void ComboBreak(void);				// コンボの終了の関数

	// Get関数
	int GetComboNum(void) { return m_nCounter; }			// コンボ数の情報

private:
	CNumber2d *m_apCombo[MAX_NUMBER_NUM];	// 桁数分
	CNumber2d *m_apDamage[MAX_DAMAGE_NUM];	// ダメージ量
	CUi *m_pHitUi;							// HITのUI
	CUi *m_pDamageUi;						// ダメージのUI
	int m_nCounter;							// コンボのカウンター
	int m_nFlameCounter;					// コンボのフレームカウント
	int m_nDamage;							// コンボ中のダメージの総量
	int m_nOldDamageDig;					// ダメージの古い桁数
	bool m_bCombo;							// コンボのフラグ
};

#endif