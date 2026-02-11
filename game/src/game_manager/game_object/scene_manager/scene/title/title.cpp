#include "title.h"
#include "../../scene_manager.h"
#include "../../../input_manager/input_manager.h"
#include "../../../effect_manager/effect_manager.h"

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
    vivid::DrawTexture("data\\titleback.png", { 0, 0 });
    vivid::DrawTexture("data\\TitleRogo.png", { 430, 0 }); // 


    // 時間で 0.0 ～ 1.0 を行き来する値を作る
    static float flashTimer = 0.0f;
    flashTimer += 0.07f; // 点滅スピード

    // 128～255の間でふわふわさせる（真っ暗にならないように）
    unsigned int alpha = (unsigned int)(190 + sinf(flashTimer) * 65);
    unsigned int color = (alpha << 24) | 0x00FFFFFF; // 白色のアルファ値だけ変える

    vivid::DrawTexture("data\\PUSHBUTTON.png", { 700,860 },color);
}

void CTitle::Finalize()
{
	IScene::Finalize();
}
