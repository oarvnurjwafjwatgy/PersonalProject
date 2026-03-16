#include "scene.h"
#include "scene_id.h"

IScene::IScene(void)
{
}

IScene::~IScene(void)
{
}

void IScene::Initialize()
{
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
