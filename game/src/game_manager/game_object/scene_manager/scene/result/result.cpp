#include "result.h"



CResult::CResult(void)
{
}

void CResult::Initialize(SCENE_ID scene_id)
{
}

void CResult::Update()
{
	auto& scene = CSceneManager::GetInstance();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
		scene.ChangeScene(SCENE_ID::TITLE);
}

void CResult::Draw()
{
	vivid::DrawText(30, "ƒŠƒUƒ‹ƒg", vivid::Vector2::ZERO);
}

void CResult::Finalize()
{
}
