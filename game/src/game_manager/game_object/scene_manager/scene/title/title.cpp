#include "title.h"
#include "../../scene_manager.h"
#include "../../../input_manager/input_manager.h"

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
	auto& input = CInputManager::GetInstance();
	auto& scene = CSceneManager::GetInstance();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE)|| input.InputAnyKey(PLAYER_ID::PLAYER1))
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
