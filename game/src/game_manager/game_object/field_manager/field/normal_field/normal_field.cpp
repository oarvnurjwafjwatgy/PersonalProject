#include "normal_field.h"

CNormalField::CNormalField(void)
{
}

CNormalField::~CNormalField(void)
{
}

void CNormalField::Initialize(const vivid::Vector2& position, FIELD_ID field_id)
{
	IField::Initialize(position,field_id);
}


void CNormalField::Update(void)
{
}

void CNormalField::Draw(void)
{
	IField::Draw();
}
