#pragma once

#include "vivid.h"
#include "../scene.h"


class CTitle : public IScene
{
public:

	/*
	 *	@brief		コンストラクタ
	 */
	CTitle(void);

	/*
	 *	@brief		デストラクタ
	 */
	~CTitle(void);

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
