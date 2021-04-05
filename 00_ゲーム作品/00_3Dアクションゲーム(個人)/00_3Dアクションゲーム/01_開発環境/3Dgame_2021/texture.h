#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
using TEXTURE_LIST = std::vector<std::string>;

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
	// �e�N�X�`���̔ԍ��̗񋓌^
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,		// �����l
		TEXTURE_NUM_FIRE,			// ��
		TEXTURE_NUM_GAGEFLAME,		// ���C�t�̘g
		TEXTURE_NUM_GAGEBAR,		// ���C�t�̃Q�[�W
		TEXTURE_NUM_TITLE_BG,		// �^�C�g���̔w�i
		TEXTURE_NUM_PARTICLE,		// �p�[�e�B�N��
		TEXTURE_NUM_SKILL_UI,		// �X�L����UI
		TEXTURE_NUM_SWORD_LOCUS,	// ���̊��
		TEXTURE_NUM_SLASH_EFFECT,	// �a���̃G�t�F�N�g
		TEXTURE_NUM_SKILL_START,	// �X�L���̑ҋ@��
		TEXTURE_NUM_QUEST_START,	// �N�G�X�g�̎n�܂�
		TEXTURE_NUM_OPERATION,		// �����UI
		TEXTURE_NUM_JUMP_IMPACT,	// �W�����v�̏Ռ�
		TEXTURE_NUM_ROAR_IMPACT,	// ���K�̏Ռ�
		TEXTURE_NUM_HIT_IMPACT_000,	// �U���q�b�g���̃G�t�F�N�g
		TEXTURE_NUM_FLOOR,			// ���̃e�N�X�`��
		TEXTURE_NUM_DUSH_IMPACT,	// �_�b�V���̃G�t�F�N�g
		TEXTURE_NUM_ENEMY_LOCUS,	// �G�̍U���̋O��
		TEXTURE_NUM_HIT_UI,			// HIT��UI
		TEXTURE_NUM_DAMAGE_UI,		// Damage��UI
		TEXTURE_NUM_MAX
	};

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_SHARP,				// �s���G�t�F�N�g
		SEPARATE_TEX_ELECTRICITY,		// �d���G�t�F�N�g
		SEPARATE_TEX_SMOKE,				// ���̃G�t�F�N�g
		SEPARATE_TEX_HIT_EFFECT,		// �q�b�g���̃G�t�F�N�g
		SEPARATE_TEX_HIT_IMPACT,		// �q�b�g���̏Ռ�
		SEPARATE_TEX_SAND_SMOKE,		// �y��
		SEPARATE_TEX_CIRCLE,			// �T�[�N���G�t�F�N�g	
		SEPARATE_TEX_ATTACK_LIGHT,		// �U�����̌�
		SEPARATE_TEX_KOBOLD_SMOKE,		// �R�{���g�̉�
		SEPARATE_TEX_JUMP_SMOKE,		// �W�����v���̉�
		SEPARATE_TEX_ATTACK_CIRCLE,		// �U���̉~
		SEPARATE_TEX_DAMAGE_NUMBER,		// �_���[�W�̃e�N�X�`��
		SEPARATE_TEX_ARM_LIGHT,			// ��̌�
		SEPARATE_TEX_DAMAGE_EFFECT,		// �_���[�W�̃G�t�F�N�g
		SEPARATE_TEX_ROAR_FIRE,			// ���̃G�t�F�N�g
		SEPARATE_TEX_ROAR_LIGHT,		// ���K�̃��C�g
		SEPARATE_TEX_COMBO_NUMBER,		// �R���{�̃i���o�[
		SEPARATE_TEX_COMBO_NUMBER_000,	// �R���{�̃_���[�W�i���o�[
		SEPARATE_TEX_MAX				// �ő�l
	};

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	};

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static CTexture *Create(void);												// �C���X�^���X����

	 HRESULT Load(void);														// �e�N�X�`�����[�h
	 void UnLoad(void);															// �e�N�X�`���A�����[�h
	 HRESULT SeparateTexLoad(void);												// �����e�N�X�`�����[�h
	 void SeparateTexUnLoad(void);												// �����e�N�X�`���A�����[�h

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// �e�N�X�`���̏��

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// �����e�N�X�`�����
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// �����e�N�X�`���@UV�̖����擾
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ���[�v���邩

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// �e�N�X�`���̃|�C���^
	std::vector<std::string> m_aTexFileName;									// �ʏ�e�N�X�`���̃t�@�C����

	// �����e�N�X�`���p�ϐ�
	std::vector<std::string> m_aSparateTexFileName;								// �����e�N�X�`���̃t�@�C����

	// �����e�N�X�`���̍\����
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_SHARP, D3DXVECTOR2(5, 5), false,
		nullptr, CTexture::SEPARATE_TEX_ELECTRICITY, D3DXVECTOR2(8, 5), false,
		nullptr, CTexture::SEPARATE_TEX_SMOKE, D3DXVECTOR2(10, 4), false,
		nullptr, CTexture::SEPARATE_TEX_HIT_EFFECT, D3DXVECTOR2(9, 2), false,
		nullptr, CTexture::SEPARATE_TEX_HIT_IMPACT, D3DXVECTOR2(6, 3), false,
		nullptr, CTexture::SEPARATE_TEX_SAND_SMOKE, D3DXVECTOR2(8, 10), false,
		nullptr, CTexture::SEPARATE_TEX_CIRCLE, D3DXVECTOR2(6, 4), false,
		nullptr, CTexture::SEPARATE_TEX_ATTACK_LIGHT, D3DXVECTOR2(8, 4), false,
		nullptr, CTexture::SEPARATE_TEX_KOBOLD_SMOKE, D3DXVECTOR2(8, 6), false,
		nullptr, CTexture::SEPARATE_TEX_JUMP_SMOKE, D3DXVECTOR2(10, 3), false,
		nullptr, CTexture::SEPARATE_TEX_ATTACK_CIRCLE, D3DXVECTOR2(2, 20), true,
		nullptr, CTexture::SEPARATE_TEX_DAMAGE_NUMBER, D3DXVECTOR2(10, 20), false,
		nullptr, CTexture::SEPARATE_TEX_ARM_LIGHT, D3DXVECTOR2(6, 2), false,
		nullptr, CTexture::SEPARATE_TEX_DAMAGE_EFFECT, D3DXVECTOR2(5, 4), false,
		nullptr, CTexture::SEPARATE_TEX_ROAR_FIRE, D3DXVECTOR2(12, 4), false,
		nullptr, CTexture::SEPARATE_TEX_ROAR_LIGHT, D3DXVECTOR2(6, 4), false,
		nullptr, CTexture::SEPARATE_TEX_COMBO_NUMBER, D3DXVECTOR2(10, 20), false,
		nullptr, CTexture::SEPARATE_TEX_COMBO_NUMBER_000, D3DXVECTOR2(10, 20), false,
	};
};
#endif
