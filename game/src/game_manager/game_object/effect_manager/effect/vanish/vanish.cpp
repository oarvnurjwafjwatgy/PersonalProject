#include "vanish.h"

const float CVanish::m_speed = 10.0f;
const float CVanish::m_max_fade = 0.1f;

CVanish::CVanish(void)
	:m_Velocity(vivid::Vector2::ZERO)
	, m_AlphaValue(1.0f)
{
}

CVanish::~CVanish(void)
{
}

void CVanish::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	m_Particles.clear();

	// 8方向ベクトル
	float s = 0.707f; // 斜めの補正値
	vivid::Vector2 directions[] = {
		{ 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 },
		{ s, -s }, { s, s }, { -s, -s }, { -s, s }
	};

	for (const auto& dir : directions) {
		Particle p;
		// 中心(position)から少しだけ外側(dir * 10.0f)にずらして発生させる
		p.position = position + (dir * 16.0f);
		p.velocity = dir * m_speed;
		m_Particles.push_back(p);
	}
}

void CVanish::Update(void)
{
	// 全ての粒を移動させる
	for (auto& p : m_Particles) {
		p.position += p.velocity;
	}

	// 透明度を減らす
	m_AlphaValue -= m_max_fade;

	if (m_AlphaValue <= 0.0f) {
		m_AlphaValue = 0.0f;
		m_ActiveFlag = false; // エフェクト終了
	}
}

void CVanish::Draw(void)
{

	// 1. 透明度を計算
	unsigned int alpha = (unsigned int)(m_AlphaValue * 255);
	unsigned int drawColor = (alpha << 24) | (m_Color & 0x00FFFFFF);

	// 2. 粒（m_Particles）だけを描画する
	for (const auto& p : m_Particles) {
		// 元の画像サイズが大きい場合は、ここでサイズを指定して小さく描画します
		// 第4引数にスケール（0.2fなど）を指定できるか確認してください
		vivid::DrawTexture("data\\particle.png", p.position, drawColor);
	}
}
