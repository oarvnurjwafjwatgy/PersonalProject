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

	int m_CurrentScore;			//!< 今のスコア
	vivid::Vector2 m_position;   //!< 位置

};