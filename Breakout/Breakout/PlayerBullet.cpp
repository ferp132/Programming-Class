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

// This Includes
#include "PlayerBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayerBullet::CPlayerBullet()
: m_fVelocityX(0.0f),
m_fVelocityY(0.0f)
{
	m_bHit = 1;
}

CPlayerBullet::~CPlayerBullet()
{

}

bool
CPlayerBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
    VALIDATE(CEntity::Initialise(IDB_BALLSPRITE, IDB_BALLMASK));
    
    m_fX = _fPosX;
    m_fY = _fPosY;

    m_fVelocityX = _fVelocityX;
    m_fVelocityY = _fVelocityY;

    return (true);
}

void
CPlayerBullet::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CPlayerBullet::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		m_fX += m_fVelocityX * _fDeltaTick;
		m_fY += m_fVelocityY * _fDeltaTick;
	}

    CEntity::Process(_fDeltaTick);
}

float 
CPlayerBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
CPlayerBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CPlayerBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

void 
CPlayerBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

void
CPlayerBullet::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CPlayerBullet::IsHit() const
{
	return (m_bHit);
}

float 
CPlayerBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
