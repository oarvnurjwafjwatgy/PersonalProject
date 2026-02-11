#pragma once

#pragma once
#include "vivid.h"
#include "../ui.h"

class CGameStart :public IUI
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CGameStart(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CGameStart(void);

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