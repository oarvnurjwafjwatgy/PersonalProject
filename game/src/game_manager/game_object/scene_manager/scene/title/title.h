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

	// 定数の宣言
	static const int m_change_volume;					  //!< BGMの調整
	static const vivid::Vector2 m_title_rogo_position;    //!< タイトルロゴの位置
	static const vivid::Vector2 m_push_button_position;   //!< 決定ボタンの位置
	static const float m_flash_speed;                     //!< 点滅の速さ
	static const int   m_flash_base_alpha;                //!< 透明度のベース値
	static const int   m_flash_amplitude;                 //!< 透明度の振れ幅
	static const int m_bit_shift_bite;					  //!< 色情報のビットシフト量
	static const unsigned int m_color_white;			  //!< ベースとなる色（真っ白）

};
