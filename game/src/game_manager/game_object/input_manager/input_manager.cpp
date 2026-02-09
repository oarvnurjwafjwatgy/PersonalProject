#include "input_manager.h"
#include "../scene_manager/scene_manager.h"

const float	CInputManager::m_half_value = 0.5f;
const float	CInputManager::m_quarter_value = 0.25f;
const float	CInputManager::m_stick_once_value = 0.9f;

CInputManager& CInputManager::GetInstance()
{
	static CInputManager instance;
	return instance;
}

void CInputManager::Initialize()
{
	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		m_Device[i] = (PLAYER_ID)i;
		for (int j = 0; j < (int)LR_ID::MAX; j++)
		{
			m_StickOnce[j][i] = false;
			m_CachedStickDir[j][i] = DIRECTION::DUMMY;
		}
	}
}

void CInputManager::Update()
{
	this->CheckStickOnce();

	this->CheckTriggerOnce();

}

void CInputManager::Finalize()
{
}

void CInputManager::EntryDevice(PLAYER_ID player_id, PLAYER_ID device_id)
{
	// 整合性チェック
	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		if (i == (int)player_id)		continue;
		if (m_Device[i] < PLAYER_ID::MAX && m_Device[i] == device_id)	return;
	}

	// デバイスの登録
	m_Device[(int)player_id] = device_id;
}

bool CInputManager::GetEnteredDevice(PLAYER_ID device_id)
{
	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		if (m_Device[i] == device_id)
			return true;
	}
	return false;
}

PLAYER_ID CInputManager::GetEmptyPlayerNum()
{/*		一旦使えない(まだない)ため コメントアウト
	for (int i = 0; i <= (int)SCENE.GetPlayerNum(); i++)
	{
		if (m_Device[i] == DEVICE::MAX)
			return (DEVICE)i;
	}*/
	return PLAYER_ID::MAX;
}

PLAYER_ID CInputManager::GetPlayerDevice(PLAYER_ID player_id)
{
	return m_Device[(int)player_id];
}

PLAYER_ID CInputManager::GetDevicePlayer(PLAYER_ID device_id)
{
	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		if (m_Device[i] == device_id)
			return (PLAYER_ID)i;
	}
	return PLAYER_ID::MAX;
}

bool CInputManager::GetKey(PLAYER_ID player_id, BUTTON_ID button_id, GET_KEY_MODE mode)
{
	vivid::controller::BUTTON_ID	button = (vivid::controller::BUTTON_ID)button_id;

	if (player_id < PLAYER_ID::MAX && player_id >= (PLAYER_ID)0)
	{
		if (mode == GET_KEY_MODE::TRIGGER && vivid::controller::Trigger((vivid::controller::DEVICE_ID)m_Device[(int)player_id], button))
			return true;
		if (mode == GET_KEY_MODE::BUTTON && vivid::controller::Button((vivid::controller::DEVICE_ID)m_Device[(int)player_id], button))
			return true;
		if (mode == GET_KEY_MODE::RELEASED && vivid::controller::Released((vivid::controller::DEVICE_ID)m_Device[(int)player_id], button))
			return true;
	}
	else if (player_id == PLAYER_ID::ALL)
	{
		if (mode == GET_KEY_MODE::TRIGGER
			&& (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, button)
				|| vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, button)
				|| vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER3, button)
				|| vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER4, button)))
			return true;
		if (mode == GET_KEY_MODE::BUTTON
			&& (vivid::controller::Button(vivid::controller::DEVICE_ID::PLAYER1, button)
				|| vivid::controller::Button(vivid::controller::DEVICE_ID::PLAYER2, button)
				|| vivid::controller::Button(vivid::controller::DEVICE_ID::PLAYER3, button)
				|| vivid::controller::Button(vivid::controller::DEVICE_ID::PLAYER4, button)))
			return true;
		if (mode == GET_KEY_MODE::RELEASED
			&& (vivid::controller::Released(vivid::controller::DEVICE_ID::PLAYER1, button)
				|| vivid::controller::Released(vivid::controller::DEVICE_ID::PLAYER2, button)
				|| vivid::controller::Released(vivid::controller::DEVICE_ID::PLAYER3, button)
				|| vivid::controller::Released(vivid::controller::DEVICE_ID::PLAYER4, button)))
			return true;
	}

	return false;
}

bool CInputManager::GetStickOnce(PLAYER_ID player_id, LR_ID lr_id, DIRECTION dir)
{
	bool stick = false;

	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		if (!((PLAYER_ID)i == player_id || player_id == PLAYER_ID::ALL))	continue;
		if (m_StickOnce[i] && dir == m_CachedStickDir[(int)lr_id][i])	continue;

		switch (dir)
		{
		case DIRECTION::UP:
			if (GetStickValue((PLAYER_ID)i, lr_id, XY_ID::Y) < -m_stick_once_value)
			{
				stick = true;
				m_StickOnce[(int)lr_id][i] = true;
				m_CachedStickDir[(int)lr_id][i] = DIRECTION::UP;
			}
			break;
		case DIRECTION::DOWN:
			if (GetStickValue((PLAYER_ID)i, lr_id, XY_ID::Y) > m_stick_once_value)
			{
				stick = true;
				m_StickOnce[(int)lr_id][i] = true;
				m_CachedStickDir[(int)lr_id][i] = DIRECTION::DOWN;
			}
			break;
		case DIRECTION::LEFT:
			if (GetStickValue((PLAYER_ID)i, lr_id, XY_ID::X) < -m_stick_once_value)
			{
				stick = true;
				m_StickOnce[(int)lr_id][i] = true;
				m_CachedStickDir[(int)lr_id][i] = DIRECTION::LEFT;
			}
			break;
		case DIRECTION::RIGHT:
			if (GetStickValue((PLAYER_ID)i, lr_id, XY_ID::X) > m_stick_once_value)
			{
				stick = true;
				m_StickOnce[(int)lr_id][i] = true;
				m_CachedStickDir[(int)lr_id][i] = DIRECTION::RIGHT;
			}
			break;
		}
	}

	return stick;
}

float CInputManager::GetStickValue(PLAYER_ID player_id, LR_ID lr_id, XY_ID xy_id)
{
	if (player_id >= PLAYER_ID::MAX || player_id < (PLAYER_ID)0) return 0.0f;

	if (m_Device[(int)player_id] >= PLAYER_ID::MAX)	return 0.0f;

	vivid::Vector2 value = { 0.0f,0.0f };

	// Lスティック
	if (lr_id == LR_ID::LEFT)
		value = vivid::controller::GetAnalogStickLeft((vivid::controller::DEVICE_ID)m_Device[(int)player_id]);
	// Rスティック
	else
		value = vivid::controller::GetAnalogStickRight((vivid::controller::DEVICE_ID)m_Device[(int)player_id]);

	// 倒す向き
	if (xy_id == XY_ID::X)	return value.x;
	else					return value.y;
}

bool CInputManager::GetAllStickTilt(LR_ID lr_id, DIRECTION dir)
{
	bool tmp = false;

	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		switch (dir)
		{
		case DIRECTION::UP:
			tmp |= (this->GetStickValue((PLAYER_ID)i, lr_id, XY_ID::Y) < -m_quarter_value);	break;
		case DIRECTION::DOWN:
			tmp |= (this->GetStickValue((PLAYER_ID)i, lr_id, XY_ID::Y) > m_quarter_value);	break;
		case DIRECTION::LEFT:
			tmp |= (this->GetStickValue((PLAYER_ID)i, lr_id, XY_ID::X) < -m_quarter_value);	break;
		case DIRECTION::RIGHT:
			tmp |= (this->GetStickValue((PLAYER_ID)i, lr_id, XY_ID::X) > m_quarter_value);	break;
		}
	}
	return tmp;
}

float CInputManager::GetTriggerValue(PLAYER_ID player_id, LR_ID lr_id)
{
	if (player_id >= PLAYER_ID::MAX || player_id < (PLAYER_ID)0) return 0.0f;

	if (m_Device[(int)player_id] >= PLAYER_ID::MAX)	return 0.0f;

	// Lトリガー
	if (lr_id == LR_ID::LEFT)
		return vivid::controller::GetTriggerLeft((vivid::controller::DEVICE_ID)m_Device[(int)player_id]);
	// Rトリガー
	else
		return vivid::controller::GetTriggerRight((vivid::controller::DEVICE_ID)m_Device[(int)player_id]);

}

bool CInputManager::GetTriggerOnce(PLAYER_ID player_id, LR_ID lr_id)
{
	bool trigger = false;

	for (int player = 0; player < (int)PLAYER_ID::MAX; player++)
	{
		if (!((PLAYER_ID)player == player_id || player_id == PLAYER_ID::ALL))	continue;
		if (m_TriggerkOnce[(int)lr_id][player])	continue;

		if (GetTriggerValue((PLAYER_ID)player, lr_id) > m_half_value)
		{
			trigger = true;
			m_TriggerkOnce[(int)lr_id][player] = true;
		}
	}

	return trigger;
}

bool CInputManager::InputAnyKey(PLAYER_ID player_id, bool button, bool stick, bool trigger)
{
	bool	input = false;

	// ALLの時
	if (player_id == PLAYER_ID::ALL)
	{
		// ボタン判定が有効の時
		if (button)
		{
			for (int i = 0; i <= (int)BUTTON_ID::MAX_NUM; i++)
			{
				if (i == 10 || i == 11)	continue;		// 非対応の番号は飛ばす
				input |= GetKey(PLAYER_ID::ALL, (BUTTON_ID)i, GET_KEY_MODE::TRIGGER);
			}
		}

		for (int player = 0; player < (int)PLAYER_ID::MAX; player++)
		{
			// LRスティック判定が有効の時
			if (stick)
			{
				// Lスティック
				input |= ((GetStickValue((PLAYER_ID)player, LR_ID::LEFT, XY_ID::X) > m_half_value)
					|| (GetStickValue((PLAYER_ID)player, LR_ID::LEFT, XY_ID::X) < -m_half_value)
					|| (GetStickValue((PLAYER_ID)player, LR_ID::LEFT, XY_ID::Y) > m_half_value)
					|| (GetStickValue((PLAYER_ID)player, LR_ID::LEFT, XY_ID::Y) < -m_half_value));
				// Rスティック
				input |= ((GetStickValue((PLAYER_ID)player, LR_ID::RIGHT, XY_ID::X) > m_half_value)
					|| (GetStickValue((PLAYER_ID)player, LR_ID::RIGHT, XY_ID::X) < -m_half_value)
					|| (GetStickValue((PLAYER_ID)player, LR_ID::RIGHT, XY_ID::Y) > m_half_value)
					|| (GetStickValue((PLAYER_ID)player, LR_ID::RIGHT, XY_ID::Y) < -m_half_value));
			}

			// LRトリガー判定が有効の時
			if (trigger)
			{
				input |= ((GetTriggerValue((PLAYER_ID)player, LR_ID::LEFT) > m_half_value)
					|| (GetTriggerValue((PLAYER_ID)player, LR_ID::RIGHT) > m_half_value));
			}
		}

	}
	// ALL以外の(player id指定)時
	else
	{
		// ボタン判定が有効の時
		if (button)
		{
			for (int i = 0; i < (int)BUTTON_ID::MAX_NUM; i++)
			{
				if (i == 10 || i == 11)	continue;		// 非対応の番号は飛ばす
				input |= GetKey(player_id, (BUTTON_ID)i, GET_KEY_MODE::TRIGGER);
			}
		}
		// LRスティック判定が有効の時
		if (stick)
		{
			// Lスティック
			input |= ((GetStickValue(player_id, LR_ID::LEFT, XY_ID::X) > m_half_value)
				|| (GetStickValue(player_id, LR_ID::LEFT, XY_ID::X) < -m_half_value)
				|| (GetStickValue(player_id, LR_ID::LEFT, XY_ID::Y) > m_half_value)
				|| (GetStickValue(player_id, LR_ID::LEFT, XY_ID::Y) < -m_half_value));
			// Rスティック
			input |= ((GetStickValue(player_id, LR_ID::RIGHT, XY_ID::X) > m_half_value)
				|| (GetStickValue(player_id, LR_ID::RIGHT, XY_ID::X) < -m_half_value)
				|| (GetStickValue(player_id, LR_ID::RIGHT, XY_ID::Y) > m_half_value)
				|| (GetStickValue(player_id, LR_ID::RIGHT, XY_ID::Y) < -m_half_value));
		}
		// LRトリガー判定が有効の時
		if (trigger)
		{
			input |= ((GetTriggerValue(player_id, LR_ID::LEFT) > m_half_value)
				|| (GetTriggerValue(player_id, LR_ID::RIGHT) > m_half_value));
		}

	}

	return input;
}

void CInputManager::Vibration(PLAYER_ID num_id, int level, float time)
{
	this->Vibration(ID::PLAYER, num_id, level, time, VIBRATION::WEAK);
}

void CInputManager::Vibration(ID id, PLAYER_ID num_id, int level, float time)
{
	this->Vibration(id, num_id, level, time, VIBRATION::WEAK);
}

void CInputManager::Vibration(PLAYER_ID num_id, int level, float time, VIBRATION mode)
{
	this->Vibration(ID::PLAYER, num_id, level, time, mode);
}

void CInputManager::Vibration(ID id, PLAYER_ID num_id, int level, float time, VIBRATION mode)
{
	if (num_id == PLAYER_ID::MAX)	return;

	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		if (!(num_id == (PLAYER_ID)i || num_id == PLAYER_ID::ALL))	continue;

		if (id == ID::PLAYER)
			StartJoypadVibration((int)(m_Device[i]) + 1, level, (int)(time * 1000.0f), (int)mode);
		else
			StartJoypadVibration((int)i + 1, level, (int)(time * 1000.0f), (int)mode);
	}
}

void CInputManager::StopVibration(PLAYER_ID player_id)
{
	this->StopVibration(ID::PLAYER, player_id);
}

void CInputManager::StopVibration(ID id, PLAYER_ID num_id)
{
	if (num_id == PLAYER_ID::MAX)	return;

	for (int i = 0; i < (int)PLAYER_ID::MAX; i++)
	{
		if (!(num_id == (PLAYER_ID)i || num_id == PLAYER_ID::ALL))	continue;

		if (id == ID::PLAYER)
			StopJoypadVibration((int)m_Device[i] + 1);
		else
			StopJoypadVibration(i + 1);
	}
}


CInputManager::CInputManager()
	: m_Device{ PLAYER_ID::MAX ,PLAYER_ID::MAX ,PLAYER_ID::MAX ,PLAYER_ID::MAX }
	, m_CachedStickDir{ {DIRECTION::DUMMY,DIRECTION::DUMMY,DIRECTION::DUMMY,DIRECTION::DUMMY},
						{DIRECTION::DUMMY,DIRECTION::DUMMY,DIRECTION::DUMMY,DIRECTION::DUMMY} }
	, m_StickOnce{ {false,false,false,false}, {false,false,false,false} }
	, m_TriggerkOnce{ {false,false,false,false}, {false,false,false,false} }
{
}

void CInputManager::CheckStickOnce()
{
	for (int player = 0; player < (int)PLAYER_ID::MAX; player++)
	{
		if (!m_StickOnce[player])	continue;

		for (int j = 0; j < (int)LR_ID::MAX; j++)
		{
			if (GetStickValue((PLAYER_ID)player, (LR_ID)j, XY_ID::X) < m_half_value
				&& GetStickValue((PLAYER_ID)player, (LR_ID)j, XY_ID::X) > -m_half_value
				&& GetStickValue((PLAYER_ID)player, (LR_ID)j, XY_ID::Y) < m_half_value
				&& GetStickValue((PLAYER_ID)player, (LR_ID)j, XY_ID::Y) > -m_half_value)
			{
				m_CachedStickDir[j][player] = DIRECTION::DUMMY;
				m_StickOnce[j][player] = false;
			}
		}
	}
}

void CInputManager::CheckTriggerOnce()
{
	for (int player = 0; player < (int)PLAYER_ID::MAX; player++)
	{
		if (!m_TriggerkOnce[player])	continue;

		for (int j = 0; j < (int)LR_ID::MAX; j++)
		{
			if (GetTriggerValue((PLAYER_ID)player, (LR_ID)j) < m_half_value)
				m_TriggerkOnce[j][player] = false;

		}
	}
}
