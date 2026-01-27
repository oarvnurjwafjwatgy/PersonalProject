#pragma once
#include "vivid.h"
#include "scene/scene_id.h"
#include "scene_manager.h"
#include <memory>
#include "scene/scene.h"
#include <list>
#include <vector>

class IScene;

class CSceneManager
{
public:
	/*!
	 *	@brief		インスタンスの取得
	 * 
	 *	@return		インスタンス
	 */
	static CSceneManager& GetInstance(void);

	/*!
	 *	@brief		初期化
	 */
	void Initialize(void);

	/*!
	 *	@brief		更新
	 */
	void Update(void);

	/*!
	 *	@brief		描画
	 */
	void Draw(void);

	/*!
	 *	@brief		解放
	 */
	void Finalize(void);

	
	using SCENE_LIST = std::vector<std::shared_ptr<IScene>>;

	const SCENE_LIST& GetList() const { return m_SceneList; }

	/*!
	 *	@brief			シーン切り替え
	 *
	 *	@param[in]	id	シーンID
	 */
	void            ChangeScene(SCENE_ID id);

private:
	/*!
	 *	@brief		コンストラクタ
	 */
	CSceneManager(void);

	/*!
	 *	@brief		コピーコンストラクタ
	 */
	CSceneManager(const CSceneManager& ) = delete;

	/*!
	 *	@brief		デストラクタ
	 */
	~CSceneManager(void) = default;

	/*!
	 *	@brief		代入演算子
	 * 
	 *	@param[in]	rhs	代入オブジェクト
	 * 
	 *	@return		自身のオブジェクト
	 */
	CSceneManager& operator=(const CSceneManager& ) = delete;

	/*!
	 *	@brief		シーン生成
	 *
	 *	@param[in]	id	シーンID
	 */
	std::shared_ptr<IScene>		CreateScene(SCENE_ID id);

	/*!
	 *	@brief		シーンの変更
	 */
	void SceneChange(void);


	SCENE_ID				m_CurrentSceneID;		//!< 現在のシーン
	SCENE_ID				m_NextSceneID;			//!< 次のシーン

	SCENE_LIST				m_SceneList; //!< シーンクラス

	bool m_ChangeScene;



};