//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));

	// 通常テクスチャの名前の設定
	m_aTexFileName =
	{
		{ "data/Texture/fire111.jpg" },
		{"data/Texture/LifeBar.png"},					// ライフの枠
		{"data/Texture/LifeBar000.png" },				// ライフバー(緑)
		{"data/Texture/bg001.png" },					// タイトル画面の背景
		{"data/Texture/effect003.png" },				// パーティクル
		{"data/Texture/skill_ui.png" },					// スキルのUI
		{"data/Texture/sword_locus000.png" },			// 剣の軌跡
		{"data/Texture/magic24.jpg" },					// 斬撃のエフェクト
		{"data/Texture/Sword_Skill_Start001.png" },		// スキルの待機時
		{"data/Texture/QuestStart_Logo.png" },			// クエストの開始
		{"data/Texture/button_ui.png" },				// 操作ボタンのUI
		{"data/Texture/inpact.tga" },					// ジャンプの衝撃
		{"data/Texture/inpact_red.tga" },				// 咆哮の衝撃
		{"data/Texture/Hit_Impact002.tga" },			// 攻撃時の衝撃
		{"data/Texture/floor.jpg" },					// 床のテクスチャ
		{"data/Texture/Hit_Impact003.tga" },			// ダッシュの衝撃
		{"data/Texture/sword_locus002.png" },			// ボスの軌跡
		{"data/Texture/hit_ui.png" },					// HITのUI
		{"data/Texture/damage_ui.png" },				// ダメージのUI
	};

	// 分割テクスチャの名前の設定
	m_aSparateTexFileName =
	{
		{"data/Texture/sharp_effect.png"},				// 鋭いエフェクト
		{ "data/Texture/Electricity_Effect000.png" },	// 電撃エフェクト
		{ "data/Texture/smoke000.png" },				// 煙エフェクト
		{ "data/Texture/hit_effect000.png" },			// ヒットエフェクト
		{ "data/Texture/slash_impact.png" },			// ヒット時の衝撃
		{ "data/Texture/sand_smoke.png" },				// ヒット時の衝撃
		{ "data/Texture/circle.png" },					// サークルエフェクト
		{ "data/Texture/attack_light_001.png" },		// 攻撃時の光
		{ "data/Texture/smoke_101.png" },				// コボルトの煙
		{ "data/Texture/smoke_effect000.png" },			// ジャンプの煙
		{ "data/Texture/attack_circle000.png" },		// 攻撃の円
		{ "data/Texture/damage_number.png" },			// ダメージの数字テクスチャ
		{ "data/Texture/arm_light.png" },				// 手の光
		{ "data/Texture/damage_impact100.tga" },		// ダメージ時のエフェクト
		{ "data/Texture/roar_attack000.png" },			// 咆哮時のファイア
		{ "data/Texture/roar_light000.png" },			// 咆哮時の光
		{ "data/Texture/combo_damage.png" },			// コンボのナンバー
		{ "data/Texture/combo_damage000.png" },			// コンボのダメージナンバー
	};
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
	// 通常テクスチャクリア
	m_aTexFileName.clear();

	// 分割テクスチャクリア
	m_aSparateTexFileName.clear();
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	// メモリ確保
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 分割テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aSparateTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aSparateTexFileName[nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}

	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// テクスチャの解放
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// テクスチャ情報
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}