//=============================================================================
//
// コンボクラス [combo.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "combo.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include "texture.h"
#include "ui.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COMBO_NUMBER_INTERVAL	(50.0f)														// コンボ数の間隔
#define COMBO_DAMAGE_INTERVAL	(30.0f)														// コンボ数の間隔
#define MAX_NUMBER				(3)															// 数字の桁最大数
#define COMBO_RIMIT				(500)														// コンボのフレーム制限

// HITのUI情報
#define HIT_UI_POS_X	(1100.0f)															// HITのUI座標
#define HIT_UI_POS_Y	(230.0f)															// HITのUI座標
#define HIT_UI_POS		(D3DXVECTOR3(HIT_UI_POS_X, HIT_UI_POS_Y, 0.0f))

#define HIT_UI_SIZE_X	(50.0f)																// HITのUIサイズ
#define HIT_UI_SIZE_Y	(40.0f)																// HITのUIサイズ
#define HIT_UI_SIZE		(D3DXVECTOR3(HIT_UI_SIZE_X, HIT_UI_SIZE_Y, 0.0f))

// HITのUI情報
#define DAMAGE_UI_POS_X		(1140.0f)														// HITのUI座標
#define DAMAGE_UI_POS_Y		(310.0f)														// HITのUI座標
#define DAMAGE_UI_POS		(D3DXVECTOR3(DAMAGE_UI_POS_X, DAMAGE_UI_POS_Y, 0.0f))

#define DAMAGE_UI_SIZE_X	(80.0f)															// HITのUIサイズ
#define DAMAGE_UI_SIZE_Y	(25.0f)															// HITのUIサイズ
#define DAMAGE_UI_SIZE		(D3DXVECTOR3(DAMAGE_UI_SIZE_X, DAMAGE_UI_SIZE_Y, 0.0f))

// コンボ数UIの情報
#define COMBO_NUMBER_POS_X (HIT_UI_POS_X-100.0f)											// コンボ数の座標
#define COMBO_NUMBER_POS_Y	(HIT_UI_POS_Y)													// コンボ数の座標
#define COMBO_NUMBER_POS	(D3DXVECTOR3(COMBO_NUMBER_POS_X, COMBO_NUMBER_POS_Y, 0.0f))

#define COMBO_NUMBER_SIZE_X (70.0f)															// コンボ数の座標
#define COMBO_NUMBER_SIZE_Y	(70.0f)															// コンボ数の座標
#define COMBO_NUMBER_SIZE	(D3DXVECTOR3(COMBO_NUMBER_SIZE_X, COMBO_NUMBER_SIZE_Y, 0.0f))

// コンボダメージ総数の情報
#define COMBO_DAMAGE_POS_X (DAMAGE_UI_POS_X-115.0f)											// コンボ数の座標
#define COMBO_DAMAGE_POS_Y	(DAMAGE_UI_POS_Y)												// コンボ数の座標
#define COMBO_DAMAGE_POS	(D3DXVECTOR3(COMBO_DAMAGE_POS_X, COMBO_DAMAGE_POS_Y, 0.0f))

#define COMBO_DAMAGE_SIZE_X (40.0f)															// コンボ数の座標
#define COMBO_DAMAGE_SIZE_Y	(40.0f)															// コンボ数の座標
#define COMBO_DAMAGE_SIZE	(D3DXVECTOR3(COMBO_DAMAGE_SIZE_X, COMBO_DAMAGE_SIZE_Y, 0.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CCombo::CCombo()
{
	m_nCounter = 0;
	m_nFlameCounter = 0;
	m_nDamage = 0;
	m_nOldDamageDig = 0;
	m_bCombo = false;
	m_pHitUi = nullptr;
	m_pDamageUi = nullptr;
	memset(m_apCombo, 0, sizeof(m_apCombo));
	memset(m_apDamage, 0, sizeof(m_apDamage));
}

//=============================================================================
// デストラクタ
//=============================================================================
CCombo::~CCombo()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CCombo * CCombo::Create(void)
{
	// メモリ確保
	CCombo *pCombo = new CCombo;

	return pCombo;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCombo::Uninit(void)
{
	// コンボが繋がっているとき
	if (m_bCombo == true)
	{
		// UIの終了処理
		UiUninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CCombo::Update(void)
{
	// コンボされているとき
	if (m_bCombo == true)
	{
		// カウンターを進める
		m_nFlameCounter++;

		// カウンターが一定になったら
		if (m_nFlameCounter >= COMBO_RIMIT)
		{
			// UIの終了
			UiUninit();

			// 値の初期化
			m_nFlameCounter = 0;
			m_nCounter = 0;
			m_nDamage = 0;
			m_bCombo = false;
		}
	}
}

//=============================================================================
// コンボ時の処理
//=============================================================================
void CCombo::Combo(int nDamage)
{
	m_nCounter++;			// コンボ回数
	m_nDamage += nDamage;	// ダメージの加算

	// コンボが使われていなかったら
	if (m_bCombo == false)
	{
		// UIの生成
		UiCreate();
	}
	else
	{
		// コンボ数の処理
		ComboNum();

		// ダメージ値処理
		DamageNum();

		// カウンターを戻す
		m_nFlameCounter = 0;
	}
}

//=============================================================================
// UIの生成
//=============================================================================
void CCombo::UiCreate(void)
{
	// コンボ数
	int nComboDigit = 0;
	int nConboNum = m_nCounter;

	// 桁数を求める
	while (nConboNum != 0)
	{
		nConboNum /= 10;
		nComboDigit++;
	}

	// テクスチャのポインタ
	CTexture *pTexture = GET_TEXTURE_PTR;

	// コンボ数の処理
	for (int nCount = 0; nCount < nComboDigit; nCount++)
	{
		if (m_apCombo[nCount] == nullptr)
		{
			// 数字のメモリ確保
			m_apCombo[nCount] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_NUMBER_POS_X - nCount*COMBO_NUMBER_INTERVAL, COMBO_NUMBER_POS_Y, 0.0f), COMBO_NUMBER_SIZE);							// 座標、サイズ

			if (m_apCombo[nCount] != nullptr)
			{
				// テクスチャの設定
				m_apCombo[nCount]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER));

				// 数字の設定
				m_apCombo[nCount]->SetNumber(m_nCounter);
			}
		}
	}

	// ダメージ総数
	int nDamageDigit = 0;
	int nDamageNum = m_nDamage;

	// 桁数を求める
	while (nDamageNum != 0)
	{
		nDamageNum /= 10;
		nDamageDigit++;
	}

	// 桁数保管
	m_nOldDamageDig = nDamageDigit;

	// コンボ数の処理
	for (int nCount = 0; nCount < nDamageDigit; nCount++)
	{
		if (m_apDamage[nCount] == nullptr)
		{
			// 数字のメモリ確保
			m_apDamage[nCount] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_DAMAGE_POS_X - nCount*COMBO_DAMAGE_INTERVAL, COMBO_DAMAGE_POS_Y, 0.0f), COMBO_DAMAGE_SIZE);							// 座標、サイズ

			if (m_apDamage[nCount] != nullptr)
			{
				m_apDamage[nCount]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER_000));	// テクスチャの設定

					// 桁の値を出す
				int nNum = (m_nDamage / (int)(pow(10, nCount))) % 10;

				// 数字の設定
				m_apDamage[nCount]->SetNumber(nNum);
			}
		}
	}

	// HITのUIが使われていなかったら
	if (m_pHitUi == nullptr)
	{
		// インスタンス生成
		m_pHitUi = CUi::Create(HIT_UI_POS, HIT_UI_SIZE);
		m_pHitUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_HIT_UI));
	}

	// ダメージのUIが使われていなかったら
	if (m_pDamageUi == nullptr)
	{
		// インスタンス生成
		m_pDamageUi = CUi::Create(DAMAGE_UI_POS, DAMAGE_UI_SIZE);
		m_pDamageUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_DAMAGE_UI));
	}

	// コンボしている状態にする
	m_bCombo = true;

}

//=============================================================================
// UIの終了
//=============================================================================
void CCombo::UiUninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apCombo[nCount] != nullptr)
		{
			// 数字のメモリ確保
			m_apCombo[nCount]->Uninit();
			m_apCombo[nCount] = nullptr;
		}
	}

	for (int nCount = 0; nCount < MAX_DAMAGE_NUM; nCount++)
	{
		if (m_apDamage[nCount] != nullptr)
		{
			// 数字のメモリ確保
			m_apDamage[nCount]->Uninit();
			m_apDamage[nCount] = nullptr;
		}
	}

	// HITのUIが使われていたら
	if (m_pHitUi != nullptr)
	{
		// 終了処理
		m_pHitUi->Uninit();
		m_pHitUi = nullptr;
	}

	// ダメージのUIが使われていたら
	if (m_pDamageUi != nullptr)
	{
		// 終了処理
		m_pDamageUi->Uninit();
		m_pDamageUi = nullptr;
	}
}

//=============================================================================
// 新しい桁が増えたとき
//=============================================================================
void CCombo::ComboNum(void)
{
	int nDigit = 0;
	int nNumber = m_nCounter;

	// 桁数を求める
	while (nNumber != 0)
	{
		nNumber /= 10;
		nDigit++;
	}

	CTexture *pTexture = GET_TEXTURE_PTR;

	//　桁が増えたら
	if (m_nCounter == 10 || m_nCounter == 100 || m_nCounter == 1000)
	{
		if (m_apCombo[nDigit - 1] == nullptr)
		{
			// 数字のメモリ確保
			m_apCombo[nDigit - 1] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_NUMBER_POS_X - (nDigit - 1) *COMBO_NUMBER_INTERVAL, COMBO_NUMBER_POS_Y, 0.0f), COMBO_NUMBER_SIZE);							// 座標、サイズ

			if (m_apCombo[nDigit - 1] != nullptr)
			{
				m_apCombo[nDigit - 1]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER));	// テクスチャの設定

				// 数字の設定
				m_apCombo[nDigit - 1]->SetNumber(0);
			}
		}
	}

	for (int nCount = 0; nCount < nDigit; nCount++)
	{
		// 桁の値を出す
		int nNum = (m_nCounter / (int)(pow(10, nCount))) % 10;

		// 数字の設定
		m_apCombo[nCount]->SetNumber(nNum);
	}
}

//=============================================================================
// ダメージ数の処理
//=============================================================================
void CCombo::DamageNum(void)
{
	int nDigit = 0;
	int nNumber = m_nDamage;

	// 桁数を求める
	while (nNumber != 0)
	{
		nNumber /= 10;
		nDigit++;
	}

	CTexture *pTexture = GET_TEXTURE_PTR;

	// 前回より桁が大きかったら
	if (m_nOldDamageDig < nDigit)
	{
		if (m_apDamage[nDigit - 1] == nullptr)
		{
			// 数字のメモリ確保
			m_apDamage[nDigit - 1] = CNumber2d::Create(D3DXVECTOR3(
				COMBO_DAMAGE_POS_X - (nDigit - 1) *COMBO_DAMAGE_INTERVAL, COMBO_DAMAGE_POS_Y, 0.0f), COMBO_DAMAGE_SIZE);							// 座標、サイズ

			if (m_apDamage[nDigit - 1] != nullptr)
			{
				m_apDamage[nDigit - 1]->BindTexture(
					pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_COMBO_NUMBER_000));	// テクスチャの設定

				// 数字の設定
				m_apDamage[nDigit - 1]->SetNumber(0);
			}
		}

		// 桁数確保
		m_nOldDamageDig = nDigit;
	}

	for (int nCount = 0; nCount < nDigit; nCount++)
	{
		// 桁の値を出す
		int nNum = (m_nDamage / (int)(pow(10, nCount))) % 10;

		// 数字の設定
		m_apDamage[nCount]->SetNumber(nNum);
	}
}

//=============================================================================
// コンボの終了関数
//=============================================================================
void CCombo::ComboBreak(void)
{
	// コンボを終了フレームまで進める
	m_nFlameCounter = COMBO_RIMIT;
}