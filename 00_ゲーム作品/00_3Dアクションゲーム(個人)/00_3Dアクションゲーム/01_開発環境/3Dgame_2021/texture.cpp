//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));

	// �ʏ�e�N�X�`���̖��O�̐ݒ�
	m_aTexFileName =
	{
		{ "data/Texture/fire111.jpg" },
		{"data/Texture/LifeBar.png"},					// ���C�t�̘g
		{"data/Texture/LifeBar000.png" },				// ���C�t�o�[(��)
		{"data/Texture/bg001.png" },					// �^�C�g����ʂ̔w�i
		{"data/Texture/effect003.png" },				// �p�[�e�B�N��
		{"data/Texture/skill_ui.png" },					// �X�L����UI
		{"data/Texture/sword_locus000.png" },			// ���̋O��
		{"data/Texture/magic24.jpg" },					// �a���̃G�t�F�N�g
		{"data/Texture/Sword_Skill_Start001.png" },		// �X�L���̑ҋ@��
		{"data/Texture/QuestStart_Logo.png" },			// �N�G�X�g�̊J�n
		{"data/Texture/button_ui.png" },				// ����{�^����UI
		{"data/Texture/inpact.tga" },					// �W�����v�̏Ռ�
		{"data/Texture/inpact_red.tga" },				// ���K�̏Ռ�
		{"data/Texture/Hit_Impact002.tga" },			// �U�����̏Ռ�
		{"data/Texture/floor.jpg" },					// ���̃e�N�X�`��
		{"data/Texture/Hit_Impact003.tga" },			// �_�b�V���̏Ռ�
		{"data/Texture/sword_locus002.png" },			// �{�X�̋O��
		{"data/Texture/hit_ui.png" },					// HIT��UI
		{"data/Texture/damage_ui.png" },				// �_���[�W��UI
	};

	// �����e�N�X�`���̖��O�̐ݒ�
	m_aSparateTexFileName =
	{
		{"data/Texture/sharp_effect.png"},				// �s���G�t�F�N�g
		{ "data/Texture/Electricity_Effect000.png" },	// �d���G�t�F�N�g
		{ "data/Texture/smoke000.png" },				// ���G�t�F�N�g
		{ "data/Texture/hit_effect000.png" },			// �q�b�g�G�t�F�N�g
		{ "data/Texture/slash_impact.png" },			// �q�b�g���̏Ռ�
		{ "data/Texture/sand_smoke.png" },				// �q�b�g���̏Ռ�
		{ "data/Texture/circle.png" },					// �T�[�N���G�t�F�N�g
		{ "data/Texture/attack_light_001.png" },		// �U�����̌�
		{ "data/Texture/smoke_101.png" },				// �R�{���g�̉�
		{ "data/Texture/smoke_effect000.png" },			// �W�����v�̉�
		{ "data/Texture/attack_circle000.png" },		// �U���̉~
		{ "data/Texture/damage_number.png" },			// �_���[�W�̐����e�N�X�`��
		{ "data/Texture/arm_light.png" },				// ��̌�
		{ "data/Texture/damage_impact100.tga" },		// �_���[�W���̃G�t�F�N�g
		{ "data/Texture/roar_attack000.png" },			// ���K���̃t�@�C�A
		{ "data/Texture/roar_light000.png" },			// ���K���̌�
		{ "data/Texture/combo_damage.png" },			// �R���{�̃i���o�[
		{ "data/Texture/combo_damage000.png" },			// �R���{�̃_���[�W�i���o�[
	};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
	// �ʏ�e�N�X�`���N���A
	m_aTexFileName.clear();

	// �����e�N�X�`���N���A
	m_aSparateTexFileName.clear();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create(void)
{
	// �������m��
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < m_aTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
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
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �����e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < m_aSparateTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aSparateTexFileName[nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}

	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// �e�N�X�`���̉��
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
// �e�N�X�`�����
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
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// �e�N�X�`�����
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}