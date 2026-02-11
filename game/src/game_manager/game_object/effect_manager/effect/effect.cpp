#include "effect.h"



IEffect::IEffect(vivid::Vector2 position, vivid::Vector2 velocity, unsigned int color)
	:m_Position(position)
	,m_Velocity(velocity)
	, m_Color(color)
	, m_Alpha(1.0f)
	, m_ActiveFlag(true)
{
}

IEffect::IEffect()
{

}

IEffect::~IEffect(void)
{
}

void IEffect::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
}

void IEffect::Update(void)
{
	m_Position += m_Velocity;
	m_Alpha -= 0.05f;

	if (m_Alpha <= 0)
	{
		m_ActiveFlag = false;
	}
}

void IEffect::Draw(void)
{
	unsigned int alphaColor = (m_Color & 0x00ffffff) | ((unsigned int)(m_Alpha * 255) << 24);
	vivid::DrawTexture("data\\particle.png", m_Position, alphaColor);
}

void IEffect::Finalize(void)
{
}

bool IEffect::GetActive(void)
{
	return m_ActiveFlag;
}

void IEffect::Delete()
{
}

EFFECT_ID IEffect::GetEffect_ID()
{
	return m_Effect_ID;
}

void IEffect::SetColor(unsigned int color)
{
	 m_Color = color; 
}
