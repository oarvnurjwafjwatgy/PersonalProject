#include "game_manager.h"
#include "game_object/scene_manager/scene_manager.h"
#include "game_object/ui_manager/ui_manager.h"
#include "game_object/input_manager/input_manager.h"
#include "game_object/effect_manager/effect_manager.h"


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
	auto& effect = CEffectManager::GetInstance();

	

	// UIマネージャー初期化
	ui.Initialize();

	// エフェクトマネージャー初期化
	effect.Initialize();

	// inputマネージャー初期化
	input.Initialize();

	// 1Pしかないのでここで登録
	input.EntryDevice(PLAYER_ID::PLAYER1, PLAYER_ID::PLAYER1);

	// シーンマネージャー初期化
	scene.Initialize();
}

void CGameManager::Update(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& input = CInputManager::GetInstance();
	auto& effect = CEffectManager::GetInstance();
	

	//シーンマネージャー更新
	scene.Update();

	// エフェクトマネージャー更新
	effect.Update();

	// inputの更新はなるべく後ろで呼ぶ
	input.Update();

}

void CGameManager::Draw(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	//シーンマネージャー描画
	scene.Draw();

	// UIマネージャー描画
	ui.Draw();

	
}

void CGameManager::Finalize(void)
{
	auto& scene = CSceneManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& input = CInputManager::GetInstance();	
	auto& effect = CEffectManager::GetInstance();


	//シーンマネージャー解放
	scene.Finalize();

	// UIマネージャー解放
	ui.Finalize();

	// エフェクトマネージャー解放
	effect.Finalize();

	// Inputマネージャー解放
	input.Finalize();
}
