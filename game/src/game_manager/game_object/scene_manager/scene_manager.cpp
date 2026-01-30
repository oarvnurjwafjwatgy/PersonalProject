#include "scene_manager.h"
#include "scene/scene_id.h"
#include "scene/gamemain/gamemain.h"
#include "scene/title/title.h"
#include "scene/result/result.h"


CSceneManager& CSceneManager::GetInstance(void)
{
	static CSceneManager instance;

	return instance;
}

void CSceneManager::Initialize(void)
{
	//リストが空か
	//if (m_SceneList.empty()) return; // empty() でもOK

	CreateScene(SCENE_ID::TITLE);

	SCENE_LIST::iterator it = m_SceneList.begin();
	while (it != m_SceneList.end())
	{
		(*it)->Initialize(m_CurrentSceneID); // ← Initialize() を呼び出す

		++it;
	}
}

void CSceneManager::Update(void)
{
	if (m_SceneList.empty()) return;

	// リストの全シーンを更新
	auto it = m_SceneList.begin();
	while (it != m_SceneList.end())
	{
		(*it)->Update();

		if (!(*it)->GetActive())
		{
			(*it)->Finalize();

			it = m_SceneList.erase(it);

			continue;
		}

		++it;
	}

	//シーンの更新があれば更新
	if (m_ChangeScene)
	{
		SceneChange();
		// シーン切り替えフラグの初期化
		m_ChangeScene = false;
	}
}

void CSceneManager::Draw(void)
{
	//リストが空か
	if (m_SceneList.empty()) return;

	SCENE_LIST::iterator it = m_SceneList.begin();

	while (it != m_SceneList.end())
	{
		(*it)->Draw();

		++it;
	}
}


void CSceneManager::Finalize(void)
{
	//リストが空か
	if (m_SceneList.empty()) return;

	SCENE_LIST::iterator it = m_SceneList.begin();

	while (it != m_SceneList.end())
	{
		(*it)->Finalize();

		it = m_SceneList.erase(it);

		continue;
	}

	m_SceneList.clear();

	
}

void CSceneManager::ChangeScene(SCENE_ID id)
{
	 m_NextSceneID = id;
	 m_ChangeScene = true; 
}

CSceneManager::CSceneManager(void)
	:m_CurrentSceneID(SCENE_ID::DUMMY)
	,m_NextSceneID(SCENE_ID::DUMMY)
	,m_SceneList()
{
}


std::shared_ptr<IScene> CSceneManager::CreateScene(SCENE_ID id)
{
	std::shared_ptr<IScene> scene = nullptr;

	switch (id)
	{
	case SCENE_ID::DUMMY: scene = std::make_shared<IScene>();
		break;
	case SCENE_ID::GAME_MAIN: scene = std::make_shared<CGameMain>();
		break;
	case SCENE_ID::TITLE: scene = std::make_shared<CTitle>();
		break;
	case SCENE_ID::RESULT: scene = std::make_shared<CResult>();
		break;
	}
	m_SceneList.emplace_back(scene);

	scene->Initialize(id);

	return scene;
}

void CSceneManager::SceneChange()
{
	if (!m_SceneList.empty())
	{
		SCENE_LIST::iterator it = m_SceneList.begin();
		while (it != m_SceneList.end())
		{
			std::shared_ptr<IScene> scene = *it;

			scene->Finalize();

			it = m_SceneList.erase(it);

			scene = nullptr;
		};
	}
	// 新しいシーン生成
	CreateScene(m_NextSceneID);

	m_CurrentSceneID = m_NextSceneID;
}
