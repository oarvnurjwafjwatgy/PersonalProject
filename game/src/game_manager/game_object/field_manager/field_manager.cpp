#include "field_manager.h"
#include "field/normal_field/normal_field.h"

CFieldManager& CFieldManager::GetInstance(void)
{
	static CFieldManager instance;

	return instance;
}

void CFieldManager::Initialize(void)
{
	// リストの初期化
	m_FieldList.clear();
}

void CFieldManager::Update(void)
{
	// リストが空だったら処理しない
	if (m_FieldList.empty())	return;

	FIELD_LIST::iterator it = m_FieldList.begin();
	
	while (it != m_FieldList.end())
	{
		std::shared_ptr<IField> field = *it;

		field->Update();

		++it;
	}
}

void CFieldManager::Draw(void)
{
	// リストが空だったら処理しない
	if (m_FieldList.empty())	return;

	FIELD_LIST::iterator it = m_FieldList.begin();

	while (it != m_FieldList.end())
	{
		std::shared_ptr<IField> field = *it;

		field->Draw();

		++it;
	}
}

void CFieldManager::Finalize(void)
{
	// リストが空だったら処理しない
	if (m_FieldList.empty())	return;

	FIELD_LIST::iterator it = m_FieldList.begin();


	while (it != m_FieldList.end())
	{
		(*it)->Finalize();
		++it;
	}

	m_FieldList.clear();
}

void CFieldManager::Create(const vivid::Vector2& position, FIELD_ID field_id)
{
	std::shared_ptr<IField> field = nullptr;

	//ID
	switch (field_id)
	{
	case FIELD_ID::NORMAL:	field = std::make_shared <CNormalField>(); break;
	}

	if (!field) return;

	field->Initialize(position, field_id);

	m_FieldList.emplace_back(field);
}

CFieldManager::CFieldManager(void)
{
}

CFieldManager::CFieldManager(const CFieldManager& rhs)
{
}

CFieldManager::~CFieldManager(void)
{
}

CFieldManager& CFieldManager::operator=(const CFieldManager& rhs)
{
	(void)rhs;

	return *this;
}
