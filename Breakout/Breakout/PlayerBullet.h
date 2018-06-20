//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__PLAYERBULLET_H__)
#define __PLAYERBULLET_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CPlayerBullet : public CEntity
{
    // Member Functions
public:
    CPlayerBullet();
    virtual ~CPlayerBullet();

    virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);
    void SetVelocityY(float _fY);

	void SetHit(bool _b);
	bool IsHit() const;

    float GetRadius() const;

protected:

private:
    CPlayerBullet(const CPlayerBullet& _kr);
    CPlayerBullet& operator= (const CPlayerBullet& _kr);

    // Member Variables
public:

protected:
	bool m_bHit;
    float m_fVelocityX;
    float m_fVelocityY;

private:

};


#endif    // __PLAYERBULLET_H__
