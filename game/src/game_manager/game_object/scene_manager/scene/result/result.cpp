#include "result.h"
#include "../../../input_manager/input_manager.h"



CResult::CResult(void)
{
}

void CResult::Initialize(SCENE_ID scene_id)
{
}

void CResult::Update()
{
	auto& scene = CSceneManager::GetInstance();
	auto& input = CInputManager::GetInstance();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE) || input.InputAnyKey(PLAYER_ID::PLAYER1))
		scene.ChangeScene(SCENE_ID::TITLE);
}

void CResult::Draw()
{
	vivid::DrawText(30, "ƒŠƒUƒ‹ƒg", vivid::Vector2::ZERO);
}

void CResult::Finalize()
{
}
