#define IR_IMPLEMENT
#include <ir_utf.h>
#include <stdio.h>
#ifdef _WIN32
	#include <Windows.h>
#endif

//So, algorithm of Visual studio compiler:
//UTF8, no BOM -> strings in normal UTF8, wide strings are trash
//UTF8/UTF16LE/UTF16BE, with BOM -> VS tries to convert source in host encoding (1251 in my case)
//If convertion fails, '?' is used
//Wide strings are normal UTF16 Little Endian

//So, for test the source must be saved in UTF8 without BOM
//It is the most predictable and cross-platform case

void printutf32(unsigned int *s)
{
	while (*s != 0)
	{
		printf("%u ", *s);
		s++;
	}
};

int main(void)
{
	const char *hello = "Hello Привет こんにちは!";
	
	ir_utf_init();
	ir_utf_c.init();
	ir_utf_utf8.init();
	ir_utf_utf16.init();
	ir_utf_utf32.init();
	ir_utf_1251.init();
	ir_utf_866.init();
	
	printf("Original: %s\n", hello);
	printf("C: %s\n", (char*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_c));
	printf("UTF8: %s\n", (char*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_utf8));
	printf("UTF16: %ls\n", (wchar_t*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_utf16));
	printf("UTF32: "); printutf32((unsigned int*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_utf32)); printf("\n");
	printf("1251: %s\n", (char*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_1251));
	printf("866: %s\n", (char*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_866));

	#ifdef _WIN32
		const wchar_t *whello = (wchar_t*)ir_utf_buffer_recode(&ir_utf_utf8, hello, '*', &ir_utf_utf16);
		DWORD written;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), whello, wcslen(whello), &written, (LPVOID)0);
	#endif

	ir_utf_free();
	getchar();

	return 0;
};