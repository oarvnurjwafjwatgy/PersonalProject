//ゲーム管理
#pragma once

class CGameManager
{
public:
	/*!
	 *  @brief      インスタンスの取得
	 * 
	 *	@return		インスタンス
	 */
	static CGameManager& GetInstance(void);

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
	CGameManager(void) = default;

	/*!
	 *  @brief      コピーコンストラクタ
	 */
	CGameManager(const CGameManager& rhs) = delete;


	/*!
	 *  @brief      デストラクタ
	 */
	~CGameManager(void) = default;

	/*!
	 *  @brief      代入演算子
	 */
	CGameManager& operator= (const CGameManager& ) = delete;

};
