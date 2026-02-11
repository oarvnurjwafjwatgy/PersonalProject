#pragma once
#pragma once

#include "vivid.h"
#include "effect_id.h"
#include <memory>
#include <vector>


class IEffect : public std::enable_shared_from_this<IEffect>
{
public:
	
	/*!
	 *	@brief		コンストラクタ
	 */
	IEffect(vivid::Vector2 position,vivid::Vector2 velocity,unsigned int color);



	IEffect();

	/*!
	 *	@brief		デストラクタ
	 */
	virtual ~IEffect(void);

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
	EFFECT_ID	GetEffect_ID();

	/*!
	 *	@brief		色の設定
	 *
	 *   @param[in] ブロックの色
	 */
	void SetColor(unsigned int color);

protected:
	bool				m_ActiveFlag;	//!< アクティブフラグ
	vivid::Vector2		m_Position;		//!< 位置
	EFFECT_ID			m_Effect_ID;		//!< ID
	vivid::Vector2		m_Velocity;		//!< 速さ
	unsigned			m_Color;		//!< 色
	float				m_Alpha;		// α値



};