#include "score_manager.h"
#include "../field_manager/field_manager.h"


const int CScoreManager:: m_base_score = 25;
const float CScoreManager::m_base_multiplier = 1.0f;
const float CScoreManager::m_half = 0.5f;
const float CScoreManager::m_one_tenth = 0.1f;


CScoreManager& CScoreManager::GetInstance(void)
{
	static CScoreManager instance;

	return instance;
}

void CScoreManager::Initialize(void)
{
	m_Score = 0;
}

void CScoreManager::Update(void)
{
}


void CScoreManager::Finalize(void)
{
}

int CScoreManager::GetScore(void)
{
	return m_Score;
}

void CScoreManager::AddScore( int chains, int combo)
{
	float chain_bonus = (float)(chains - CFieldManager::GetInstance().GetBlockMinChains()) * m_half;
	float combo_bonus = (float)combo * m_one_tenth;
	
	m_Score += m_base_score * chains * (chain_bonus + m_base_multiplier + combo_bonus);
}
