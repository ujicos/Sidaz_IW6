#pragma once
 
class CVMTHookManager
{
public:
	CVMTHookManager()
	{
		memset(this, 0, sizeof(CVMTHookManager));
	}

	CVMTHookManager(DWORD64** ppdwClassBase)
	{
		bInitialize(ppdwClassBase);
	}

	~CVMTHookManager()
	{
		UnHook();
	}

	bool bInitialize(DWORD64** ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new DWORD64[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD64) * m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;
		return true;
	}

	bool bInitialize(DWORD64*** pppdwClassBase) // fix for pp
	{
		return bInitialize(*pppdwClassBase);
	}

	void UnHook()
	{
		if (m_ppdwClassBase && m_ppdwClassBase != NULL)
		{
			try
			{
				*m_ppdwClassBase = m_pdwOldVMT;
			}
			catch (...)
			{
				return;
			}
		}
	}

	void ReHook()
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}

	int iGetFuncCount()
	{
		return (int)m_dwVMTSize;
	}

	DWORD64 dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
		{
			return m_pdwOldVMT[Index];
		}
		return NULL;
	}

	DWORD64* pdwGetOldVMT()
	{
		return m_pdwOldVMT;
	}

	DWORD64 dwHookMethod(DWORD64 dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return m_pdwOldVMT[iIndex];
		}

		return NULL;
	}

private:
	DWORD64 dwGetVMTCount(DWORD64* pdwVMT)
	{
		DWORD64 dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
			{
				break;
			}
		}
		return dwIndex;
	}

	DWORD64** m_ppdwClassBase;
	DWORD64*	m_pdwNewVMT, *m_pdwOldVMT;
	DWORD64	m_dwVMTSize;
};
