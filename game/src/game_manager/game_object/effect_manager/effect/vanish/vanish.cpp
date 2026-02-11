#include "vanish.h"

const float CVanish::m_speed = 10.0f;
const float CVanish::m_max_fade = 0.1f;
const int CVanish::m_max_color_table = 6;
unsigned int g_color = 0xffff8888;

CVanish::CVanish(void)
	:m_Velocity(vivid::Vector2::ZERO)
	,m_Color(0)
{
}

CVanish::~CVanish(void)
{
}

void CVanish::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	vivid::LoadTexture("data\\particle.png");

	float angle = (float)(rand() % 360) * 3.14f / 180.0f;
	m_Velocity.x = cos(angle) * m_speed;
	m_Velocity.y = sin(angle) * m_speed;

	m_Color = g_color;
}

void CVanish::Update(void)
{
	m_Position += m_Velocity;

	int alpha = (m_Color & 0xff000000) >> 24;

	alpha -= m_max_fade;

	if (alpha < 0)
	{
		alpha = 0;

		m_Color = 0x00000000;
	}

	m_Color = (alpha << 24) | (m_Color & 0x00ffffff);
}

void CVanish::Draw(void)
{
	vivid::DrawTexture("data\\particle.png", m_Position, m_Color);
	m_Position.x + (3.14f * 180.0f);
	m_Position.y + (3.14f * 180.0f);
}
