#ifndef _INI_FILE_H_
#define _INI_FILE_H_
/*
ini�ļ�����
*/
#include <Windows.h>
#include <tchar.h>
#include <string>

class CIniFile
{
public:
	CIniFile(void){}
	virtual ~CIniFile(void){}
public:
	/*
	����������д�������ݵ�ini�ļ���
	������
		szItemName�������
		szKeyName������ļ�������
		nValuesҪ���õ�ֵ
	����ֵ���ɹ�����TRUE,ʧ�ܷ���FALSE
	*/
	BOOL  WriteInt(LPCTSTR szItemName, LPCTSTR szKeyName, int nValues)
	{
		BOOL	bRet = FALSE;

		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;

			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}

			TCHAR	szValues[16] = {0};
			::wsprintf(szValues, _T("%d"), nValues);
			bRet = ::WritePrivateProfileString(szItemName, szKeyName, szValues, m_strFileName.c_str());
			if (!bRet)
			{
				m_dwLastError = ::GetLastError();
			}
		} while (0);

		return bRet;
	}

	/*
	����������д�ַ������ݵ�ini�ļ���
	������
		szItemName�������
		szKeyName������ļ�������
		szValuesҪ���õ�ֵ,ΪNULL�����ÿ�ֵ
	����ֵ���ɹ�����TRUE,ʧ�ܷ���FALSE
	*/
	BOOL  WriteStr( LPCTSTR szItemName, LPCTSTR szKeyName, LPCTSTR szValues)
	{
		BOOL	bRet = FALSE;

		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;

			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}

			bRet = ::WritePrivateProfileString(szItemName, szKeyName, szValues, m_strFileName.c_str());
			if (!bRet)
			{
				m_dwLastError = ::GetLastError();
			}
		} while (0);

		return bRet;
	}

	/*
	������������ȡָ���ָ����������
	������
		szItemName�������
		szKeyName������ļ�������
		szBuffer ���յ����ݴ��λ��
		nSize szBuffer��С
	����ֵ������������򷵻ؼ���ֵ�������򷵻ؿ��ַ���
	*/
	void  GetStr( LPCTSTR szItemName, LPCTSTR szKeyName, LPTSTR szBuffer, int nSize)
	{
		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;
			if (NULL == szBuffer)
			{
				break;
			}
			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}
			GetPrivateProfileString(szItemName, szKeyName, _T(""), szBuffer, nSize, m_strFileName.c_str());
			m_dwLastError = GetLastError();
		} while (0);
	}

	/*
	������������ȡָ���ָ����������
	������
		szItemName�������
		szKeyName������ļ�������
	����ֵ������������򷵻ؼ���ֵ�������򷵻ؿ��ַ���
	*/
	int  GetInt( LPCTSTR szItemName,  LPCTSTR szKeyName)
	{
		int		nRet = 0;

		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;
			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}

			nRet = GetPrivateProfileInt(szItemName, szKeyName, 0, m_strFileName.c_str());
			m_dwLastError = GetLastError();
		} while (0);

		return nRet;
	}

	/*
	��������������INI�ļ��������ļ����������ļ���ȫ·��
	������szFileName�ļ���
	����ֵ����
	*/
	void  SetFileName( LPCTSTR szFileName)
	{
		if (szFileName)
		{
			m_strFileName = szFileName;
		}
	}

	/*
	������������ȡ��������ʱ��Ĵ�����
	��������
	����ֵ�������Ĵ�����
	*/
	DWORD  GetLastError()
	{
		return m_dwLastError;
	}
private:
	DWORD						m_dwLastError;//������
	std::basic_string<TCHAR>	m_strFileName;//ini�ļ�����
};

#endif