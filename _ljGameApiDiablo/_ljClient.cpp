#include "_ljClient.h"
#include <_ljGameInput.h>
#include <_ljGameTime.h>
#include <_ljGameScene.h>
#include <_ljGameTextureMgr.h>
#include <_ljGameRandomNum.h>

#include "_ljDemoBlizzard.h"
#include "_ljDemoDiablo.h"
#include "_ljTitle.h"
#include "_ljCharacterSelect.h"
#include "_ljEnding.h"
#include "_ljDungeon2.h"
#include "_ljDungeon15.h"
#include "_ljDungeon18.h"

#include "_ljTestScene.h"
#include "_ljTestPlayerScene.h"



_ljClient::_ljClient()
{
}

_ljClient::~_ljClient()
{
}

void _ljClient::GameInit()
{
	_ljGameTextureMgr::Inst().Init();
	_ljGameRandomNum::Init();

	_ljGameScene::CreateScene<_ljDemoBlizzard>(L"DemoBlizzard");
	_ljDemoDiablo* dia = (_ljDemoDiablo*)_ljGameScene::CreateScene<_ljDemoDiablo>(L"DemoDiablo");
	_ljTitle* main = (_ljTitle*)_ljGameScene::CreateScene<_ljTitle>(L"Title");
	main->SetOpening(dia);

	_ljGameScene::CreateScene<_ljCharacterSelect>(L"CharacterSelect");
	_ljGameScene::CreateScene<_ljEnding>(L"Ending");
	_ljGameScene::CreateScene<_ljTestPlayerScene>(L"TestPlayerScene");

	_ljTestScene* test = (_ljTestScene*)_ljGameScene::CreateScene<_ljTestScene>(L"TestScene");
	_ljDungeon15* d15 = (_ljDungeon15*)_ljGameScene::CreateScene<_ljDungeon15>(L"Dungeon15");
	_ljDungeon18* d18 = (_ljDungeon18*)_ljGameScene::CreateScene<_ljDungeon18>(L"Dungeon18");
	_ljDungeon2* d2 = (_ljDungeon2*)_ljGameScene::CreateScene<_ljDungeon2>(L"Dungeon2");

	test->SetDungeon15(d15);
	d15->SetTestScene(test);
	d15->SetDungeon18(d18);
	d18->SetDungeon15(d15);
	d18->SetDungeon2(d2);
	d2->SetDungeon18(d18);

	_ljGameScene::SetCurScene(L"DemoBlizzard");

	_ljGameInput::CreateKey(L"MOVEL", L'A');
	_ljGameInput::CreateKey(L"MOVER", L'D');
	_ljGameInput::CreateKey(L"MOVET", L'W');
	_ljGameInput::CreateKey(L"MOVEB", L'X');
	_ljGameInput::CreateKey(L"MOVELT", L'Q');
	_ljGameInput::CreateKey(L"MOVERT", L'E');
	_ljGameInput::CreateKey(L"MOVELB", L'Z');
	_ljGameInput::CreateKey(L"MOVERB", L'C');
	_ljGameInput::CreateKey(L"ATTACK", L'R');
	_ljGameInput::CreateKey(L"DIE", L'O');
	_ljGameInput::CreateKey(L"INVEN", L'I');
	_ljGameInput::CreateKey(L"STAT", L'C');
	_ljGameInput::CreateKey(L"GoToNextScene", VK_SPACE);
	_ljGameInput::CreateKey(L"SHIFT", VK_SHIFT);
	_ljGameInput::CreateKey(L"LMOUSEBTN", VK_LBUTTON);
	_ljGameInput::CreateKey(L"RMOUSEBTN", VK_RBUTTON);
	_ljGameInput::CreateKey(L"OUTPUT", VK_RETURN);
	_ljGameInput::CreateKey(L"DEBUG", VK_F1);
	_ljGameInput::CreateKey(L"COLDEBUG", VK_F2);
	_ljGameInput::CreateKey(L"MakeARoom", L'P');
	_ljGameInput::CreateKey(L"EXPUP", VK_F4);
	_ljGameInput::CreateKey(L"MONEY", VK_F6);
	_ljGameInput::CreateKey(L"ITEM", VK_F7);
	_ljGameInput::CreateKey(L"1", L'1');
	_ljGameInput::CreateKey(L"2", L'2');
	_ljGameInput::CreateKey(L"3", L'3');
	_ljGameInput::CreateKey(L"4", L'4');
	_ljGameInput::CreateKey(L"5", L'5');
	_ljGameInput::CreateKey(L"6", L'6');
	_ljGameInput::CreateKey(L"7", L'7');
	_ljGameInput::CreateKey(L"8", L'8');

	Rect.Pos = _ljVector{ 100.f, 100.f };
	Rect.Size = _ljVector{ 100.f, 100.f };
}

static int prevFPS = _ljGameTime::FPS();

void _ljClient::GameUpdate()
{
	_ljGameScene::Progress();
}
