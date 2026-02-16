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

	/*!
	 *  @brief      解放
	 */
	void Finalize(void) override;



private:

	vivid::Vector2 m_Position;  //!< 位置

	float m_Scale;      // 現在の拡大率
	float m_Alpha;      // 現在の不透明度
	int   m_FrameCount; // 演出開始からの経過フレーム
};