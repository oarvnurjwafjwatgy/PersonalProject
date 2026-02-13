#pragma once
#include "vivid.h"

enum class BGMSOUND_ID
{
	TITLE,		//!< タイトル画面
	MAIN,		//!< メイン画面
	RESULT,		//!< リザルト画面
	BGMMAX
};


enum class SESOUND_ID
{
	DECISION_RESULT, //!< リザルト決定
	DRAM_RESULT,	 //!< リザルトドラムロール
	FINISH,			 //!< ゲーム終わり
	GAMESTART,		 //!< ゲームスタート
	TITLEBUTTON,	 //!< タイトルボタン
	VANISH,			 //!< ブロックが消える音
	SEMAX,
};


class CSoundManager
{
public:
	//インスタンスの取得
	static CSoundManager& GetInstance(void);

	// BGMの読み込み
	void Load(BGMSOUND_ID id);

	// SEの読み込み
	void Load();

	// BGMの再生
	void Play(BGMSOUND_ID id, bool loop = true);

	// BGMの停止
	void Stop(BGMSOUND_ID id);

	// SEの再生
	void Play(SESOUND_ID id, bool loop = false);

	// SEの停止
	void Stop(SESOUND_ID id);

	// BGMの音量調整
	void ChangeBGMVolume(BGMSOUND_ID id, int volume);

	
private:
	//コンストラクタ
	CSoundManager(void);

	//コピーコンストラクタ
	CSoundManager(const CSoundManager& rhs);

	//デストラクタ
	~CSoundManager(void);

	//代入演算子
	CSoundManager& operator =(const CSoundManager& rhs);

	static const char* m_bgm_fill_name[(int)BGMSOUND_ID::BGMMAX];
	static const char* m_se_fill_name[(int)SESOUND_ID::SEMAX];
};