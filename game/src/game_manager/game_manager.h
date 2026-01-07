//ゲーム管理
#pragma once

class CGameManager
{
public:
	//インスタンスの取得
	static CGameManager& GetInstance(void);

	void Initiaize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

private:
	//コンストラクタ
	CGameManager(void);
	//コピーコンストラクタ
	CGameManager(const CGameManager& rhs);
	//デストラクタ
	~CGameManager(void);
	//代入演算子 rhs 代入オブジェクト
	CGameManager& operator= (const CGameManager& rhs);

};
