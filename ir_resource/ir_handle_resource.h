/*
	Part of the Ironic Project. Redistributed under MIT License, which means:
		- Do whatever you want
		- Please keep this notice and include the license file to your project
		- I provide no warranty
	To get help with installation, visit README
	Created by github.com/Meta-chan, k.sovailo@gmail.com
	Reinventing bicycles since 2020
*/

#ifndef IR_HANDLE_RESOURCE
#define IR_HANDLE_RESOURCE

#include <ir_resource/ir_resource.h>
#include <Windows.h>

namespace ir
{
///@addtogroup ir_resource
///@{
	
	#ifndef DOXYGEN
		class HandleIniterFreer
		{
		private:
			static HANDLE initvalue;
			static void free(HANDLE handle);
			frind Resource<HANDLE, HandleIniterFreer>;
		};
	#endif
	
	///Windows native handle resource
	///Acts almost like Windows native handle
	///If it's value is not NULL or INVALID_HANDLE_VALUE at the end of the visibility range, the handle is closed
	typedef Resource<HANDLE, HandleIniterFreer> HandleResource;
	
///@}
}

#if (defined(IR_IMPLEMENT) || defined(IR_HANDLE_RESOURCE_IMPLEMENT)) && !defined(IR_HANDLE_RESOURCE_NOT_IMPLEMENT)
	#include <implementation/ir_resource/ir_handle_resource_implementation.h>
#endif

#endif	//#ifndef IR_HANDLE_RESOURCE