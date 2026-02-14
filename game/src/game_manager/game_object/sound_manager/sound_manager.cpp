#include "sound_manager.h"
#include "vivid.h"
#include <fstream>
#include <iostream>


const char* CSoundManager::m_bgm_fill_name[] =
{
	"data\\Sound\\BGM\\Title.mp3",

};

const char* CSoundManager::m_se_fill_name[] =
{
"data\\Sound\\SE\\decision_result.mp3",
"data\\Sound\\SE\\dram_result.mp3",
"data\\Sound\\SE\\Finish.mp3",
"data\\Sound\\SE\\GameStart.mp3",
"data\\Sound\\SE\\TitleBuuton.mp3",
"data\\Sound\\SE\\Vanish.mp3",

};


CSoundManager& CSoundManager::GetInstance(void)
{
	static CSoundManager instance;
	return instance;
}

void CSoundManager::Load(BGMSOUND_ID id)
{
	vivid::LoadSound(m_bgm_fill_name[(int)id]);
}

void CSoundManager::Load()
{
	for (int i = 0; i < (int)SESOUND_ID::SEMAX; i++)
	{
		vivid::LoadSound(m_se_fill_name[i]);
	}
}

void CSoundManager::Play(BGMSOUND_ID id, bool loop)
{
	vivid::PlaySound(m_bgm_fill_name[(int)id],loop);
}

void CSoundManager::Stop(BGMSOUND_ID id)
{
	vivid::StopSound(m_bgm_fill_name[(int)id]);
}

void CSoundManager::Play(SESOUND_ID id, bool loop)
{
	vivid::PlaySound(m_se_fill_name[(int)id], loop);
}

void CSoundManager::Stop(SESOUND_ID id)
{
	vivid::StopSound(m_se_fill_name[(int)id]);
}

void CSoundManager::ChangeBGMVolume(BGMSOUND_ID id, int volume)
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
