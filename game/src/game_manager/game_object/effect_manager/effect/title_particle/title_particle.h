#pragma once
#include "vivid.h"
#include "../effect.h"



class CTitleParticle :public IEffect
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CTitleParticle(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CTitleParticle(void);

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

private:

	vivid::Vector2 m_BasePosition; //!< 基準となる中心位置
	float m_Timer;                 //!< 往復運動を計算するための時間
}; 
