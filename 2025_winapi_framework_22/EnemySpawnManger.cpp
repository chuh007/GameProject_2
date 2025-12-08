#include "pch.h"
#include "Scene.h"
#include "Enemy.h"
#include "Boss.h"
#include "EnemySpawnManger.h"
#include "BossHPBar.h"
void EnemySpawnManger::Init()
{
	AssignPath();
	m_currentTime = 0;
	m_bossSpawned = false;
	m_bossSpawnTime = 20000.f;
}

void EnemySpawnManger::Update()
{
	m_currentTime += fDT;
	TryToSpawn();
	m_bossSpawned = TryToSpawnBoss();
}

void  EnemySpawnManger::StopSpawn()
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
	for (std::pair<wstring, BezierPathData*> kvp : m_calcedPath)
	{
		SAFE_DELETE(kvp.second)
	}
}

void EnemySpawnManger::AddEnemySpawnQueue(SpawnInfo _spawnInfo)
{
	cout << "enemy added" << endl;
	m_enemySpawnQueue.push(_spawnInfo);
}

void EnemySpawnManger::AddBossSpawn(float _time)
{
	m_bossSpawnTime = _time;
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

bool EnemySpawnManger::TryToSpawnBoss()
{
	if (m_bossSpawned)
		return true;
	if (m_currentTime >= m_bossSpawnTime)
	{
		Boss* boss = m_spawnTargetScene->Spawn<Boss>(Layer::ENEMY, { GAME_WIDTH / 2, GAME_HEIGHT / 4 }, { 50.f,75.f });;
		auto* hpBar = m_spawnTargetScene->Spawn<BossHPBar>(Layer::UI, { GAME_WIDTH / 2, 25 }, { GAME_WIDTH - 20, 50 });
		hpBar->SetBoss(boss);
		return true;
	}
	return false;
}

void EnemySpawnManger::AssignPath()
{
	BezierPathData* defaultPath = new BezierPathData;
	defaultPath->BezierPathData::CalculateArcLengthMap({ {0,0},{200,200},{400,-200},{600,0} });
	m_calcedPath.insert({ L"Default", defaultPath });
	BezierPathData* reverse = new BezierPathData;
	reverse->BezierPathData::CalculateArcLengthMap({ {0,0},{-200,-500},{-400,100},{-600,-300} });
	m_calcedPath.insert({ L"Reverse", reverse });
	BezierPathData* circlePath = new BezierPathData;
	circlePath->BezierPathData::CalculateArcLengthMap({ {-100,300},{100,0},{600,600},{400,300} });
	m_calcedPath.insert({ L"Circle", circlePath });

	BezierPathData* up = new BezierPathData;
	up->BezierPathData::CalculateArcLengthMap({ {0,0}, {0,100} });
	m_calcedPath.insert({ L"Up", up });

	BezierPathData* down = new BezierPathData;
	down->BezierPathData::CalculateArcLengthMap({ {0,0}, {0,-100} });
	m_calcedPath.insert({ L"Down", down });

	BezierPathData* left = new BezierPathData;
	left->BezierPathData::CalculateArcLengthMap({ {0,0}, {-100,0} });
	m_calcedPath.insert({ L"Left", left });

	BezierPathData* rightPath = new BezierPathData;
	rightPath->BezierPathData::CalculateArcLengthMap({ {0,0}, {100,0} });
	m_calcedPath.insert({ L"Right", rightPath });

	BezierPathData* zigzagR = new BezierPathData;
	zigzagR->BezierPathData::CalculateArcLengthMap({ {0,0}, {100,100} });
	m_calcedPath.insert({ L"ZigzagR", zigzagR });

	BezierPathData* zigzagL = new BezierPathData;
	zigzagL->BezierPathData::CalculateArcLengthMap({ {0,0}, {-100,100} });
	m_calcedPath.insert({ L"ZigzagL", zigzagL });

}
