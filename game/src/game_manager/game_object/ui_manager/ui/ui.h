#pragma once

#include "vivid.h"
#include "ui_id.h"


class IUI
{
public:
	/*!
	 *	@brief		コンストラクタ
	 */
	IUI(void);

	/*!
	 *	@brief		デストラクタ
	 */
	virtual ~IUI(void);

	/*!
	 *	@brief		初期化
	 */
	virtual void  Initialize(const vivid::Vector2& position,UI_ID ui_id);

	/*!
	 *	@brief		更新
	 */
	virtual void Update(void);

	/*!
	 *	@brief		描画
	 */
	virtual void Draw(void);

	/*!
	 *	@brief		解放
	 */
	virtual void Finalize(void);

	/*!
	 *	@brief		アクティブフラグの取得
	 */
	bool GetActive(void);

protected:
	bool		 m_ActiveFlag;
};