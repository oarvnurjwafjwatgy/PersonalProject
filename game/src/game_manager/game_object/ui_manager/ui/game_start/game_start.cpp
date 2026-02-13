#include "game_start.h"


CGameStart::CGameStart(void)
	: IUI()
{
}

CGameStart::~CGameStart(void)
{
}

void CGameStart::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_UI_Delete_Timer = 4*60;
}

void CGameStart::Update(void)
{
	UIDeleteTimer();
}

void CGameStart::Draw(void)
{
	vivid::DrawTexture("data\\GAMESTART.png", m_Position);

	vivid::DrawText(100, std::to_string(m_UI_Delete_Timer), { 700,700 }, 0xff000000);
}

void CGameStart::Finalize(void)
{
	m_Position.x = 3000;
}