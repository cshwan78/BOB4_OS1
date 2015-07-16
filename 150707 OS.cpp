// 150707 OS.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"
#include "Strsafe.h"
#include "stdint.h"
#include <iostream>


/**
* @brief
* @param
* @see
* @remarks
* @code
* @endcode
* @return
**/
void print(_In_ const char* fmt, _In_ ...)
{
	char log_buffer[2048];
	va_list args;

	va_start(args, fmt);
	HRESULT hRes = StringCbVPrintfA(log_buffer, sizeof(log_buffer), fmt, args);
	if (S_OK != hRes)
	{
		fprintf(
			stderr,
			"%s, StringCbVPrintfA() failed. res = 0x%08x",
			__FUNCTION__,
			hRes
			);
		return;
	}

	OutputDebugStringA(log_buffer);
	fprintf(stdout, "%s \n", log_buffer);
}


/**
* @brief
* @param
* @see
* @remarks
* @code
* @endcode
* @return
**/
bool create_bob_txt()
{
	// current directory 를 구한다.
	wchar_t *buf = NULL;
	uint32_t buflen = 0;
	buflen = GetCurrentDirectoryW(buflen, buf);
	if (0 == buflen)
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		return false;
	}

	buf = (PWSTR)malloc(sizeof(WCHAR)* buflen);
	if (0 == GetCurrentDirectoryW(buflen, buf))
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		free(buf);
		return false;
	}

	// current dir \\ bob.txt 파일명 생성
	wchar_t file_name[260];
	wchar_t file_name2[260];
	if (!SUCCEEDED(StringCbPrintfW(
		file_name,
		sizeof(file_name),
		L"%ws\\bob.txt",
		buf)))
	{
		print("err, can not create file name");
		free(buf);
		return false;
	}
	if (!SUCCEEDED(StringCbPrintfW(
		file_name2,
		sizeof(file_name2),
		L"%ws\\bob2.txt",
		buf)))
	{
		print("err, can not create file name");
		free(buf);
		return false;
	}
	free(buf); buf = NULL;

	/*if (true == is_file_existsW(file_name))
	{
		::DeleteFileW(file_name);
	}
*/
	// 파일 생성
	HANDLE file_handle = CreateFileW(
		file_name,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
		return false;
	}

	// 파일에 데이터 쓰기
	DWORD bytes_written = 0;
	WCHAR string_buf[1024];
	char utfbuf[2048];
	int utflen;
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세\n")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}
	utflen = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, utfbuf, 0, 0, 0);
	utflen = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, utfbuf, utflen, 0, 0);

	if (!WriteFile(file_handle, utfbuf, utflen-1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	// 영어로 쓰기
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"All work and no play makes jack a dull boy.\n")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}
	utflen = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, utfbuf, 0, 0, 0);
	utflen = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, utfbuf, utflen, 0, 0);

	if (!WriteFile(file_handle, utfbuf, utflen-1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	WCHAR string_bufa[1024];
	if (!SUCCEEDED(StringCbPrintfW(
		string_bufa,
		sizeof(string_bufa),
		L"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세\n")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	utflen = WideCharToMultiByte(CP_UTF8, 0, string_bufa, -1, utfbuf, 0, 0, 0);
	utflen = WideCharToMultiByte(CP_UTF8, 0, string_bufa, -1, utfbuf, utflen, 0, 0);
	if (!WriteFile(file_handle, utfbuf, utflen-1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	
	// 영어로 쓰기
	if (!SUCCEEDED(StringCbPrintfW(
		string_bufa,
		sizeof(string_bufa),
		L"All work and no play makes jack a dull boy.\n")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	utflen = WideCharToMultiByte(CP_UTF8, 0, string_bufa, -1, utfbuf, 0, 0, 0);
	utflen = WideCharToMultiByte(CP_UTF8, 0, string_bufa, -1, utfbuf, utflen, 0, 0);
	if (!WriteFile(file_handle, utfbuf, utflen, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}
	// 파일 닫기
	CloseHandle(file_handle);

	
	CopyFileW( file_name, file_name2 , false);
	
	HANDLE file_handle2 = CreateFileW(
		file_name2,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
		return false;
	}



	char readed_buf[2048];
	WCHAR Wbuf[1024];
	DWORD dwRead;
	int r, i ;
	r = ReadFile(file_handle2, readed_buf, 2048, &dwRead, NULL);
	
	MultiByteToWideChar(CP_UTF8, 0, readed_buf, dwRead, Wbuf, 1024);
	WideCharToMultiByte(CP_ACP, 0, Wbuf, 1024, readed_buf, 2048, 0, 0);
		
	printf("%s", readed_buf);
	CloseHandle(file_handle2);
	//DeleteFileW(file_name);

	//Read via mapped io
	file_handle2 = CreateFileW(
		file_name2,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file_handle2 == INVALID_HANDLE_VALUE)
	{
		print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
		return false;
	}

	HANDLE file_map = CreateFileMapping(
		file_handle2,
		NULL,
		PAGE_READONLY,
		0,
		0,
		NULL
		);

	PCHAR file_view = (PCHAR)MapViewOfFile(
		file_map,
		FILE_MAP_READ,
		0,
		0,
		0
		);
	char fileviewbuf[2048];
	for (i = 0; file_view[i]; i++){
		fileviewbuf[i] = file_view[i];
	}

	fileviewbuf[i] = 0;
	UnmapViewOfFile(file_view);
	CloseHandle(file_map);
	CloseHandle(file_handle2);
	printf("\n\n Read by mapped io \n\n");
	MultiByteToWideChar(CP_UTF8, 0, fileviewbuf, dwRead, Wbuf, 1024);
	WideCharToMultiByte(CP_ACP, 0, Wbuf, 1024, fileviewbuf, 2048, 0, 0);
	printf("%s", fileviewbuf);



	DeleteFile(file_name);
	DeleteFile(file_name2);


	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("Hello world.");
	create_bob_txt();
	return 0;
}
