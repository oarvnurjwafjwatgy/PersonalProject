#pragma once
#include "vivid.h"

//// 定義 ////
enum class LR_ID { LEFT, RIGHT, MAX };
enum class XY_ID { X, Y };
enum class GET_KEY_MODE { TRIGGER, BUTTON, RELEASED };
enum class DIRECTION { UP, DOWN, LEFT, RIGHT, DUMMY };
enum class PLAYER_ID
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,

	MAX,
	ALL,
};
enum class BUTTON_ID
{
	A = (int)vivid::controller::BUTTON_ID::A,					// Aボタン
	B = (int)vivid::controller::BUTTON_ID::B,					// Bボタン
	X = (int)vivid::controller::BUTTON_ID::X,					// Xボタン
	Y = (int)vivid::controller::BUTTON_ID::Y,					// Yボタン
	UP = (int)vivid::controller::BUTTON_ID::UP,					// 十字キー上
	DOWN = (int)vivid::controller::BUTTON_ID::DOWN,				// 十字キー下
	LEFT = (int)vivid::controller::BUTTON_ID::LEFT,				// 十字キー左
	RIGHT = (int)vivid::controller::BUTTON_ID::RIGHT,			// 十字キー右
	LB = (int)vivid::controller::BUTTON_ID::LEFT_SHOULDER,		// Lボタン
	RB = (int)vivid::controller::BUTTON_ID::RIGHT_SHOULDER,		// Rボタン
	L_THUMB = (int)vivid::controller::BUTTON_ID::LEFT_THUMB,	// Lスティック押し込み
	R_THUMB = (int)vivid::controller::BUTTON_ID::RIGHT_THUMB,	// Rスティック押し込み
	START = (int)vivid::controller::BUTTON_ID::START,			// STARTボタン
	BACK = (int)vivid::controller::BUTTON_ID::BACK,				// BACKボタン

	MAX_NUM = 16,
};
enum class ID
{
	PLAYER,
	DEVICE,
};
enum class VIBRATION
{
	STRONG = 0,
	WEAK = 1,
};