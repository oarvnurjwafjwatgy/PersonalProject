#include "sound_manager.h"


const char* CSoundManager::m_bgm_fill_name[] =
{
	
};

const char* CSoundManager::m_se_fill_name[] =
{

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

void CSoundManager::Load(SESOUND_ID id)
{
	vivid::LoadSound(m_se_fill_name[(int)id]);
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
