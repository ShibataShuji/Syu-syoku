#pragma once

#include "CComponent.h"
//#include "gameObject.h"

class Collision : public CComponent
{
private:
	int			m_Collision_type = 0;		// �J�v�Z���q���W�����Ȃ̂��{�b�N�X�Ȃ̂��Ƃ���ݒ肷��
	bool		m_Movable = false;


	// �J�v�Z���R���W����
	D3DXVECTOR2 m_Capusule_Size = D3DXVECTOR2(20.0f, 40.0f);		// �J�v�Z���̏㉺�̃X�t�B�A�̔��a�ƁA�^�񒆂̃{�b�N�X�̍���

	// �X�t�B�A�R���W����
	float		Sphere_Radius = 20.0f;			// �X�t�B�A�̔��a

	// �{�b�N�X�R���W����
	D3DXVECTOR2 m_Box_Size = D3DXVECTOR2(20.0f, 20.0f);				// �{�b�N�X�R���W�����̉����Əc��




public:

	// �e�N���X�̃R���X�g���N�^������Ă����B
	using CComponent::CComponent;


	void Init() override
	{

	}

	void Uninit() override
	{

	}

	void Update() override
	{
		// �v�Z�p�̕ϐ����Q�b�g
		D3DXVECTOR3 t_Position = m_ParentGameObject->GetTempPosition();
		D3DXVECTOR3 t_Velocity = m_ParentGameObject->GetTempVelocity();

























		// �Ƃ肠�����n�ʂ�0.0f�Ƃ��Ă���
		float groundHeight = 0.0f;

		// �n�ʂƂ̓����蔻��B�ڒn
		if (t_Position.y < groundHeight && t_Velocity.y < 0.0f)
		{
			t_Position.y = groundHeight;
			t_Velocity.y = 0.0f;
		}




		// m_TempVelocity�̍X�V
		m_ParentGameObject->SetTempVelocity(t_Velocity);

		// m_Position�̍X�V
		m_ParentGameObject->SetTempPosition(t_Position);
	}

	void Draw() override
	{

	}

	void SetMovable(bool movable)
	{
		m_Movable = movable;
	}


};

