// 盤面の基底クラス

#pragma once

#include "vivid.h"
#include "field_id.h"

class IField
{
public:
	/*!
	 *	@brief		コンストラクタ
	 */
	IField(void);

	/*!
	 *	@brief		デストラクタ
	 */
	virtual ~IField(void);

	/*!
	 *	@brief		初期化
	 * 
	 *  @param[in]  position	位置
	 *  @param[in]  field_id	フィールドのID
	 */
	virtual void  Initialize(const vivid::Vector2& position , FIELD_ID field_id);

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
	 *	@brief		ブロックのサイズを取得するための関数
	 */
	static int GetBlockSizeConstant(void);

	/*!
	 *	@brief		ブロックが最大おける縦の数を取得するための関数
	 */
	static int GetBlockMaxHeightConstant(void);

	/*!
	 *	@brief		ブロックが最大おける横の数を取得するための関数
	 */
	static int GetBlockMaxWidthConstant(void);

protected:

	static const int m_block_max_height = 16;	//!< ブロックの最大詰める高さ
	static const int m_block_max_width = 8;		//!< ブロックの最大詰める幅
	static const int m_block_size;				//!< ブロックは正方形なので大きさ固定
	static const float m_block_max_scale;			//!< ブロックの拡縮の最大値
	static const int m_used_block_max_color;	//!< ブロックの色の種類


	/*!
	 *	@brief		ブロックの色
	 */
	enum class BLOCK_COLOR
	{
		EMPTY,	//!< 空の状態

		RED,
		GREEN,
		BLUE,
		CYAN,
		MAGENTA,
		YELLOW,

		MAX,
	};

	/*!
	 *	@brief		ブロックの状態
	 */
	enum class BLOCK_STATE
	{
		WAIT,	//!< 止まっているか
		SHIFT,	//!< 動いているか
		FALL,	//!< 落ちる
		VANISH, //!< 消えるか
	};

	/*!
	 *	@brief		ブロック一個に対する情報
	 */
	struct BLOCK
	{
		BLOCK_COLOR color; //!< ブロックの色
		BLOCK_STATE state; //!< ブロックの状態
		float scale;		//!< ブロックの大きさ
	};

	/*!
	 *	@brief		カーソルの位置
	 */
	struct CURSOR_POSITION
	{
		int x, y;
	};


	/*!
	 *	@brief		カーソルの移動
	 */
	void MoveCursor(void);

	/*!
	 *	@brief		ブロックの入れ替え
	 */
	void ShiftBlock(void);

	vivid::Vector2	m_Position;								//!< ブロックの左上の位置
	BLOCK	m_Field[m_block_max_height][m_block_max_width];	//!< ブロックの二次元配列
	BLOCK_STATE m_GameState;				//!< ブロックの状態
	FIELD_ID	 m_FieldID;										//!< フィールドのID
	bool		 m_ActiveFlag;									//!< アクティブフラグ
	CURSOR_POSITION	m_CursorPosition;							//!< カーソルの位置
	

};