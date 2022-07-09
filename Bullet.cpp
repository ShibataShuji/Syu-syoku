#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Bullet.h"
#include "scene.h"
#include "manager.h"
#include "gameObject.h"
#include "Explosion.h"
#include "Enemy.h"

Model* Bullet::m_Model;	// �X�^�e�B�b�N�����o�ϐ�
						// �o���b�g�N���X��static class �ō���Ă�̂ŁB
						// static�̐錾��cpp���ł������錾���Ȃ��Ƃ����Ȃ�
						// ����Y���ƃ����J�G���[�o���Ⴄ
						// static�n�ŃG���[�o�Ă��炾����������

void Bullet::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}


void Bullet::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void Bullet::Update()
{
	// ���f�����ړ������肷��Ƃ��͂����ɏ������肷��
	m_Position.x += m_Velocity.x;
	m_Position.y += m_Velocity.y;
	m_Position.z += m_Velocity.z;

	if (m_Position.z > 100.0f)
	{
		SetDestroy();
		return;
	}


	Scene * scene = Manager::GetScene();
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1);

	for (Enemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

			enemy->SetDestroy();
			SetDestroy();
			return;
		}
	}
}


void Bullet::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// ���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}


void Bullet::Load()
{
	// Init �Ń��f���̃��[�h������ƁA�o���b�g������邽�тɃ��f���̓ǂݍ��݂��N���Ă��܂�
	// �̂łׂɂ킯�Ă���

	// static���\�b�h(static�̃����o�֐�)�̒��ł�
	// ������cpp�Ƃ��̒��ŏ����Ă�����̂����g���Ȃ��B
	// static�ɂ���ƕ��ʂ̃O���[�o���ϐ��ƁA���ʂ̊֐����Ċ����̈����Ɠ���������B

	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");
}

void Bullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}