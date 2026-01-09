#include "score_manager.h"

CScoreManager& CScoreManager::GetInstance(void)
{
	static CScoreManager instance;

	return instance;
}

void CScoreManager::Initialize(void)
{
}

void CScoreManager::Update(void)
{
}

void CScoreManager::Draw(void)
{
}

void CScoreManager::Finalize(void)
{
}

CScoreManager::CScoreManager(void)
{
}

CScoreManager::CScoreManager(const CScoreManager& rhs)
{
}

CScoreManager::~CScoreManager(void)
{
}

CScoreManager& CScoreManager::operator=(const CScoreManager& rhs)
{
	(void)rhs;

	return *this;
}
