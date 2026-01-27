#include "ui_manager.h"

CUIManager& CUIManager::GetInstance(void)
{
	static CUIManager instance;

	return instance;
}

void CUIManager::Initialize(void)
{
}

void CUIManager::Update(void)
{
}

void CUIManager::Draw(void)
{
}

void CUIManager::Finalize(void)
{
}
