#pragma once

#include <d3dx9.h>

class GameObject;

// CComponent��Update�Ƃ���gameObject��Update�Ƃ��ŌĂ�ł���

class CComponent
{
protected:
	GameObject* m_ParentGameObject;		// �e�ɂȂ��Ă���Q�[���I�u�W�F�N�g

public:

	// �R���X�g���N�^�B����̈������Ȃ��R���X�g���N�^�́A��΂ɐe�̃I�u�W�F�N�g��ݒ肵�Ȃ��ƃ_���ɂ��邽�߂ɏ����Ă���B
	CComponent() = delete;
	CComponent(GameObject* gameObject)
	{
		m_ParentGameObject = gameObject;
	}
	// �f�X�g���N�^
	virtual ~CComponent(){}

	virtual void Init() {}			// ���z�֐�virtual������Ɠ���CComponent.Init()���Ă�ł�override�������̊֐����Ă΂��
	virtual void Uninit() {}		// ������virtual�����āAoverride�����֐��̕��Őe�̊֐����ĂԂ悤�ɂ���ΐe���������Ă΂��OK
	virtual void Update() {}
	virtual void Draw() {}

};

