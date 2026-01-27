	//フィールド管理

	#pragma once

	#include "vivid.h"
	#include <list>
	#include "field/field_id.h"
	#include <memory>

	class IField;


	class CFieldManager
	{
	public:
		/*!
		 *  @brief      インスタンスの取得
		 */
		static CFieldManager& GetInstance(void);

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

		/*!
		 *  @brief      フィールドの生成
		 * 
		 *	@param[in]	position	生成位置
		 *	@param[in]	field_id	フィールドのID
		 */
		void Create(const vivid::Vector2& position,FIELD_ID field_id);

		/*!
		 *  @brief      ブロックのサイズを取得
		 * 
		 *	@return		サイズ
		 */
		int GetBlockSize(void);

		/*!
		 *  @brief      ブロックがおける最大の行の数を取得
		 * 
		 *  @return		最大の縦の数
		 */
		int GetBlockMaxHeight(void) const;

		/*!
		 *  @brief      ブロックがおける最大のの数を取得
		 * 
		 *	@return     最大の横の数
		 */
		int GetBlockMaxWidth(void) const;


		/*!
		 *  @brief      ブロックが消える最低値の取得
		 *  @return      ブロックが消える最低値
		 */
		int GetBlockMinChains(void);

		/*!
		 *  @brief					ブロックが消える最低値の設定
		 *  @param[in]      chains ブロックが消える最低値
		 */
		void SetBlockMinChains(int chains);

	private:

		/*!
		 *  @brief      コンストラクタ
		 */
		CFieldManager(void) = default;

		/*!
		 *  @brief      コピーコンストラクタ
		 */
		CFieldManager(const CFieldManager& rhs) = delete;

		/*!
		 *  @brief      デストラクタ
		 */
		~CFieldManager(void) = default;

		/*!
		 *  @brief      代入演算子
		 */
		CFieldManager& operator= (const CFieldManager&) = delete;

	
		using FIELD_LIST = std::list<std::shared_ptr<IField>>;	// 名前空間の省略を行う
		FIELD_LIST m_FieldList;									//!<  フィールドオブジェクトを入れるリスト(カーソル、ブロック等)
		int m_BlockSize;											//!< ブロックのサイズ
		int m_BlockMinChains;									//!< ブロックが消える最低値
	};
