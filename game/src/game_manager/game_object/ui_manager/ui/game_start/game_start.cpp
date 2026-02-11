#include "game_start.h"


CGameStart::CGameStart(void)
	:m_Position(vivid::Vector2::ZERO)
{
}

CGameStart::~CGameStart(void)
{
}

void CGameStart::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CGameStart::Update(void)
{

}

void CGameStart::Draw(void)
{
	vivid::DrawTexture("data\\GAMESTART.png", m_Position);
}

void CGameStart::Finalize(void)
{
	m_Position.x = 3000;
}