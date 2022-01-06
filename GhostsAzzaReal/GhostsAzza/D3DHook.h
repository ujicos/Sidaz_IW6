#pragma onc

class D3DHook
{
public:
	static void Hook();
};

extern void* DetourFunc64(byte* origFunc, byte* hooKFunc);
extern void RemoveDetour64(byte* origFunc);