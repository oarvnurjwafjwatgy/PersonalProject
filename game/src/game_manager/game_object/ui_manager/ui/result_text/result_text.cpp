#include "result_text.h"

CResult_text::CResult_text(void)
{
}

CResult_text::~CResult_text(void)
{
}

void CResult_text::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CResult_text::Update(void)
{
}

void CResult_text::Draw(void)
{
	vivid::DrawTexture("data\\RESULT.png", m_Position);
}

void CResult_text::Finalize(void)
{
}
