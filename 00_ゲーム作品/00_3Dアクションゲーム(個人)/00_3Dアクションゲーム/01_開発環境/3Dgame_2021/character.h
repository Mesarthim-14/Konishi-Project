#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[����  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// �L�����N�^�[�̃p�[�c��
#define MAX_KEYFRAME		(10)	// �L�[�t���[���̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CLifeBar;
class CLifeFrame;
class CMotion;

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter : public CScene
{
public:
	enum STATE
	{
		STATE_NONE = 0,		// �����l
		STATE_APPEAR,		// �o��
		STATE_NO_ACTIVE,	// ��퓬���
		STATE_NORMAL,		// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
		STATE_MAX,			// �ő�l
	};

	enum CHARACTER_TYPE
	{
		CHARACTER_TYPE_NONE = 0,	// �����l
		CHARACTER_TYPE_PLAYER,		// �v���C���[
		CHARACTER_TYPE_ENEMY,		// �G�l�~�[
		CHARACTER_TYPE_MAX,			// �ő吔
	};

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	virtual ~CCharacter();											// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	virtual void Uninit();											// �I������
	virtual void Update();											// �X�V����
	virtual void Draw();											// �`�揈��

	void AddDamage(int nDamage);									// �_���[�W�̉��Z
	void HeelLife(int nHeelNum);									// �񕜂̏���
	void Gravity(void);												// �n�ʂ̐���
	void BodyCollision(void);										// �����蔻��
	bool AttackCollision(void);										// �U�����̓����蔻��
	void LifeBarCreate(D3DXVECTOR3 posFrame, D3DXVECTOR3 sizeFrame,	// �̗̓o�[�̐ݒu
		D3DXVECTOR3 posBar, D3DXVECTOR3 sizeBar,
		D3DXCOLOR color, int nLife);								// �̗̓o�[�̐����֐�

	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// ���f���̐���
	void ModelAnimeUpdate(void);									// ���f���A�j���[�V����
	void Landing(float fPosY);										// ���n����

	// �������z�֐�
	virtual void UpdateState(void) = 0;								// �L�����N�^�[���
	virtual void UpdateMotionState(void) = 0;						// ���[�V�����̏��
	virtual void Attack(void) = 0;									// �U���̏���
	virtual void Death(void) = 0;									// ���񂾂Ƃ��̏���

	// Set�֐�
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 posOld);								// ���W�̐ݒ�
	void SetState(STATE state);										// �v���C���[���̐ݒ�
	void SetMove(D3DXVECTOR3 move);									// �ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 rot);									// �p�x�̐ݒ�
	void SetLife(int nLife);										// ���C�t�̐ݒ�
	void SetCountMotion(int CountMotion);							// ���[�V�����̃J�E���g�ݒ�
	void SetMotionState(int nMotionState);							// ���[�V�����̏�Ԑݒ�
	void SetMotion(int nMotion);									// ���[�V�����̐ݒ� 
	void SetKey(int nKey);											// �L�[�ݒ�
	void SetJump(bool bJump);										// �W�����v�̃t���O
	void SetLanding(bool bLanding);									// ���n�̐ݒ�
	void SetRadius(float fRadius);									// ���a�̐ݒ�
	void SetCType(CHARACTER_TYPE Ctype);							// �L�����N�^�[�̃^�C�v
	void SetSpeed(float fSpeed);									// ���x�̐ݒ�
	void SetWeaponTipNum(int nWeaponTipNum);						// ����̃p�[�c�ԍ�
	void SetWeaponRootNum(int nWeaponRootNum);						// ���̍��{�̃p�[�c�ԍ�
	void SetWeaponRadius(float fWeaponRadius);						// ����̔��a
	void SetArmor(bool bArmor);										// ���G�t���O�ݒ�
	void SetStateCounter(int nStateCounter);						// ��ԃJ�E���^�[�̐ݒ�
	void SetAttackPower(int m_nAttackPowar);						// �U���͂̐ݒ�
	void SetHitNumber(int nHitNumber);								// ���ꔻ��̐ݒ�

	// Get�֐�
	D3DXVECTOR3 GetPos(void)				{ return m_pos; }						// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void)				{ return m_posOld; }					// �Â����W���
	D3DXVECTOR3 GetRot(void)				{ return m_rot; }						// �p�x���
	D3DXVECTOR3 GetMove(void)				{ return m_move; }						// �ړ��ʂ̏��
	STATE GetState(void)					{ return m_state; }						// �v���C���[�̏�ԏ��
	CHARACTER_TYPE GetCType(void)			{ return m_Ctype; }						// �L�����N�^�[�̃^�C�v
	int GetLife(void)						{ return m_nLife; }						// ���C�t�̏��
	int GetWeaponPartsNum(void)				{ return m_nWeaponTipNum; }				// ����̃p�[�c�ԍ��̏��
	int GetWeaponRootNum(void)				{ return m_nWeaponTipNum; }				// ����̃p�[�c�ԍ��̏��
	int GetStateCounter(void)				{ return m_nStateCounter; }				// ��ԃJ�E���^�[�̏��
	int GetAttackPower(void)				{ return m_nAttackPowar; }				// �U���̏��
	int GetHitNumber(void)					{return m_nHitNumber; }					// ���ꔻ��̏��
	float GetSpeed(void)					{ return m_fSpeed; }					// �X�s�[�h�̏��
	float GetRadius(void)					{ return m_fRadius; }					// ���a�̏��
	CModelAnime *GetModelAnime(int nCount)	{ return m_apModelAnime[nCount]; }		// ���[�V�����̃J�E���g���
	bool GetJump(void)						{ return m_bJump; }						// �W�����v
	bool GetLanding(void)					{ return m_bLanding; }					// ���n�̃t���O
	bool GetArmor(void)						{ return m_bArmor;}						// ���G����
	CLifeBar *GetLifeBar(void)				{ return m_pLifeBar; }					// ���C�t�o�[�̏��
	CMotion *GetMotion(void)				{ return m_pMotion; }					// ���[�V�����̃|�C���^���

private:
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// ���f���p�[�c�p�̃|�C���^
	CMotion *m_pMotion;								// ���[�V�����N���X�̃|�C���^
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_posOld;			// �Â����W
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rot;				// ���݂̉�]
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	STATE m_state;					// �L�����N�^�[�̏��
	CHARACTER_TYPE m_Ctype;			// �L�����N�^�[�̃^�C�v
	int m_nLife;					// �̗�
	int m_nMaxLife;					// ���C�t�̍ő��
	int m_nAttack;					// �U����
	int m_nCharaNum;				// �L�����N�^�[�̃i���o�[
	int m_nWeaponTipNum;			// ����̃p�[�c�ԍ�
	int m_nWeaponRootNum;			// ���̍��{�̃p�[�c
	int m_nStateCounter;			// ��Ԃ̃J�E���^�[
	int m_nAttackPowar;				// �U����
	int m_nHitNumber;				// ���ꔻ��̃p�[�c�ԍ�
	int m_nParts;					// �p�[�c��
	float m_fSpeed;					// �ړ���
	float m_fAngle;					// �p�x
	float m_fRadius;				// ���a
	float m_fWeaponRadius;			// ����̔��a
	bool m_bJump;					// �W�����v���Ă���t���O
	bool m_bLanding;				// ���n�̃t���O
	bool m_bArmor;					// ���G�t���O
	CLifeBar *m_pLifeBar;			// ���C�t�o�[�̃|�C���^
	CLifeFrame *m_pLifeFrame;		// ���C�t�o�[�̃t���[��
	// �ÓI�����o�ϐ�
	static int m_nAllNum;			// �L�����N�^�[�̑���
};
#endif