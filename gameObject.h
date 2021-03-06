#pragma once

#define OBJNUM (4)

#include "CComponent.h"
#include <list>

class GameObject
{
protected:	// アクセス指定子

	bool		m_Destroy = false;


	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

	D3DXVECTOR3	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 現在の速度ベクトル


	// 計算用
	D3DXVECTOR3 m_Old_Position;
	D3DXVECTOR3 m_temp_Position;
	D3DXVECTOR3	m_temp_Velocity;




	std::list<CComponent*> m_ComponentList;
	std::list<GameObject*> m_Child;

	/*GameObject*				m_Parent;*/

public:

	GameObject() {}

	virtual ~GameObject()
	{
		for (auto c : m_ComponentList)
			delete c;
		m_ComponentList.clear();

		for (auto c : m_Child)
			delete c;
		m_Child.clear();
	}


	virtual void Uninit()
	{
		for (auto c : m_ComponentList)
			c->Uninit();

		for (auto c : m_Child)
			c->Uninit();
	}

	// virtual(純粋仮想関数)なので、これを継承したplayerクラスなどでUpdate関数を作るとそっちが呼ばれて
	// これは呼ばれないが、playerのupdateの方でこれを呼ぶ(親クラスのupdate)と呼べる。
	virtual void Update()
	{
		// 座標の保存
		m_Old_Position = m_Position;
		m_temp_Position = m_Position;
		m_temp_Velocity = m_Velocity;


		// playerとか子クラスのUpdateの後に来てほしいので、playerとか子クラスのUpdateの最後に書く。
		/*for (auto c : m_ComponentList)
			c->Update();*/
		/*------->>>>>> ComponentUpdate()関数にまとめた*/


		// 子供の必要性がわからない；；
		/*for (auto c : m_Child)
			c->Update();*/
	}

	// コンポーネントのアップデート
	virtual void ComponentUpdate()
	{
		for (auto c : m_ComponentList)
			c->Update();
	}

	// Tempの更新
	virtual void TemporarySetUpdate()
	{
		m_Position = m_temp_Position;
		m_Velocity = m_temp_Velocity;
	}


	virtual void Init() = 0;	// 純粋仮想関数
	/*virtual void Uninit() = 0;*/
	/*virtual void Update() = 0;*/
	virtual void Draw() = 0;

	D3DXVECTOR3 GetPosition() { return m_Position; }
	void SetPosition(D3DXVECTOR3 Position){	m_Position = Position;	}

	D3DXVECTOR3 GetOldPosition() { return m_Old_Position; }
	void SetOldPosition(D3DXVECTOR3 Position) { m_Old_Position = Position; }

	D3DXVECTOR3 GetTempPosition() { return m_temp_Position; }
	void SetTempPosition(D3DXVECTOR3 Position) { m_temp_Position = Position; }

	D3DXVECTOR3 GetVelocity() { return m_Velocity; }
	void SetVelocity(D3DXVECTOR3 Velocity) { m_Velocity = Velocity; }

	D3DXVECTOR3 GetTempVelocity() { return m_temp_Velocity; }
	void SetTempVelocity(D3DXVECTOR3 Velocity) { m_temp_Velocity = Velocity; }


	D3DXVECTOR3 GetRotation() { return m_Rotation; }

	void SetDestroy() { m_Destroy = true; }

	D3DXVECTOR3 GetScale() { return m_Scale; }
	void SetScale(D3DXVECTOR3 setscale) {
		m_Scale = setscale
			;
	}


	D3DXVECTOR3 GetForward()	// 前方向ベクトル
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;

	}

	D3DXVECTOR3 GetRight()	// 右方向ベクトル
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	D3DXVECTOR3 GetUp()	// 上方向ベクトル
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
	}

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T* AddComponent()
	{
		// このオブジェクトが追加するコンポーネントの親になるので、コンストラクタでthisを設定する
		T* ccomponent  = new T(this);
		ccomponent->Init();
		m_ComponentList.push_back(ccomponent);

		return ccomponent;
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto c : m_ComponentList)
		{
			if (typeid(*c) == typeid(T))
			{
				return (T*)c;
			}
		}

		return nullptr;

	}

};

// private そのクラスからしかアクセスできない。そのクラスの関数とか。
// prootected private + 継承先のクラスからはアクセスできる。ゲームエンジンだとこれが多いかな〜
// public アクセスできる