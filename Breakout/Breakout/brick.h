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

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CBrick : public CEntity
{
    // Member Functions
public:
    CBrick();
    virtual ~CBrick();

    virtual bool Initialise(float _fVelocityX);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    void SetHit(bool _b);
    bool IsHit() const;

	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float _fX);
	void SetVelocityY(float _fY);

protected:

private:
    CBrick(const CBrick& _kr);
    CBrick& operator= (const CBrick& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;
	float m_fVelocityX;
	float m_fVelocityY;
	float MovementCounter;

private:

};


#endif    // __BRICK_H__

