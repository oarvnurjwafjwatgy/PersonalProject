#include "combo_count.h"

CComboCount::CComboCount(void)
	:m_Count(0)
{
}

CComboCount::~CComboCount(void)
{
}

void CComboCount::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void CComboCount::Update(void)
{
}

void CComboCount::Draw(void)
{
	if (m_Count > 0)
	{
		vivid::DrawText(200, std::to_string(m_Count), m_Position);
	}

	vivid::DrawTexture("data\\combo.png", { (float)(vivid::WINDOW_WIDTH- vivid::GetTextureWidth("data\\combo.png")),800.0f });
}

void CComboCount::SetCount(int count)
{
	m_Count = count;
}
