//=============================================================================
//
// ガードエフェクトのクラス [guard_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "guard_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GUARD_EFFECT_ALPHA_NUM		(0.7f)												// ガードエフェクトの透過値
#define GUARD_EFFECT_LUMINOUS_COLOR (D3DXCOLOR(0.9f, 1.0f, 0.9f, 0.8f))					// 発行の値
#define GUARD_EFFECT_ADD_NUM		(0.01f)												// 色の加算値

#define GUARD_EFFECT_COLOR_R	(0.3f)													// 色の設定
#define GUARD_EFFECT_COLOR_G	(1.0f)													// 色の設定
#define GUARD_EFFECT_COLOR_B	(0.3f)													// 色の設定
#define GUARD_EFFECT_COLOR_A	(0.2f)													// 色の設定

#define GUARD_EFFECT_COLOR	(D3DXCOLOR(GUARD_EFFECT_COLOR_R, GUARD_EFFECT_COLOR_G, GUARD_EFFECT_COLOR_B, GUARD_EFFECT_COLOR_A))

//=============================================================================
// コンストラクタ
//=============================================================================
CGuardEffect::CGuardEffect(PRIORITY Priority) : CModel(Priority)
{
	m_fSubNum = 0.0f;
	m_bLuminous = false;
	m_Emissive = WhiteColor;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGuardEffect::~CGuardEffect()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CGuardEffect * CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//3Dポリゴンクラスのポインタ変数
	CGuardEffect *pGuardEffect = new CGuardEffect;

	//メモリが確保できていたら
	if (pGuardEffect != nullptr)
	{
		//初期化処理呼び出し
		pGuardEffect->Init(pos, size);
	}

	return pGuardEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGuardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(pos, size);
	SubAlpha(GUARD_EFFECT_ALPHA_NUM);

	// Xファイルのポインタ
	CXfile *pXFile = GET_XFILE_PTR;

	// モデル情報取得
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_GUARD_EFFECT));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_GUARD_EFFECT));

	// 色の設定
	m_Emissive = GUARD_EFFECT_COLOR;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGuardEffect::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGuardEffect::Update(void)
{
	// 更新処理
	CModel::Update();

	// 発光時
	if (m_bLuminous == true)
	{
		// 色の減算
			m_Emissive.r -= GUARD_EFFECT_ADD_NUM;
			m_Emissive.g -= GUARD_EFFECT_ADD_NUM;
			m_Emissive.b -= GUARD_EFFECT_ADD_NUM;
			m_Emissive.a -= GUARD_EFFECT_ADD_NUM;

			// 一定以上で
		if (m_Emissive.r <= GUARD_EFFECT_COLOR_R)
		{
			// カラーを戻す
			m_Emissive = GUARD_EFFECT_COLOR;

			m_bLuminous = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGuardEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//マテリアルデータへのポインタ

	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pMat[nCntMat].MatD3D.Emissive = m_Emissive;

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

//=============================================================================
// 発光の処理
//=============================================================================
void CGuardEffect::Luminous(void)
{
	// 色を白にする
	m_Emissive = GUARD_EFFECT_LUMINOUS_COLOR;

	m_bLuminous = true;
}