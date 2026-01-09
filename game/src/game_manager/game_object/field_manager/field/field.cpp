#include "field.h"

IField::IField(void)
{
}

IField::~IField(void)
{
}

void IField::Initialize(const vivid::Vector2& position, FIELD_ID field_id)
{
}

void IField::Update(void)
{
}

void IField::Draw(void)
{
}

void IField::Finalize(void)
{
}

bool IField::GetActive(void)
{
	return false;
}

void IField::MoveCursor(void)
{
}

void IField::ShiftBlock(void)
{
}
