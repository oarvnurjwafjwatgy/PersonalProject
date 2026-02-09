/**
*	@file	input_manager.h
*	@brief	入力関係のマネージャー
*	@author	K.Kawakami
*/
#pragma once
#include "input_id.h"

class CInputManager
{
public:

	//// 関数 ////

	/**
	*	@brief	インスタンスの取得
	*
	*	@return	instance
	*/
	static CInputManager& GetInstance();

	/**
	*	@brief	初期化
	*/
	void Initialize();
	/**
	*	@brief	更新
	*/
	void Update();
	/**
	*	@brief	解放
	*/
	void Finalize();

/* デバイスの登録系関数 */

	/**
	*	@brief		デバイスの登録
	* 
	*	@param[in]	player_id プレイヤー順番
	*	@param[in]	device_id デバイスID
	*/
	void EntryDevice(PLAYER_ID player_id, PLAYER_ID device_id);
	/**
	*	@brief		プレイヤー番号にデバイス番号を格納
	*
	*	@param[in]	device_id
	*/
	bool GetEnteredDevice(PLAYER_ID device_id);
	/**
	*	@brief		空いているプレイヤー番号を探索
	*
	*	@return		一番早い空白のプレイヤー番号（全て埋まっている場合MAXを返す）
	*/
	PLAYER_ID GetEmptyPlayerNum();
	/**
	*	@brief		プレイヤーIDからデバイスIDを探す
	*
	*	@param[in]	player_id
	*	@return		デバイスID
	*/
	PLAYER_ID GetPlayerDevice(PLAYER_ID player_id);
	/**
	*	@brief		デバイスIDからプレイヤーIDを探す
	*
	*	@param[in]	device_id
	*	@return		プレイヤーID
	*/
	PLAYER_ID GetDevicePlayer(PLAYER_ID device_id);

/* 入力系関数 */

	/**
	*	@brief		ボタン入力の取得
	*
	*	@param[in]	player_id プレイヤー順番
	*	@param[in]	button_id ボタンID
	*	@param[in]	mode TriggerかButtonか
	*	@return		そのボタンが押されたらtrueを返す
	*/
	bool GetKey(PLAYER_ID player_id, BUTTON_ID button_id, GET_KEY_MODE mode);

	/**
	*	@brief		スティックを倒した瞬間のbool値の取得
	*
	*	@param[in]	player_id プレイヤー順番
	*	@param[in]	lr_id 右左スティック
	*	@param[in]	dir スティックの倒す向き
	*	@return		スティックを倒した瞬間のみtrueを返す
	*/
	bool GetStickOnce(PLAYER_ID player_id, LR_ID lr_id, DIRECTION dir);
	/**
	*	@brief		スティックの入力値の取得
	*
	*	@param[in]	player_id プレイヤー順番
	*	@param[in]	lr_id 右左スティック
	*	@param[in]	xy_id スティックの倒す向き
	*	@return		入力値
	*/
	float GetStickValue(PLAYER_ID player_id, LR_ID lr_id, XY_ID xy_id);
	/**
	*	@brief		全コントローラーのスティックの連続入力の取得
	*
	*	@param[in]	lr_id 右左スティック
	*	@param[in]	dir スティックの倒す向き
	*	@return		入力値
	*/
	bool GetAllStickTilt(LR_ID lr_id, DIRECTION dir);

	/**
	*	@brief		LRトリガーの入力値の取得
	*
	*	@param[in]	player_id プレイヤー順番
	*	@param[in]	lr_id 右左
	*	@return		入力値
	*/
	float GetTriggerValue(PLAYER_ID player_id, LR_ID lr_id);

	/**
	*	@brief		LRトリガーを押した瞬間のbool値の取得
	*
	*	@param[in]	player_id プレイヤー順番
	*	@param[in]	lr_id 右左トリガー
	*	@return		LRトリガーを押した瞬間のみtrueを返す
	*/
	bool GetTriggerOnce(PLAYER_ID player_id, LR_ID lr_id);

	/**
	*	@brief		何かコントローラー入力がされたか
	*
	*	@param[in]	player_id	プレイヤーID
	*	@param[in]	button		ボタン
	*	@param[in]	stick		LRスティック
	*	@param[in]	trigger		LRトリガー
	*	@return		どれかしら入力がされた場合、trueを返す
	*/
	bool InputAnyKey(PLAYER_ID player_id, bool button = true, bool stick = true, bool trigger = true);

/* 振動系関数 */

	/**
	*	@brief		コントローラーの振動（PlayerID）（振動モード：弱め）
	*
	*	@param[in]	num_id		順番ID
s	*	@param[in]	level		振動の強さ（0～1000）
	*	@param[in]	time		振動する時間
	*/
	void Vibration(PLAYER_ID num_id, int level, float time);
	/**
	*	@brief		コントローラーの振動（振動モード：弱め）
	*
	*	@param[in]	id			PlayerID か DeviceID か
	*	@param[in]	num_id		順番ID
	*	@param[in]	level		振動の強さ（0～1000）
	*	@param[in]	time		振動する時間
	*/
	void Vibration(ID id, PLAYER_ID num_id, int level, float time);
	/**
	*	@brief		コントローラーの振動（PlayerID）
	*
	*	@param[in]	num_id		順番ID
	*	@param[in]	level		振動の強さ（0～1000）
	*	@param[in]	time		振動する時間
	*	@param[in]	mode		振動のモード（強め・弱め）
	*/
	void Vibration(PLAYER_ID num_id, int level, float time, VIBRATION mode);
	/**
	*	@brief		コントローラーの振動
	*
	*	@param[in]	id			PlayerID か DeviceID か
	*	@param[in]	num_id		順番ID
	*	@param[in]	level		振動の強さ（0～1000）
	*	@param[in]	time		振動する時間
	*	@param[in]	mode		振動のモード（強め・弱め）
	*/
	void Vibration(ID id, PLAYER_ID num_id, int level, float time, VIBRATION mode);

	/**
	*	@brief		コントローラーの振動を止める（PlayerID）
	*
	*	@param[in]	player_id	プレイヤーID
	*/
	void StopVibration(PLAYER_ID player_id);
	/**
	*	@brief		コントローラーの振動を止める
	*	
	*	@param[in]	id			PlayerID か DeviceID か
	*	@param[in]	num_id		順番ID
	*/
	void StopVibration(ID id, PLAYER_ID num_id);

private:
	//// 関数 ////

	/**
	* @brief	コンストラクタ
	*/
	CInputManager();

	/**
	* @brief	コピーコンストラクタ
	*/
	CInputManager(const CInputManager& rhs);

	/**
	* @brief	デストラクタ
	*/
	~CInputManager() {};

	/**
	* @brief	代入演算子
	*/
	CInputManager& operator=(const CInputManager& rhs)
	{
		(void)rhs;
		return *this;
	};

	/**
	*	@brief	スティックの傾きが無くなったか
	*/
	void CheckStickOnce();

	/**
	*	@brief	トリガーの入力が無くなったか
	*/
	void CheckTriggerOnce();


	//// 定数 ////
	static const float	m_half_value;			// 0.5f
	static const float	m_quarter_value;		// 0.25f
	static const float	m_stick_once_value;		// スティック1回入力の反応値


	//// 変数 ////
	PLAYER_ID	m_Device[(int)PLAYER_ID::MAX];								// プレイヤーIDにデバイスIDを格納
	DIRECTION	m_CachedStickDir[(int)LR_ID::MAX][(int)PLAYER_ID::MAX];		// 倒したスティックの向き
	bool		m_StickOnce[(int)LR_ID::MAX][(int)PLAYER_ID::MAX];			// スティックの傾きフラグ
	bool		m_TriggerkOnce[(int)LR_ID::MAX][(int)PLAYER_ID::MAX];		// スティックの傾きフラグ

};

#define INPUTS CInputManager::GetInstance()
