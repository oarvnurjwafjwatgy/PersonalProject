#include "game_manager.h"
#include "game_object/scene_manager/scene_manager.h"
#include "game_object/ui_manager/ui_manager.h"
#include "game_object/input_manager/input_manager.h"


CGameManager& CGameManager::GetInstance(void)
{
	static CGameManager instance;

	return instance;
}

void CGameManager::Initialize(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& input = CInputManager::GetInstance();

	// シーンマネージャー初期化
	scene.Initialize();

	// UIマネージャー初期化
	ui.Initialize();

	// inputマネージャー初期化
	input.Initialize();

	// 1Pしかないのでここで登録
	input.EntryDevice(PLAYER_ID::PLAYER1, PLAYER_ID::PLAYER1);
}

void CGameManager::Update(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& input = CInputManager::GetInstance();
	

	//シーンマネージャー更新
	scene.Update();

	// inputの更新はなるべく後ろで呼ぶ
	input.Update();

}

void CGameManager::Draw(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	//シーンマネージャー描画
	scene.Draw();

	ui.Draw();
	
}

void CGameManager::Finalize(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& input = CInputManager::GetInstance();


	//シーンマネージャー解放
	scene.Finalize();
	ui.Finalize();
	input.Finalize();
}
