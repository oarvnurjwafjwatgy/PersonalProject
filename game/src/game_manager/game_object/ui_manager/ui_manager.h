//UI管理
#pragma once

#include "vivid.h"
#include "ui/ui_id.h"
#include <list>
#include <memory>

class IUI;

class CUIManager
{
public:
	/*!
	 *  @brief      インスタンスの取得
	 */
	static CUIManager& GetInstance(void);

	/*!
	 *  @brief      初期化
	 */
	void Initialize(void);

	/*!
	 *  @brief      更新
	 */
	void Update(void);

	/*!
	 *  @brief      描画
	 */
	void Draw(void);

	/*!
	 *  @brief      解放
	 */
	void Finalize(void);

	/*!
	 *  @brief      UI生成
	 */
	void Create(const vivid::Vector2& position , UI_ID ui_id);

private:

	/*!
	 *  @brief      コンストラクタ
	 */
	CUIManager(void) = default;

	/*!
	 *  @brief      コピーコンストラクタ
	 */
	CUIManager(const CUIManager& ) = delete;


	/*!
	 *  @brief      デストラクタ
	 */
	~CUIManager(void) = default;

	/*!
	 *  @brief      代入演算子
	 */
	CUIManager& operator= (const CUIManager& ) = delete;


	using UI_LIST = std::list<std::shared_ptr<IUI>>;	// 名前空間の省略を行う
	UI_LIST m_UIList;									//!<  フィールドオブジェクトを入れるリスト(カーソル、ブロック等)
};
