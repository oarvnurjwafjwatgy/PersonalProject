//スコア管理
#pragma once

class CScoreManager
{
public:
	/*!
	 *  @brief      インスタンスの取得
	 * 
	  *	@return		インスタンス
	 */
	static CScoreManager& GetInstance(void);

	/*!
	 *  @brief      初期化
	 */
	void Initialize(void);

	/*!
	 *  @brief      更新
	 */
	void Update(void);

	/*!
	 *  @brief      解放
	 */
	void Finalize(void);

	/*!
	 *  @brief      スコアの取得
	 *  @return		スコア
	 */
	int GetScore(void);

	/*!
	 *  @brief					スコアの加算
	 *  @param[in]       chains	連結数
	 *  @param[in]       combo	コンボ数
	 */
	void AddScore(int chains,int combo);

private:

	/*!
	 *  @brief      コンストラクタ
	 */
	CScoreManager(void) = default;

	/*!
	 *  @brief      コピーコンストラクタ
	 */
	CScoreManager(const CScoreManager&) = delete;

	/*!
	 *  @brief      デストラクタ
	 */
	~CScoreManager(void) = default;

	/*!
	 *  @brief      代入演算子
	 */
	CScoreManager& operator= (const CScoreManager& ) = delete;

	static const int m_base_score;	//!< 基礎スコア
	static const float m_base_multiplier;	//!< 基本倍率
	static const float m_half;	//!< 2分の1（連結ボーナスの計算に使用）
	static const float m_one_tenth;		//!< 10分の1


	int m_Score;					//!< 現在のスコア

	
};
