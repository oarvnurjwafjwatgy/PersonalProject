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
		 */
		int GetBlockSize(void) const;

		/*!
		 *  @brief      ブロックがおける最大の縦の数を取得
		 */
		int GetBlockMaxHeight(void) const;

		/*!
		 *  @brief      ブロックがおける最大の横の数を取得
		 */
		int GetBlockMaxWidth(void) const;

	private:

		/*!
		 *  @brief      コンストラクタ
		 */
		CFieldManager(void);

		/*!
		 *  @brief      コピーコンストラクタ
		 */
		CFieldManager(const CFieldManager& rhs);


		/*!
		 *  @brief      デストラクタ
		 */
		~CFieldManager(void);

		/*!
		 *  @brief      代入演算子
		 */
		CFieldManager& operator= (const CFieldManager& rhs);

	
		using FIELD_LIST = std::list<std::shared_ptr<IField>>;	// 名前空間の省略を行う
		FIELD_LIST m_FieldList;									//!<  フィールドオブジェクトを入れるリスト(カーソル、ブロック等)
		int m_BlockSize;											//!< ブロックのサイズ
	};
