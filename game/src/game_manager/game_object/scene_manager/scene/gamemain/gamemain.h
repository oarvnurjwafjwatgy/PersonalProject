#pragma once

#include "vivid.h"
#include "../scene.h"
#include "../../scene_manager.h"

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
	 */
	void Initialize(SCENE_ID scene_id) override;

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

	void Start(void);

	void Play(void);

	void Finish(void);

	static const int m_start_wait_time;	//!< 始まるまでの時間

	enum class GAME_STATE
	{
		DUMMY,	//!< ダミー
		START, //!< 開始
		PLAY,  //!< メイン
		FINISH, //!< 終了
	};

	GAME_STATE	m_GameState;		//!< ゲームの状態

	int m_State_Wait_Timer;
};
