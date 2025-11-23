#include "pch.h"
#include "EnemySpawnManger.h"
#include "Scene.h"
#include "Enemy.h"
void EnemySpawnManger::StartSpawn(Scene* targetScene)
{
	m_spawnTargetScene = targetScene;
}

void EnemySpawnManger::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	TryToSpawn();
}

void EnemySpawnManger::StopSpawn()
{
}

void EnemySpawnManger::Realese()
{
    while (!m_enemySpawnQueue.empty())
    {
        SpawnInfo info = m_enemySpawnQueue.top();

        SAFE_DELETE(info.enemy)

        m_enemySpawnQueue.pop();
    }
}

void EnemySpawnManger::AddEnemySpawn(SpawnInfo _spawnInfo)
{
	m_enemySpawnQueue.push(_spawnInfo);
}

bool EnemySpawnManger::TryToSpawn()
{
	if (m_enemySpawnQueue.empty())
	{
		return false;
	}

	SpawnInfo info = m_enemySpawnQueue.top();
	if (m_currentTime >= info.spawnTime)
	{
		m_spawnTargetScene->AddObject(info.enemy, Layer::ENEMY);
		m_enemySpawnQueue.pop();
		return true;
	}
	return false;
}
