#include "gamemain.h"

CGameMain::CGameMain(void)
{
}

CGameMain::~CGameMain(void)
{
}

void CGameMain::Initialize(SCENE_ID scene_id)
{
}

void CGameMain::Update()
{
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
}

void CGameMain::Draw()
{
	vivid::DrawText(30, "ÉÅÉCÉìâÊñ ", vivid::Vector2::ZERO);
}

void CGameMain::Finalize()
{
}
