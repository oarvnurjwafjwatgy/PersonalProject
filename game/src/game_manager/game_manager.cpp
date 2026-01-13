#include "game_manager.h"
#include "game_object/scene_manager/scene_manager.h"


CGameManager& CGameManager::GetInstance(void)
{
	static CGameManager instance;

	return instance;
}

void CGameManager::Initialize(void)
{
	auto& scene = CSceneManager::GetInstance();

	//シーンマネージャー初期化
	scene.Initialize();
}

void CGameManager::Update(void)
{
	auto& scene = CSceneManager::GetInstance();

	//シーンマネージャー初期化
	scene.Update();
}

void CGameManager::Draw(void)
{
	auto& scene = CSceneManager::GetInstance();

	//シーンマネージャー初期化
	scene.Draw();
}

void CGameManager::Finalize(void)
{
	auto& scene = CSceneManager::GetInstance();

	//シーンマネージャー初期化
	scene.Finalize();
}

CGameManager::CGameManager(void)
{
}

CGameManager::CGameManager(const CGameManager& rhs)
{
}

CGameManager::~CGameManager(void)
{
}

CGameManager& CGameManager::operator=(const CGameManager& rhs)
{
	(void)rhs;
	return *this;
}
