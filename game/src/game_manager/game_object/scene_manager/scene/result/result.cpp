#include "result.h"
#include "../../../input_manager/input_manager.h"
#include "../../../score_manager/score_manager.h"
#include "../../../sound_manager/sound_manager.h"


auto& ResultSound = CSoundManager::GetInstance();


CResult::CResult(void)
	: m_ResultScore(0)
{
}

void CResult::Initialize(SCENE_ID scene_id)
{
	auto& ui = CUIManager::GetInstance();

	ResultSound.Load(BGMSOUND_ID::RESULT);
	ResultSound.ChangeBGMVolume(BGMSOUND_ID::RESULT, 100);
	ResultSound.Play(BGMSOUND_ID::RESULT);



	auto score_text_ui = ui.Create(UI_ID::SCORE_TEXT, vivid::Vector2{ 300,200 });

	m_ScoreTextUI = std::dynamic_pointer_cast<CScoreText>(score_text_ui);

	m_ResultScore = CScoreManager::GetInstance().GetScore();

	ui.Create(UI_ID::RESULT_TEXT, { 500,100 });

	if (!m_ScoreTextUI.expired())
		m_ScoreTextUI.lock()->SetCurrentScore(m_ResultScore);

}

void CResult::Update()
{
	auto& scene = CSceneManager::GetInstance();
	auto& input = CInputManager::GetInstance();

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE) || input.GetKey(PLAYER_ID::PLAYER1,BUTTON_ID::A,GET_KEY_MODE::TRIGGER))
		scene.ChangeScene(SCENE_ID::TITLE);


}

void CResult::Draw()
{
	vivid::DrawText(30, "ƒŠƒUƒ‹ƒg", vivid::Vector2::ZERO);

	vivid::DrawTexture("data\\titleback.png", { 0.0f,0.0f });


}

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
