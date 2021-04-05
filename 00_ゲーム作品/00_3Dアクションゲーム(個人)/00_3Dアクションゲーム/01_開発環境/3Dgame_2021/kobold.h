#ifndef _KOBOLD_H_
#define _KOBOLD_H_
//=============================================================================
//
// �I�G�l�~�[�N���X�w�b�_�[ [kobold.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_KOBOLD_PARTS			(19)		// ���f���̃p�[�c�̍ő吔

//=============================================================================
// �R�{���g�N���X
//=============================================================================
class CKobold : public CEnemy
{
public:
	CKobold(PRIORITY Priority = PRIORITY_CHARACTER);	// �R���X�g���N�^
	~CKobold();											// �f�X�g���N�^

	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	typedef enum
	{
		KOBOLD_MOTION_NONE = -1,
		KOBOLD_MOTION_IDOL,			// �A�C�h�����[�V����
		KOBOLD_MOTION_WALK,			// ���s���[�V����
		KOBOLD_MOTION_JUMP_ATTACK,	// �W�����v�U�����[�V����
		KOBOLD_MOTION_SMASH,		// �@�������[�V����
		KOBOLD_MOTION_WIPE,			// �������[�V����
		KOBOLD_MOTION_ROAR,			// ���K���[�V����
		KOBOLD_MOTION_DAMAGE,		// �_���[�W���[�V����
		KOBOLD_MOTION_MAX,			// ���[�V�����ő吔
	}KOBOLD_MOTION;

	//=============================================================================
	//�@���[�V�����p�[�c�̗񋓌^
	//=============================================================================
	typedef enum
	{
		KOBOLD_PARTS_NUM_NONE = -1,
		KOBOLD_PARTS_NUM_BODY,						// [0]��
		KOBOLD_PARTS_NUM_HEAD,						// [1]��
		KOBOLD_PARTS_NUM_RIGHT_SHOLDER,				// [2]�E��
		KOBOLD_PARTS_NUM_RIGHT_UPPERARM,			// [3]�E��r
		KOBOLD_PARTS_NUM_RIGHT_ARM,					// [4]�E�r
		KOBOLD_PARTS_NUM_LEFT_SHOLDER,				// [5]����
		KOBOLD_PARTS_NUM_LEFT_UPPERARM,				// [6]����r
		KOBOLD_PARTS_NUM_LEFT_ARM,					// [7]���r
		KOBOLD_PARTS_NUM_RIGHT_LEG,					// [8]�E��
		KOBOLD_PARTS_NUM_RIGHT_FOOT,				// [9]�E��
		KOBOLD_PARTS_NUM_LEFT_LEG,					// [10]����
		KOBOLD_PARTS_NUM_LEFT_FOOT,					// [11]����
		KOBOLD_PARTS_NUM_RIGHT_ARM_COLLISION,		// [12]�E�蓖���蔻��
		KOBOLD_PARTS_NUM_LEFT_ARM_COLLISION,		// [13]���蓖���蔻��
		KOBOLD_PARTS_NUM_RIGHT_LEG_COLLISION,		// [14]�E�������蔻��
		KOBOLD_PARTS_NUM_LEFT_LEG_COLLISION,		// [15]���������蔻��
		KOBOLD_PARTS_NUM_RIGHT_ARM_INSIDE,			// [16]�e�w
		KOBOLD_PARTS_NUM_RIGHT_ARM_OUTSIDE,			// [17]���w
		KOBOLD_PARTS_NUM_BODY_COLLISION,			// [18]�{�̂̓����蔻��
		KOBOLD_PARTS_NUM_MAX,						// �p�[�c�ő吔
	}KOBOLD_PARTS_NUM;

	static CKobold *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void Locus(void);											// �O��
	void Attack(void);											// �U���̏���
	void UpdateMotionState(void);								// ���[�V�������

private:
	int m_nSmokeCounter;			// ���̃J�E���^�[
	int m_nRoarAttackCounter = 0;	// ���эU���̃J�E���^�[
};
#endif