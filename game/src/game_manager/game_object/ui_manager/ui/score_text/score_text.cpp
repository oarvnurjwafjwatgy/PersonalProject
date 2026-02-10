#include "score_text.h"

CScoreText::CScoreText(void)
	: m_CurrentScore(0)
{
}

CScoreText::~CScoreText(void)
{
}

void CScoreText::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CScoreText::Update()
{
}

void CScoreText::Draw()
{
	vivid::DrawText(80, std::to_string(m_CurrentScore), m_Position);
}

void CScoreText::Finalize()
{
}

void CScoreText::SetCurrentScore(int current_score)
{
	m_CurrentScore = current_score;
}

int CScoreText::GetCurrentScore()
{
	return m_CurrentScore;
}

