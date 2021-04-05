//=========================================================
//
// ゲージクラス	[gage.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "gage.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"

//=========================================================
// マクロ定義
//=========================================================
#define DECREASE_LIFE_SPEED		(1)		// 体力を減らす速度

//=========================================================
// コンストラクタ
//=========================================================
CGage::CGage(PRIORITY Priority) : CScene(Priority)
{
	m_pVtxBuff = nullptr;
	m_nGage = 0;
	m_nMaxGage = 0;
	m_nSubNum = 0;
	m_size = ZeroVector3;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=========================================================
// デストラクタ
//=========================================================
CGage::~CGage()
{
}

//=========================================================
// 初期化処理
//=========================================================
HRESULT CGage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = nullptr;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	m_Pos = pos;
	m_size = size;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// HPが減った場合、画像の右側から描画をやめる
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + (m_size.x)*((float)m_nGage / m_nMaxGage)), m_Pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + (m_size.x)*((float)m_nGage / m_nMaxGage)), m_Pos.y + m_size.y, 0.0f);

	//rhwの設定（値は1.0で設定する）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーを設定（0～255の値で設定する）
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================
// 終了処理
//=========================================================
void CGage::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//オブジェクト破棄
	Release();
}

//=========================================================
// 更新処理
//=========================================================
void CGage::Update(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// HPが減った場合、画像の右側から描画をやめる
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + (m_size.x * 2)*((float)m_nGage / m_nMaxGage)), m_Pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + (m_size.x * 2)*((float)m_nGage / m_nMaxGage)), m_Pos.y + m_size.y, 0.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラーを設定（0～255の値で設定する）
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		pVtx[nCount].col = m_color;
	}

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================================
// 描画処理
//=========================================================
void CGage::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//アルファテストを有効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	CTexture *pTexture = GET_TEXTURE_PTR;

	// テクスチャの設定
	pD3DDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_GAGEBAR));

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//アルファテストを無効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, nullptr);
}

//=========================================================
// 体力の最大数
//=========================================================
void CGage::SetMaxGage(int nMaxGage)
{
	m_nMaxGage = nMaxGage;
}

//=========================================================
// 体力の設定
//=========================================================
void CGage::SetGage(int nGage)
{
	m_nGage = nGage;
}

//=========================================================
// 色の設定
//=========================================================
void CGage::SetColor(D3DXCOLOR color)
{
	m_color = color;
}

//=========================================================
// ダメージ値
//=========================================================
void CGage::SetSubNum(int nSubNum)
{
	m_nSubNum = nSubNum;
}

//=========================================================
// ゲージを減らす
//=========================================================
void CGage::SubGage(int nGage)
{
	m_nGage -= nGage;

	if (m_nGage <= 0)
	{
		m_nGage = 0;
	}
}

//=========================================================
// ゲージを徐々に減らす処理
//=========================================================
void CGage::AddSubNum(int nAddNum)
{
	m_nSubNum -= nAddNum;
	m_nGage -= nAddNum;
}

//=========================================================
// ゲージの回復
//=========================================================
void CGage::HealGage(int nHealGage)
{
	// ゲージの最大より少なかったら
	if (m_nMaxGage > m_nGage)
	{
		// ゲージを増やす
		m_nGage += nHealGage;

		// 増やしたゲージが最大数を超えたら
		if (m_nGage > m_nMaxGage)
		{
			// 最大数と同じ値にする
			m_nGage = m_nMaxGage;
		}
	}
}