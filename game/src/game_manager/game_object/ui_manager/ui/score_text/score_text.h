#pragma once
#include "../ui.h"
#include "../../ui_manager.h"



class CScoreText: public IUI
{
public:

	/*
	 *	@brief		コンストラクタ
	 */
	CScoreText(void);

	/*
	 *	@brief		デストラクタ
	 */
	~CScoreText(void);

	/*
	 *	@brief		初期化
	 */
	void Initialize(const vivid::Vector2& position) override;

	/*
	 *	@brief		更新
	 */
	void Update() override;

	/*
	 *	@brief		描画
	 */
	void Draw() override;

	/*
	 *	@brief		解放
	 */
	void Finalize() override;

	/*!
	 *  @brief      現在のスコアの設定
	 */
	void SetCurrentScore(int current_score);

	/*!
	 *  @brief      現在のスコアの取得
	 */
	int GetCurrentScore();

private:

	static const int m_number_digit_width;		//!< 数字一桁の横幅
	static const int m_number_digit_height;		//!< 数字一桁の高さ
	static const unsigned int m_number_color;	//!< 初期数字の色
	static const int m_digit_max = 6;

	unsigned int m_Color;					//!< 数字の色

	int m_CurrentScore;				//!< 今のスコア
	vivid::Vector2 m_position;		//!< 位置

	vivid::Rect	m_Rect[m_digit_max];
	 

};