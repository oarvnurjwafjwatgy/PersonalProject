// 盤面の基底クラス

#pragma once

#include "vivid.h"
#include "field_id.h"
#include "../field_manager.h"
#include <vector>

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
	static const int m_block_min_chains;		//!< 何個連結していたら消えるのかの数
	static const int m_block_start_row;			//!< 最初ブロックを表示する行
	static const float m_combo_max_duration_time; //!< コンボ最大継続時間
	static const int m_finish_max_time;			//!< 終了判定後の最大猶予時間

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

	enum class DIRECTION
	{
		DOWN,
		RIGHT,

		MAX,
	};


	/*!
	 *	@brief		ブロック一個に対する情報
	 */
	struct BLOCK
	{
		BLOCK_COLOR color; //!< ブロックの色
		BLOCK_STATE state; //!< ブロックの状態
		float scale;		//!< ブロックの大きさ
		bool check_flag;	//!< ブロック連結の確認フラグ
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

	/*!
	 *	@brief		ブロックの落下
	 */
	void CheckFall(void);

	/*!
	 *	@brief		ブロック消去
	 */
	void BlockVanish(void);

	/*!
	 *	@brief		特定のブロックの直線並びのチェック
	 *  @pram[in]	dir	探索する向き
	 *  @pram[in]	x,y	現在の座標
	 *  @pram[in]	color	現在の色
	 *  @return		連結している数
	 */
	int CheckStraight(DIRECTION dir,int x,int y, BLOCK_COLOR color);


	/*!
	 *	@brief		チェンジフラグが立っているブロックのステートを[Vanish]にする
	 *  @pram[in]	dir	探索する向き
	 *  @pram[in]	x,y	現在の座標
	 */
	void SetStateVanish(DIRECTION dir, int x, int y);

	
	/*!
	 *	@brief		ブロック連結の確認フラグ(check_flag)のリセット
	 */
	void ResetCheckFlag(void);

	/*!
	 *	@brief		ブロックの状態が「Vanish」だったらemptyにする
	 */
	void Vanishing(void);

	/*!
	 *	@brief		新しい行を一番下に生成する
	 */
	void CreateNextLine(void);

	/*!
	 *	@brief		１段せりあがりを確定させ、配列を一行上にシフトする
	 */
	void PushUpField(void);

	/*!
	 *	@brief		一番上の行にブロックがきているか
	 */
	bool CheckTopRowFull(void);

	/*!
	 *	@brief		コンボ持続時間を減らす
	 */
	void ComboDurationTimer(void);

	/*!
	 *	@brief		終了猶予タイマーを減らす
	 */
	void FinishTimer(void);

	vivid::Vector2	m_Position;									//!< ブロックの左上の位置
	BLOCK	m_Field[m_block_max_height][m_block_max_width];		//!< ブロックの二次元配列
	BLOCK_STATE m_GameState;									//!< ブロックの状態
	FIELD_ID	 m_FieldID;										//!< フィールドのID
	bool		 m_ActiveFlag;									//!< アクティブフラグ
	CURSOR_POSITION	m_CursorPosition;							//!< カーソルの位置
	CURSOR_POSITION m_SelectPosition;							//!< 選択しているブロックの位置
	bool m_SelectedFlag;										//!< 選択しているかのフラグ
	float m_RaiseOffset;										//!< 現在のせり上がり量
	float m_RaiseSpeed;											//!< せりあがる速度
	BLOCK m_NextLine[m_block_max_width];						//!< 次に出現する一番下の行
	int m_RowIndex;												//!< 色が付き始める行のインデックス
	bool m_ShiftButtonFlag;										//!< 入れ替えボタンが押されているか
	int m_ComboCounter;											//!< コンボの回数を数える
	float m_ComboDurationTimer;									//!< コンボ持続時間
	int m_FinishTimer;											//!< 終了タイマー
};