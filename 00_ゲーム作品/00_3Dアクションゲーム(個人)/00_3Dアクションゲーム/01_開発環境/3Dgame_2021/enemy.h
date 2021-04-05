#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�l�~�[�N���X�w�b�_�[ [enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PARTS			(10)		// �p�[�c�̐�
#define MOTION_KEYSET_MAX	(32)		// �L�[�Z�b�g�ő吔
#define ENEMY_SIZE_X		(1)			// �T�C�Y
#define ENEMY_SIZE_Y		(1)			// �T�C�Y
#define ENEMY_SIZE_Z		(1)			// �T�C�Y
#define ENEMY_COLLISION_X	(200)		// �����蔻��
#define ENEMY_COLLISION_Y	(175)		// �����蔻��
#define ENEMY_COLLISION_Z	(200)		// �����蔻��
#define ENEMY_RADIUS		(150)		// ���a

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy : public CCharacter
{
public:
	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum ENEMY_MOTION_STATE
	{
		ENEMY_MOTION_NONE = -1,
		ENEMY_MOTION_IDOL,			// �A�C�h�����[�V����
		ENEMY_MOTION_WALK,			// ���s���[�V����
		ENEMY_MOTION_ATTACK,		// �U�����[�V����
		ENEMY_MOTION_DAMAGE,		// ����
		ENEMY_MOTION_LOSE,			// �������[�V����
		ENEMY_MOTION_MAX,			// ���[�V�����ő吔
	};

	CEnemy(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	~CEnemy();													// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void UpdateState(void);										// �v���C���[�̏��
	void Perception(void);										// �v���C���[�����m
	void Death(void);											// ���񂾂Ƃ��̏���
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	virtual void Attack(void);									// �U���̏���
	virtual void UpdateMotionState(void);						// ���[�V�������

	// Set�֐�
	void SetActive(bool bActive);								// �v���C���[���m�̐ݒ�
	void SetAttackInter(int nAttackInter);						// �U���̊Ԋu�ݒ�
	void SetArmorFlame(int nArmorFlame);						// ���G���Ԃ̃t���[��
	void SetPerception(bool bPerception);						// �Ǐ]�̐ݒ�
	void SetAttackCnt(int nAttackCnt);							// �U���J�E���g�̐ݒ�

	// Get�֐�
	int GetAttackInter(void) { return m_nAttackInter; }			// �U���J�E���g�̏��
	int ArmotFlame(void) { return m_nArmorFlame; }				// �A�[�}�[�̃t���[��
	bool GetPerception(void) { return m_bPerception; }			// �����t���O���

private:
	int m_nMotionState;					// ���[�V�����̏��
	int m_nAttackInter;					// �U���̊Ԋu
	int m_nAttackFlameCnt;				// �U���̃t���[���J�E���g
	int m_nArmorFlame;					// ���G���Ԃ̐ݒ�
	bool m_bActive;						// �G���v���C���[�����m���邩
	bool m_bRange;						// �U�����͂��͈͂̃t���O
	bool m_bAttack;						// �U���̍s���t���O
	bool m_bPerception;					// �Ǐ]���邩�ǂ���
};
#endif