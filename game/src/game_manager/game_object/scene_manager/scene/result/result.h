#pragma once
#include "vivid.h"
#include "../scene.h"
#include "../../scene_manager.h"
#include "../../../ui_manager/ui/score_text/score_text.h"

/*!
 *	@brief		ゲーム内のリザルトシーンクラス
 */

class CResult : public IScene
{
public:

	/*
	 *	@brief		コンストラクタ
	 */
	CResult(void);

	/*
	 *	@brief		デストラクタ
	 */
	~CResult(void) = default;

	/*
	 *	@brief		初期化
	 */
	void Initialize() override;

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

	/*
	 *	@brief		スコア取得
	 *  @param[in]	score 最終的なスコア
	 */
	void GetResultScore(int score);

private:

	static const int m_change_volume;					//!< BGMの調整
	static const vivid::Vector2 m_score_text;			//!< スコアテキストの位置
	static const vivid::Vector2 m_result_text;			//!< リザルトテキストの位置
	static const vivid::Vector2 m_push_button_position; //!< ボタンの位置
	static const float m_flash_speed;                     //!< 点滅の速さ
	static const int   m_flash_base_alpha;                //!< 透明度のベース値
	static const int   m_flash_amplitude;                 //!< 透明度の振れ幅
	static const int m_bit_shift_bite;					  //!< 色情報のビットシフト量
	static const unsigned int m_color_white;			  //!< ベースとなる色（真っ白）

	int m_ResultScore;									//!< スコアの結果

	std::weak_ptr<CScoreText>	m_ScoreTextUI;			//!< スコアテキストUI

};

