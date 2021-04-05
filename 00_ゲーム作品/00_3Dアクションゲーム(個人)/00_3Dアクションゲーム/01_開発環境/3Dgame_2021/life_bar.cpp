//=========================================================
//
// 体力バークラス	[life_bar.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "life_bar.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"

//=========================================================
// マクロ定義
//=========================================================
#define DECREASE_LIFE_SPEED		(1)		// 体力を減らす速度

//=========================================================
// ポリゴン生成
//=========================================================
CLifeBar * CLifeBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color,
	CCharacter::CHARACTER_TYPE Ctype, int nLife)
{
	// メモリ確保
	CLifeBar *pLifeBar = new CLifeBar;

	pLifeBar->SetGage(nLife);			// 体力の設定
	pLifeBar->SetMaxGage(nLife);		// ライフの設定
	pLifeBar->Init(pos, size);			// 初期化
	pLifeBar->m_Ctype = Ctype;			// バーの種類
	pLifeBar->SetColor(color);			// 色の設定

	return pLifeBar;
}

//=========================================================
// コンストラクタ
//=========================================================
CLifeBar::CLifeBar(PRIORITY Priority) : CGage(Priority)
{

}

//=========================================================
// デストラクタ
//=========================================================
CLifeBar::~CLifeBar()
{
}

//=========================================================
// 初期化処理
//=========================================================
HRESULT CLifeBar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CGage::Init(pos, size);

	return S_OK;
}

//=========================================================
// 終了処理
//=========================================================
void CLifeBar::Uninit(void)
{
	// 終了処理
	CGage::Uninit();
}

//=========================================================
// 更新処理
//=========================================================
void CLifeBar::Update(void)
{
	// 徐々に減らしていく
	if (GetSubGage() > 0)
	{
		// バーの減算
		AddSubNum(DECREASE_LIFE_SPEED);
	}
	else
	{
		// 無くなったら0に戻す
		SetSubNum(0);
	}

	// 更新処理
	CGage::Update();

	// プレイヤーのタイプ
	if (m_Ctype == CCharacter::CHARACTER_TYPE_PLAYER)
	{
		// カラーの変更関数
		ColorChange();
	}
}

//=========================================================
// 描画処理
//=========================================================
void CLifeBar::Draw(void)
{
	// 描画処理
	CGage::Draw();
}

//=========================================================
// カラーの変更
//=========================================================
void CLifeBar::ColorChange(void)
{
	//HPに応じてカラーを変える（満タンから半分まで緑）
	if (GetGage() <= GetMaxGage() && GetGage() > GetMaxGage() / 2)
	{
		SetColor(D3DCOLOR_RGBA(70, 185, 127, 255));
	}

	// HPに応じてカラーを変える（半分から4分の1まで黄色）
	if (GetGage() <= GetMaxGage() / 2 && GetGage() > GetMaxGage() / 4)
	{
		SetColor(D3DCOLOR_RGBA(254, 236, 0, 255));
	}

	// HPに応じてカラーを変える（4分の1からは赤色）
	if (GetGage() <= GetMaxGage() / 4)
	{
		SetColor(D3DCOLOR_RGBA(254, 83, 12, 255));
	}
}