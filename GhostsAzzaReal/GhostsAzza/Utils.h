#pragma once

typedef unsigned char byte;

class Utils
{
public:
	static void PatchAddy(DWORD_PTR Address, byte* buffer, size_t length);

	template<typename T>
	static void PatchAddy(DWORD_PTR Address, T buffer);


	static void ReadAddy(DWORD_PTR Address, byte* buffer, size_t length);

	template<typename T>
	static T ReadAddy(DWORD_PTR Address);

	static void NOPAddy(DWORD_PTR Address, size_t length);

	static void* DetourFunctionn(void* pSource, void* pDestination, int dwLen);
	static void DetourRemoven(void* pSource, int dwLen);

	static bool CheckKeyState(DWORD key, int flag);

	static bool DetourFunc(void* target, void* hkfunc, const char* funcname);
};

template<typename T>
inline T Utils::ReadAddy(DWORD_PTR Address)
{
	T lol;
	ReadAddy(Address, &lol, sizeof(T));
	return T;
}

template<typename T>
inline void Utils::PatchAddy(DWORD_PTR Address, T buffer)
{
	T buf2 = buffer;
	PatchAddy(Address, (byte*)&buf2, sizeof(T));
}
