/*
	Part of the Ironic Project. Redistributed under MIT License, which means:
		- Do whatever you want
		- Please keep this notice and include the license file to your project
		- I provide no warranty
	To get help with installation, visit README
	Created by github.com/Meta-chan, k.sovailo@gmail.com
	Reinventing bicycles since 2020
*/

#ifndef IR_HINTERNET_RESOURCE_IMPLEMENTATION
#define IR_HINTERNET_RESOURCE_IMPLEMENTATION

HINTERNET ir::HInternetIniterFreer::initvalue = NULL;

void ir::HInternetIniterFreer::free(HINTERNET hinternet)
{
	if (hinternet != NULL && hinternet != INVALID_HANDLE_VALUE) WinHttpCloseHandle(hinternet);
}

#endif	//#ifndef IR_HINTERNET_RESOURCE_IMPLEMENTATION