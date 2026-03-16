#include "sound_manager.h"
#include "vivid.h"
#include <fstream>
#include <iostream>


const char* CSoundManager::m_bgm_fill_name[] =
{
	"data\\Sound\\BGM\\title.mp3",
	"data\\Sound\\BGM\\main.mp3",
	"data\\Sound\\BGM\\result.mp3",
};

const char* CSoundManager::m_se_fill_name[] =
{
"data\\Sound\\SE\\decision_result.mp3",
"data\\Sound\\SE\\dram_result.mp3",
"data\\Sound\\SE\\finish.mp3",
"data\\Sound\\SE\\game_start.mp3",
"data\\Sound\\SE\\title_button.mp3",
"data\\Sound\\SE\\vanish.mp3",
"data\\Sound\\SE\\fall.mp3",
"data\\Sound\\SE\\cursor_move.mp3",
"data\\Sound\\SE\\block_change.mp3",
};


CSoundManager& CSoundManager::GetInstance(void)
{
	static CSoundManager instance;
	return instance;
}

void CSoundManager::Load(BGM_ID id)
{
	vivid::LoadSound(m_bgm_fill_name[(int)id]);
}

void CSoundManager::Load()
{
	for (int i = 0; i < (int)SE_ID::SEMAX; i++)
	{
		vivid::LoadSound(m_se_fill_name[i]);
	}
}

void CSoundManager::Play(BGM_ID id)
{
	vivid::PlaySound(m_bgm_fill_name[(int)id],true);
}

void CSoundManager::Stop(BGM_ID id)
{
	vivid::StopSound(m_bgm_fill_name[(int)id]);
}

void CSoundManager::Play(SE_ID id)
{
	vivid::PlaySound(m_se_fill_name[(int)id], false);
}

void CSoundManager::Stop(SE_ID id)
{
	vivid::StopSound(m_se_fill_name[(int)id]);
}

void CSoundManager::ChangeBGMVolume(BGM_ID id, int volume)
{
	vivid::SetSoundVolume(m_bgm_fill_name[(int)id], volume);
}

CSoundManager::CSoundManager(void)
{
}

CSoundManager::CSoundManager(const CSoundManager& rhs)
{
	(void)rhs;
}

CSoundManager::~CSoundManager(void)
{
}

CSoundManager& CSoundManager::operator=(const CSoundManager& rhs)
{
	(void)rhs;
	return *this;
}
