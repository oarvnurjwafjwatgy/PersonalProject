#include "ui_manager.h"
#include "ui/ui.h"
#include <memory>

CUIManager& CUIManager::GetInstance(void)
{
	static CUIManager instance;

	return instance;
}

void CUIManager::Initialize(void)
{
	// リストの初期化
	m_UIList.clear();
}

void CUIManager::Update(void)
{
	// リストが空だったら処理しない
	if (m_UIList.empty())	return;

	UI_LIST::iterator it = m_UIList.begin();

	while (it != m_UIList.end())
	{
		std::shared_ptr<IUI> ui = *it;

		ui->Update();

		++it;
	}
}

void CUIManager::Draw(void)
{
	// リストが空だったら処理しない
	if (m_UIList.empty())	return;

	UI_LIST::iterator it = m_UIList.begin();

	while (it != m_UIList.end())
	{
		std::shared_ptr<IUI> ui = *it;

		ui->Draw();

		++it;
	}
}

void CUIManager::Finalize(void)
{
	// リストが空だったら処理しない
	if (m_UIList.empty())	return;

	UI_LIST::iterator it = m_UIList.begin();

	while (it != m_UIList.end())
	{
		std::shared_ptr<IUI> ui = *it;

		ui->Finalize();

		++it;
	}
}

void CUIManager::Create(const vivid::Vector2& position, UI_ID ui_id)
{
	std::shared_ptr<IUI> ui = nullptr;

	//ID
	switch (ui_id)
	{
	/*case UI_ID::SCORE:	ui = std::make_shared <CScore>(); break;
	case UI_ID::COMBO_GAUGE: ui = std::make_shared<CComboGauge>(); break;
	case UI_ID::COMBO_COUNT: ui = std::make_shared<CComboCount>(); break;*/
	default: break;
	}

	if (!ui) return;

	ui->Initialize(position, ui_id);

	m_UIList.emplace_back(ui);
}