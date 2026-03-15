#include "result.h"
#include "../../../input_manager/input_manager.h"
#include "../../../score_manager/score_manager.h"
#include "../../../sound_manager/sound_manager.h"


auto& ResultSound = CSoundManager::GetInstance();

const int CResult::m_change_volume = 100;
const vivid::Vector2 CResult::m_score_text = { 700,500 };
const vivid::Vector2 CResult::m_result_text = { 600,400 };


CResult::CResult(void)
	: m_ResultScore(0)
{
}

// èâä˙âª
void CResult::Initialize(SCENE_ID scene_id)
{
	
	auto& ui = CUIManager::GetInstance();

	ResultSound.Load(BGMSOUND_ID::RESULT);
	ResultSound.ChangeBGMVolume(BGMSOUND_ID::RESULT, m_change_volume);
	ResultSound.Play(BGMSOUND_ID::RESULT);



	auto score_text_ui = ui.Create(UI_ID::SCORE_TEXT, m_score_text);

	m_ScoreTextUI = std::dynamic_pointer_cast<CScoreText>(score_text_ui);

	m_ResultScore = CScoreManager::GetInstance().GetScore();

	ui.Create(UI_ID::RESULT_TEXT, m_result_text);

	if (!m_ScoreTextUI.expired())
		m_ScoreTextUI.lock()->SetCurrentScore(m_ResultScore);

}

// çXêV
void CResult::Update()
{
	auto& scene = CSceneManager::GetInstance();
	auto& input = CInputManager::GetInstance();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE) || input.GetKey(PLAYER_ID::PLAYER1,BUTTON_ID::A,GET_KEY_MODE::TRIGGER))
		scene.ChangeScene(SCENE_ID::TITLE);


}

// ï`âÊ
void CResult::Draw()
{
	vivid::DrawTexture("data\\title_back.png", vivid::Vector2::ZERO);
}

// âï˙
void CResult::Finalize()
{
	auto& ui = CUIManager::GetInstance();
	ResultSound.Stop(BGMSOUND_ID::RESULT);
	ui.Finalize();
}

void CResult::GetResultScore(int score)
{
	m_ResultScore = score;
}
