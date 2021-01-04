#include "Game.h"

#include <iostream>

int Game::w_width = 480;
int Game::w_height = Game::w_width * 5 / 3;

Game::Game()
	: projection(1)
{

}

void Game::Init()
{
	projection = glm::ortho(-240.f, 240.f, -240.f * 5 / 3, 240.f * 5 / 3, -1.f, 1.f);

	// Texture Init
	Texture::LoadTexture("space", "Texture/pixel_space.png", true);
	Texture::LoadTexture("bullet", "Texture/pink_bullet.png", true);
	Texture::LoadTexture("bg", "Texture/background-black.png", true);
	Texture::LoadTexture("littleEnemy", "Texture/litteEnemy.png", true);
	Texture::LoadTexture("heart", "Texture/heart.png", true);
	Texture::LoadTexture("boss", "Texture/boss.png", true);
	Texture::LoadTexture("win", "Texture/win.png", true);

	// Shader Init
	Shader::LoadShader("health", "Shader/healthbar.vertex.shader", "Shader/healthbar.fragment.shader");
	Shader::GetShader("health").Bind();
	Shader::GetShader("health").SetMatrix("projection", projection);

	Shader::LoadShader("sprite", "Shader/sprite.vertex.shader", "Shader/sprite.fragment.shader");
	Shader::GetShader("sprite").Bind();
	Shader::GetShader("sprite").SetMatrix("projection", projection);
	Shader::GetShader("sprite").SetInt("tex", 1);

	renderer = new SpriteRenderer();
	space = new Space();
	boss = new Boss();
	bg = new BackGround();
	enemySpawnManager = new EnemySpawnManager();
	showWin = new ShowWin();

	bg->OnInit(glm::vec3(0, 0, 0), 0, glm::vec3(w_width, w_height, 0));
	space->OnInit(glm::vec3(0, -300, 0), 0, glm::vec3(50, 50, 0));
	boss->OnInit(glm::vec3(0, 500, 0), 180, glm::vec3(150));
	enemySpawnManager->OnInit(glm::vec3(0), 0, glm::vec3(1));
	showWin->OnInit(glm::vec3(0, 600, 0), 0, glm::vec3(400));
	InitBulletPool();
}

void Game::OnProcessInput()
{
	if (canShoot && Input::GetKeyDown(GLFW_KEY_Z))
		PlayerShoot();
}

void Game::OnUpdate(float ds)
{
	// background update
	bg->OnUpdate(ds);

	// bullet update
	for (int i = 0; i < max_bullet; i++)
		player_bulletPool[i]->OnUpdate(ds);

	PlayerShootSpaceTime(ds);

	// Little Enemy update
	enemySpawnManager->OnUpdate(ds);

	// boss update
	boss->OnUpdate(ds);
	boss->SetPlayerPosition(space->GetPosition().x);

	// player update
	space->OnUpdate(ds);

	if (boss->GetState() == BossState::dead)
		showWin->ShowWinUI(space, boss, enemySpawnManager);
	showWin->OnUpdate(ds);

	// Collision
	DoCollision();
}

void Game::OnRender()
{
	// background render
	bg->OnRender(renderer);

	// bullet render
	for (int i = 0; i < max_bullet; i++)
		player_bulletPool[i]->OnRender(renderer);

	// Little Enemy render
	enemySpawnManager->OnRender(renderer);

	// boss render
	boss->OnRender(renderer);

	showWin->OnRender(renderer);

	// player render
	space->OnRender(renderer);
}

void Game::InitBulletPool()
{
	for (int i = 0; i < max_bullet; i++)
	{
		player_bulletPool.push_back(new Bullet(glm::vec3(space->GetPosition().x, space->GetPosition().y + 35, space->GetPosition().z), 0, glm::vec3(25)));
		player_bulletPool[i]->SetPlayerOrEnemy(1);
	}
}

void Game::PlayerShoot()
{
	canShoot = false;
	player_bulletPool[bullet_index]->Shoot(glm::vec3(space->GetPosition().x, space->GetPosition().y + 35, space->GetPosition().z));
	bullet_index++;
	if (bullet_index >= max_bullet)
		bullet_index = 0;
}

void Game::PlayerShootSpaceTime(float ds)
{
	// Caculate wheater player can shoot
	if (time_btw >= 0) {
		time_btw -= ds;
	}
	else {
		canShoot = true;
		time_btw = time_to_next_shoot;
	}
}

void Game::DoCollision()
{
	if (space->IsAlive())
	{
		// Player And Enemy Collision
		for (int i = 0; i < enemySpawnManager->GetEnemys().size(); i++)
		{
			if (!enemySpawnManager->GetEnemys()[i]->IsAlive()) // if enemy is not alive then do nothing !
				continue;
			bool collisionX = abs(space->GetPosition().x - enemySpawnManager->GetEnemys()[i]->GetPosition().x) <=
				space->GetSize().x / 2.f - 10.f + enemySpawnManager->GetEnemys()[i]->GetSize().x / 2.f - 10.f;
			bool collisionY = abs(space->GetPosition().y - enemySpawnManager->GetEnemys()[i]->GetPosition().y) <=
				space->GetSize().y / 2.f - 15.f + enemySpawnManager->GetEnemys()[i]->GetSize().y / 2.f - 15.f;
			
			if (collisionX && collisionY)
			{
				space->TakeDamage(1);
				enemySpawnManager->GetEnemys()[i]->Destroy();
			}
		}

		// Player Bullet And Enemy Collision
		for (int i = 0; i < player_bulletPool.size(); i++)
		{
			if (!player_bulletPool[i]->IsShooting()) // If bullet is not alive then do nothing !
				continue;

			for (int j = 0; j < enemySpawnManager->GetEnemys().size(); j++)
			{
				if (!enemySpawnManager->GetEnemys()[j]->IsAlive()) // If enemy is not alive then do nothing !
					continue;

				bool collisionX = abs(player_bulletPool[i]->GetPosition().x - enemySpawnManager->GetEnemys()[j]->GetPosition().x) <=
					player_bulletPool[i]->GetSize().x / 2.f - 10 + enemySpawnManager->GetEnemys()[j]->GetSize().x / 2.f - 10;

				bool collisionY = abs(player_bulletPool[i]->GetPosition().y - enemySpawnManager->GetEnemys()[j]->GetPosition().y) <=
					player_bulletPool[i]->GetSize().y / 2.f - 15 + enemySpawnManager->GetEnemys()[j]->GetSize().y / 2.f - 15;
					
				if (collisionX && collisionY)
				{
					enemySpawnManager->GetEnemys()[j]->TakeDamage(40);
					player_bulletPool[i]->Destroy();
					kill++;
					if (kill == 20) // touch little enemy 20 times will show boss
						boss->SetAlive(true);
				}
			}
		}
	}

	if (space->IsAlive() && boss->IsAlive())
	{
		// Player and Boss collisition ////////////////////////
		bool collistionX = space->GetPosition().x - space->GetSize().x / 2.f >= boss->GetPosition().x - boss->GetSize().x / 2.f &&
			space->GetPosition().x + space->GetSize().x / 2.f <= boss->GetPosition().x + boss->GetSize().x / 2.f;

		bool collistionY = space->GetPosition().y - space->GetSize().y / 2.f >= boss->GetPosition().y - boss->GetSize().y / 2.f &&
			space->GetPosition().y + space->GetSize().y / 2.f <= boss->GetPosition().y + boss->GetSize().y / 2.f;
		
		if (collistionX && collistionY)
		{
			// Todo
			space->TakeDamage(4);
			space->SetPositionY(space->GetPosition().y - 80);
		}
		////////////////////////////////////////////////////

		// Player And Boss Bullet Collision
		for (int i = 0; i < boss->GetBullets().size(); i++)
		{
			if (!boss->GetBullets()[i]->IsShooting())
				continue; // if bullet is not shootin then do nothing !

			bool collisionX = abs(space->GetPosition().x - boss->GetBullets()[i]->GetPosition().x) <=
				space->GetSize().x + boss->GetBullets()[i]->GetSize().x;

			bool collisionY = abs(space->GetPosition().y - boss->GetBullets()[i]->GetPosition().y) <=
				space->GetSize().y + boss->GetBullets()[i]->GetSize().y;

			if (collisionX && collisionY)
			{
				space->TakeDamage(1);
				boss->GetBullets()[i]->Destroy();
			}
		}

		// Player Bullet And Boss Collision
		for (int i = 0; i < player_bulletPool.size(); i++)
		{
			if (!player_bulletPool[i]->IsShooting()) // if bullet is not shooting then do nothing !
				continue;

			bool collisionX = abs(player_bulletPool[i]->GetPosition().x - boss->GetPosition().x) <=
				player_bulletPool[i]->GetSize().x / 2.f - 1.f+ boss->GetSize().x / 2.f - 1.f;

			bool collisionY = abs(player_bulletPool[i]->GetPosition().y - boss->GetPosition().y) <=
				player_bulletPool[i]->GetSize().y / 2.f - 1.5f + boss->GetSize().y / 2.f - 1.f;

			if (collisionX && collisionY)
			{
				player_bulletPool[i]->Destroy();
				boss->TakeDamage();
			}
		}
	}
}

Game::~Game()
{
	delete renderer;
	delete boss;
	delete space;
	delete bg;
	for (int i = 0; i < max_bullet; i++)
		delete player_bulletPool[i];
	delete showWin;
}