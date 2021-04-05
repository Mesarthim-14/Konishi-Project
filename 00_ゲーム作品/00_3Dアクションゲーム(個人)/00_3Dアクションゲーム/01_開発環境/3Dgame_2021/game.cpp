//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "fire.h"
#include "enemy.h"
#include "life_frame.h"
#include "life_bar.h"
#include "quest_logo.h"
#include "effect_factory.h"
#include "kobold.h"
#include "mesh_tube.h"
#include "mesh_3d.h"
#include "mesh_pillar.h"
#include "resource_manager.h"

//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_pCamera = nullptr;
CLight *CGame::m_pLight = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CBg *CGame::m_pBg = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CPause *CGame::m_pPause = nullptr;
CSea *CGame::m_pSea = nullptr;

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// クリエイト
//=======================================================================================
CGame* CGame::Create(void)
{
	// メモリ確保
	CGame* pGame = new CGame();

	// 初期化処理
	pGame->Init(ZeroVector3, ZeroVector3);

	return pGame;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// カメラクラスのクリエイト
	m_pCamera = CCamera::Create();

	//ライトクラスの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(ZeroVector3, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));	
	}

	// メッシュフィールド
	m_pMeshField = CMeshField::Create();

	// 背景
	if (m_pBg == nullptr)
	{
		m_pBg = CBg::Create(BG_POS, BG_SIZE);
	}

	// 蟹の生成
	//CCrab::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), ZeroVector3);

	// コボルトの生成
	CKobold::Create(D3DXVECTOR3(0.0f, 0.0f, -6000.0f), ZeroVector3);

	//BGM
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//フォントの生成
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != nullptr)
	{
		//カメラクラスの終了処理呼び出す
		m_pCamera->Uninit();

		//メモリの破棄
		delete m_pCamera;

		//メモリのクリア
		m_pCamera = nullptr;
	}

	// 背景
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// ライトの終了処理
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// プレイヤーの終了処理
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// 地面の終了処理
	if (m_pMeshField != nullptr)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}

	// !nullcheck
	if (CManager::GetResourceManager() != nullptr)
	{
		//サウンド情報取得
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

		// !nullcheck
		if (pSound != nullptr)
		{
			//ゲームBGM停止
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	if (m_pCamera != nullptr)
	{
		//カメラクラスの更新処理
		m_pCamera->Update();
	}

	// ゲームの設定
	SetGame();
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
	// 背景
	if (m_pBg != nullptr)
	{
		m_pBg->Draw();
	}

	// ライト
	if (m_pLight != nullptr)
	{
		m_pLight->ShowLightInfo();
	}
}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
	// ゲームのタイムカウンター
	m_nTimeCounter++;

	// クエストロゴ生成
	if (m_nTimeCounter == 60)
	{
		// クエストロゴ生成
		CQuestLogo::Create();
	}
}

//=======================================================================================
// カメラの情報
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ライトの情報
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// プレイヤーの情報
//=======================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=======================================================================================
// コンテニューの情報
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}