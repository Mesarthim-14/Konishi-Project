#ifndef _EFFECT_FACTORY_H_
#define _EFFECT_FACTORY_H_
//=============================================================================
//
// �p�[�e�B�N�������N���X�w�b�_�[ [effect_factory.h]
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

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
class CEffectFactory
{
public:
	// �p�[�e�B�N���̍\����
	typedef struct
	{
		D3DXVECTOR3 size;		// �T�C�Y
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 Distance;	// ����
		int nLife;				// ���C�t
		int nNum;				// ��
		D3DXCOLOR color;		// �F
		bool bGravity;			// �d��
		bool bAlpha;			// �A���t�@�e�X�g
		int nAlphaNum;			// �A���t�@�e�X�g�̒l
		bool bAnimation;		// �A�j���[�V���������邩�ǂ���
		bool bBlend;			// ���Z����
		int nPriority;			// �`��D�揇��
	}EFFECT;

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		EFFECT_NUM_NONE = -1,			// �����l
		EFFECT_NUM_EXPLOSION,			// �_���[�W���󂯂��Ƃ�
		EFFECT_NUM_SWORD_SKILL,			// �X�L���̑ҋ@���Ԓ�
		EFFECT_NUM_SKILL_BLADE,			// �X�L�����̓��g
		EFFECT_NUM_SHARP_EFFECT,		// �s���G�t�F�N�g
		EFFECT_NUM_ELECTRICITY_EFFECT,	// �d���G�t�F�N�g
		EFFECT_NUM_SMOKE_EFFECT,		// ���̃G�t�F�N�g
		EFFECT_NUM_HIT_EFFECT,			// �q�b�g�G�t�F�N�g
		EFFECT_NUM_HIT_EXPLOSION,		// �q�b�g���̔����G�t�F�N�g
		EFFECT_NUM_HIT_IMPACT,			// �q�b�g���̏Ռ��G�t�F�N�g
		EFFECT_NUM_SAND_SMOKE,			// �y��
		EFFECT_NUM_CIRCLE,				// �T�[�N���G�t�F�N�g
		EFFECT_NUM_ATTACK_LIGHT,		// �U�����̃��C�g
		EFFECT_NUM_KOBOLD_SMOKE,		// �R�{���g�̉�
		EFFECT_NUM_JUMP_SMOKE,			// �W�����v�̉�
		EFFECT_NUM_ATTACK_CIRCLE,		// �U�����̃T�[�N��
		EFFECT_NUM_JUMP_IMPACT,			// �W�����v���̃T�[�N��
		EFFECT_NUM_ROAR_IMPACT,			// ���K���̏Ռ�
		EFFECT_NUM_HIT_IMPACT_000,		// �q�b�g���̏Ռ�
		EFFECT_NUM_ROAR_CIRCLE,			// ���K���̏������T�[�N��
		EFFECT_NUM_ARM_LIGHT,			// ��̌�
		EFFECT_NUM_GUARD_PARTICLE,		// �K�[�h���̃p�[�e�B�N��
		EFFECT_NUM_DUSH_IMPACT,			// �_�b�V���̏Ռ�
		EFFECT_NUM_DAMAGE_EFFECT,		// �_���[�W���̃G�t�F�N�g
		EFFECT_NUM_ROAR_FIRE,			// ���K���̉�
		EFFECT_NUM_ROAR_LIGHT,			// ���K���̌�
		EFFECT_NUM_MAX
	}EFFECT_TYPE;

	CEffectFactory();												// �R���X�g���N�^
	~CEffectFactory();												// �f�X�g���N�^

	static HRESULT ReadFile(void);									// �t�@�C���̓ǂݍ���
	static void CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type);	// �p�[�e�B�N���̃N���X
private:
	static EFFECT m_Effect[EFFECT_NUM_MAX];							// �p�[�e�B�N��
};
#endif
