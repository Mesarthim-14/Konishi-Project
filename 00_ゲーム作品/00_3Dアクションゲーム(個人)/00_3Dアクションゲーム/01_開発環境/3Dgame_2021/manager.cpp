//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "bg.h"
#include "billboard.h"
#include "fade.h"
#include "fire.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "mesh_3d.h"
#include "model.h"
#include "effect_factory.h"
#include "player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "result.h"
#include "scene3D.h"
#include "sound.h"
#include "stone_effect.h"
#include "texture.h"
#include "title.h"
#include "title_bg.h"
#include "tutorial.h"
#include "xfile.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInput = nullptr;
CFade *CManager::m_pFade = nullptr;
CTitle *CManager::m_pTitle = nullptr;
CTutorial *CManager::m_pTutorial = nullptr;
CGame *CManager::m_pGame = nullptr;
CResult *CManager::m_pResult = nullptr;
CInputJoypad *CManager::m_pJoypad = nullptr;
CScene *CManager::m_pScene = nullptr;
CTitleBg *CManager::m_pTitleBg = nullptr;
CResourceManager *CManager::m_pResourceManager = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダラークラスのインスタンス生成
	m_pRenderer = new CRenderer;

	//メモリが確保できたら
	if (m_pRenderer != nullptr)
	{
		// 初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//入力処理クラスのインスタンス生成
	m_pInput = new CInputKeyboard;

	//メモリが確保できたら
	if (m_pInput != nullptr)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//入力処理クラスのインスタンス生成
	m_pJoypad = new CInputJoypad;

	//メモリが確保できたら
	if (m_pJoypad != nullptr)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	// nullcheck
	if (m_pResourceManager == nullptr)
	{
		// リソースマネージャのインスタンス生成
		m_pResourceManager = CResourceManager::GetInstance();
	}

	//フェードクラスのクリエイト
	m_pFade = CFade::Create();

	//全テクスチャの読み込み
	LoadAll();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//全テクスチャの破棄
	UnLoadAll();

	//現在モードの終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		if (m_pTitle != nullptr)
		{
			// 終了処理
			m_pTitle->Uninit();
			m_pTitle = nullptr;
		}

		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != nullptr)
		{
			// 終了処理
			m_pTutorial->Uninit();
			m_pTutorial = nullptr;
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame != nullptr)
		{
			// 終了処理
			m_pGame->Uninit();
			m_pGame = nullptr;
		}
		break;

		// リザルト
	case MODE_TYPE_RESULT:
		if (m_pResult != nullptr)
		{
			// 終了処理
			m_pResult->Uninit();
			m_pResult = nullptr;
		}
		break;
	}

	// nullchack
	if (m_pFade != nullptr)
	{
		//フェードクラスの終了処理呼び出し
		m_pFade->Uninit();

		//メモリの破棄
		delete m_pFade;

		//メモリのクリア
		m_pFade = nullptr;
	}

	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// リソースのロード
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}

	if (m_pInput != nullptr)
	{
		//入力処理クラスの終了処理呼び出し
		m_pInput->Uninit();

		//メモリの削除
		delete m_pInput;

		//メモリのクリア
		m_pInput = nullptr;
	}

	if (m_pJoypad != nullptr)
	{
		//入力処理クラスの終了処理呼び出し
		m_pJoypad->Uninit();

		//メモリの削除
		delete m_pJoypad;

		//メモリのクリア
		m_pJoypad = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの終了処理呼び出し
		m_pRenderer->Uninit();

		//メモリの削除
		delete m_pRenderer;

		//メモリのクリア
		m_pRenderer = nullptr;
	}

	// シーン情報のリリース
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != nullptr)
	{
		//入力処理クラスの更新処理呼び出し
		m_pInput->Update();
	}

	if (m_pJoypad != nullptr)
	{
		//入力処理クラスの更新処理呼び出し
		m_pJoypad->Update();
	}

	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの更新処理呼び出し
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		//フェードクラスの更新処理呼び出し
		m_pFade->Update();
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの描画処理呼び出し
		m_pRenderer->Draw();
	}
}

//=============================================================================
//テクスチャの全ロード処理
//=============================================================================
void CManager::LoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// リソースのロード
		m_pResourceManager->LoadAll();
	}

	CResult::Load();
	CTutorial::Load();
	CTitle::Load();
	CEffectFactory::ReadFile();
	CStoneEffect::ReadFile();
	CMesh3d::ReadFile();

}

//=============================================================================
//テクスチャの全アンロード処理
//=============================================================================
void CManager::UnLoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// リソースのロード
		m_pResourceManager->UnLoadAll();
	}

	CTitle::UnLoad();
	CResult::UnLoad();
}

//=============================================================================
//ゲームモードの設定処理
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	// サウンドの情報
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	//現在モードの終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		if (m_pTitle != nullptr)
		{
			// タイトル処理
			m_pTitle->Uninit();
			m_pTitle = nullptr;
		}
		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != nullptr)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = nullptr;
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame != nullptr)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pGame = nullptr;
		}
		break;

		// リザルト
	case MODE_TYPE_RESULT:
		if (m_pResult != nullptr)
		{
			m_pResult = nullptr;
		}
		break;

	}

	// シーン情報のリリース
	CScene::ReleaseAll();

	//モードを設定
	m_mode = mode;

	//設定されたモードをクリエイト
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		if (m_pTitle == nullptr)
		{
			// タイトル生成
			m_pTitle = CTitle::Create();
		}
		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == nullptr)
		{
			// チュートリアル生成
			m_pTutorial = CTutorial::Create();
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame == nullptr)
		{
			// ゲーム生成
			m_pGame = CGame::Create();
		}

		break;

		// リザルト
	case MODE_TYPE_RESULT:
		if (m_pGame == nullptr)
		{
			// リザルト生成
			m_pResult = CResult::Create();
		}

	default:
		break;
	}
}

//=============================================================================
//ゲームモード情報の取得
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//レンダラー情報取得
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//キーボード情報取得
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

//=============================================================================
//フェード情報取得
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//ジョイパッド情報取得
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}