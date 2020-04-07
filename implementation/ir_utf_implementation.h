/*
	Part of the Ironic Project. Redistributed under MIT License, which means:
		- Do whatever you want
		- Please keep this notice and include the license file to your project
		- I provide no warranty
	To get help with installation, visit README
	Created by @meta-chan, k.sovailo@gmail.com
	Reinventing bicycles since 2020
*/

#ifndef IR_UTF_IMPLEMENTATION
#define IR_UTF_IMPLEMENTATION

#include <stdlib.h>

struct UTF_Codec utf_c;
struct UTF_Codec utf_utf8;
struct UTF_Codec utf_utf16;
struct UTF_Codec utf_utf32;
struct UTF_Codec utf_1251;

#pragma region ASCII

unsigned int utf_c_charsize()
{
	return 1;
};

unsigned int utf_c_encode(unsigned int code, void *symbols, unsigned int errcode)
{
	char *s = (char*)symbols;
	if (code < 0x80)
	{
		if (s != (void*)0) s[0] = code;
		return 1;
	}
	else return utf_c_encode(errcode, symbols, ' ');
};

unsigned int utf_c_decode(const void *string, unsigned int *nsymbols)
{
	const char *s = (const char*)string;
	unsigned int nskipped = 0;
	while (1)
	{
		if (s[0] < 0x80)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 1;
			return (s[0] & 0x7F);
		}
		else
		{
			nskipped++;
			s++;
		}
	}
};

void utf_c_free(void)
{
};

unsigned char utf_c_init(void)
{
	utf_c.charsize = utf_c_charsize;
	utf_c.encode = utf_c_encode;
	utf_c.decode = utf_c_decode;
	utf_c.free = utf_c_free;
	return 1;
};

#pragma endregion

#pragma region UTF8

unsigned int utf_utf8_charsize()
{
	return 1;
};

unsigned int utf_utf8_encode(unsigned int code, void *symbols, unsigned int errcode)
{
	char *s = (char*)symbols;
	if (code < 0x80)
	{
		if (s != (void*)0) s[0] = code;
		return 1;
	}
	else if (code < 0x800)
	{
		if (s != (void*)0)
		{
			s[0] = 0xC0 | ((code >> 6) & 0x1F);
			s[1] = 0x80 | (code & 0x3F);
		}
		return 2;
	}
	else if (code < 0x10000)
	{
		if (s != (void*)0)
		{
			s[0] = 0xE0 | ((code >> 12) & 0x0F);
			s[1] = 0x80 | ((code >> 6) & 0x3F);
			s[2] = 0x80 | (code & 0x3F);
		}
		return 3;
	}
	else if (code < 0x110000)
	{
		if (s != (void*)0)
		{
			s[0] = 0xE0 | ((code >> 18) & 0x07);
			s[1] = 0x80 | ((code >> 12) & 0x3F);
			s[2] = 0x80 | ((code >> 6) & 0x3F);
			s[3] = 0x80 | (code & 0x3F);
		}
		return 4;
	}
	else return utf_utf8_encode(errcode, symbols, ' ');
};

unsigned int utf_utf8_decode(const void *string, unsigned int *nsymbols)
{
	const char *s = (const char*)string;
	unsigned int nskipped = 0;
	while (1)
	{
		if ((s[0] & 0x80) == 0)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 1;
			return s[0];
		}
		else if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 2;
			return ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
		}
		else if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 3;
			return ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
		}
		else if ((s[0] & 0xF8) == 0xF0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 4;
			return ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
		}
		else
		{
			nskipped++;
			s++;
		}
	}
};

void utf_utf8_free(void)
{
};

unsigned char utf_utf8_init(void)
{
	utf_utf8.charsize = utf_utf8_charsize;
	utf_utf8.encode = utf_utf8_encode;
	utf_utf8.decode = utf_utf8_decode;
	utf_utf8.free = utf_utf8_free;
	return 1;
};

#pragma endregion

#pragma region UTF16

unsigned int utf_utf16_charsize()
{
	return 2;
};

unsigned int utf_utf16_encode(unsigned int code, void *symbols, unsigned int errcode)
{
	wchar_t *s = (wchar_t*)symbols;
	if (code < 0x10000 && !(code >= 0xD800 && code < 0xE000))
	{
		if (s != (void*)0) s[0] = code;
		return 1;
	}
	else if (code < 0x110000)
	{
		if (s != (void*)0)
		{
			s[0] = ((code - 0x10000) >> 10) & 0x3FF;
			s[1] = (code - 0x10000) & 0x3FF;
		}
		return 2;
	}
	else return utf_c_encode(errcode, symbols, ' ');
};

unsigned int utf_utf16_decode(const void *string, unsigned int *nsymbols)
{
	const char *s = (const char*)string;
	unsigned int nskipped = 0;
	while (1)
	{
		if (!(s[0] >= 0xD800 && s[0] < 0xE000))
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 1;
			return s[0];
		}
		else if ((s[0] >= 0xD800 && s[0] < 0xDC00) && (s[1] >= 0xDC00 && s[1] < 0xE000))
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 2;
			return 0;
		}
		else
		{
			nskipped++;
			s++;
		}
	}
};

void utf_utf16_free(void)
{
};

unsigned char utf_utf16_init(void)
{
	utf_utf16.charsize = utf_utf16_charsize;
	utf_utf16.encode = utf_utf16_encode;
	utf_utf16.decode = utf_utf16_decode;
	utf_utf16.free = utf_utf16_free;
	return 1;
};

#pragma endregion

#pragma region UTF32

unsigned int utf_utf32_charsize()
{
	return 4;
};

unsigned int utf_utf32_encode(unsigned int code, void *symbols, unsigned int errcode)
{
	if (symbols != (void*)0) *((unsigned int*)symbols) = code;
	return 1;
};

unsigned int utf_utf32_decode(const void *string, unsigned int *nsymbols)
{
	if (nsymbols != (void*)0) *nsymbols = 1;
	return *((unsigned int*) nsymbols);
};

void utf_utf32_free(void)
{
};

unsigned char utf_utf32_init(void)
{
	utf_utf32.charsize = utf_utf32_charsize;
	utf_utf32.encode = utf_utf32_encode;
	utf_utf32.decode = utf_utf32_decode;
	utf_utf32.free = utf_utf32_free;
	return 1;
};

#pragma endregion

#pragma region 1251

const unsigned short int utf_1251_symbols[0x40] =
{
	0x402,	0x403,	0x201A,	0x453,	0x201E,	0x2026,	0x2020,	0x2021,	0x20AC,	0x2030,	0x409,	0x2039,	0x40A,	0x40C,	0x40B,	0x40F,
	0x452,	0x2018,	0x2019,	0x201C,	0x201D,	0x2022,	0x2013,	0x2014,	0x0,	0x2122,	0x459,	0x203A,	0x45A,	0x45C,	0x45B,	0x45F,
	0xA0,	0x40E,	0x45E,	0x408,	0xA4,	0x490,	0xA6,	0xA7,	0x401,	0xA9,	0x404,	0xAB,	0xAC,	0xAD,	0xAE,	0x407,
	0xB0,	0xB1,	0x406,	0x456,	0x491,	0xB5,	0xB6,	0xB7,	0x451,	0x2116,	0x454,	0xBB,	0x458,	0x405,	0x455,	0x457
};

unsigned int utf_1251_charsize()
{
	return 1;
};

unsigned int utf_1251_encode(unsigned int code, void *symbols, unsigned int errcode)
{
	char *s = (char*)symbols;
	
	if (code < 0x80)
	{
		if (s != (void*)0) s[0] = code;
		return 1;
	}
	else if (code >= 0x410 && code < 0x450)
	{
		if (s != (void*)0) s[0] = code - 0x410 + 0xC0;
		return 1;
	}
	else if (code >= 0xA0 && code <= 0x2122)
	{
		for (unsigned int i = 0; i < 0x40; i++)
		{
			//can be optimized with binar search
			if (utf_1251_symbols[i] == code)
			{
				if (s != (void*)0) s[0] = 0x80 + i;
				return 1;
			}
		}
		return utf_1251_encode(errcode, symbols, ' ');
	}
	else return utf_1251_encode(errcode, symbols, ' ');
};

unsigned int utf_1251_decode(const void *string, unsigned int *nsymbols)
{
	const char *s = (const char*)string;
	unsigned int nskipped = 0;
	while (1)
	{
		if (s[0] < 0x80)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 1;
			return s[0];
		}
		else if (s[0] < 0xC0)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 1;
			return utf_1251_symbols[s[0] - 0xC0];
		}
		else if (s[0] != 0x98)
		{
			if (nsymbols != (void*)0) *nsymbols = nskipped + 1;
			return s[0] - 0xC0 + 0x410;
		}
		else
		{
			nskipped++;
			s++;
		}
	}
};

void utf_1251_free(void)
{
};

unsigned char utf_1251_init(void)
{
	utf_1251.charsize = utf_1251_charsize;
	utf_1251.encode = utf_1251_encode;
	utf_1251.decode = utf_1251_decode;
	utf_1251.free = utf_1251_free;
	return 1;
};

#pragma endregion

unsigned int utf_recode(struct UTF_Codec *codec1, const void *string1, unsigned int errcode, struct UTF_Codec *codec2, void *string2)
{
	const char *s1 = (const char *)string1;
	char *s2 = (char *)string2;
	unsigned int c1 = codec1->charsize();
	unsigned int c2 = codec2->charsize();
	unsigned int i1 = 0;
	unsigned int i2 = 0;

	while (1)
	{
		unsigned int n1;
		unsigned int code = codec1->decode(s1 + c1 * i1, &n1);
		unsigned int n2 = codec2->encode(code, (s2 == (void*)0) ? s2 : (s2 + c2 * i2), errcode);

		if (code == 0) return i2;
		
		i1 += n1;
		i2 += n2;
	}
};

void *utf_alloc_recode(struct UTF_Codec *codec1, const void *string1, unsigned int errcode, struct UTF_Codec *codec2)
{
	unsigned int size = codec2->charsize() * (utf_recode(codec1, string1, errcode, codec2, (void*)0) + codec2->encode(0, (void*)0, errcode));
	void *result = malloc(size);
	if (result == (void*)0) return (void*)0;
	utf_recode(codec1, string1, errcode, codec2, result);
	return result;
};

//INIT AND FREE
void utf_init(void)
{
	utf_c.init = utf_c_init;
	utf_utf8.init = utf_utf8_init;
	utf_utf16.init = utf_utf16_init;
	utf_utf32.init = utf_utf32_init;
	utf_1251.init = utf_1251_init;
};

void utf_free(void)
{
	utf_c_free();
	utf_utf8_free();
	utf_utf16_free();
	utf_utf32_free();
	utf_1251_free();
};

#endif	//#ifndef IR_UTF_IMPLEMENTATION