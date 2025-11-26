#include "pch.h"
#include "Scene.h"
#include "Enemy.h"
#include "EnemySpawnManger.h"
void EnemySpawnManger::Init()
{
	cout << "spawn manager init" << endl;
	m_currentTime = 0;
}

void EnemySpawnManger::Update()
{
	m_currentTime += fDT;
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

void EnemySpawnManger::AddEnemySpawnQueue(SpawnInfo _spawnInfo)
{
	cout << "enemy added" << endl;
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
