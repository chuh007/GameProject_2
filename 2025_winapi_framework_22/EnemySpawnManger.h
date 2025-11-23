#pragma once
#include "queue"
class Enemy;
class Scene;
struct SpawnInfo
{
	float spawnTime;
	Enemy* enemy;
	Vec2 position;
};
struct CompareSpawnInfo
{
	bool operator()(const SpawnInfo& a, const SpawnInfo& b) const {
		return a.spawnTime > b.spawnTime;
	}
};
bool CmpSpawnInfo(SpawnInfo& a, SpawnInfo& b)
{
	return a.spawnTime < b.spawnTime;
}
class EnemySpawnManger
{ 
	DECLARE_SINGLE(EnemySpawnManger)

public:
	void StartSpawn(Scene* targetScene);
	void Update(float deltaTime);
	void StopSpawn();
	void Realese();
public:
	void AddEnemySpawn(SpawnInfo _spawn);
private: 
	bool TryToSpawn();
private:
	float m_currentTime;
	Scene* m_spawnTargetScene;
	std::priority_queue<SpawnInfo, std::vector<SpawnInfo>, CompareSpawnInfo> m_enemySpawnQueue;
};

