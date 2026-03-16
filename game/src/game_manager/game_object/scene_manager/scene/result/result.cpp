#include "result.h"
#include "../../../input_manager/input_manager.h"
#include "../../../score_manager/score_manager.h"
#include "../../../sound_manager/sound_manager.h"


auto& ResultSound = CSoundManager::GetInstance();
const int CResult::m_change_volume = 100;
const vivid::Vector2 CResult::m_score_text = { 700,500 };
const vivid::Vector2 CResult::m_result_text = { 600,400 };
const vivid::Vector2 CResult::m_push_button_position = { 700.0f, 860.0f };
const float CResult::m_flash_speed = 0.07f;
const int   CResult::m_flash_base_alpha = 190;
const int   CResult::m_flash_amplitude = 65;
const int   CResult::m_bit_shift_bite = 24;
const unsigned  int   CResult::m_color_white = 0x00ffffff;


CResult::CResult(void)
	: m_ResultScore(0)
{
}

// 初期化
void CResult::Initialize()
{
	IScene::Initialize();

	auto& ui = CUIManager::GetInstance();

	ResultSound.Load(BGM_ID::RESULT);
	ResultSound.ChangeBGMVolume(BGM_ID::RESULT, m_change_volume);
	ResultSound.Play(BGM_ID::RESULT);

	auto score_text_ui = ui.Create(m_score_text,UI_ID::SCORE_TEXT);

	m_ScoreTextUI = std::dynamic_pointer_cast<CScoreText>(score_text_ui);

	m_ResultScore = CScoreManager::GetInstance().GetScore();

	ui.Create(m_result_text, UI_ID::RESULT_TEXT);

	if (!m_ScoreTextUI.expired()) {
		auto scoreUI = m_ScoreTextUI.lock();
		scoreUI->SetCurrentScore(m_ResultScore);
		scoreUI->StartResultAnimation();
	}
}

// 更新
void CResult::Update()
{
	auto& scene = CSceneManager::GetInstance();
	auto& input = CInputManager::GetInstance();

	// アニメーションが終わっているかチェック
	bool finish_flag = false;
	if (!m_ScoreTextUI.expired()) {
		finish_flag = m_ScoreTextUI.lock()->IsAnimationFinished();
	}

	// ボタン入力でシーン遷移
	if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE) ||
		input.GetKey(PLAYER_ID::PLAYER1, BUTTON_ID::A, GET_KEY_MODE::TRIGGER)) && finish_flag)

	{
		ResultSound.Play(SE_ID::BUTTON);
		scene.ChangeScene(SCENE_ID::TITLE);
	}
}

// 描画
void CResult::Draw()
{
	vivid::DrawTexture("data\\title_back.png", vivid::Vector2::ZERO);

	// アニメーション終了後のみボタンを表示
	if (!m_ScoreTextUI.expired() && m_ScoreTextUI.lock()->IsAnimationFinished()) {

		// 点滅計算
		static float flashTimer = 0.0f;
		flashTimer += m_flash_speed;

		// 透明度の計算
		unsigned int alpha = (unsigned int)(m_flash_base_alpha + sinf(flashTimer) * m_flash_amplitude);
		unsigned int color = (alpha << m_bit_shift_bite) | m_color_white;

		vivid::DrawTexture("data\\push_button_title.png", m_push_button_position, color);
	}
}

// 解放
void CResult::Finalize()
{
	auto& ui = CUIManager::GetInstance();
	ResultSound.Stop(BGM_ID::RESULT);
	ui.Finalize();
}

void CResult::GetResultScore(int score)
{
	m_ResultScore = score;
}
