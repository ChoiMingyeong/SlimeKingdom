#include "stdafx.h"
#include "GameProcess.h"

void GameProcess::Start()
{
/*
#pragma region Test(민경)
	A = new GameObject();
	B = new GameObject();
	C = new GameObject();

	TestTextUI = new TextUI();
*/
	MyEngine->LoadSpriteSheet(_T("run_human"), _T("..\\resource\\run_human.bmp"));
	MyEngine->LoadSpriteSheet(_T("stand_human"), _T("..\\resource\\stand_human.bmp"));
	MyEngine->LoadSpriteSheet(_T("LinkSprite"), _T("..\\resource\\LinkSprite.png"));
	/*
	std::vector<Sprite*> pSprites;
	pSprites.push_back(new Sprite(_T("run_human"), { 0, 0, 111, 168 }, { 55.5,84 }));
	pSprites.push_back(new Sprite(_T("run_human"), { 111, 0, 222, 168 }, { 55.5,84 }));
	pSprites.push_back(new Sprite(_T("run_human"), { 222, 0, 333, 168 }, { 55.5,84 }));
	pSprites.push_back(new Sprite(_T("run_human"), { 333, 0, 444, 168 }, { 55.5,84 }));
	pSprites.push_back(new Sprite(_T("run_human"), { 444, 0, 555, 168 }, { 55.5,84 }));

	Animation* pMyAnim1 = new Animation(pSprites);
	//pMyAnim1->m_IsLoop = false;
	pMyAnim1->m_Speed = 2.0f;

	Animation* pMyAnim2 = new Animation(pSprites);

	//A->m_Parent = B;
	//A->SetCircleCollider();
	A->m_Transform.Position = { 200,200 };
	A->m_Transform.Scale = { 2,2 };
	A->SetAnimation(pMyAnim1);
	//A->m_pCollider->m_Visible = false;

	//B->SetCircleCollider();
	B->m_Transform.Position = { 5,5 };
	//B->SetSprite(pSprite[1]);
	//B->m_pCollider->m_Visible = false;
	B->SetAnimation(pMyAnim2);

	C->SetCircleCollider();
	C->m_pCollider->m_Visible = false;

	TestTextUI->m_Text = _T("TestMessage\nWASD : CameraMove\n↑←↓→ : ObjectMove");
	TestTextUI->m_Transform.Position = { 800 };
#pragma endregion
*/

#pragma region 게임매니져 생성 및 게임초기화
	// 게임매니져 생성
	m_pGameManager = new GameManager;

	// 게임초기화
	m_pGameManager->Initialize();

#pragma endregion

}

void GameProcess::Update()
{
/*
#pragma region Test(민경)
	//B->m_Transform.Angle += 1.0f;

	if (Input::InputKey(VK_RIGHT))
	{
		B->m_Transform.Position.x++;
	}
	if (Input::InputKey(VK_LEFT))
	{
		B->m_Transform.Position.x--;
	}
	if (Input::InputKey(VK_UP))
	{
		B->m_Transform.Position.y--;
	}
	if (Input::InputKey(VK_DOWN))
	{
		B->m_Transform.Position.y++;
	}

	if (Input::InputKey(VK_W))
	{
		MyCamera->m_Transform.Position.y--;
	}
	if (Input::InputKey(VK_A))
	{
		MyCamera->m_Transform.Position.x--;
	}
	if (Input::InputKey(VK_S))
	{
		MyCamera->m_Transform.Position.y++;
	}
	if (Input::InputKey(VK_D))
	{
		MyCamera->m_Transform.Position.x++;
	}

	C->m_Visible = !A->IsHit(B);

#pragma endregion
*/

#pragma region 게임루프
	m_pGameManager->GameLoop();

#pragma endregion
}
