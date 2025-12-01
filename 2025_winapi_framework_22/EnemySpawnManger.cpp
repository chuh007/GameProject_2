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
	defaultPath->BezierPathData::CalculateArcLengthMap({ {0,0},{200,200},{400,-200},{600,300} });
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
