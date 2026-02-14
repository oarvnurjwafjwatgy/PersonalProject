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
	m_UI_Delete_Timer = 3*60;
}

void CGameStart::Update(void)
{
	UIDeleteTimer();
}

void CGameStart::Draw(void)
{
	vivid::DrawTexture("data\\GAMESTART.png", m_Position);
}

void CGameStart::Finalize(void)
{
}