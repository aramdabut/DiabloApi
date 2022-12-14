#pragma once
#include <_ljGameWin.h>
#include <_ljGameDebug.h>
#include <_ljGameTextureMgr.h>
#include <_ljGameDir.h> /* 수정 할 것 */
#include <_ljGameFile.h>
#include <_ljGameRenderer.h>
#include <_ljGameSound.h>
#include "_ljClient.h" 

void LoadResource();

int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{
	_ljGameDebug::LeakCheckSetting();

	// 메모리 릭 찾는 방법 . 
	// _CrtSetBreakAlloc(64078);

	_ljGameSound::SoundInit();

	LoadResource(); 	// 이미지 파일 경로 설정

	_ljGameWin::CreateWindowClass(L"Diablo");

	_ljGameWin::MainWindow()->Size(640, 480);

	_ljClient Updater;

	return _ljGameWin::BaseLoop(Updater);
}

void LoadResource()
{
	_ljGameDir newDir;

	newDir.MoveParent();
	newDir.Move(L"Image"); /* ☆ */

	std::vector<_ljGameFile> allTex = newDir.DirToAllFile();

	for (size_t i = 0; i < allTex.size(); ++i)
	{
		_ljGameTextureMgr::Inst().LoadTexture(allTex[i]);
	}

	_ljGameTextureMgr::Inst().CreateImage(L"NormalCursor.bmp", 1, 1);

	// Opening
	_ljGameTextureMgr::Inst().CreateImage(L"BackBuffer.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"SmallFire.bmp", 1, 15);
	_ljGameTextureMgr::Inst().CreateImage(L"Select.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"Pentagram.bmp", 9, 1);


	// Player
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&ATTACK.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&BLOCK.bmp", 2, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&GETHIT.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&BLUESKILL.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&REDSKILL.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&IDLE.bmp", 10, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&WALK.bmp", 8, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&SS&DIE.bmp", 21, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&AX&ATTACK.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&AX&GETHIT.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&AX&REDSKILL.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&AX&IDLE.bmp", 10, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&AX&WALK.bmp", 8, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"PW&LA&AX&DIE.bmp", 15, 8);

	// :::::::::::::::::::::::::::::::: MON :::::::::::::::::::::::::::::::: 
	 
	// Skeleton
	_ljGameTextureMgr::Inst().CreateImage(L"SK&ATTACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&DIE.bmp", 15, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&GETHIT.bmp", 7, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&IDLE.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&SPECIAL.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&WALK.bmp", 8, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"SK&ATTACK&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&DIE&BLACK.bmp", 15, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&GETHIT&BLACK.bmp", 7, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&IDLE&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&SPECIAL&BLACK.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK&WALK&BLACK.bmp", 8, 8);

	// Butcher
	_ljGameTextureMgr::Inst().CreateImage(L"B&ATTACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&DIE.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&GETHIT.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&IDLE.bmp", 10, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&WALK.bmp", 8, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"B&ATTACK&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&DIE&BLACK.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&GETHIT&BLACK.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&IDLE&BLACK.bmp", 10, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"B&WALK&BLACK.bmp", 8, 8);

	// FALLEN ONE
	_ljGameTextureMgr::Inst().CreateImage(L"F&ATTACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&DIE.bmp", 18, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&GETHIT.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&IDLE.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&SPECIAL.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&WALK.bmp", 11, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"F&ATTACK&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&DIE&BLACK.bmp", 18, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&GETHIT&BLACK.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&IDLE&BLACK.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&SPECIAL&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F&WALK&BLACK.bmp", 11, 8);


	// GoatMan
	_ljGameTextureMgr::Inst().CreateImage(L"GM&ATTACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&DIE.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&GETHIT.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&IDLE.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&SPECIAL.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&WALK.bmp", 8, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"GM&ATTACK&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&DIE&BLACK.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&GETHIT&BLACK.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&IDLE&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&SPECIAL&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"GM&WALK&BLACK.bmp", 8, 8);

	// Scavenger
	_ljGameTextureMgr::Inst().CreateImage(L"SC&ATTACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&DIE.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&GETHIT.bmp", 8, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&IDLE.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&WALK.bmp", 8, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"SC&ATTACK&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&DIE&BLACK.bmp", 20, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&GETHIT&BLACK.bmp", 8, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&IDLE&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SC&WALK&BLACK.bmp", 8, 8);

	// Skeleton2
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&ATTACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&DIE.bmp", 17, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&GETHIT.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&IDLE.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&SPECIAL.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&WALK.bmp", 8, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"SK2&ATTACK&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&DIE&BLACK.bmp", 17, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&GETHIT&BLACK.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&IDLE&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&SPECIAL&BLACK.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"SK2&WALK&BLACK.bmp", 8, 8);

	// Zombie
	_ljGameTextureMgr::Inst().CreateImage(L"Z&ATTACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&DIE.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&GETHIT.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&IDLE.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&WALK.bmp", 24, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"Z&ATTACK&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&DIE&BLACK.bmp", 16, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&GETHIT&BLACK.bmp", 6, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&IDLE&BLACK.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"Z&WALK&BLACK.bmp", 24, 8);

	// BAT
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&ATTACK.bmp", 10, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&DIE.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&GETHIT.bmp", 9, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&IDLE.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&WALK.bmp", 13, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"BAT&ATTACK&BLACK.bmp", 10, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&DIE&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&GETHIT&BLACK.bmp", 9, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&IDLE&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"BAT&WALK&BLACK.bmp", 13, 8);

	// Fallen one 2
	_ljGameTextureMgr::Inst().CreateImage(L"F2&ATTACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&DIE.bmp", 14, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&GETHIT.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&IDLE.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&SPECIAL.bmp", 15, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&WALK.bmp", 12, 8);

	_ljGameTextureMgr::Inst().CreateImage(L"F2&ATTACK&BLACK.bmp", 13, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&DIE&BLACK.bmp", 14, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&GETHIT&BLACK.bmp", 11, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&IDLE&BLACK.bmp", 12, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&SPECIAL&BLACK.bmp", 15, 8);
	_ljGameTextureMgr::Inst().CreateImage(L"F2&WALK&BLACK.bmp", 12, 8);

	// :::::::::::::::::::::::::::::::::: Tile ::::::::::::::::::::::::::::::::::
	
	// Tile
	_ljGameTextureMgr::Inst().CreateImage(L"ChurchDungeon.bmp", 20, 11);
	_ljGameTextureMgr::Inst().CreateImage(L"ChurchDungeonTile.bmp", 20, 11);
	_ljGameTextureMgr::Inst().CreateImage(L"ChurchDungeonWall.bmp", 20, 11);
	_ljGameTextureMgr::Inst().CreateImage(L"DibDoor.bmp", 30, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"DibDoorBlack.bmp", 30, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"DibDoorEdge.bmp", 30, 1);

	_ljGameTextureMgr::Inst().CreateImage(L"ChurchDungeonWallBlack.bmp", 20, 11);
	_ljGameTextureMgr::Inst().CreateImage(L"TileBlack.bmp", 1, 1);

	// Title Scenes
	_ljGameTextureMgr::Inst().CreateImage(L"BlizzardOpening.bmp", 20, 12);

	_ljGameTextureMgr::Inst().CreateImage(L"Diablo.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"DiabloFire.bmp", 1, 15); // 550, 216

	// Debug
	_ljGameTextureMgr::Inst().CreateImage(L"TileDebug.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"ActorTile.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"WallTile.bmp", 1, 1);

	// UI
	_ljGameTextureMgr::Inst().CreateImage(L"DibUI.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"DibInven.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"DibStat.bmp", 1, 1);

	_ljGameTextureMgr::Inst().CreateImage(L"HP.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"MP.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"LightSource.bmp", 16, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"BlueLightSource.bmp", 16, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"YellowLightSource.bmp", 16, 1);

	_ljGameTextureMgr::Inst().CreateImage(L"DibButton.bmp", 1, 1);
	_ljGameTextureMgr::Inst().CreateImage(L"LevelUpButton.bmp", 2, 1);


	_ljGameTextureMgr::Inst().CreateImage(L"NewFont.bmp", 26, 2);
	_ljGameTextureMgr::Inst().CreateImage(L"NewYellowFont.bmp", 26, 2);
	_ljGameTextureMgr::Inst().CreateImage(L"NewRedFont.bmp", 26, 2);

	// ::::::::::::::::::::::::::::::: Item :::::::::::::::::::::::::::::::

	// Item
	_ljGameTextureMgr::Inst().CreateImage(L"InGameItem.bmp", 20, 33);
	_ljGameTextureMgr::Inst().CreateImage(L"InGameItemB.bmp", 20, 33);
	_ljGameTextureMgr::Inst().CreateImage(L"Items.bmp", 6, 5);
	_ljGameTextureMgr::Inst().CreateImage(L"ItemsEdge.bmp", 6, 5);
	_ljGameTextureMgr::Inst().CreateImage(L"InvenBack.bmp", 1, 1);


	// :::::::::::::::::::::::::::::::: Sound ::::::::::::::::::::::::::::::::


	_ljGameDir soundDir;

	soundDir.MoveParent();
	soundDir.Move(L"Sound");
	soundDir.Move(L"items");

	std::vector<_ljGameFile> allSound1 = soundDir.DirToAllFile();

	for (size_t i = 0; i < allSound1.size(); ++i)
	{
		_ljGameSound::SoundLoad(allSound1[i]);
	}

	soundDir.MoveParent();
	soundDir.Move(L"misc");

	std::vector<_ljGameFile> allSound2 = soundDir.DirToAllFile();

	for (size_t i = 0; i < allSound2.size(); ++i)
	{
		_ljGameSound::SoundLoad(allSound2[i]);
	}

	soundDir.MoveParent();
	soundDir.Move(L"monsters");

	std::vector<_ljGameFile> allSound3 = soundDir.DirToAllFile();

	for (size_t i = 0; i < allSound3.size(); ++i)
	{
		_ljGameSound::SoundLoad(allSound3[i]);
	}

	soundDir.MoveParent();
	soundDir.Move(L"music");

	std::vector<_ljGameFile> allSound4 = soundDir.DirToAllFile();

	for (size_t i = 0; i < allSound4.size(); ++i)
	{
		_ljGameSound::SoundLoad(allSound4[i]);
	}

	soundDir.MoveParent();
	soundDir.Move(L"warrior");

	std::vector<_ljGameFile> allSound5 = soundDir.DirToAllFile();

	for (size_t i = 0; i < allSound5.size(); ++i)
	{
		_ljGameSound::SoundLoad(allSound5[i]);
	}

}