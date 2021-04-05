//=============================================================================
//
// 斬撃エフェクトのクラス [slashing_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "slashing_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSlashingEffect::CSlashingEffect(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSlashingEffect::~CSlashingEffect()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CSlashingEffect * CSlashingEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//3Dポリゴンクラスのポインタ変数
	CSlashingEffect *pLightEffect = new CSlashingEffect;

	//メモリが確保できていたら
	if (pLightEffect != NULL)
	{
		//初期化処理呼び出し
		pLightEffect->Init(pos, size);
	}

	return pLightEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSlashingEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), size);

	// Xファイルのポインタ
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	// Xファイルの設定
//	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_SWORD_LOCUS_EFFECT));				// モデル情報
//	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_SWORD_LOCUS_EFFECT));		// テクスチャ情報

	return S_OK;
}