//=============================================================================
//
// 衝撃エフェクトクラス [impact.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "impact.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define IMPACT_SCALE_CHANGE_NUM		(0.02f)		// 変わった後
#define IMPACT_SUB_ALPHA_NUM		(0.08f)		// 透明度
#define IMPACT_CHANGE_TIME			(20)		// 代わりのフレーム

//=============================================================================
// インスタンス生成
//=============================================================================
CImpact * CImpact::Create(D3DXVECTOR3 pos, CEffectFactory::EFFECT Particle,
	int nTexInfo, bool bInverse, float fNum)
{
	// インスタンス生成
	CImpact *pImpact = new CImpact;

	// nullcheck
	if (pImpact != nullptr)
	{
		// 距離の設定
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x),
			(float)(rand() % (int)Particle.Distance.y + rand() % (int)Particle.Distance.y),
			(float)(rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		// 初期化処理
		pImpact->Init(TargetPos, Particle.size);

		CTexture *pTexture = GET_TEXTURE_PTR;

		// アニメーション情報
		if (Particle.bAnimation == false)
		{
			// テクスチャ設定
			pImpact->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));
		}
		else
		{
			// アニメーションテクスチャ設定
			pImpact->BindTexture(pTexture->GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));

			// アニメーション情報
			pImpact->InitAnimation(
				pTexture->GetSparateTexInfo((CTexture::SEPARATE_TEX_TYPE)nTexInfo),
				pTexture->GetSparateTexLoop((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
		}

		// 移動量が一定以上なら
		if (Particle.move.x >= 1.0f &&
			Particle.move.y >= 1.0f &&
			Particle.move.z >= 1.0f)
		{
			// 移動量設定
			D3DXVECTOR3 move;
			switch (Particle.bGravity)
			{
				// 重力無し
			case false:
				// 移動量
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;

				// 重力あり
			case true:
				// 移動量
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;
			}

			// 移動量
			pImpact->SetMove(move);
		}
		else
		{
			// 移動量
			pImpact->SetMove(Particle.move);
		}

		// 値の代入
		pImpact->SetColor(Particle.color);			// 色の設定
		pImpact->SetLife(Particle.nLife);			// 体力の設定
		pImpact->SetAlpha(Particle.bAlpha);			// アルファテストの設定
		pImpact->SetAlphaNum(Particle.nAlphaNum);	// アルファテストの値
		pImpact->SetBlend(Particle.bBlend);			// 加算合成を行うか
		pImpact->SetInverse(bInverse);				// 逆行列を行うか
		pImpact->m_fScaleNum = fNum;				// スケール値の設定
	}

	return pImpact;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CImpact::CImpact()
{
	m_nCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CImpact::~CImpact()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CImpact::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CEffect3D::Init(pos, size);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CImpact::Uninit(void)
{
	// 終了処理
	CEffect3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CImpact::Update(void)
{
	m_nCounter++;

	// 一定以上で
	if (m_nCounter >= IMPACT_CHANGE_TIME)
	{
		// 拡大する
		ScaleUp(IMPACT_SCALE_CHANGE_NUM);
		SubAlpha(IMPACT_SUB_ALPHA_NUM);
	}
	else
	{
		// 拡大する
		ScaleUp(m_fScaleNum);
	}

	// 更新処理
	CEffect3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CImpact::Draw(void)
{
	// 描画処理
	CEffect3D::Draw();
}