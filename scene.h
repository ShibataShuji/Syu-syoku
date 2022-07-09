#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "gameObject.h"
#include "CComponent.h"

// Scene�N���X���p�����ă^�C�g���A�Q�[���A���U���g�A������Ă����B

class Scene
{
	// ��protected�ɂ��Ă���Ă��Ƃ͌p�����Ďg�����Ă��Ɓ`
protected:
	std::list<GameObject*> m_GameObject[3];	// STL�̃��X�g�\��


public:
	Scene(){}				// �R���X�g���N�^
	virtual ~Scene(){}		// �f�X�g���N�^ �͂΁[�����邶��Ȃ��ƃ_��
							// ��������Ȃ��ƌp����ŌĂ΂�Ȃ��G�G

	virtual void Init() = 0;	// �������z�֐�

	// ���ʂ̕ϐ����ƕϐ��������炦�Ȃ����ǁAT���ƌ^�������p����
	template <typename T>	//�e���v���[�g�֐�
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;		// ���������C���X�^���X�̃|�C���^�������Ă���
	}


	// �ЂƂ��������݂���Ȃ����
	template <typename T>	//�e���v���[�g�֐�
	T* GetGameObject(int Layer)
	{
		
			for (GameObject* object : m_GameObject[Layer])
			{
				// typeid���g���ɂ� #includee <typeinfo> ���K�v
				if (typeid(*object) == typeid(T))		// �^�𒲂ׂ�(RTTI���I�^���)
				{
					return (T*)object;
				}
			}
		
		return NULL;
	}


	// ������������
	template <typename T>	//�e���v���[�g�֐�
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects; // STL�̔z��
		
			for (GameObject* object : m_GameObject[Layer])
			{
				if (typeid(*object) == typeid(T))
				{
					objects.push_back((T*)object);
				}
			}
		
		return objects;
	}




	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();	// ���X�g�̃N���A
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])	// �͈�for���[�v
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });		// �����_��
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
};

