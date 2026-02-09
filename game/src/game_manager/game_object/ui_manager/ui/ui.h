#pragma once

#include "vivid.h"
#include "ui_id.h"
#include <memory>
#include <vector>


class IUI : public std::enable_shared_from_this<IUI>
{
public:
	/*!
	 *	@brief		コンストラクタ
	 */
	IUI(UI_ID id = UI_ID::DUMMY);

	/*!
	 *	@brief		デストラクタ
	 */
	virtual ~IUI(void);

	/*!
	 *	@brief		初期化
	 */
	virtual void  Initialize(const vivid::Vector2& position);

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

	/*!
	 *	@brief		削除
	 */
	void	Delete();

	/*!
	 *	@brief		IDの取得
	 * 
	 *  @return		UIのID
	 */
	UI_ID	GetUI_ID();



protected:
	bool				m_ActiveFlag;	//!< アクティブフラグ
	vivid::Vector2		m_Position;		//!< 位置
	UI_ID				m_UI_ID;		//!< ID

};