#ifndef _GAGE_H_
#define _GAGE_H_
//=========================================================
//
// 体力バークラスヘッダー	[gage.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "scene.h"

//=========================================================
// マクロ定義
//=========================================================

//=========================================================
// ゲージバークラス
//=========================================================
class CGage : public CScene
{
public:
	CGage(PRIORITY Priority = PRIORITY_1);						// コンストラクタ
	~CGage();													// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理

	// Set関数
	void SubGage(int nGage);									// HPバーの設定
	void SetMaxGage(int nMaxGage);								// ライフの最大値設定
	void SetGage(int nGage);									// ライフの設定
	void SetColor(D3DXCOLOR color);								// 色の設定	
	void SetSubNum(int nSubNum);								// ダメージ値の設定
	void AddSubNum(int nAddNum);								// ダメージ値の加算
	void HealGage(int nHealGage);								// ゲージの回復

	// Get関数
	int GetGage(void) { return m_nGage; }						// 体力の情報
	int GetMaxGage(void) { return m_nMaxGage; }					// 体力の最大数情報
	int GetSubGage(void) { return m_nSubNum; }					// ダメージの値情報
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// バッファのポインタ
	D3DXVECTOR3 m_Pos;						// 座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXCOLOR m_color;						// 色
	int m_nMaxGage;							// 体力の最大値
	int m_nGage;							// 体力
	int m_nSubNum;							// ダメージの値
};
#endif