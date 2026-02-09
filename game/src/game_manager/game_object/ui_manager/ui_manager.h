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
	 * 
	 *  @param[in] id UIのID
	 *  @param[in] position UIの位置
	 */
	std::shared_ptr<IUI>  Create( UI_ID ui_id, const vivid::Vector2& position);

	/*!
	 *  @brief      UIの削除
	 *
	 *  @param[in] id UIのID
	 */
	void	Delete(UI_ID id);


private:

	/*!
	 *  @brief      UIのクラスを制作
	 * 
	 *  @param[in] id UIのID
	 */
	std::shared_ptr<IUI>  CreateClass(UI_ID id);


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
