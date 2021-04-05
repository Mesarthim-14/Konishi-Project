//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
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
// static������
//=======================================================================================
CCamera *CGame::m_pCamera = nullptr;
CLight *CGame::m_pLight = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CBg *CGame::m_pBg = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CPause *CGame::m_pPause = nullptr;
CSea *CGame::m_pSea = nullptr;

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init(ZeroVector3, ZeroVector3);

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �J�����N���X�̃N���G�C�g
	m_pCamera = CCamera::Create();

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(ZeroVector3, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));	
	}

	// ���b�V���t�B�[���h
	m_pMeshField = CMeshField::Create();

	// �w�i
	if (m_pBg == nullptr)
	{
		m_pBg = CBg::Create(BG_POS, BG_SIZE);
	}

	// �I�̐���
	//CCrab::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), ZeroVector3);

	// �R�{���g�̐���
	CKobold::Create(D3DXVECTOR3(0.0f, 0.0f, -6000.0f), ZeroVector3);

	//BGM
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�t�H���g�̐���
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != nullptr)
	{
		//�J�����N���X�̏I�������Ăяo��
		m_pCamera->Uninit();

		//�������̔j��
		delete m_pCamera;

		//�������̃N���A
		m_pCamera = nullptr;
	}

	// �w�i
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// ���C�g�̏I������
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �v���C���[�̏I������
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// �n�ʂ̏I������
	if (m_pMeshField != nullptr)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}

	// !nullcheck
	if (CManager::GetResourceManager() != nullptr)
	{
		//�T�E���h���擾
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

		// !nullcheck
		if (pSound != nullptr)
		{
			//�Q�[��BGM��~
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	if (m_pCamera != nullptr)
	{
		//�J�����N���X�̍X�V����
		m_pCamera->Update();
	}

	// �Q�[���̐ݒ�
	SetGame();
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
	// �w�i
	if (m_pBg != nullptr)
	{
		m_pBg->Draw();
	}

	// ���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->ShowLightInfo();
	}
}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{
	// �Q�[���̃^�C���J�E���^�[
	m_nTimeCounter++;

	// �N�G�X�g���S����
	if (m_nTimeCounter == 60)
	{
		// �N�G�X�g���S����
		CQuestLogo::Create();
	}
}

//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ���C�g�̏��
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// �v���C���[�̏��
//=======================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=======================================================================================
// �R���e�j���[�̏��
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}