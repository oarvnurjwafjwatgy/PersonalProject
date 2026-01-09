#pragma once
#include "vivid.h"
#include "../field.h"

class CNormalField :public IField
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CNormalField(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CNormalField(void);

	/*!
	 *  @brief      初期化
	 */
	void Initialize(const vivid::Vector2& position, FIELD_ID field_id) override;

	/*!
	 *  @brief      更新
	 */
	void Update(void) override;

	/*!
	 *  @brief      描画
	 */
	void Draw(void) override;


};