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
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 

// Local Includes
#include "Game.h"
#include "Paddle.h"
#include "Brick.h"
#include "PlayerBullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"
#include "InvaderBullet.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iBricksRemaining(0)
, m_pPaddle(0)
, m_pPlayerBullet(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecBricks.size() > 0)
    {
        CBrick* pBrick = m_vecBricks[m_vecBricks.size() - 1];

        m_vecBricks.pop_back();

        delete pBrick;
    }

    delete m_pPaddle;
    m_pPaddle = 0;

    delete m_pPlayerBullet;
    m_pPlayerBullet = 0;

	delete pInvaderBullets[0];
	pInvaderBullets[0] = 0;

	delete pInvaderBullets[1];
	pInvaderBullets[1] = 0;

	delete pInvaderBullets[2];
	pInvaderBullets[2] = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	srand(time(NULL));

    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    const float fPlayerBulletVelX = 0.0f;
    const float fPlayerBulletVelY = -300.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	

    m_pPaddle = new CPaddle();
    VALIDATE(m_pPaddle->Initialise());

    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pPaddle->SetX(_iWidth / 2.0f);
    m_pPaddle->SetY(_iHeight - ( 1.5f * m_pPaddle->GetHeight()));

	m_pPlayerBullet = new CPlayerBullet();
	VALIDATE(m_pPlayerBullet->Initialise(m_pPaddle->GetX(), m_pPaddle->GetY(), fPlayerBulletVelX, fPlayerBulletVelY));

    const int kiNumBricks = 55;
    const int kiStartX = 75;
    const int kiGap = 10;
	const float InitialVelocity = 200;

    int iCurrentX = kiStartX;
    int iCurrentY = static_cast<int>(m_pPaddle->GetY()) - (11 + 5) * 45; //40 = drop height, 11 = number of drops (change this to a variable later set based on difficulty)

    for (int i = 0; i < kiNumBricks; ++i)
    {
        CBrick* pBrick = new CBrick();
        VALIDATE(pBrick->Initialise(InitialVelocity));

        pBrick->SetX(static_cast<float>(iCurrentX));
        pBrick->SetY(static_cast<float>(iCurrentY));

        iCurrentX += pBrick->GetWidth() + kiGap /*- (static_cast<int>(pBrick->GetWidth())/2)*/ ;

        if (iCurrentX > kiStartX + (11 * pBrick->GetWidth() + 9 * kiGap))
        {
            iCurrentX = kiStartX;
            iCurrentY += 45;
        }

        m_vecBricks.push_back(pBrick);
    }

	float InvaderBulletVelocity = 300;
	int InvaderGetsBullet;
	float InvaderBulletX;
	float InvaderBulletY;


	for (int i = 0; i < 3; i++)
	{
		InvaderGetsBullet = floor(rand() % m_vecBricks.size());
		InvaderBulletX = m_vecBricks[InvaderGetsBullet]->GetX();
		InvaderBulletY = m_vecBricks[InvaderGetsBullet]->GetY();

		pInvaderBullets[i] = new CPlayerBullet();
		VALIDATE(pInvaderBullets[i]->Initialise(InvaderBulletX, InvaderBulletY, 0, InvaderBulletVelocity));

		InvaderBulletVelocity += 50;
	}

    SetBricksRemaining(kiNumBricks);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        m_vecBricks[i]->Draw();
    }

    m_pPaddle->Draw();
    m_pPlayerBullet->Draw();

	for (int i = 0; i < 3; i++)
	{
		pInvaderBullets[i]->Draw();
	}

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	m_pPlayerBullet->Process(_fDeltaTick);
	for (int i = 0; i < 3; i++)
	{
		pInvaderBullets[i]->Process(_fDeltaTick);
	}
	m_pPaddle->Process(_fDeltaTick);
	ProcessPlayerBulletWallCollision();
	ProcessInvaderBulletWallCollision();
	ProcessInvaderWallCollision();
	//ProcessPaddleWallCollison();
    ProcessPlayerBulletPaddleCollision();
    ProcessPlayerBulletBrickCollision();
	ProcessPlayerBulletFire();
	ProcessInvaderFire();

    ProcessCheckForWin();
	ProcessPlayerBulletBounds();

    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        m_vecBricks[i]->Process(_fDeltaTick);
    }
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPaddle* 
CLevel::GetPaddle() const
{
    return (m_pPaddle);
}

void 
CLevel::ProcessPlayerBulletWallCollision()
{
    float fPlayerBulletX = m_pPlayerBullet->GetX();
    float fPlayerBulletY = m_pPlayerBullet->GetY();
    float fPlayerBulletW = m_pPlayerBullet->GetWidth();
    float fPlayerBulletH = m_pPlayerBullet->GetHeight();

    float fHalfPlayerBulletW = fPlayerBulletW / 2;
	float fHalfPlayerBulletH = fPlayerBulletH / 2;

    //if (fPlayerBulletX < fHalfPlayerBulletW) //represents the situation when the PlayerBullet has hit the left wall
    //{
    //    m_pPlayerBullet->SetVelocityX(m_pPlayerBullet->GetVelocityX() * -1); //reverse the PlayerBullet's x velocity
    //}
    //else if (fPlayerBulletX > m_iWidth - fHalfPlayerBulletW) //represents the situation when the PlayerBullet has hit the right wall
    //{
    //    m_pPlayerBullet->SetVelocityX(m_pPlayerBullet->GetVelocityX() * -1); //reverse the PlayerBullet's x velocity direction
    //}

	if (fPlayerBulletY < fHalfPlayerBulletH  || fPlayerBulletY > m_iHeight - fHalfPlayerBulletH) //represents the situation when the PlayerBullet has hit the top wall
    {
		m_pPlayerBullet->SetHit(true);
    }
}

void
CLevel::ProcessInvaderBulletWallCollision()
{
	for (int i = 0; i < 3; i++)
	{
		float fPlayerBulletX = pInvaderBullets[i]->GetX();
		float fPlayerBulletY = pInvaderBullets[i]->GetY();
		float fPlayerBulletW = pInvaderBullets[i]->GetWidth();
		float fPlayerBulletH = pInvaderBullets[i]->GetHeight();

		float fHalfPlayerBulletW = fPlayerBulletW / 2;
		float fHalfPlayerBulletH = fPlayerBulletH / 2;

		//if (fPlayerBulletX < fHalfPlayerBulletW) //represents the situation when the PlayerBullet has hit the left wall
		//{
		//    m_pPlayerBullet->SetVelocityX(m_pPlayerBullet->GetVelocityX() * -1); //reverse the PlayerBullet's x velocity
		//}
		//else if (fPlayerBulletX > m_iWidth - fHalfPlayerBulletW) //represents the situation when the PlayerBullet has hit the right wall
		//{
		//    m_pPlayerBullet->SetVelocityX(m_pPlayerBullet->GetVelocityX() * -1); //reverse the PlayerBullet's x velocity direction
		//}

		if (fPlayerBulletY < fHalfPlayerBulletH || fPlayerBulletY > m_iHeight - fHalfPlayerBulletH) //represents the situation when the PlayerBullet has hit the top wall
		{
			pInvaderBullets[i]->SetHit(true);
		}
	}
}

void 
CLevel::ProcessInvaderWallCollision()
{
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
			float fBrickX = m_vecBricks[i]->GetX();
			float fBrickY = m_vecBricks[i]->GetY();

			float fBrickH = m_vecBricks[i]->GetHeight();
			float fBrickW = m_vecBricks[i]->GetWidth();

			float fHalfBrickW = fBrickW / 2;
			float fHalfBrickH = fBrickH / 2;

		
            if (fBrickX - fHalfBrickW < fHalfBrickW)
            {
                for (unsigned int j = 0; j < m_vecBricks.size(); ++j)
                {
                    m_vecBricks[j]->SetVelocityX(m_vecBricks[j]->GetVelocityX() * -1);
					m_vecBricks[j]->SetX(m_vecBricks[j]->GetX() + 10);
                    m_vecBricks[j]->SetY(m_vecBricks[j]->GetY() + 45);	

					if (m_vecBricks[j]->GetY() > m_pPaddle->GetY())
					{
						CGame::GetInstance().GameOverLost();
					}
				}
				return;
			} 
			else if (fBrickW + fBrickX > 1000 - fHalfBrickW)
			{
				for (unsigned int j = 0; j < m_vecBricks.size(); ++j)
				{
					m_vecBricks[j]->SetVelocityX(m_vecBricks[j]->GetVelocityX() * -1);
					m_vecBricks[j]->SetX(m_vecBricks[j]->GetX() + -10);
					m_vecBricks[j]->SetY(m_vecBricks[j]->GetY() + 45);

					if (m_vecBricks[j]->GetY() > m_pPaddle->GetY() - 10)
					{
						CGame::GetInstance().GameOverLost();
					}
				}
				return;
			}
    }
}

void
CLevel::ProcessPlayerBulletPaddleCollision()
{
    float fPlayerBulletR = m_pPlayerBullet->GetRadius();

    float fPlayerBulletX = m_pPlayerBullet->GetX();
    float fPlayerBulletY = m_pPlayerBullet->GetY(); 

    float fPaddleX = m_pPaddle->GetX();
    float fPaddleY = m_pPaddle->GetY();

    float fPaddleH = m_pPaddle->GetHeight();
    float fPaddleW = m_pPaddle->GetWidth();

    if ((fPlayerBulletX + fPlayerBulletR > fPaddleX - fPaddleW / 2) && //PlayerBullet.right > paddle.left
        (fPlayerBulletX - fPlayerBulletR < fPaddleX + fPaddleW / 2) && //PlayerBullet.left < paddle.right
        (fPlayerBulletY + fPlayerBulletR > fPaddleY - fPaddleH / 2) && //PlayerBullet.bottom > paddle.top
        (fPlayerBulletY - fPlayerBulletR < fPaddleY + fPaddleH / 2))  //PlayerBullet.top < paddle.bottom
    {
        m_pPlayerBullet->SetY((fPaddleY - fPaddleH / 2) - fPlayerBulletR);  //Set the PlayerBullet.bottom = paddle.top; to prevent the PlayerBullet from going through the paddle!
        m_pPlayerBullet->SetVelocityY(m_pPlayerBullet->GetVelocityY() * -1); //Reverse PlayerBullet's Y direction
    }
}

void
CLevel::ProcessPlayerBulletBrickCollision()
{
    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        if (!m_vecBricks[i]->IsHit())
        {
            float fPlayerBulletR = m_pPlayerBullet->GetRadius();

            float fPlayerBulletX = m_pPlayerBullet->GetX();
            float fPlayerBulletY = m_pPlayerBullet->GetY(); 

            float fBrickX = m_vecBricks[i]->GetX();
            float fBrickY = m_vecBricks[i]->GetY();

            float fBrickH = m_vecBricks[i]->GetHeight();
            float fBrickW = m_vecBricks[i]->GetWidth();

            if ((fPlayerBulletX + fPlayerBulletR > fBrickX - fBrickW / 2) &&
                (fPlayerBulletX - fPlayerBulletR < fBrickX + fBrickW / 2) &&
                (fPlayerBulletY + fPlayerBulletR > fBrickY - fBrickH / 2) &&
                (fPlayerBulletY - fPlayerBulletR < fBrickY + fBrickH / 2))
            {
                //Hit the front side of the brick...
                m_pPlayerBullet->SetY((fBrickY + fBrickH / 2.0f) + fPlayerBulletR);
              //m_pPlayerBullet->SetVelocityY(m_pPlayerBullet->GetVelocityY() * -1);
				m_pPlayerBullet->SetHit(true);
				m_vecBricks[i]->SetHit(true);
                SetBricksRemaining(GetBricksRemaining() - 1);
            }
        }
    }
}

void 
CLevel::ProcessPlayerBulletFire()
{
	if (m_pPlayerBullet->IsHit())
	{
		m_pPlayerBullet->SetY(m_pPaddle->GetY());
		m_pPlayerBullet->SetX(m_pPaddle->GetX());
	
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_pPlayerBullet->SetHit(false);
		}
	}
}

void 
CLevel::ProcessInvaderFire()
{
	int ChooseBullet = rand() % 3;
	int CanFire		= rand() % 250;

	if (pInvaderBullets[ChooseBullet]->IsHit() && CanFire == 0)
	{
		int InvaderGetsBullet = floor(rand() % m_vecBricks.size());
		while (m_vecBricks[InvaderGetsBullet]->IsHit())
		{
			InvaderGetsBullet = floor(rand() % m_vecBricks.size());
		}

		pInvaderBullets[ChooseBullet]->SetX(m_vecBricks[InvaderGetsBullet]->GetX());
		pInvaderBullets[ChooseBullet]->SetY(m_vecBricks[InvaderGetsBullet]->GetY());
		pInvaderBullets[ChooseBullet]->SetHit(false);


	}

	//for (int i = 0; i < 3; i++)
	//{
	//	if (pInvaderBullets[i]->IsHit())
	//	{
	//		pInvaderBullets[i]->SetY(m_pPaddle->GetY());
	//		pInvaderBullets[i]->SetX(m_pPaddle->GetX());
	//	}
	//}
}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        if (!m_vecBricks[i]->IsHit())
        {
            return;
        }
    }

    CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessPlayerBulletBounds()
{
	if (m_pPlayerBullet->GetX() < 0)
    {
       // m_pPlayerBullet->SetX(0);
    }
	else if (m_pPlayerBullet->GetX() > m_iWidth)
    {
        //m_pPlayerBullet->SetX(static_cast<float>(m_iWidth));
    }

    if (m_pPlayerBullet->GetY() < 0)
    {
       // m_pPlayerBullet->SetY(0.0f);
		m_pPlayerBullet->SetHit(true);
		m_pPaddle->SetCanFire(true);
	}
    else if (m_pPlayerBullet->GetY() > m_iHeight)
    {
        //CGame::GetInstance().GameOverLost();
        //m_pPlayerBullet->SetY(static_cast<float>(m_iHeight));
    }
}

int 
CLevel::GetBricksRemaining() const
{
    return (m_iBricksRemaining);
}

void 
CLevel::SetBricksRemaining(int _i)
{
    m_iBricksRemaining = _i;
    UpdateScoreText();
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void 
CLevel::UpdateScoreText()
{
    m_strScore = "Bricks Remaining: ";

    m_strScore += ToString(GetBricksRemaining());
}

void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}
