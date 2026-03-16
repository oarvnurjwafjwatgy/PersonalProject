#pragma once
#include "vivid.h"


/*!
 *	@brief		サウンド管理
 */


/*!
 *  @enum       BGMサウンドID
 *  @brief      BGMの種類を管理するID
 */
enum class BGM_ID
{
	TITLE,		//!< タイトル画面
	MAIN,		//!< メイン画面
	RESULT,		//!< リザルト画面
	BGMMAX
};

/*!
 *  @enum       SEサウンドID
 *  @brief      SEの種類を管理するID
 */
enum class SE_ID
{
	DECISION_RESULT, //!< リザルト決定
	DRAM_RESULT,	 //!< リザルトドラムロール
	FINISH,			 //!< ゲーム終わり
	GAMESTART,		 //!< ゲームスタート
	BUTTON,			 //!< ボタン決定音
	VANISH,			 //!< ブロックが消える音
	FALL,			 //!< ブロックが落ちる音
	CURSORMOVE,		 //!< カーソルの移動音
	BLOCKCHANGE,	 //!< ブロックを交換する音
	SEMAX,
};

class CSoundManager
{
public:
	/*!
	 *  @brief      インスタンスの取得
	 */
	static CSoundManager& GetInstance(void);

	/*!
	 *  @brief		  BGMの読み込み
	 *	@param[in] id BGMのID
	 */
	void Load(BGM_ID id);

	/*!
	 *  @brief		SEの読み込み
	 */
	void Load(void);

	/*!
	 *  @brief		BGMの再生
	 *  @param[in, optional] loop ループ再生するかどうか (デフォルトはtrue)
	 */
	void Play(BGM_ID id);

	/*!
	 *  @brief		BGMの停止
	 *	@param[in] id BGMのID
	 */
	void Stop(BGM_ID id);

	/*!
	 *  @brief		SEの再生
	 *	@param[in, optional] loop ループ再生するかどうか (デフォルトはtrue)
	 */
	void Play(SE_ID id);

	/*!
	 *  @brief		SEの停止
	 *	@param[in] id SEのID
	 */
	void Stop(SE_ID id);

	/*!
	 *  @brief		BGMの音量変更
	 *	@param[in] id BGMのID
	 *	@param[in] volume どのくらいに変更するか
	 */
	void ChangeBGMVolume(BGM_ID id, int volume);

private:
	/*!
	 *  @brief		コンストラクタ
	 */
	CSoundManager(void);

	/*!
	 *  @brief		コピーコンストラクタ
	 */
	CSoundManager(const CSoundManager& rhs);

	/*!
	 *  @brief		デストラクタ
	 */
	~CSoundManager(void);

	/*!
	 *  @brief		代入演算子
	 */
	CSoundManager& operator =(const CSoundManager& rhs);

	static const char* m_bgm_fill_name[(int)BGM_ID::BGMMAX];	//!< BGMのファイルパスを格納したテーブル
	static const char* m_se_fill_name[(int)SE_ID::SEMAX];		//!< SEのファイルパスを格納したテーブル

};