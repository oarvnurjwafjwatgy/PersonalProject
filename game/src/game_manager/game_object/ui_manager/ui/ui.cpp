#include "ui.h"

IUI::IUI(UI_ID id )
    : m_ActiveFlag(true)
    ,m_UI_ID(id)
    ,m_Position(vivid::Vector2::ZERO)
{
}

IUI::~IUI(void)
{
}

void IUI::Initialize(const vivid::Vector2& position )
{
}

void IUI::Update(void)
{
}

void IUI::Draw(void)
{
}

void IUI::Finalize(void)
{
}

bool IUI::GetActive(void)
{
    return m_ActiveFlag;
}

void IUI::Delete()
{
    m_ActiveFlag = false;
}

UI_ID IUI::GetUI_ID()
{
    return m_UI_ID;
}
