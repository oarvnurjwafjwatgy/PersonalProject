#pragma once

#pragma once
#include "vivid.h"
#include "../ui.h"

class CResult_text :public IUI
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CResult_text(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CResult_text(void);

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

	void Finalize(void) override;



private:

	vivid::Vector2 m_Position;  //!< 位置


};