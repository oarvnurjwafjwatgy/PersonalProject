//UI管理
#pragma once

#include "vivid.h"

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

private:

	/*!
	 *  @brief      コンストラクタ
	 */
	CUIManager(void);

	/*!
	 *  @brief      コピーコンストラクタ
	 */
	CUIManager(const CUIManager& rhs);


	/*!
	 *  @brief      デストラクタ
	 */
	~CUIManager(void);

	/*!
	 *  @brief      代入演算子
	 */
	CUIManager& operator= (const CUIManager& rhs);

};
