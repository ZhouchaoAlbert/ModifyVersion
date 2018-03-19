#pragma once

#include "resource.h"
#include "IniFile.h"
#define  MIABUILD_PATH _T("D:\\mia-build\\mia-obs-pc-build\\ResInstall\\miabuild.ini")



TCHAR szFileDiscription[256] = { 0 };
TCHAR szCompanyName[256] = { 0 };
TCHAR szFileVersion[256] = { 0 };

TCHAR szLegalCopyright[256] = { 0 };
TCHAR szOriginalFilename[256] = { 0 };
TCHAR szProductName[256] = { 0 };
TCHAR szInternalName[256] = { 0 };
TCHAR szProductVersion[256] = { 0 };

void ModifyRcW(LPCTSTR lpszRCFile)
{
	CFile fileRc, fileRcOut;
	WCHAR byteRead, *ptr, *ptr2;
	WCHAR szLine[250] = { 0 };
	int iIndex = 0;
	CString strRcOut = lpszRCFile;
	strRcOut += _T(".rcmv");
	if (fileRcOut.Open(strRcOut, CFile::modeCreate | CFile::modeWrite))
	{
		if (fileRc.Open(lpszRCFile, CFile::modeRead))
		{
			while (fileRc.Read(&byteRead, sizeof(byteRead)) > 0)
			{
				if (iIndex >= 200)
				{
					fileRc.Close();
					fileRcOut.Close();
					ASSERT(FALSE);
					return;
				}

				if (byteRead == L'\n')
				{
					szLine[iIndex] = L'\0';
					int iIndex_old = iIndex;
					iIndex = 0;

					if (wcsstr(szLine, L"VALUE \"CompanyName\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szCompanyName);
						wcscat_s(szLine, L"\"\r");
					}
					else if (wcsstr(szLine, L"VALUE \"FileDescription\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szFileDiscription);
						int m = 0;
						wcscat_s(szLine, L"\"\r");
					}
					else if (wcsstr(szLine, L"VALUE \"FileVersion\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szFileVersion);
						wcscat_s(szLine, L"\"\r");
					}
					else if (wcsstr(szLine, L"VALUE \"LegalCopyright\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szLegalCopyright);
						wcscat_s(szLine, L"\"\r");
					}
					else if (wcsstr(szLine, L"VALUE \"InternalName\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szInternalName);
						wcscat_s(szLine, L"\"\r");
					}
					else if (wcsstr(szLine, L"VALUE \"OriginalFilename\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szOriginalFilename);
						wcscat_s(szLine, L"\"\r");
					}

					else if (wcsstr(szLine, L"VALUE \"ProductName\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szProductName);
						wcscat_s(szLine, L"\"\r");
					}
					else if (wcsstr(szLine, L"VALUE \"ProductVersion\""))
					{
						ptr = wcschr(szLine, L',');
						ptr++;
						while (iswspace(*ptr)) ptr++;
						wcscpy_s(ptr, _countof(szLine) - (ptr - szLine), L"\"");
						ptr++;
						wcscat_s(ptr, _countof(szLine) - (ptr - szLine), szProductVersion);
						wcscat_s(szLine, L"\"\r");
					}

					wcscat_s(szLine, L"\n");
					fileRcOut.Write(szLine, wcslen(szLine) * sizeof(WCHAR));
				}
				else
				{
					szLine[iIndex++] = byteRead;
				}
			}
			fileRc.Close();
			fileRcOut.Close();
			SetFileAttributes(lpszRCFile, GetFileAttributes(lpszRCFile) & ~FILE_ATTRIBUTE_READONLY);
			DeleteFile(lpszRCFile);
			MoveFile(strRcOut, lpszRCFile);
		}
		else
		{
			fileRcOut.Close();
		}
	}
}


void ModifyRcA(LPCTSTR lpszRCFile)
{
	USES_CONVERSION;

	CFile fileRc, fileRcOut;
	char byteRead, *ptr, *ptr2;
	char szLine[250] = { 0 };
	int iIndex = 0;
	int i = 0;
	CString strRcOut = lpszRCFile;
	strRcOut += _T(".rcmv");
	if (fileRcOut.Open(strRcOut, CFile::modeCreate | CFile::modeWrite))
	{
		if (fileRc.Open(lpszRCFile, CFile::modeRead))
		{
			while (fileRc.Read(&byteRead, 1) > 0)
			{

				if (byteRead == '\n')
				{
					szLine[iIndex] = '\0';
					int iIndex_old = iIndex;
					iIndex = 0;

					if (strstr(szLine, "VALUE \"CompanyName\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szCompanyName));
						strcat_s(szLine, "\"\r");
					}
					else if (strstr(szLine, "VALUE \"FileDescription\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szFileDiscription));
						strcat_s(szLine, "\"\r");
					}
					else if (strstr(szLine, "VALUE \"FileVersion\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szFileVersion));
						strcat_s(szLine, "\"\r");
					}
					else if (strstr(szLine, "VALUE \"LegalCopyright\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szLegalCopyright));
				
						strcat_s(szLine, "\"\r");
					}
					else if (strstr(szLine, "VALUE \"InternalName\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szInternalName));
						strcat_s(szLine, "\"\r");
					}
					else if (strstr(szLine, "VALUE \"OriginalFilename\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szOriginalFilename));
						strcat_s(szLine, "\"\r");
					}

					else if (strstr(szLine, "VALUE \"ProductName\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szProductName));
						strcat_s(szLine, "\"\r");
					}
					else if (strstr(szLine, "VALUE \"ProductVersion\""))
					{
						ptr = strchr(szLine, ',');
						ptr++;
						while (isspace(*ptr)) ptr++;
						strcpy_s(ptr, sizeof(szLine)-(ptr - szLine), "\"");
						ptr++;
						strcat_s(ptr, sizeof(szLine)-(ptr - szLine), W2A(szProductVersion));
						strcat_s(szLine, "\"\r");
					}

					strcat_s(szLine, "\n");
					fileRcOut.Write(szLine, strlen(szLine));
				}
				else
				{
					szLine[iIndex++] = byteRead;
				}

			}

			fileRc.Close();
			fileRcOut.Close();
			SetFileAttributes(lpszRCFile, GetFileAttributes(lpszRCFile) & ~FILE_ATTRIBUTE_READONLY);
			DeleteFile(lpszRCFile);
			MoveFile(strRcOut, lpszRCFile);
		}
		else
		{
			fileRcOut.Close();
		}
	}
}

UINT16 GetFileHeader(LPCTSTR szConfFilePath)
{
	UINT16 head = 0;

	CFile fileRc;
	if (fileRc.Open(szConfFilePath, CFile::modeRead))
	{
		if (fileRc.Read(&head, sizeof(head)) > 0)
		{
			//ANSI ：　　　　　　　  无格式定义；
			//Unicode ：　　　　　　前两个字节为 FFFE ；
			//Unicode big endian ：　前两字节为 FEFF ；　
			//UTF - 8 ：　　　　　　  前两字节为 EFBB ；
			if (head == 0xfeff)
			{
			}
			else if (head == 0xfeff)
			{
			}
			else if (0xbbef)
			{
				ASSERT(FALSE);
				head = 0;
			}
			else
			{
				head = 0;
			}
		}
	}

	fileRc.Close();

	return head;
}



void  ReadIniCommon()
{
	CIniFile rIniFile;
	if (FALSE == PathFileExists(MIABUILD_PATH))
	{
		MessageBoxW(NULL, _T("提示"), _T("本地miabuild文件不存在"), MB_OK);
		return;
	}
	rIniFile.SetFileName(MIABUILD_PATH);
	rIniFile.GetStr(_T("Common"), _T("FileDescription"), szFileDiscription, MAX_PATH - 1);
	rIniFile.GetStr(_T("Common"), _T("CompanyName"), szCompanyName, MAX_PATH - 1);
	rIniFile.GetStr(_T("Common"), _T("LegalCopyright"), szLegalCopyright, MAX_PATH - 1);
	rIniFile.GetStr(_T("Common"), _T("OriginalFilename"), szOriginalFilename, MAX_PATH - 1);
	rIniFile.GetStr(_T("Common"), _T("ProductName"), szProductName, MAX_PATH - 1);
	rIniFile.GetStr(_T("Common"), _T("InternalName"), szInternalName, MAX_PATH - 1);

	INT32 nMajorVersion = rIniFile.GetInt(_T("Version"), _T("MajorVersion"));
	INT32 nMinorVersion = rIniFile.GetInt(_T("Version"), _T("MinorVersion"));
	INT32 nTinyVersion = rIniFile.GetInt(_T("Version"), _T("TinyVersion"));
	INT32 nPersonalVersion = rIniFile.GetInt(_T("Version"), _T("PersonalVersion"));

	_stprintf_s(szFileVersion, _T("%d.%d.%d.%d"), nMajorVersion, nMinorVersion, nTinyVersion, nPersonalVersion);
	_stprintf_s(szProductVersion, _T("%d.%d.%d.%d"), nMajorVersion, nMinorVersion, nTinyVersion, nPersonalVersion);
}



void ModifySingleRC(LPCTSTR lpszRCFile)
{
	UINT16 head = GetFileHeader(lpszRCFile);
	if (0 == head)
	{
		ModifyRcA(lpszRCFile);
	}
	else
	{
		ModifyRcW(lpszRCFile);
	}
}