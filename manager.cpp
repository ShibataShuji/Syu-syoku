#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "polygon2D.h"
#include "Field.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "scene.h"
#include "Game.h"
#include "Title.h"
#include "audio.h"


Scene* Manager::m_Scene = NULL;			// �����.h�̕��̂�ŏ������悤�ɂ��������Ă΂Ȃ��Ⴂ���Ȃ�����A
									// Scene�N���X�̃|�C���^��Manager�N���X�̃����o�ϐ�m_Scene���Z�b�g���Ă���B


void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();		// static���\�b�h�Ȃ̂�::���̌Ăѕ�

	SetScene<Title>();

}


void Manager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();


	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();// �J�����͐�I�Ăяo�����厞// 3D��Ԃł̕\��// UI�n�͍Ō�ɁB
	
}
