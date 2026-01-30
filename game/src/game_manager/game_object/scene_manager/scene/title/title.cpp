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

	auto& scene = CSceneManager::GetInstance();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
		scene.ChangeScene(SCENE_ID::GAME_MAIN);
}

void CTitle::Draw()
{
	vivid::DrawText(30, "ƒ^ƒCƒgƒ‹‰æ–Ê", vivid::Vector2::ZERO);
}

void CTitle::Finalize()
{
	IScene::Finalize();
}
