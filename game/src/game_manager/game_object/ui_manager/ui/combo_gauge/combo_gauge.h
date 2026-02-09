#pragma once
#include "vivid.h"
#include "../ui.h"

class CComboGauge :public IUI
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CComboGauge(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CComboGauge(void);

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
	 *  @brief      現在の値の設定
	 */
	void SetValue(int max_value, int value);

private:
	 
	static const int m_combo_max_gauge;		//!< コンボゲージ最大値
	static const int m_bar_width;			//!< バーの幅
	static const int m_bar_height;			//!< バーの高さ
	static const int m_bar_flame_width;		//!< バーの枠の幅
	static const int m_bar_flame_height;	//!< バーの枠の高さ
	static const vivid::Rect m_bar_rect;	//!< バーの初期化
	static const unsigned int m_bar_gauge_color;	//!< ゲージの初期の色

	vivid::Rect m_Rect;						//!< 現在の読み込み範囲
	vivid::Vector2 m_BarPosition;			//!< バーの位置
	vivid::Vector2 m_BarFlamePosition;		//!< バーの枠の位置
	unsigned int m_BarColor;



};