#include "field.h"

const int IField::m_block_size = 48;	
const float IField::m_block_max_scale = 1.0f;	
const int IField::m_used_block_max_color = 6;

IField::IField(void)
	:m_FieldID(FIELD_ID::DUMMY)
	, m_ActiveFlag(true)
	, m_CursorPosition{ 0,0 }
	, m_GameState(BLOCK_STATE::WAIT)
	, m_Position(vivid::Vector2::ZERO)
{
}

IField::~IField(void)
{
}

void IField::Initialize(const vivid::Vector2& position, FIELD_ID field_id)
{

	m_Position = position;

	// 盤面(フィールド)の初期化を行う
	for (int i = 0; i < m_block_max_height; i++)
	{
		for (int j = 0; j < m_block_max_width; j++)
		{
			m_Field[i][j].color = (BLOCK_COLOR)(rand() % (m_used_block_max_color));
			m_Field[i][j].state = BLOCK_STATE::WAIT;
			m_Field[i][j].scale = 1.0f;
		}
	}
}

void IField::Update(void)
{
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
}

void IField::Finalize(void)
{
}

bool IField::GetActive(void)
{
	return m_ActiveFlag;
}

void IField::MoveCursor(void)
{
}

void IField::ShiftBlock(void)
{
}
