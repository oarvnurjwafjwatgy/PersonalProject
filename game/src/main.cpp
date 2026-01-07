
/*!
 *  @file       main.cpp
 *  @brief      エントリーポイント
 *  @author     Toshihito Ohashi
 *  @date       2023/03/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2023, Toshihto Ohashi. All rights reserved.
 */

#include "vivid.h"
#include "game_manager/game_manager.h"
#include "game_manager/game_object/scene_manager/scene_manager.h"


/*!
 *  @brief      描画関数
 */
void
Display(void) 
{
    CGameManager::GetInstance().Update();

    CGameManager::GetInstance().Draw();

}

/*!
 *  @brief      メイン関数
 *
 *  @param[in]  hInst       インスタンスハンドル
 *  @param[in]  hPrevInst   Win16時代の遺物
 *  @param[in]  lpCmdLine   コマンドライン文字列
 *  @param[in]  nCmdShow    ウィンドの表示方法
 *
 *  @return     メイン関数の成否
 */
int WINAPI
WinMain( _In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
    (void)hPrevInst;
    (void)lpCmdLine;
    (void)nCmdShow;

    // vividライブラリ初期化   randは一回しかよびだされないところに書く
    vivid::Initialize( hInst );

    //シーン初期化
    CGameManager::GetInstance().Initiaize();

    // 更新/描画関数登録
    vivid::DisplayFunction( Display );

    // ゲームループ
    vivid::MainLoop( );

    CGameManager::GetInstance().Finalize();

    // vividライブラリ解放
    vivid::Finalize( );
}
