//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
//�ÓI�����o�ϐ��錾
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
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[�N���X�̃C���X�^���X����
	m_pRenderer = new CRenderer;

	//���������m�ۂł�����
	if (m_pRenderer != nullptr)
	{
		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pInput = new CInputKeyboard;

	//���������m�ۂł�����
	if (m_pInput != nullptr)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pJoypad = new CInputJoypad;

	//���������m�ۂł�����
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
		// ���\�[�X�}�l�[�W���̃C���X�^���X����
		m_pResourceManager = CResourceManager::GetInstance();
	}

	//�t�F�[�h�N���X�̃N���G�C�g
	m_pFade = CFade::Create();

	//�S�e�N�X�`���̓ǂݍ���
	LoadAll();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�e�N�X�`���̔j��
	UnLoadAll();

	//���݃��[�h�̏I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		if (m_pTitle != nullptr)
		{
			// �I������
			m_pTitle->Uninit();
			m_pTitle = nullptr;
		}

		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != nullptr)
		{
			// �I������
			m_pTutorial->Uninit();
			m_pTutorial = nullptr;
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame != nullptr)
		{
			// �I������
			m_pGame->Uninit();
			m_pGame = nullptr;
		}
		break;

		// ���U���g
	case MODE_TYPE_RESULT:
		if (m_pResult != nullptr)
		{
			// �I������
			m_pResult->Uninit();
			m_pResult = nullptr;
		}
		break;
	}

	// nullchack
	if (m_pFade != nullptr)
	{
		//�t�F�[�h�N���X�̏I�������Ăяo��
		m_pFade->Uninit();

		//�������̔j��
		delete m_pFade;

		//�������̃N���A
		m_pFade = nullptr;
	}

	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// ���\�[�X�̃��[�h
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}

	if (m_pInput != nullptr)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pInput->Uninit();

		//�������̍폜
		delete m_pInput;

		//�������̃N���A
		m_pInput = nullptr;
	}

	if (m_pJoypad != nullptr)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pJoypad->Uninit();

		//�������̍폜
		delete m_pJoypad;

		//�������̃N���A
		m_pJoypad = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̏I�������Ăяo��
		m_pRenderer->Uninit();

		//�������̍폜
		delete m_pRenderer;

		//�������̃N���A
		m_pRenderer = nullptr;
	}

	// �V�[�����̃����[�X
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != nullptr)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pInput->Update();
	}

	if (m_pJoypad != nullptr)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pJoypad->Update();
	}

	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̍X�V�����Ăяo��
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		//�t�F�[�h�N���X�̍X�V�����Ăяo��
		m_pFade->Update();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Draw();
	}
}

//=============================================================================
//�e�N�X�`���̑S���[�h����
//=============================================================================
void CManager::LoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// ���\�[�X�̃��[�h
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
//�e�N�X�`���̑S�A�����[�h����
//=============================================================================
void CManager::UnLoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// ���\�[�X�̃��[�h
		m_pResourceManager->UnLoadAll();
	}

	CTitle::UnLoad();
	CResult::UnLoad();
}

//=============================================================================
//�Q�[�����[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	// �T�E���h�̏��
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	//���݃��[�h�̏I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		if (m_pTitle != nullptr)
		{
			// �^�C�g������
			m_pTitle->Uninit();
			m_pTitle = nullptr;
		}
		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != nullptr)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = nullptr;
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame != nullptr)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pGame = nullptr;
		}
		break;

		// ���U���g
	case MODE_TYPE_RESULT:
		if (m_pResult != nullptr)
		{
			m_pResult = nullptr;
		}
		break;

	}

	// �V�[�����̃����[�X
	CScene::ReleaseAll();

	//���[�h��ݒ�
	m_mode = mode;

	//�ݒ肳�ꂽ���[�h���N���G�C�g
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		if (m_pTitle == nullptr)
		{
			// �^�C�g������
			m_pTitle = CTitle::Create();
		}
		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == nullptr)
		{
			// �`���[�g���A������
			m_pTutorial = CTutorial::Create();
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame == nullptr)
		{
			// �Q�[������
			m_pGame = CGame::Create();
		}

		break;

		// ���U���g
	case MODE_TYPE_RESULT:
		if (m_pGame == nullptr)
		{
			// ���U���g����
			m_pResult = CResult::Create();
		}

	default:
		break;
	}
}

//=============================================================================
//�Q�[�����[�h���̎擾
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//�����_���[���擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//�L�[�{�[�h���擾
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

//=============================================================================
//�t�F�[�h���擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//�W���C�p�b�h���擾
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}