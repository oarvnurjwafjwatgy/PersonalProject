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

		// アクティブフラグがfalseの時、リストから削除
		if (!effect->GetActive())
		{
			(*it)->Finalize();

			it = m_EffetList.erase(it);

			continue;
		}

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

std::shared_ptr<IEffect> CEffectManager::Create(const vivid::Vector2& position, EFFECT_ID effect_id, unsigned int color = 0xffffffff)
{
	std::shared_ptr<IEffect> effect = CreateClass(effect_id);

	if (!effect) return nullptr;

	// 初期化の前に色をセットする
	effect->SetColor(color);
	effect->Initialize(position,effect_id);

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
