#include "finish.h"

CFinish::CFinish(void)
{
}

CFinish::~CFinish(void)
{
}

void CFinish::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CFinish::Update(void)
{
}

void CFinish::Draw(void)
{
	vivid::DrawTexture("data\\FINISH.png", m_Position);
}

void CFinish::Finalize(void)
{
	m_Position.x = 3000;
}