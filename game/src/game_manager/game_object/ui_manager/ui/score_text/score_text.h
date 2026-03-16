#pragma once
#include "../ui.h"
#include "../../ui_manager.h"
#include <vector>
#include <string>

//!< スコア一つ分のデータ
struct ScoreLog
{
	int value;		//!< 加算されたスコア
	float timer;	//!< 残り時間
	float alpha;	//!< 透明度
};

/*!
 *	@brief		ゲーム中に表示されるスコアテキストのUIクラス
 */
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

	/*!
	 *  @brief      スコア履歴を追加する関数
	 */
	void AddScoreLog(int score);

	/*!
	 *  @brief      リザルトでのスコアアニメーション関数
	 */
	void StartResultAnimation();

	/*!
	 * @brief  演出アニメーションが終了したかどうかを取得
	 * @return true:終了 false:演出中
	 */
	bool IsAnimationFinished(void);

private:
	static const int m_number_digit_width;		//!< 数字一桁の横幅
	static const int m_number_digit_height;		//!< 数字一桁の高さ
	static const unsigned int m_number_color;	//!< 初期数字の色
	static const int m_digit_max = 6;			//!< 桁数
	static const float m_display_max_time;		//!< スコア履歴が表示されてから消えるまでの時間
	static const float m_digit_interval;		//!< 1つの桁が確定するまでの時間（例：0.5秒）

	bool  m_IsResultMode = false;				//!< リザルト演出中か
	float m_ResultTimer = 0.0f;					//!< 演出開始からの経過時間
	int   m_ConfirmedDigits = 0;				//!< 確定した桁数（右から数える）
	unsigned int m_Color;						//!< 数字の色
	int m_CurrentScore;							//!< 今のスコア
	vivid::Vector2 m_position;					//!< スコアテキストの位置
	vivid::Rect	m_Rect[m_digit_max];			//!< 各桁の数字を画像から切り出すための表示範囲
	std::vector<ScoreLog> m_ScoreLogs;			//!< スコア履歴を格納する動的配列
};