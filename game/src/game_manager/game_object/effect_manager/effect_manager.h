//UI管理
#pragma once

#include "vivid.h"
#include "effect/effect_id.h"
#include <list>
#include <memory>

class IEffect;

class CEffectManager
{
public:
	/*!
	 *  @brief      インスタンスの取得
	 */
	static CEffectManager& GetInstance(void);

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
	 *  @brief      エフェクト生成
	 *
	 *  @param[in] id エフェクトのID
	 *  @param[in] position エフェクトの位置
	 */
	std::shared_ptr<IEffect>  Create(EFFECT_ID effect_id, const vivid::Vector2& position);





	/*!
	 *  @brief      UIの削除
	 *
	 *  @param[in] id UIのID
	 */
	void	Delete(EFFECT_ID id);


private:

	/*!
	 *  @brief      UIのクラスを制作
	 * 
	 *  @param[in] id UIのID
	 */
	std::shared_ptr<IEffect>  CreateClass(EFFECT_ID id);


	/*!
	 *  @brief      コンストラクタ
	 */
	CEffectManager(void) = default;

	/*!
	 *  @brief      コピーコンストラクタ
	 */
	CEffectManager(const CEffectManager& ) = delete;


	/*!
	 *  @brief      デストラクタ
	 */
	~CEffectManager(void) = default;

	/*!
	 *  @brief      代入演算子
	 */
	CEffectManager& operator= (const CEffectManager& ) = delete;


	using EFFECT_LIST = std::list<std::shared_ptr<IEffect>>;	// 名前空間の省略を行う
	EFFECT_LIST m_EffetList;									//!<  フィールドオブジェクトを入れるリスト(カーソル、ブロック等)
};
