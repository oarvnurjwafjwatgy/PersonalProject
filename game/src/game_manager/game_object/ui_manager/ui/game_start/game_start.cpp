#include "game_start.h"


CGameStart::CGameStart(void)
	: IUI()
{
}

CGameStart::~CGameStart(void)
{
}

void CGameStart::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_UI_Delete_Timer = 3*60;

	m_Scale = 5.0f;          // 最初はかなり大きく（遠くから迫る演出）
	m_Alpha = 0.0f;          // 最初は透明
	m_FrameCount = 0;
}

void CGameStart::Update(void)
{
    m_FrameCount++;

    // 最初の60フレーム（1秒）で迫ってくる
    if (m_FrameCount <= 60) {
        // スケールを 5.0 から 1.0 へ近づける
        m_Scale -= (5.0f - 1.0f) / 60.0f;
        // 透明度を 0.0 から 1.0 へ（フェードイン）
        m_Alpha += 1.0f / 60.0f;
    }
    else {
        m_Scale = 1.0f; // 1秒後は等倍で固定
        m_Alpha = 1.0f;
    }
	UIDeleteTimer();
}

void CGameStart::Draw(void)
{
	// vivid2DのDrawTextureに「スケール」と「色（アルファ）」を指定
    vivid::Rect rect = { 0, 0, (int)vivid::GetTextureWidth("data\\GAMESTART.png"), (int)vivid::GetTextureHeight("data\\GAMESTART.png") };
    vivid::Vector2 anchor = { rect.right / 2.0f, rect.bottom / 2.0f }; // 画像の中心
    vivid::Vector2 scale = { m_Scale, m_Scale };

    // アルファ値を色に変換 (0xrrggbbaa の場合)
    unsigned int alphaInt = (unsigned char)(m_Alpha * 255);
    unsigned int color = 0xffffff00 | alphaInt;

    vivid::DrawTexture("data\\GAMESTART.png", m_Position, color, rect, anchor, scale);
}

void CGameStart::Finalize(void)
{
}