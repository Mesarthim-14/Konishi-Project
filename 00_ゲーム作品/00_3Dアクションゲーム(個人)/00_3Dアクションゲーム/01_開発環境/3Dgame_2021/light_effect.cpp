//=============================================================================
//
// ライトエフェクトのクラス [light_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "light_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLightEffect::CLightEffect(PRIORITY Priority) : CModel(Priority)
{
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLightEffect::~CLightEffect()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CLightEffect * CLightEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
{
	// メモリ確保
	CLightEffect *pLightEffect = new CLightEffect;

	// nullchack
	if (pLightEffect != NULL)
	{
		//初期化処理呼び出し
		pLightEffect->Init(pos, size);		// 座標・サイズ
		pLightEffect->m_nLife = nLife;		// ライフ
	}

	return pLightEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLightEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(pos, size);

	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	// モデル情報
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_SWORD_EFFECT));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_SWORD_EFFECT));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLightEffect::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLightEffect::Update(void)
{
	// 更新処理
	CModel::Update();
	
	// 寿命減算
	m_nLife--;

	// もしライフが指定されたフレーム以下になったら
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLightEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//マテリアルデータへのポインタ

	// マテリアル情報取得
	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.3f, 1.0f, 0.3f, 0.2f);
		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;
	}

	// 描画処理
	CModel::Draw();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}
}