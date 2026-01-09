#include "normal_field.h"

CNormalField::CNormalField(void)
{
}

CNormalField::~CNormalField(void)
{
}

void CNormalField::Initialize(const vivid::Vector2& position, FIELD_ID field_id)
{
	m_CursorPosition = position;
}


void CNormalField::Update(void)
{
}

void CNormalField::Draw(void)
{

	vivid::DrawTexture("data/abe.png", m_CursorPosition);
}
