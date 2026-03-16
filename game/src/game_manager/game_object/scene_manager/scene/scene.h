#pragma once
#include "scene_id.h"
#include "../scene_manager.h"


/*!
 *	@brief		シーンの基底クラス
 */

class IScene
{
public:
	/*!
	 *	@brief		コンストラクタ
	 */
	IScene(void);

	/*!
	 *	@brief		デストラクタ
	 */
	virtual ~IScene(void);

	/*!
	 *	@brief		初期化
	 */
	virtual void  Initialize();

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
	bool		 m_ActiveFlag;  //!< アクティブフラグ

};