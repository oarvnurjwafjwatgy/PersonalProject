#include "score_text.h"

const int CScoreText::m_number_digit_width = 88;
const int CScoreText::m_number_digit_height = 128;
const unsigned int CScoreText::m_number_color = 0xffffffff;
const float CScoreText::m_display_max_time = 2.0f;



CScoreText::CScoreText(void)
	: m_CurrentScore(0)
	, m_Color(m_number_color)
	, m_ScoreLogs()
{
}

CScoreText::~CScoreText(void)
{
}

void CScoreText::Initialize(const vivid::Vector2& position)
{

	m_Position = position;

	for (int i = 0; i < m_digit_max; i++)
	{
		m_Rect[i] = { 0,0,m_number_digit_width,m_number_digit_height };
	}

}

void CScoreText::Update()
{
	int score_calc = m_CurrentScore;


	for(int  i = m_digit_max-1; i >= 0; i--)
	{
		// 一桁ずつ取り出す
		int digit = score_calc % 10;

		//次の一桁のために１の位を切り捨て
		score_calc /= 10;
		m_Rect[i].left = digit * m_number_digit_width;
		m_Rect[i].right = m_Rect[i].left + m_number_digit_width;

		
	}


	float dt = vivid::GetDeltaTime();

	// リストをループして更新。時間が切れたものは削除する
	for (auto it = m_ScoreLogs.begin(); it != m_ScoreLogs.end(); ) {
		it->timer -= dt;

		// 徐々に透明にする計算
		it->alpha = it->timer / m_display_max_time;

		if (it->timer <= 0) {
			it = m_ScoreLogs.erase(it); // 削除して次の要素のイテレータを貰う
		}
		else {
			++it; // 次の要素へ
		}
	}

}

void CScoreText::Draw()
{

	for (int i = 0; i < m_digit_max; i++)
	{
		vivid::DrawTexture("data\\number.png", m_Position + vivid::Vector2((float)(m_number_digit_width * i), 0.0f),m_Color,m_Rect[i]);
	}

	// スコア履歴の描画
	for (int i = 0; i < m_ScoreLogs.size(); ++i) {
		// 数値を文字列にする
		std::string text = "+" + std::to_string(m_ScoreLogs[i].value);

		// --- 右揃えのための計算 ---
		// 1. 基準となるX座標（メインスコアの右端）
		float baseRightX = m_Position.x + 490.0f;

		// 2. 文字列の幅を計算（フォントサイズ60に合わせて係数を30に調整）
		float textWidth = text.length() * 30.0f;

		// 開始位置を「右端 - 幅」にする。Y軸はメインスコア(m_Position.y)から120下げる
		vivid::Vector2 LogPos = vivid::Vector2(baseRightX - textWidth, m_Position.y + 140.0f + (i * 60.0f));

		// 描画 (黒色 0x000000xx で、下2桁にアルファ値をセット)
		unsigned char alpha = (unsigned char)(m_ScoreLogs[i].alpha * 255);
		unsigned int color = 0xff000000 | alpha;

		vivid::DrawText(60, text, LogPos, color);
	}
}

void CScoreText::Finalize()
{
}

void CScoreText::SetCurrentScore(int current_score)
{
	m_CurrentScore = current_score;
}

int CScoreText::GetCurrentScore()
{
	return m_CurrentScore;
}

void CScoreText::AddScoreLog(int score)
{
	ScoreLog newLog;
	newLog.value = score;
	newLog.timer = m_display_max_time; // タイマーをセット
	newLog.alpha = 1.0f;             // 最初はくっきり表示

	m_ScoreLogs.push_back(newLog);   // リストの末尾に追加
}

