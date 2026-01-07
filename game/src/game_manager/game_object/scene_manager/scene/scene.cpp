
#include "scene.h"
#include "scene_id.h"

IScene::IScene(void)
{
}

IScene::~IScene(void)
{
}

void IScene::Initialize(SCENE_ID scene_id)
{
	m_SceneID = scene_id;
}

void IScene::Update(void)
{
}

void IScene::Draw(void)
{

}

void IScene::Finalize(void)
{
	m_ActiveFlag = false;
}

bool IScene::GetActive(void)
{
	return  m_ActiveFlag;
}
