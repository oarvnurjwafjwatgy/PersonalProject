#include "ui_manager.h"
#include "ui/ui.h"
#include "ui/combo_gauge/combo_gauge.h"
#include <memory>
#include "../ui_manager/ui/combo_count/combo_count.h"
#include "../ui_manager/ui/score_text/score_text.h"
#include "../ui_manager/ui/game_start/game_start.h"
#include "../ui_manager/ui/finish/finish.h"
#include "../ui_manager/ui/result_text/result_text.h"

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
		(*it)->Finalize();

		++it;
	}

	m_UIList.clear();
}

std::shared_ptr<IUI> CUIManager::Create(UI_ID ui_id, const vivid::Vector2& position)
{
	std::shared_ptr<IUI> ui = CreateClass(ui_id);

	if (!ui) return nullptr;

	ui->Initialize(position);
	m_UIList.emplace_back(ui);

	return ui;
}

void CUIManager::Delete(UI_ID id)
{
	if (m_UIList.empty()) return;
	
	UI_LIST::iterator it = m_UIList.begin();

	while (it != m_UIList.end())
	{
		std::shared_ptr<IUI> ui = (*it);

		if (ui->GetUI_ID() == id)
		{
			ui->Delete();
		}

		++it;
	}
}
 
std::shared_ptr<IUI> CUIManager::CreateClass(UI_ID id)
{
	std::shared_ptr<IUI> ui = nullptr;

	switch (id)
	{
	case UI_ID::COMBO_GAUGE: ui = std::make_shared<CComboGauge>(); break;
	case UI_ID::COMBO_COUNT: ui = std::make_shared<CComboCount>(); break;
	case UI_ID::SCORE_TEXT:  ui = std::make_shared<CScoreText>();  break;
	case UI_ID::GAME_START: ui = std::make_shared<CGameStart>();  break;
	case UI_ID::FINISH: ui = std::make_shared<CFinish>();  break;
	case UI_ID::RESULT_TEXT: ui = std::make_shared<CResult_text>();  break;

	}
	return ui;
}
