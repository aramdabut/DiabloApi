#pragma once
#include <vector>
#include <_ljGameActor.h>


class _ljRandomMap;
class _ljMapTester : public _ljGameActor
{
	friend _ljRandomMap;

public:
	_ljMapTester();
	~_ljMapTester();

	void Update() override;
	void DebugRender() override;


	void SetRandomMap(_ljRandomMap* map);
	void MakeAMap();

private:
	_ljRandomMap* mRandomMap;
	int mMapIndex;
	std::vector<_ljRandomMap> mAllMap;
};

