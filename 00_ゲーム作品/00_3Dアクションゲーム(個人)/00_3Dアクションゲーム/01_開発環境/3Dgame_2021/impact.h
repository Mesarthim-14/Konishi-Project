#ifndef _IMPACT_H_
#define _IMPACT_H_
//=============================================================================
//
// 衝撃エフェクトクラスヘッダー [impact.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "effect_3d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define IMPACT_SCALE_NUM			(0.045f)	// 拡大の値
#define ATTACK_IMPACT_SCALE_NUM		(0.05f)		// 攻撃時のスケール
#define DUSH_IMPACT_SCALE_NUM		(0.1f)		// 攻撃時のスケール

//=============================================================================
// 衝撃クラス
//=============================================================================
class CImpact : public CEffect3D
{
public:
	CImpact();			// コンストラクタ
	~CImpact();			// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CImpact * Create(D3DXVECTOR3 pos,			// インスタンス生成
		CEffectFactory::EFFECT Particle,
		int nTexInfo, bool bInverse, float fNum);

private:
	int m_nCounter;		// カウンター
	float m_fScaleNum;	// 拡大の値
};

#endif