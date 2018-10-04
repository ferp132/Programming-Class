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

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CPlayerBullet;
class CPaddle;
class CBrick;
class CFPSCounter;
class CBackGround;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPaddle* GetPaddle() const;

    int GetBricksRemaining() const;

protected:
    void ProcessPlayerBulletWallCollision();
	void ProcessInvaderBulletWallCollision();
	void ProcessInvaderWallCollision();
//	void ProcessPaddleWallCollison();
    void ProcessInvaderBulletPaddleCollision();
    void ProcessPlayerBulletBrickCollision();
	void ProcessPlayerBulletFire();
	void ProcessInvaderFire();

    void ProcessCheckForWin();

    void ProcessPlayerBulletBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

    void SetBricksRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CPlayerBullet* m_pPlayerBullet;
	CPlayerBullet* pInvaderBullets[3];
    CPaddle* m_pPaddle;
    std::vector<CBrick*> m_vecBricks;
	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

    int m_iBricksRemaining;
	int InvaderBulletCount = 0;

    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
