#pragma once


class _ljInventory
{
public:
	_ljInventory();
	~_ljInventory();

public:
	static void Init();

private:
	static wchar_t** mItemBlocks;

};

