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

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CPaddle : public CEntity
{
    // Member Functions
public:
    CPaddle();
    virtual ~CPaddle();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void SetCanFire(bool Fire);
	void SetFire(bool Fire);
	bool GetCanFire();
	bool GetFire();
	void LoseALife();
	int GetLives();


protected:

private:
    CPaddle(const CPaddle& _kr);
    CPaddle& operator= (const CPaddle& _kr);

    // Member Variables
public:

protected:
	bool m_bCanFire;
	bool m_bFire;
	int Lives;

private:

};

#endif    // __PADDLE_H__
