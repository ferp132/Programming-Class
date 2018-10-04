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
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBrick::CBrick()
: m_bHit(false)
{

}

CBrick::~CBrick()
{

}

bool
CBrick::Initialise(float _fVelocityX)
{
    VALIDATE(CEntity::Initialise(IDB_INVADER_1, IDB_INVADER_1_MASK));

	m_fVelocityX = _fVelocityX;
	MovementCounter = 0;

    return (true);
}

void
CBrick::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void
CBrick::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
		MovementCounter += abs(m_fVelocityX * _fDeltaTick);
		if (MovementCounter > 10)
		{
			m_fX += m_fVelocityX;
			MovementCounter = 0;
		}

		CEntity::Process(_fDeltaTick);
    }

}

void
CBrick::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
CBrick::IsHit() const
{
    return (m_bHit);
}

float
CBrick::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CBrick::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CBrick::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}

void
CBrick::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

