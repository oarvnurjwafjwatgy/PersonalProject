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
	 *  @brief      描画
	 */
	void Draw(void);

	/*!
	 *  @brief      解放
	 */
	void Finalize(void);

private:

	/*!
	 *  @brief      コンストラクタ
	 */
	CScoreManager(void);

	/*!
	 *  @brief      コピーコンストラクタ
	 */
	CScoreManager(const CScoreManager& rhs);


	/*!
	 *  @brief      デストラクタ
	 */
	~CScoreManager(void);

	/*!
	 *  @brief      代入演算子
	 */
	CScoreManager& operator= (const CScoreManager& rhs);

};
