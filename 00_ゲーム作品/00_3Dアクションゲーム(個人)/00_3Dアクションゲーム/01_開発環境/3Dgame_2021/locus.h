#ifndef _LOCUS_H_
#define _LOCUS_H_
//=============================================================================
//
// 軌跡の処理 [locus.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene3D.h"

//=========================================================================
// マクロ定義
//=========================================================================
#define LOCUS_SIZE_X	(30.0f)		// サイズ
#define LOCUS_SIZE_Y	(100.0f)	// サイズ
#define LOCUS_SIZE_Z	(50.0f)		// サイズ
#define LOCUS_LIFE		(8)			// 軌跡のライフ

//=========================================================================
// 軌跡クラス
//=========================================================================
class CLocus :public CScene
{
public:
	CLocus();		// コンストラクタ
	~CLocus();		// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2,
		D3DXVECTOR3 posOld1, D3DXVECTOR3 posOld2);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	static CLocus *Create(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2,
		D3DXVECTOR3 posOld1, D3DXVECTOR3 posOld2,
		D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,
		LPDIRECT3DTEXTURE9 pTex);							// インスタンス生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファポインタ
	D3DXMATRIX	m_mtxWorld;					// ワールドマトリクス
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posOld;					// 古い座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXVECTOR3 m_rot;						// 向き
	D3DXCOLOR m_color;						// 色
	float m_fAlphaNum;						// 透明度の値
	int m_nLife;							// ライフ
};
#endif