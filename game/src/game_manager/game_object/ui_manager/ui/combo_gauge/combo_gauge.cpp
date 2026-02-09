#include "combo_gauge.h"

 const int CComboGauge::m_combo_max_gauge = 100;		//!< コンボゲージ最大値
 const int CComboGauge::m_bar_width = 306;		//!< バーの幅
 const int CComboGauge::m_bar_height = 42;		//!< バーの高さ
 const int CComboGauge::m_bar_flame_width = 306;		//!< バーの枠の幅
 const int CComboGauge::m_bar_flame_height = 42;		//!< バーの枠の高さ
 const vivid::Rect CComboGauge::m_bar_rect = {0,0,0,m_bar_height};		//!< バーの初期化
 const unsigned int CComboGauge::m_bar_gauge_color = 0xffffffff;		//!< ゲージの初期の色

CComboGauge::CComboGauge(void)
{
}

CComboGauge::~CComboGauge(void)
{
}

void CComboGauge::Initialize( const vivid::Vector2& position)
{
	m_Rect = m_bar_rect;
	m_BarColor = m_bar_gauge_color;
	m_BarPosition = position;
	m_BarFlamePosition = position;
}

void CComboGauge::Update(void)
{
}

void CComboGauge::Draw(void)
{

	vivid::DrawTexture("data\\bar.png", m_BarPosition,m_BarColor,m_Rect);
}

void CComboGauge::SetValue(int max_value, int value)
{
	m_Rect.right = (int)(((float)value / (float)max_value) * (float)m_bar_width);
}
