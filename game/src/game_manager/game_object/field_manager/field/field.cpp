#include "field.h"
#include "../../score_manager/score_manager.h"
#include "../../ui_manager/ui_manager.h"
#include "../../effect_manager/effect_manager.h"

const int IField::m_block_size = 48;				//!< ブロックのサイズ
const float IField::m_block_max_scale = 1.0f;		//!< ブロックの最大の拡大値
const int IField::m_used_block_max_color = 5	;		//!< ブロックの色の種類の数
const int IField::m_block_min_chains = 4;			//!< ブロックの最小消せる連結数
const int IField::m_block_start_row = 5;			//!< ゲーム開始の初期表示列
const int IField::m_combo_max_duration_time = 4*60;	//!< コンボ最大継続時間
const int IField::m_finish_max_time = 30;			//!< 終了判定後の最大猶予時間
const int IField::m_cursor_move_frame = 5;			//!< カーソルの長押しで１マス移動するまでのフレーム


IField::IField(void)
	:m_FieldID(FIELD_ID::DUMMY)
	, m_ActiveFlag(true)
	, m_CursorPosition{ 0,0 }
	, m_GameState(BLOCK_STATE::WAIT)
	, m_Position(vivid::Vector2::ZERO)
	, m_SelectPosition{0,0}
	, m_SelectedFlag(false)
	, m_RaiseOffset(0)
	, m_RaiseSpeed(0)
	, m_RowIndex(0)
	, m_ShiftButtonFlag(false)
	, m_ComboCounter(0)
	, m_ComboDurationTimer(0.0f)
	, m_CursorMoveTimer(0)
{
}

IField::~IField(void)
{
}

void IField::Initialize(const vivid::Vector2& position, FIELD_ID field_id)
{
	auto& field = CFieldManager::GetInstance();
	
	
	field.SetBlockMinChains(m_block_min_chains);
	field.SetFinishFlag(false);

	m_Position = position;

	auto combo_gauge_ui = CUIManager::GetInstance().Create(UI_ID::COMBO_GAUGE, vivid::Vector2{30,600});
	auto combo_count_ui = CUIManager::GetInstance().Create(UI_ID::COMBO_COUNT, vivid::Vector2{30,500});
	auto score_text_ui = CUIManager::GetInstance().Create(UI_ID::SCORE_TEXT, vivid::Vector2{30,200});

	m_ComboGaugeUI = std::dynamic_pointer_cast<CComboGauge>(combo_gauge_ui);
	m_ComboCountUI = std::dynamic_pointer_cast<CComboCount>(combo_count_ui);
	m_ScoreTextUI = std::dynamic_pointer_cast<CScoreText>(score_text_ui);


	m_RowIndex = m_block_max_height - m_block_start_row;

	m_ComboDurationTimer = 0.0f;
	m_ComboDurationTimer = 0;

	// 盤面(フィールド)の初期化を行う
	for (int y = 0; y < m_block_max_height; y++)
	{
		for (int x = 0; x < m_block_max_width; x++)
		{
			if (y >= m_RowIndex)
			{
				m_Field[y][x].color = (BLOCK_COLOR)(1+rand() % (m_used_block_max_color));
			}
			else
			{
				m_Field[y][x].color = BLOCK_COLOR::EMPTY;
			}
			
			m_Field[y][x].state = BLOCK_STATE::WAIT;
			m_Field[y][x].scale = 1.0f;
			m_Field[y][x].check_flag = false;
		}
	}

	CreateNextLine();

	m_CursorPosition.x = m_block_max_width / 2;
	m_CursorPosition.y = m_RowIndex;

	m_FinishTimer = m_finish_max_time;
}

void IField::Update(void)
{
	auto& field = CFieldManager::GetInstance();
	auto& score = CScoreManager::GetInstance();

	if (!CheckTopRowFull())
	{
		// せり上がり速度を加算
		m_RaiseOffset += 0.2f;
	}

	// 1ブロック分せり上がったら、配列を更新
	if (m_RaiseOffset >= (float)m_block_size)
	{
		PushUpField();
		m_RaiseOffset = 0.0f; // リセット
	}


	if (!m_ComboGaugeUI.expired())
		m_ComboGaugeUI.lock()->SetValue(m_combo_max_duration_time, m_ComboDurationTimer);

	if (!m_ComboCountUI.expired())
		m_ComboCountUI.lock()->SetCount(m_ComboCounter);

	if (!m_ScoreTextUI.expired())
		m_ScoreTextUI.lock()->SetCurrentScore(score.GetScore());
	

	MoveCursor();
	ShiftBlock();
	BlockVanish();
	Vanishing();

	CheckFall();
	ComboDurationTimer();
	FinishTimer();
}

void IField::Draw(void)
{
	vivid::Rect rect = { 0,0,m_block_size,m_block_size };
	vivid::Vector2 anchor = { (float)m_block_size / 2.0f,(float)m_block_size / 2.0f };
	vivid::Vector2 scale = { m_block_max_scale,m_block_max_scale };

	vivid::Vector2 field_back_graund = m_Position - vivid::Vector2(3.0f, 4.0f);

	vivid::DrawTexture("data\\field.png", field_back_graund);


	// ブロックの描画
	for (int i = 0; i < m_block_max_height; i++)
	{
		for (int j = 0; j < m_block_max_width; j++)
		{
			// 描画したい地点(x,y)の色情報を見てそれに基づいて、読み込みの最初の地点(左)を設定
			rect.left = (int)m_Field[i][j].color * m_block_size;

			// 最初の地点(左)からsizeを足して上げると読み込み範囲が決まる(右側)
			rect.right = rect.left + m_block_size;

			vivid::DrawTexture("data\\block.png", m_Position + vivid::Vector2(j * m_block_size, i * m_block_size), 0xffffffff, rect, anchor, scale);
		}
	}

	if (m_SelectedFlag)
	{
		vivid::Vector2 selectPos = m_Position + vivid::Vector2(
			(float)m_SelectPosition.x * (float)m_block_size,
			(float)m_SelectPosition.y * (float)m_block_size
		);

		// 選択中を示す画像を上から描画
		vivid::DrawTexture("data\\block_selected.png", selectPos, 0x90ffffff);
	}


	vivid::Vector2 pos = m_Position + vivid::Vector2((float)m_CursorPosition.x*(float)m_block_size, (float)m_CursorPosition.y * (float)m_block_size);

	vivid::DrawTexture("data\\block_choice_flame.png", pos);

	/*vivid::DrawText(50, std::to_string(this->CheckStraight(DIRECTION::RIGHT, 0, 0, m_Field[0][0].color)),{0.0f,100.0f});*/
	vivid::DrawText(50, std::to_string(m_CursorPosition.x) + " , " + std::to_string(m_CursorPosition.y), {0.0f,100.0f});

#ifdef DEBUG
	vivid::DrawText(50, std::to_string(CScoreManager::GetInstance().GetScore()), { 0,200 });
	vivid::DrawText(50, std::to_string(m_ComboDurationTimer), { 0,400 });
#endif // DEBUG	
}

void IField::Finalize(void)
{
}

bool IField::GetActive(void)
{
	return m_ActiveFlag;
}

int IField::GetBlockSizeConstant(void)
{
	return m_block_size;
}

int IField::GetBlockMaxHeightConstant(void)
{
	return m_block_max_height;
}

int IField::GetBlockMaxWidthConstant(void)
{
	return m_block_max_width;
}

unsigned int IField::ConvertBlockColor(BLOCK_COLOR color)
{
	switch (color) {
	case BLOCK_COLOR::RED:     return 0xFFFF3333; // 鮮やかな赤
	case BLOCK_COLOR::GREEN:   return 0xFF33FF33; // 鮮やかな緑
	case BLOCK_COLOR::BLUE:    return 0xFF3333FF; // 鮮やかな青
	case BLOCK_COLOR::CYAN:    return 0xFF33FFFF; // 水色
	case BLOCK_COLOR::YELLOW:  return 0xFFFFFF33; // 黄色
	case BLOCK_COLOR::MAGENTA: return 0xFFFF33FF; // 紫・ピンク
	}
}


void IField::MoveCursor(void)
{
	auto& input = CInputManager::GetInstance();

	if (m_SelectedFlag)	return;

	// 移動キー単押し条件
	bool	input_left_t = input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::LEFT) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A);
	bool	input_right_t = input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::RIGHT) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D);
	bool	input_up_t = input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::UP) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W);
	bool	input_down_t = input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::DOWN) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S);

	// 移動タイマーフラグ
	bool move_flag = m_CursorMoveTimer % m_cursor_move_frame == 0 && m_CursorMoveTimer > 10;

	// 移動キー長押し条件
	bool	input_left_b = move_flag && (input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::X) < -0.5f || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A));
	bool	input_right_b = move_flag && (input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::X) > 0.5f || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D));
	bool	input_up_b = move_flag && (input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::Y) < -0.5f || vivid::keyboard::Button(vivid::keyboard::KEY_ID::W));
	bool	input_down_b = move_flag && (input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::Y) > 0.5f || vivid::keyboard::Button(vivid::keyboard::KEY_ID::S));

	// 移動キー連続入力
	if (input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::X) < -0.5f
		|| input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::X) > 0.5f
		|| input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::Y) < -0.5f
		|| input.GetStickValue(PLAYER_ID::PLAYER1, LR_ID::LEFT, XY_ID::Y) > 0.5f
		|| vivid::keyboard::Button(vivid::keyboard::KEY_ID::A)
		|| vivid::keyboard::Button(vivid::keyboard::KEY_ID::D)
		|| vivid::keyboard::Button(vivid::keyboard::KEY_ID::W)
		|| vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
	{
		m_CursorMoveTimer++;
	}
	else
	{
		m_CursorMoveTimer = 0;
	}

	if((input_up_t || input_up_b) && m_CursorPosition.y> 0)
	{
		m_CursorPosition.y--;
	}
	
	if ((input_down_t || input_down_b) && m_CursorPosition.y < m_block_max_height-1)
	{
		m_CursorPosition.y++;
	}

	if ((input_right_t || input_right_b) && m_CursorPosition.x < m_block_max_width-1)
	{
		m_CursorPosition.x++;
	}

	if ((input_left_t || input_left_b) && m_CursorPosition.x > 0)
	{
		m_CursorPosition.x--;
	}
}

void IField::ShiftBlock(void)
{
	auto& input = CInputManager::GetInstance();

	if ((vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN)|| input.GetKey(PLAYER_ID::PLAYER1,BUTTON_ID::A,GET_KEY_MODE::BUTTON))&& m_Field[m_CursorPosition.y][m_CursorPosition.x].color != BLOCK_COLOR::EMPTY)
	{
		m_SelectPosition = m_CursorPosition;
		m_SelectedFlag = true;
	}
	else
	{
		m_SelectedFlag = false;
	}


	if (!m_SelectedFlag)		return;

	BLOCK tmp = m_Field[m_CursorPosition.y][m_CursorPosition.x];

	if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) || input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::UP)) && m_CursorPosition.y > 0)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y - 1][m_CursorPosition.x];
		m_Field[m_CursorPosition.y - 1][m_CursorPosition.x] = tmp;

		
		m_CursorPosition.y--;
	}

	if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::DOWN)) && m_CursorPosition.y < m_block_max_height - 1)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y + 1][m_CursorPosition.x];
		m_Field[m_CursorPosition.y + 1][m_CursorPosition.x] = tmp;
		
		m_CursorPosition.y++;
	}

	if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D) || input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::RIGHT)) && m_CursorPosition.x < m_block_max_width - 1)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y][m_CursorPosition.x + 1 ];
		m_Field[m_CursorPosition.y][m_CursorPosition.x + 1] = tmp;

		m_CursorPosition.x++;
	}

	if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A) || input.GetStickOnce(PLAYER_ID::PLAYER1, LR_ID::LEFT, DIRECTION::LEFT)) && m_CursorPosition.x > 0)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y][m_CursorPosition.x -1 ];
		m_Field[m_CursorPosition.y][m_CursorPosition.x - 1] = tmp;

		m_CursorPosition.x--;
	}

}

void IField::CheckFall(void)
{
	for (int y = 0; y < m_block_max_height - 1; y++)
	{
		for (int x = 0; x < m_block_max_width; x++)
		{
			if (m_Field[y][x].state != BLOCK_STATE::WAIT)  continue;

			if (m_Field[y + 1][x].color == BLOCK_COLOR::EMPTY)
			{
				m_Field[y + 1][x].color = m_Field[y][x].color;
				m_Field[y][x].color = BLOCK_COLOR::EMPTY;
				
			}
		}
	}
}

void IField::BlockVanish(void)
{
	for (int y = 0; y < m_block_max_height; y++)
	{
		for (int x = 0; x < m_block_max_width; x++)
		{
			for (int i = 0; i < (int)BLOCK_DIRECTION::MAX; i++)
			{
				if (m_Field[y][x].color == BLOCK_COLOR::EMPTY)	continue;

				ResetCheckFlag();

				int check_straight = (CheckStraight((BLOCK_DIRECTION)i, x, y, m_Field[y][x].color)) + 1;

				if (m_block_min_chains <= check_straight)
				{
					// コンボ開始
					CScoreManager::GetInstance().AddScore(check_straight, m_ComboCounter);
					m_ComboDurationTimer = m_combo_max_duration_time;
					m_ComboCounter++;
					SetStateVanish((BLOCK_DIRECTION)i, x, y);
				}
			}
		}
	}
}

int IField::CheckStraight(BLOCK_DIRECTION dir, int x, int y,  BLOCK_COLOR color)
{
	int nx = x, ny = y;		//!< 次の座標
	BLOCK_COLOR ncolor;		//!< 次の色

	m_Field[y][x].check_flag = true;

	if (dir == IField::BLOCK_DIRECTION::DOWN && ny + 1 < m_block_max_height)		ny++;
	else if (dir == IField::BLOCK_DIRECTION::RIGHT && nx + 1 < m_block_max_width)	nx++;
	else return 0;

	ncolor = m_Field[ny][nx].color;

	if (ncolor != color) return 0;

	m_Field[ny][nx].check_flag = true;

	// 再帰処理で連なっている時は+1され続ける、結果的に連結しているブロックの数が返される
	return CheckStraight(dir, nx, ny, ncolor) + 1;
	 
}

void IField::SetStateVanish(BLOCK_DIRECTION dir, int x, int y)
{
	if (!m_Field[y][x].check_flag)	return;

	m_Field[y][x].state = BLOCK_STATE::VANISH;

	int nx = x, ny = y;
	switch (dir)
	{
	case IField::BLOCK_DIRECTION::DOWN:	ny++;	break;
	case IField::BLOCK_DIRECTION::RIGHT:	nx++;	break;
	}

	this->SetStateVanish(dir, nx, ny);
	return;
}

void IField::ResetCheckFlag(void)
{
	for (int y = 0; y < m_block_max_height; y++)
	{
		for (int x = 0; x < m_block_max_width; x++)
		{
			m_Field[y][x].check_flag = false;
		}
	}
}



void IField::Vanishing(void)
{


	for (int y = 0; y < m_block_max_height; y++)
	{
		for (int x = 0; x < m_block_max_width; x++)
		{
			if (m_Field[y][x].state == BLOCK_STATE::VANISH)
			{
				// フィールドの左上座標 + (列番 * サイズ, 行番 * サイズ)
				vivid::Vector2 blockPos = m_Position + vivid::Vector2(
					(float)x * m_block_size,
					(float)y * m_block_size
				);

				// ブロックの中心を狙い、サイズの半分を足す
				vivid::Vector2 centerPos = blockPos + vivid::Vector2(m_block_size / 2.0f, m_block_size / 2.0f);

				unsigned int colorCode = ConvertBlockColor(m_Field[y][x].color);
				CEffectManager::GetInstance().Create(EFFECT_ID::VANISH, centerPos, colorCode);

				// ブロックを消す処理
				m_Field[y][x].color = BLOCK_COLOR::EMPTY;
				m_Field[y][x].state = BLOCK_STATE::WAIT;

			}
		}
	}
}

void IField::CreateNextLine(void)
{
	for (int x = 0; x < m_block_max_width; x++)
	{
		m_NextLine[x].color = (BLOCK_COLOR)(1 + rand() % m_used_block_max_color);
		m_NextLine[x].state = BLOCK_STATE::WAIT;
		m_NextLine[x].scale = 1.3f;
		m_NextLine[x].check_flag = false;
	}


}

void IField::PushUpField(void)
{
	bool JustOnceFlag = false;

	
	// 全ての行を1段上にコピー（0行目は消滅する）
	for (int y = 0; y < m_block_max_height - 1; y++)
	{
		for (int x = 0; x < m_block_max_width; x++)
		{
			m_Field[y][x] = m_Field[y + 1][x];
		}
	}

	// 一番下の行に用意していた m_NextLine を流し込む
	for (int x = 0; x < m_block_max_width; x++)
	{
		m_Field[m_block_max_height - 1][x] = m_NextLine[x];
	}

	// カーソルの位置も1段上げてあげる
	if (m_CursorPosition.y > 0)
	{
		m_CursorPosition.y --;
	}

	
	// ブロックがおける最大行じゃなければ次に控える行を新しく生成
	if (!CheckTopRowFull())
	{
		CreateNextLine();
	}
}

bool IField::CheckTopRowFull(void)
{
	for (int x = 0; x < m_block_max_width; x++)
	{
		// 0行目に一つでも空じゃないブロックがあれば true
		if (m_Field[0][x].color != BLOCK_COLOR::EMPTY)
		{
			return true;
			m_RaiseOffset = 0;
			m_RaiseSpeed = 0;
		}
	}
	return false;
}

void IField::ComboDurationTimer(void)
{
	// コンボがないなら処理をやめる
	if (m_ComboCounter <= 0) return;

	// 継続し終わってるから処理をやめる
	if (m_ComboDurationTimer < 0) return;

	m_ComboDurationTimer -= vivid::GetDeltaTime();

	if (m_ComboDurationTimer <= 0)
	{
		// 時間切れ
		m_ComboCounter = 0;
	}
}

void IField::FinishTimer(void)
{
	if (!CheckTopRowFull()) return;

	m_FinishTimer--;

	if (m_FinishTimer <= 0)
	{
		// ゲームオーバーなのでFinishFlagをtrueにする
		CFieldManager::GetInstance().SetFinishFlag(true);

	}
}
