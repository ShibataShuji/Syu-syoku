#include <random>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"


#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "field.h"
#include "Enemy.h"
#include "Platform.h"
#include "Bullet.h"
#include "Sky.h"
#include "Explosion.h"
#include "Tree.h"
#include "polygon2D.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "audio.h"

Audio* bgm;

void Game::Init()
{
	Bullet::Load();

	Enemy::Load();
	Platform::Load();

	// ���ԑ厖�` ���߂�A�R�����Ԃ����A�Q�����Ԃ���e
	AddGameObject<Camera>(0);

	AddGameObject<Field>(1);
	AddGameObject<Sky>(1);
	// �ǂ��ɂ����ăv���C���[�̃|�C���^�[�������Ă��������A�O���[�o���ϐ��Ƃ��ŁB
	//T p_Player = AddGameObject<Player>(1);
	AddGameObject<Player>(1);
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(3.0f, 1.0f, 5.0f));

	Platform* platform = AddGameObject<Platform>(1);
	platform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	platform->SetScale(D3DXVECTOR3(3.0f, 1.0f, 3.0f));

	for (int i = 0; i < 20; i++)
	{
		D3DXVECTOR3 randpos;
		//(float)rand() / RAND_MAX;		// 0~1���łĂ���

		randpos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		randpos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		randpos.y = 0.0f;
		AddGameObject<Tree>(1)->SetPosition(randpos);
		//randpos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		//randpos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		//AddGameObject<Platform>(1)->SetPosition(randpos);
	}


	AddGameObject<Polygon2D>(2);
	// 2D�̌�ɂ�3D�͕\���ł��Ȃ��G�G



	bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\bgm.wav");
	bgm->Play(true);		// ��������true�̓��[�v���邩���Ȃ����B��������Ȃ��ƃf�t�H���g��false


}

void Game::Uninit()
{
	Scene::Uninit();		// �p�����̃N���X�̃��\�b�h�Ăяo��
	Bullet::Unload();
	Enemy::Unload();
	Platform::Unload();
}

void Game::Update()
{
	Scene::Update();

	/*if (Input::GetKeyPress('E'))
	{
		bgm->Stop();
	}*/

	if (Input::GetKeyPress('E'))
	{
		bgm->SetFadeout(120);
	}

	if (Input::GetKeyPress('Q'))
	{
		bgm->SetFadein(120);
	}

	if (Input::GetKeyPress('R'))
	{
		bgm->SetVolume(2.0f);
	}

	// �����ŃV�[���̑@�ۂ�����
	// ��������ƃV�[���̃A�b�v�f�[�g���I����Ă���
	// �V�[���̑J�ڂ��s����

	// �v���C���[�����Ȃ��Ȃ����`


	// �G�L���������Ȃ��Ȃ�����`
	Scene* scene = Manager::GetScene();
	std::vector<Enemy*> enemys = scene->GetGameObjects<Enemy>(1);
	int AliveEnemyNum = 0;
	for (auto& i : enemys)
	{
		AliveEnemyNum++;
	}
	if (AliveEnemyNum == 0)
	{
		Manager::SetScene<Result>();
	}

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Result>();
	}
}