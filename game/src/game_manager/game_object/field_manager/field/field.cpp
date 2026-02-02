#include "field.h"
#include "../../score_manager/score_manager.h"

const int IField::m_block_size = 48;	
const float IField::m_block_max_scale = 1.0f;	
const int IField::m_used_block_max_color = 6;
const int IField::m_block_min_chains = 4;
const int IField::m_block_start_row = 5;
const float IField::m_combo_max_duration_time = 3.0f;
const int IField::m_finish_max_time = 30;

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


	m_RowIndex = m_block_max_height - m_block_start_row;

	m_ComboDurationTimer = 0.0f;
	m_ComboDurationTimer = m_combo_max_duration_time;

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

	if (!CheckTopRowFull())
	{
		// せり上がり速度を加算
		m_RaiseOffset += 0.5f;
	}

	// 1ブロック分せり上がったら、配列を更新
	if (m_RaiseOffset >= (float)m_block_size)
	{
		PushUpField();
		m_RaiseOffset = 0.0f; // リセット
	}

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
			(float)m_SelectPosition.y * (float)m_block_size - m_RaiseOffset
		);

		// 選択中を示す画像を上から描画
		vivid::DrawTexture("data\\block_selected.png", selectPos, 0x90ffffff);
	}


	vivid::Vector2 pos = m_Position + vivid::Vector2((float)m_CursorPosition.x*(float)m_block_size, (float)m_CursorPosition.y * (float)m_block_size - m_RaiseOffset);

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

void IField::MoveCursor(void)
{
	if (m_SelectedFlag)	return;

	if(vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) && m_CursorPosition.y> 0)
	{
		m_CursorPosition.y--;
	}
	
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) && m_CursorPosition.y < m_block_max_height-1)
	{
		m_CursorPosition.y++;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D) && m_CursorPosition.x < m_block_max_width-1)
	{
		m_CursorPosition.x++;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A) && m_CursorPosition.x > 0)
	{
		m_CursorPosition.x--;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C))
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x].color = BLOCK_COLOR::EMPTY;
	}
}

void IField::ShiftBlock(void)
{
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN) && m_Field[m_CursorPosition.y][m_CursorPosition.x].color != BLOCK_COLOR::EMPTY)
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

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) && m_CursorPosition.y > 0)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y - 1][m_CursorPosition.x];
		m_Field[m_CursorPosition.y - 1][m_CursorPosition.x] = tmp;

		
		m_CursorPosition.y--;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) && m_CursorPosition.y < m_block_max_height - 1)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y + 1][m_CursorPosition.x];
		m_Field[m_CursorPosition.y + 1][m_CursorPosition.x] = tmp;
		
		m_CursorPosition.y++;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D) && m_CursorPosition.x < m_block_max_width - 1)
	{
		m_Field[m_CursorPosition.y][m_CursorPosition.x] = m_Field[m_CursorPosition.y][m_CursorPosition.x + 1 ];
		m_Field[m_CursorPosition.y][m_CursorPosition.x + 1] = tmp;

		m_CursorPosition.x++;
	}

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A) && m_CursorPosition.x > 0)
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
			for (int i = 0; i < (int)DIRECTION::MAX; i++)
			{
				if (m_Field[y][x].color == BLOCK_COLOR::EMPTY)	continue;

				// 消えることが確定している場合、スキップする
				//if (m_Field[y][x].state == BLOCK_STATE::VANISH) continue;
				
				ResetCheckFlag();

				int check_straight = (CheckStraight((DIRECTION)i, x, y, m_Field[y][x].color)) + 1;

				if (m_block_min_chains <= check_straight)
				{
					CScoreManager::GetInstance().AddScore(check_straight, m_ComboCounter);
					m_ComboDurationTimer = m_combo_max_duration_time;
					m_ComboCounter++;
					SetStateVanish((DIRECTION)i, x, y);
				}
			}
		}
	}
}

int IField::CheckStraight(DIRECTION dir, int x, int y,  BLOCK_COLOR color)
{
	int nx = x, ny = y;		//!< 次の座標
	BLOCK_COLOR ncolor;		//!< 次の色

	m_Field[y][x].check_flag = true;

	if (dir == IField::DIRECTION::DOWN && ny + 1 < m_block_max_height)		ny++;
	else if (dir == IField::DIRECTION::RIGHT && nx + 1 < m_block_max_width)	nx++;
	else return 0;

	ncolor = m_Field[ny][nx].color;

	if (ncolor != color) return 0;

	m_Field[ny][nx].check_flag = true;

	// 再帰処理で連なっている時は+1され続ける、結果的に連結しているブロックの数が返される
	return CheckStraight(dir, nx, ny, ncolor) + 1;
	 
}

void IField::SetStateVanish(DIRECTION dir, int x, int y)
{
	if (!m_Field[y][x].check_flag)	return;

	m_Field[y][x].state = BLOCK_STATE::VANISH;

	int nx = x, ny = y;
	switch (dir)
	{
	case IField::DIRECTION::DOWN:	ny++;	break;
	case IField::DIRECTION::RIGHT:	nx++;	break;
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
		m_NextLine[x].scale = 1.0f;
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
