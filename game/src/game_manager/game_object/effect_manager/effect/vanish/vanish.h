#pragma once
#include "vivid.h"
#include "../effect.h"

/*!
 *	@brief		ブロックが消えた際のエフェクト
 */

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
	void Initialize(const vivid::Vector2& position, EFFECT_ID id) override;

	/*!
	 *  @brief      更新
	 */
	void Update(void) override;

	/*!
	 *  @brief      描画
	 */
	void Draw(void) override;

private:
	static const float m_speed;			//!< 速さ
	static const float m_fade_value;	//!< エフェクトのフェードしていく最大時間

	struct Particle 
	{
		vivid::Vector2 position;
		vivid::Vector2 velocity;
	};

	std::vector<Particle> m_Particles; // 複数の粒子を格納するリスト
	float m_AlphaValue;                // 透明度管理用 (0.0f ～ 1.0f)

};