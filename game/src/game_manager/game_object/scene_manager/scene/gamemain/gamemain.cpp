#include "gamemain.h"
#include "../../../field_manager/field_manager.h"
#include "../../../field_manager/field/field.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../effect_manager/effect_manager.h"



CGameMain::CGameMain(void)
{
}

CGameMain::~CGameMain(void)
{
}

void CGameMain::Initialize(SCENE_ID scene_id)
{
	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	field.Initialize();

	field.Create(vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - field.GetBlockSize() * field.GetBlockMaxWidth() / 2.0f, 200.0f), FIELD_ID::NORMAL);

	vivid::Vector2 combogauge_pos = { 50,300 };
	vivid::Vector2 combocount_pos = { 50,250 };

	//std::shared_ptr<IUI> ComboGaugeUI = ui.Create(UI_ID::COMBO_GAUGE,combogauge_pos);
	//std::shared_ptr<IUI> ComboCountUI = ui.Create(UI_ID::COMBO_COUNT, combocount_pos);
}

void CGameMain::Update()
{
	auto& field = CFieldManager::GetInstance(); 
	auto& scene = CSceneManager::GetInstance();

	field.Update();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
		scene.ChangeScene(SCENE_ID::RESULT);

	if (field.GetFinishFlag())
	{
		scene.ChangeScene(SCENE_ID::RESULT);
	}
}

void CGameMain::Draw()
{
	vivid::DrawTexture("data\\backGraund.png", { 0,0 });

	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& effect = CEffectManager::GetInstance();

	field.Draw();
	ui.Draw();
	effect.Draw();
	

	vivid::DrawText(30, "ÉÅÉCÉìâÊñ ", vivid::Vector2::ZERO);

	

}

void CGameMain::Finalize()
{
	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	field.Finalize();
	ui.Finalize();
}
