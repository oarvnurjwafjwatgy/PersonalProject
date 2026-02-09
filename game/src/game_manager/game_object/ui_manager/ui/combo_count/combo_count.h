#pragma once
#include "vivid.h"
#include "../ui.h"

class CComboCount :public IUI
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	CComboCount(void);

	/*!
	 *  @brief      デストラクタ
	 */
	~CComboCount(void);

	/*!
	 *  @brief      初期化
	 */
	void Initialize(const vivid::Vector2& position) override;

	/*!
	 *  @brief      更新
	 */
	void Update(void) override;

	/*!
	 *  @brief      描画
	 */
	void Draw(void) override;


	/*!
	 *  @brief      現在の値の設定
	 */
	void SetCount(int count);

private:

	int m_Count;  //!< コンボ数
	vivid::Vector2 m_Position;  //!< 位置


};