#pragma once
#include "vivid.h"
#include "../ui.h"


/*!
 *	@brief		ゲーム中に表示されるフィニッシュの文字のUIクラス
 */

class CFinish :public IUI
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CFinish(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CFinish(void);

	/*!
	 *  @brief      初期化
	 */
	void Initialize(const vivid::Vector2& position) override;

	/*!
	 *  @brief      更新
	 */
	void Update(void) override;

	/*!
	 *  @brief      描画
	 */
	void Draw(void) override;

	/*!
	 *  @brief      解放
	 */
	void Finalize(void) override;

private:
	vivid::Vector2 m_Position;  //!< 「FINISH」という文字の位置

};