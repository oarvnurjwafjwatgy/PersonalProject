#include "effect_manager.h"
#include "effect/effect.h"
#include "effect/vanish/vanish.h"
#include <memory>

CEffectManager& CEffectManager::GetInstance(void)
{
	static CEffectManager instance;

	return instance;
}

void CEffectManager::Initialize(void)
{
	// リストの初期化
	m_EffetList.clear();
}

void CEffectManager::Update(void)
{
	// リストが空だったら処理しない
	if (m_EffetList.empty())	return;

	EFFECT_LIST::iterator it = m_EffetList.begin();

	while (it != m_EffetList.end())
	{
		std::shared_ptr<IEffect> effect = *it;

		effect->Update();

		++it;
	}
}

void CEffectManager::Draw(void)
{
	// リストが空だったら処理しない
	if (m_EffetList.empty())	return;

	EFFECT_LIST::iterator it = m_EffetList.begin();

	while (it != m_EffetList.end())
	{
		std::shared_ptr<IEffect> effect = *it;

		effect->Draw();

		++it;
	}
}

void CEffectManager::Finalize(void)
{
	// リストが空だったら処理しない
	if (m_EffetList.empty())	return;

	EFFECT_LIST::iterator it = m_EffetList.begin();

	while (it != m_EffetList.end())
	{
		(*it)->Finalize();

		++it;
	}

	m_EffetList.clear();
}

std::shared_ptr<IEffect> CEffectManager::Create(EFFECT_ID effect_id, const vivid::Vector2& position)
{
	std::shared_ptr<IEffect> effect = CreateClass(effect_id);

	if (!effect) return nullptr;

	effect->Initialize(position);
	m_EffetList.emplace_back(effect);

	return effect;
}

void CEffectManager::Delete(EFFECT_ID id)
{
	if (m_EffetList.empty()) return;

	EFFECT_LIST::iterator it = m_EffetList.begin();

	while (it != m_EffetList.end())
	{
		std::shared_ptr<IEffect> effect = (*it);

		if (effect->GetEffect_ID() == id)
		{
			effect->Delete();
		}

		++it;
	}
}

std::shared_ptr<IEffect> CEffectManager::CreateClass(EFFECT_ID id)
{
	std::shared_ptr<IEffect> effect = nullptr;

	switch (id)
	{
	case EFFECT_ID::VANISH: effect = std::make_shared<CVanish>(); break;
	}
	return effect;
}
