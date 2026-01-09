#include "gamemain.h"
#include "../../../field_manager/field_manager.h"

CGameMain::CGameMain(void)
{
}

CGameMain::~CGameMain(void)
{
}

void CGameMain::Initialize(SCENE_ID scene_id)
{
	CFieldManager::GetInstance().Initialize();
	CFieldManager::GetInstance().Create(vivid::Vector2(100.0f, 100.0f), FIELD_ID::NORMAL);
}

void CGameMain::Update()
{
	CFieldManager::GetInstance().Update();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
}

void CGameMain::Draw()
{
	CFieldManager::GetInstance().Draw();
	vivid::DrawText(30, "ÉÅÉCÉìâÊñ ", vivid::Vector2::ZERO);
}

void CGameMain::Finalize()
{
	CFieldManager::GetInstance().Finalize();
}
