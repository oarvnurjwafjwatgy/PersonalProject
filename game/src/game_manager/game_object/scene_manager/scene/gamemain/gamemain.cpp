#include "gamemain.h"
#include "../../../field_manager/field_manager.h"
#include "../../../field_manager/field/field.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../score_manager/score_manager.h"

auto& GameMainSound = CSoundManager::GetInstance();


const int CGameMain::m_change_volume = 100;
const int CGameMain::m_start_wait_time = 3*60;
const vivid::Vector2 CGameMain::m_ui_center_pos = { 770.0f, 500.0f };
const float CGameMain::m_field_y_offset = 200.0f;

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

	// サウンドの再生とロード
	GameMainSound.Load(BGMSOUND_ID::MAIN);
	GameMainSound.ChangeBGMVolume(BGMSOUND_ID::MAIN, m_change_volume);
	GameMainSound.Play(BGMSOUND_ID::MAIN);
	GameMainSound.Play(SESOUND_ID::GAMESTART);

	// 各マネージャーの初期化
	field.Initialize();
	score.Initialize();

	// フィールドの生成: 画面中央に配置されるよう計算
	field.Create(vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - field.GetBlockSize() * field.GetBlockMaxWidth() / 2.0f, m_field_y_offset), FIELD_ID::NORMAL);

	// 開始待ち状態へ移行
	m_State_Wait_Timer = m_start_wait_time;
	m_GameState = GAME_STATE::START;

	// 「GAME START」のUIを表示
	auto& gamestart = ui.Create(UI_ID::GAME_START, m_ui_center_pos);
}

void CGameMain::Update()
{
	auto& scene = CSceneManager::GetInstance();

	// 現在のゲーム状態（開始前/プレイ中/終了演出）に応じて処理を分岐
	switch (m_GameState)
	{
	case CGameMain::GAME_STATE::START: Start();		break;
	case CGameMain::GAME_STATE::PLAY: Play(); break;
	case CGameMain::GAME_STATE::FINISH: Finish(); break;
	}
}

void CGameMain::Draw()
{
	vivid::DrawTexture("data\\back_graund.png", vivid::Vector2::ZERO);

	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();
	auto& effect = CEffectManager::GetInstance();

	// 各要素の描画
	field.Draw();
	ui.Draw();
	effect.Draw();
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
	// 一定時間待機したらプレイ状態へ移行
	if (m_State_Wait_Timer-- <= 0)
	{
		m_GameState = GAME_STATE::PLAY;
	}
}


void CGameMain::Play(void)
{
	auto& field = CFieldManager::GetInstance();
	auto& ui = CUIManager::GetInstance();

	field.Update();

	// ゲーム終了判定（クリア条件達成、またはデバッグキーK押下）
	if (field.GetFinishFlag())
	{
		ui.Create(UI_ID::FINISH, m_ui_center_pos);
		m_State_Wait_Timer = m_start_wait_time;
		GameMainSound.Play(SESOUND_ID::FINISH);
		m_GameState = GAME_STATE::FINISH;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::K))
	{
		ui.Create(UI_ID::FINISH, m_ui_center_pos);

		m_GameState = GAME_STATE::FINISH;
		m_State_Wait_Timer = m_start_wait_time;
	}
}

void CGameMain::Finish(void)
{
	auto& scene = CSceneManager::GetInstance();
	
	// 終了演出の待機時間が終わったらリザルトシーンへ
	if (m_State_Wait_Timer-- <= 0)
	{
		scene.ChangeScene(SCENE_ID::RESULT);
		GameMainSound.Stop(BGMSOUND_ID::MAIN);
	}
}