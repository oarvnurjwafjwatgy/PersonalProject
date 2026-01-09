#include "game_manager.h"
#include "game_object/scene_manager/scene_manager.h"


CGameManager& CGameManager::GetInstance(void)
{
	static CGameManager instance;

	return instance;
}

void CGameManager::Initialize(void)
{
	//シーンマネージャー初期化
	CSceneManager::GetInstance().Initialize();
}

void CGameManager::Update(void)
{
	//シーンマネージャー初期化
	CSceneManager::GetInstance().Update();
}

void CGameManager::Draw(void)
{
	//シーンマネージャー初期化
	CSceneManager::GetInstance().Draw();
}

void CGameManager::Finalize(void)
{
	//シーンマネージャー初期化
	CSceneManager::GetInstance().Finalize();
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
