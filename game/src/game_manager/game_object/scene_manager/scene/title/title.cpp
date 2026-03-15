#include "title.h"
#include "../../scene_manager.h"
#include "../../../input_manager/input_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"

auto& TitleSound = CSoundManager::GetInstance();

const int   CTitle::m_change_volume = 100;
const vivid::Vector2 CTitle::m_title_rogo_position = { 430.0f, 0.0f };
const vivid::Vector2 CTitle::m_push_button_position = { 700.0f, 860.0f };
const float CTitle::m_flash_speed = 0.07f;
const int   CTitle::m_flash_base_alpha = 190;
const int   CTitle::m_flash_amplitude = 65;
const int   CTitle::m_bit_shift_bite = 24;
const unsigned  int   CTitle::m_color_white = 0x00ffffff;


CTitle::CTitle(void)
{
}

CTitle::~CTitle(void)
{
}

void CTitle::Initialize(SCENE_ID scene_id)
{
    TitleSound.Load(BGMSOUND_ID::TITLE);
    TitleSound.ChangeBGMVolume(BGMSOUND_ID::TITLE, m_change_volume);
    TitleSound.Play(BGMSOUND_ID::TITLE);

   
}

void CTitle::Update()
{
	auto& input = CInputManager::GetInstance();
	auto& scene = CSceneManager::GetInstance();


    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE) || input.InputAnyKey(PLAYER_ID::PLAYER1))
    {
        TitleSound.Play(SESOUND_ID::TITLEBUTTON);
		scene.ChangeScene(SCENE_ID::GAME_MAIN);
    }
}

void CTitle::Draw()
{
    // îwåiï`âÊ
    vivid::DrawTexture("data\\title_back.png", vivid::Vector2::ZERO);

    // ÉçÉSï`âÊ
    vivid::DrawTexture("data\\title_rogo.png", m_title_rogo_position);

    // ì_ñ≈åvéZ
    static float flashTimer = 0.0f;
    flashTimer += m_flash_speed;

    // ìßñæìxÇÃåvéZ
    unsigned int alpha = (unsigned int)(m_flash_base_alpha + sinf(flashTimer) * m_flash_amplitude);
    unsigned int color = (alpha << m_bit_shift_bite) | m_color_white;

    // É{É^Éìï`âÊ
    vivid::DrawTexture("data\\push_button.png", m_push_button_position, color);
}

void CTitle::Finalize()
{
	IScene::Finalize();
    TitleSound.Stop(BGMSOUND_ID::TITLE);
}
