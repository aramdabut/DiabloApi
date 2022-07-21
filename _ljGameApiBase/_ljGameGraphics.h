#pragma once

class _ljGameGraphics
{
public:
	static int ColorToInt(int r, int g, int b, int a)
	{
		int color;
		char* arrColor = (char*)&color;
		arrColor[0] = r;
		arrColor[1] = g;
		arrColor[2] = b;
		arrColor[3] = a;
		return color;
	}
private:
	_ljGameGraphics() {}
	virtual ~_ljGameGraphics() = 0;
};
