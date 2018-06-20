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
#include "InvaderBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CInvaderBullet::CInvaderBullet()
: m_fVelocityX(0.0f),
m_fVelocityY(0.0f)
{
	m_bHit = 0;
}

CInvaderBullet::~CInvaderBullet()
{

}

bool
CInvaderBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
    VALIDATE(CEntity::Initialise(IDB_BALLSPRITE, IDB_BALLMASK));
    
    m_fX = _fPosX;
    m_fY = _fPosY;

    m_fVelocityX = _fVelocityX;
    m_fVelocityY = _fVelocityY;

    return (true);
}

void
CInvaderBullet::Draw()
{
//	if (!m_bHit)
//	{
		CEntity::Draw();
//	}
}

void
CInvaderBullet::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		m_fX += m_fVelocityX * _fDeltaTick;
		m_fY += m_fVelocityY * _fDeltaTick;
	}

    CEntity::Process(_fDeltaTick);
}

float 
CInvaderBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
CInvaderBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CInvaderBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

void 
CInvaderBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

void
CInvaderBullet::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CInvaderBullet::IsHit() const
{
	return (m_bHit);
}

float 
CInvaderBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
