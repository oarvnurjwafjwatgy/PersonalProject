#include "score_text.h"

const int CScoreText::m_number_digit_width = 88;
const int CScoreText::m_number_digit_height = 128;
const unsigned int CScoreText::m_number_color = 0xffffffff;



CScoreText::CScoreText(void)
	: m_CurrentScore(0)
	, m_Color(m_number_color)
{
}

CScoreText::~CScoreText(void)
{
}

void CScoreText::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	for (int i = 0; i < m_digit_max; i++)
	{
		m_Rect[i] = { 0,0,m_number_digit_width,m_number_digit_height };
	}

}

void CScoreText::Update()
{
	int score_calc = m_CurrentScore;


	for(int  i = m_digit_max-1; i >= 0; i--)
	{
		// ˆêŒ…‚¸‚Âæ‚èo‚·
		int digit = score_calc % 10;

		//Ÿ‚ÌˆêŒ…‚Ì‚½‚ß‚É‚P‚ÌˆÊ‚ğØ‚èÌ‚Ä
		score_calc /= 10;
		m_Rect[i].left = digit * m_number_digit_width;
		m_Rect[i].right = m_Rect[i].left + m_number_digit_width;

		
	}


}

void CScoreText::Draw()
{

	for (int i = 0; i < m_digit_max; i++)
	{
		vivid::DrawTexture("data\\number.png", m_Position + vivid::Vector2((float)(m_number_digit_width * i), 0.0f),m_Color,m_Rect[i]);
	}

	//vivid::DrawText(80, std::to_string(m_CurrentScore), m_Position);
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

