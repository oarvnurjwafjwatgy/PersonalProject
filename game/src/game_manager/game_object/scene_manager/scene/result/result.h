#pragma once

#include "vivid.h"
#include "../scene.h"
#include "../../scene_manager.h"
#include "../../../ui_manager/ui/score_text/score_text.h"

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
	void Initialize(SCENE_ID scene_id) override;

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
	 */
	void GetResultScore(int score);


private:

	int m_ResultScore;			//!< スコアの結果

	std::weak_ptr<CScoreText>		m_ScoreTextUI;				//!< スコアテキストUI
};

