#pragma once
#include "vivid.h"


/*!
 *	@brief		サウンド管理
 */


/*!
 *  @enum       BGMサウンドID
 *  @brief      BGMの種類を管理するID
 */
enum class BGMSOUND_ID
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
enum class SESOUND_ID
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
	void Load(BGMSOUND_ID id);

	/*!
	 *  @brief		SEの読み込み
	 */
	void Load(void);

	/*!
	 *  @brief		BGMの再生
	 *  @param[in, optional] loop ループ再生するかどうか (デフォルトはtrue)
	 */
	void Play(BGMSOUND_ID id, bool loop = true);

	/*!
	 *  @brief		BGMの停止
	 *	@param[in] id BGMのID
	 */
	void Stop(BGMSOUND_ID id);

	/*!
	 *  @brief		SEの再生
	 *	@param[in, optional] loop ループ再生するかどうか (デフォルトはtrue)
	 */
	void Play(SESOUND_ID id, bool loop = false);

	/*!
	 *  @brief		SEの停止
	 *	@param[in] id SEのID
	 */
	void Stop(SESOUND_ID id);

	/*!
	 *  @brief		BGMの音量変更
	 *	@param[in] id BGMのID
	 *	@param[in] volume どのくらいに変更するか
	 */
	void ChangeBGMVolume(BGMSOUND_ID id, int volume);

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

	static const char* m_bgm_fill_name[(int)BGMSOUND_ID::BGMMAX];	//!< BGMのファイルパスを格納したテーブル
	static const char* m_se_fill_name[(int)SESOUND_ID::SEMAX];		//!< SEのファイルパスを格納したテーブル

};