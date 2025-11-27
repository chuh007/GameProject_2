#include "pch.h"
#include "PoolManager.h"
#include "EnemyProjectile.h"

void PoolManager::Init()
{
	
}

PoolManager::~PoolManager()
{
    for (auto const& item : m_pools)
    {
        delete item.second;
    }
    m_pools.clear();
}
