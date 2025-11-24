#pragma once
#include <queue>
class Enemy;
class Scene;
struct SpawnInfo
{
	float spawnTime;
	Enemy* enemy;

};
struct CompareSpawnInfo
{
	bool operator()(const SpawnInfo& a, const SpawnInfo& b) const {
		return a.spawnTime > b.spawnTime;
	}
};
class EnemySpawnManger
{ 
	DECLARE_SINGLE(EnemySpawnManger)

public:
	void Init();
	void Update();
	void StopSpawn();
	void Realese();
public:
	void AddEnemySpawnQueue(SpawnInfo _spawn);
	void SetSpawnScene(Scene* scene)
	{
		m_spawnTargetScene = scene;
	}
private: 
	bool TryToSpawn();
private:
	float m_currentTime;
	Scene* m_spawnTargetScene;
	std::priority_queue<SpawnInfo, std::vector<SpawnInfo>, CompareSpawnInfo> m_enemySpawnQueue;
};

