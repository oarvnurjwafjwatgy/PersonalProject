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

};
