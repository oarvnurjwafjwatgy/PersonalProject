#pragma once
#include "vivid.h"
#include "../scene.h"
#include "../../scene_manager.h"

/*!
 *	@brief		ゲーム内のゲームメインシーンクラス
 */

class CGameMain : public IScene
{
public:
	/*
	 *	@brief		コンストラクタ
	 */
	CGameMain(void);

	/*
	 *	@brief		デストラクタ
	 */
	~CGameMain(void);

	/*
	 *	@brief		初期化
	 *  @param[in]　scene_id シーンID
	 */
	void Initialize() override;

	/*
	 *	@brief		更新
	 */
	void Update() override;

	/*
	 *	@brief		描画
	 */
	void Draw() override;

	/*
	 *	@brief		解放
	 */
	void Finalize() override;

private:
	/*
	 *	@brief		ゲーム始めの処理
	 */
	void Start(void);

	/*
	 *	@brief		ゲームメインの処理
	 */
	void Play(void);

	/*
	 *	@brief		ゲーム終了の処理
	 */
	void Finish(void);

	static const int m_change_volume;				//!< BGMの調整
	static const int m_start_wait_time;				//!< 始まるまでの時間
	static const vivid::Vector2 m_ui_center_pos;    //!< 中央表示UI（START/FINISH）の位置
	static const vivid::Vector2 m_combogauge_pos;	//!< コンボゲージの位置
	static const vivid::Vector2 m_combocount_pos;	//!< コンボカウントの位置
	static const float m_field_y_offset;			//!< フィールドの表示高さ

	enum class GAME_STATE
	{
		DUMMY,	//!< ダミー
		START,  //!< 開始
		PLAY,   //!< メイン
		FINISH, //!< 終了
	};

	GAME_STATE	m_GameState;		//!< ゲームの状態

	int m_State_Wait_Timer;			//!< ステートが切り替わる時の待機時間

};
