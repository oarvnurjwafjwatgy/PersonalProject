#pragma once
#include "vivid.h"
#include "../effect.h"



class CVanish :public IEffect
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CVanish(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CVanish(void);

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

	static const float m_speed;		//!< 速さ
	static const float m_max_fade;	//!< エフェクトのフェードしていく最大時間
	static const int m_max_color_table;		//!< カラーテーブル
	
	vivid::Vector2 m_Velocity;		//!< 加速度
	unsigned	int m_Color;		//!< 色
};