#include "pch.h"
#include "PoolManager.h"

PoolManager::~PoolManager()
{
    for (auto& item : m_pools)
    {
        SAFE_DELETE(item.second);
    }
    m_pools.clear();
}
