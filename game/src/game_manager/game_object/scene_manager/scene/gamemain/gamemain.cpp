#include "gamemain.h"
#include "../../../field_manager/field_manager.h"
#include "../../../field_manager/field/field.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../score_manager/score_manager.h"

auto& GameMainSound = CSoundManager::GetInstance();


const int CGameMain::m_start_wait_time = 3*60;

CGameMain::CGameMain(void)
	: m_GameState(GAME_STATE::DUMMY)
	, m_State_Wait_Timer(0)
{
}

CGameMain::~CGameMain(void)
{
}

void CGameMain::Initialize(SCENE_ID scene_id)
{
	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& score = CScoreManager::GetInstance();


	GameMainSound.Load(BGMSOUND_ID::TITLE);
	GameMainSound.Play(BGMSOUND_ID::TITLE);
	GameMainSound.Play(SESOUND_ID::GAMESTART);

	field.Initialize();
	score.Initialize();

	field.Create(vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - field.GetBlockSize() * field.GetBlockMaxWidth() / 2.0f, 200.0f), FIELD_ID::NORMAL);

	m_State_Wait_Timer = m_start_wait_time;
	m_GameState = GAME_STATE::START;

	auto& gamestart = ui.Create(UI_ID::GAME_START, { 500,500 });
}

void CGameMain::Update()
{
	
	auto& scene = CSceneManager::GetInstance();


	switch (m_GameState)
	{
	case CGameMain::GAME_STATE::START: Start();		break;
	case CGameMain::GAME_STATE::PLAY: Play(); break;
	case CGameMain::GAME_STATE::FINISH: Finish(); break;
	}


	

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
		scene.ChangeScene(SCENE_ID::RESULT);

	
}

void CGameMain::Draw()
{
	vivid::DrawTexture("data\\backGraund.png", { 0,0 });

	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& effect = CEffectManager::GetInstance();

	field.Draw();
	ui.Draw();
	effect.Draw();
	

	vivid::DrawText(30, "ÉÅÉCÉìâÊñ ", vivid::Vector2::ZERO);

	

}

void CGameMain::Finalize()
{
	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	field.Finalize();
	ui.Finalize();
}

void CGameMain::Start(void)
{
	


	if (m_State_Wait_Timer-- <= 0)
	{
		m_GameState = GAME_STATE::PLAY;

		printfDx("PlayÇ…Ç»Ç¡ÇΩÇÊ\n");
	}


}


void CGameMain::Play(void)
{
	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	field.Update();


	if (field.GetFinishFlag())
	{
		ui.Create(UI_ID::FINISH, { 500,500 });
		m_State_Wait_Timer = m_start_wait_time;
		m_GameState = GAME_STATE::FINISH;

		printfDx("FinishÇ…Ç»Ç¡ÇΩÇÊ\n");
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::K))
	{
		ui.Create(UI_ID::FINISH, { 500,500 });
		m_GameState = GAME_STATE::FINISH;
		m_State_Wait_Timer = m_start_wait_time;
		printfDx("FinishÇ…Ç»Ç¡ÇΩÇÊ\n");
	}
}

void CGameMain::Finish(void)
{
	auto& scene = CSceneManager::GetInstance();
	
	
	
	if (m_State_Wait_Timer-- <= 0)
	{
		scene.ChangeScene(SCENE_ID::RESULT);
	}
	
	
}