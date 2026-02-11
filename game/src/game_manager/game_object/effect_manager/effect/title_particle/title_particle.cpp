#include "title_particle.h"

CTitleParticle::CTitleParticle(void)
    : m_Timer(0.0f)
    ,m_BasePosition(vivid::Vector2::ZERO)
{
}

CTitleParticle::~CTitleParticle(void)
{
}

void CTitleParticle::Initialize(const vivid::Vector2& position)
{
    m_BasePosition = position; // ロゴの中心座標などを保存
    m_Position = position;
    m_Timer = 0.0f;
    m_ActiveFlag = true; // これを忘れずに！
    m_Color = 0xFFFFFFFF; // 真っ白（不透明）に設定
}

void CTitleParticle::Update(void)
{


    m_Timer += 0.05f;
}

void CTitleParticle::Draw(void)
{
    // 1.0(元のサイズ) を基準に、0.8倍 ～ 1.2倍 の間でふわふわさせる
    float wave = sinf(m_Timer);
    float scale = 1.0f + wave * 0.2f;

    // もし「もっとドクドク動かしたい」なら、sinf の結果を絶対値にしたり、
    // 1.2f + wave * 0.4f (1.6倍～0.8倍) のように数値を大きくします。

    vivid::Vector2 anchor = { 0.5f, 0.5f }; // 画像の中心を軸にする
    vivid::Vector2 scaleVec = { scale, scale };

    // 第4引数の Rect は、画像全体を描画するために Rect::ZERO に戻しておきましょう
    vivid::DrawTexture("data\\BlockOnly.png", m_BasePosition, m_Color,
        vivid::Rect{0,0,1000,788}, anchor, scaleVec);
}
