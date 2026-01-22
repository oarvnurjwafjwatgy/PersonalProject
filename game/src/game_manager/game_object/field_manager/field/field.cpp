#include "field.h"

const int IField::m_block_size = 48;	
const float IField::m_block_max_scale = 1.0f;	
const int IField::m_used_block_max_color = 6;
const int IField::m_block_vanish_count = 4;

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
	, m_NextLine()
	, m_StartRow(0)
	, m_StartRowIndex(0)
{
}

IField::~IField(void)
{
}

void IField::Initialize(const vivid::Vector2& position, FIELD_ID field_id)
{

	m_Position = position;
	
	m_StartRow = 5;

	m_StartRowIndex = m_block_max_height - m_StartRow;

	// 盤面(フィールド)の初期化を行う
	for (int i = 0; i < m_block_max_height; i++)
	{
		for (int j = 0; j < m_block_max_width; j++)
		{
			if (i >= m_StartRowIndex)
			{
				m_Field[i][j].color = (BLOCK_COLOR)(1+rand() % (m_used_block_max_color));
			}
			else
			{
				m_Field[i][j].color = BLOCK_COLOR::EMPTY;
			}
			
			m_Field[i][j].state = BLOCK_STATE::WAIT;
			m_Field[i][j].scale = 1.0f;
			m_Field[i][j].check_flag = false;
		}
	}

	m_CursorPosition.x = m_block_max_width / 2;
	m_CursorPosition.y = m_StartRowIndex;
}

void IField::Update(void)
{
	MoveCursor();
	ShiftBlock();
	BlockVanish();
	Vanishing();
	CheckFall();
}

void IField::Draw(void)
{
	vivid::Rect rect = { 0,0,m_block_size,m_block_size };
	vivid::Vector2 anchor = { (float)m_block_size / 2.0f,(float)m_block_size / 2.0f };
	vivid::Vector2 scale = { m_block_max_scale,m_block_max_scale };

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

	if(vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) && m_CursorPosition.y> m_StartRowIndex)
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
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN))
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

				if (m_block_vanish_count <= (this->CheckStraight((DIRECTION)i, x, y, m_Field[y][x].color)) + 1)
				{
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
