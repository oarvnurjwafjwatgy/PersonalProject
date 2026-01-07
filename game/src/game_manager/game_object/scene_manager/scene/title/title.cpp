#include "title.h"
#include "../../scene_manager.h"

CTitle::CTitle(void)
{
}

CTitle::~CTitle(void)
{
}

void CTitle::Initialize(SCENE_ID scene_id)
{
}

void CTitle::Update()
{
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
		CSceneManager::GetInstance().ChangeScene(SCENE_ID::GAME_MAIN);
}

void CTitle::Draw()
{
	vivid::DrawText(30, "ƒ^ƒCƒgƒ‹‰æ–Ê", vivid::Vector2::ZERO);
}

void CTitle::Finalize()
{
	IScene::Finalize();
}
