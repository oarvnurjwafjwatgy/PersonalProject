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
	SELECT,		//!< 選択
	VANISH,		//!< 消す
	GAMEOVER,	//!< 終了
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
	void Load(SESOUND_ID id);

	// BGMの再生
	void Play(BGMSOUND_ID id, bool loop = true);

	// BGMの停止
	void Stop(BGMSOUND_ID id);

	// SEの再生
	void Play(SESOUND_ID id, bool loop = false);

	// SEの停止
	void Stop(SESOUND_ID id);

	
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