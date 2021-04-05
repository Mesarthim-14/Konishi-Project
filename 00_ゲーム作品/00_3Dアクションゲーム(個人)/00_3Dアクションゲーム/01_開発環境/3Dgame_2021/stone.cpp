//=============================================================================
//
// 岩のクラス [stone.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "stone.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define STONE_GRAVITY_POWAR			(1.0f)			// 重力の強さ
#define STONE_GROUND_RIMIT			(0.0f)			// 地面の制限
#define STONE_SUB_ALPHA_SPEED		(0.05f)			// 透明度の速度

//=============================================================================
// コンストラクタ
//=============================================================================
CStone::CStone(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CStone::~CStone()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CStone * CStone::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CStoneEffect::STONE stone, CXfile::XFILE_NUM StoneNum)
{
	//3Dポリゴンクラスのポインタ変数
	CStone *pStone = new CStone;

	//メモリが確保できていたら
	if (pStone != nullptr)
	{
		// 距離の設定
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)stone.Distance.x + rand() % (int)stone.Distance.x - rand() % (int)stone.Distance.x - rand() % (int)stone.Distance.x),
			(float)(rand() % (int)stone.Distance.y + rand() % (int)stone.Distance.y),
			(float)(rand() % (int)stone.Distance.z + rand() % (int)stone.Distance.z - rand() % (int)stone.Distance.z - rand() % (int)stone.Distance.z));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y + 100.0f,
			pos.z + Distance.z);

		//初期化処理呼び出し
		pStone->Init(TargetPos, stone.size);

		// 移動量をランダムで決める
		D3DXVECTOR3 RandMove = D3DXVECTOR3(
		(float)(move.x * ((rand() % (int)stone.move.x + rand() % (int)stone.move.x - rand() % (int)stone.move.x))),
			(float)(rand() % (int)stone.move.y + rand() % (int)stone.move.y + rand() % (int)stone.move.y),
			(float)((move.z * (rand() % (int)stone.move.z + rand() % (int)stone.move.z - rand() % (int)stone.move.z))));

		// Xファイルのポインタ
		CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	// モデルの読み込み
		pStone->BindModel(pXFile->GetXfile(StoneNum));
		pStone->BindTexture(pXFile->GetXfileTexture(StoneNum));

		// 移動量の設定
		pStone->SetMove(RandMove);

		// ライフの設定
		int nLife = stone.nLife;
		pStone->SetLife(nLife);

		// カラーの設定
		pStone->SetColor(stone.color);
	}

	return pStone;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStone::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(pos, size);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStone::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStone::Update(void)
{
	// 更新処理
	CModel::Update();

	// 着地の処理
	if (GetPos().y <= STONE_GROUND_RIMIT)
	{
		// 移動を0にする
		SetMove(ZeroVector3);

		// 座標を戻す
		SetPos(D3DXVECTOR3(GetPos().x, STONE_GROUND_RIMIT, GetPos().z));

		// 透明にしていく
		SubAlpha(STONE_SUB_ALPHA_SPEED);
	}
	else
	{
		// 重力をかける
		SetMove(D3DXVECTOR3(GetMove().x, GetMove().y - STONE_GRAVITY_POWAR, GetMove().z));
	}

	// ライフが0を下回ったら
	if (GetLife() <= 0 || GetAlphaNum() >= 1.0f)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CStone::Draw(void)
{
	// 描画処理
	CModel::Draw();
}