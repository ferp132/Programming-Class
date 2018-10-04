//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Paddle.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPaddle::CPaddle()
{

}

CPaddle::~CPaddle()
{

}

bool
CPaddle::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));

	Lives = 3;

    return (true);
}

void
CPaddle::Draw()
{
    CEntity::Draw();
}

void
CPaddle::Process(float _fDeltaTick)
{
    
	float fHalfPaddleW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 400.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 400.0f * _fDeltaTick;
	}
	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPaddleW;
	}
	else if (m_fX + fHalfPaddleW >= 1000 - fHalfPaddleW)
	{
		m_fX = 385-fHalfPaddleW;
	}
	
	CEntity::Process(_fDeltaTick);
}

void CPaddle::SetCanFire(bool Fire)
{
	m_bCanFire = Fire;
}

void CPaddle::SetFire(bool Fire)
{
	m_bFire = Fire;
}

bool CPaddle::GetCanFire()
{
	return m_bCanFire;
}

bool CPaddle::GetFire()
{
	return m_bFire;
}

void CPaddle::LoseALife()
{
	Lives--;
}

int CPaddle::GetLives()
{
	return Lives;
}
