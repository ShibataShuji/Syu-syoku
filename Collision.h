#pragma once

#include "CComponent.h"
//#include "gameObject.h"

class Collision : public CComponent
{
private:
	int			m_Collision_type = 0;		// カプセル子リジョンなのかボックスなのかとかを設定する
	bool		m_Movable = false;


	// カプセルコリジョン
	D3DXVECTOR2 m_Capusule_Size = D3DXVECTOR2(20.0f, 40.0f);		// カプセルの上下のスフィアの半径と、真ん中のボックスの高さ

	// スフィアコリジョン
	float		Sphere_Radius = 20.0f;			// スフィアの半径

	// ボックスコリジョン
	D3DXVECTOR2 m_Box_Size = D3DXVECTOR2(20.0f, 20.0f);				// ボックスコリジョンの横幅と縦幅




public:

	// 親クラスのコンストラクタをやってくれる。
	using CComponent::CComponent;


	void Init() override
	{

	}

	void Uninit() override
	{

	}

	void Update() override
	{
		// 計算用の変数をゲット
		D3DXVECTOR3 t_Position = m_ParentGameObject->GetTempPosition();
		D3DXVECTOR3 t_Velocity = m_ParentGameObject->GetTempVelocity();

























		// とりあえず地面は0.0fとしておく
		float groundHeight = 0.0f;

		// 地面との当たり判定。接地
		if (t_Position.y < groundHeight && t_Velocity.y < 0.0f)
		{
			t_Position.y = groundHeight;
			t_Velocity.y = 0.0f;
		}




		// m_TempVelocityの更新
		m_ParentGameObject->SetTempVelocity(t_Velocity);

		// m_Positionの更新
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

