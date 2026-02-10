#include "result.h"
#include "../../../input_manager/input_manager.h"
#include "../../../score_manager/score_manager.h"



CResult::CResult(void)
	: m_ResultScore(0)
{
}

void CResult::Initialize(SCENE_ID scene_id)
{

	auto score_text_ui = CUIManager::GetInstance().Create(UI_ID::SCORE_TEXT, vivid::Vector2{ 300,200 });

	m_ScoreTextUI = std::dynamic_pointer_cast<CScoreText>(score_text_ui);

	m_ResultScore = CScoreManager::GetInstance().GetScore();


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

}

void CResult::Finalize()
{
}

void CResult::GetResultScore(int score)
{
	m_ResultScore = score;
}
