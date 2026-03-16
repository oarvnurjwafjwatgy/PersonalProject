#include "score_text.h"
#include "../../../sound_manager/sound_manager.h"

const int CScoreText::m_number_digit_width = 88;
const int CScoreText::m_number_digit_height = 128;
const unsigned int CScoreText::m_number_color = 0xffffffff;
const float CScoreText::m_display_max_time = 2.0f;
const float CScoreText::m_digit_interval = 0.4f; // 0.4秒ごとに1桁確定


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

	if (m_IsResultMode) {
        m_ResultTimer += vivid::GetDeltaTime();
        // 現在何桁目まで確定すべきか計算
        int newConfirmed = (int)(m_ResultTimer / m_digit_interval);
        
		// 新しい桁が確定したかチェック
		if (newConfirmed > m_ConfirmedDigits) 
		{

			// 全ての桁（最後の桁）が決まった瞬間だけ判定
			if (newConfirmed >= m_digit_max)
			{
				CSoundManager::GetInstance().Stop(SE_ID::DRAM_RESULT);
				CSoundManager::GetInstance().Play(SE_ID::DECISION_RESULT);
				m_IsResultMode = false;
			}
		}

		m_ConfirmedDigits = newConfirmed;
    }

     score_calc = m_CurrentScore;

    for(int i = m_digit_max - 1; i >= 0; i--)
    {
        // 右からの位置（0が一番右の桁）
        int distanceFromRight = (m_digit_max - 1) - i;

        int digit;
        if (m_IsResultMode && distanceFromRight >= m_ConfirmedDigits) 
		{
            // まだ確定していない桁を動かす
            digit = rand() % 10;
        } 
		else 
		{
            // 確定した桁は正しい数字を表示
            // スコアを10で割りながら一桁ずつ抽出（既存のロジック）
            int temp_score = m_CurrentScore;
            for(int j = 0; j < distanceFromRight; j++) temp_score /= 10;
            digit = temp_score % 10;
        }

        m_Rect[i].left = digit * m_number_digit_width;
        m_Rect[i].right = m_Rect[i].left + m_number_digit_width;
    }
}

void CScoreText::Draw()
{
	for (int i = 0; i < m_digit_max; i++)
	{
		vivid::DrawTexture("data\\number.png", m_Position + vivid::Vector2((float)(m_number_digit_width * i), 0.0f),m_Color,m_Rect[i]);
	}

	// スコア履歴の描画
	for (int i = 0; i < m_ScoreLogs.size(); ++i)
	{
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

void CScoreText::StartResultAnimation()
{
	CSoundManager::GetInstance().Play(SE_ID::DRAM_RESULT);
	m_IsResultMode = true;
	m_ResultTimer = 0.0f;
	m_ConfirmedDigits = 0;
}

bool CScoreText::IsAnimationFinished(void)
{
	// リザルトモードが終了(false)しており、かつ全桁が確定しているか
	if (!m_IsResultMode && m_ConfirmedDigits >= m_digit_max)
	{
		return true;
	}

	return false;
}

