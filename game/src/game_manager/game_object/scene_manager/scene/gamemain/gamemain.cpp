#include "gamemain.h"
#include "../../../field_manager/field_manager.h"
#include "../../../field_manager/field/field.h"

CGameMain::CGameMain(void)
{
}

CGameMain::~CGameMain(void)
{
}

void CGameMain::Initialize(SCENE_ID scene_id)
{
	auto& field = CFieldManager::GetInstance();

	field.Initialize();
	field.Create(vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - field.GetBlockSize() * field.GetBlockMaxWidth() / 2.0f, 200.0f), FIELD_ID::NORMAL);
}

void CGameMain::Update()
{
	auto& field = CFieldManager::GetInstance(); 
	auto& scene = CSceneManager::GetInstance();

	field.Update();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
		scene.ChangeScene(SCENE_ID::TITLE);
}

void CGameMain::Draw()
{
	auto& field = CFieldManager::GetInstance();

	field.Draw();
	vivid::DrawText(30, "ÉÅÉCÉìâÊñ ", vivid::Vector2::ZERO);
}

void CGameMain::Finalize()
{
	auto& field = CFieldManager::GetInstance();

	field.Finalize();
}
