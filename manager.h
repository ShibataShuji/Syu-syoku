#pragma once

#include "scene.h"

class Manager
{
private:
	// static �̃����o�ϐ���cpp���ł�����x�錾���Ă����Ȃ��Ƃ����Ȃ�
	// ��class �����Ă�̂͑O���錾�B����Ȃ�w�b�_�[��include���Ȃ��Ă悭�Ȃ�I�I�I
	// static����ƃO���[�o���ϐ��̂悤�Ɏg����
	// class �̓|�C���^�ϐ��ɂ����g���Ȃ��B
	// include���Əz�Ăяo�����ꂿ����ăG���[�o�邩��A�|�C���^�ϐ��Ȃ� class�ŉ������Ă����āA
	// ����ł����߂Ȃ�C��t���Ȃ���C���N���[�h���g��

	static class Scene* m_Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static class Scene* GetScene() { return m_Scene; }

	template <typename T> 
	static void SetScene() 
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = new T();
		m_Scene->Init();
	}

	// override���p����ł���ƁA�X�y���~�X��h�����Ƃ��ł���B���s���ʂ͑S���ς��Ȃ��̂ł��Ȃ��Ă��������ǂ��ĂˁB

};