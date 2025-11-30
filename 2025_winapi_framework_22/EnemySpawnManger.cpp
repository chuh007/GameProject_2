#include "pch.h"
#include "Scene.h"
#include "Enemy.h"
#include "EnemySpawnManger.h"
void EnemySpawnManger::Init()
{
	AssignPath();
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

void EnemySpawnManger::AssignPath()
{
	BezierPathData* defaultPath = new BezierPathData;
	defaultPath->BezierPathData::CalculateArcLengthMap({ {0,0},{300,300},{600,600},{500,800} });
	m_calcedPath.insert({ L"Default", defaultPath });
}
