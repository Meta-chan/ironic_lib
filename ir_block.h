/*
	Part of the Ironic Project. Redistributed under MIT License, which means:
		- Do whatever you want
		- Please keep this notice and include the license file to your project
		- I provide no warranty
	To get help with installation, visit README
	Created by @meta-chan, k.sovailo@gmail.com
	Reinventing bicycles since 2020
*/

#ifndef IR_BLOCK
#define IR_BLOCK

namespace ir
{
	class BufferBlock
	{
	public:
		unsigned int used;
		unsigned int reserved;
		void *data;
		
		BufferBlock();
		bool reserve(unsigned int newsize);
		void free();
	};

	class Block
	{
	public:
		unsigned int size;
		void *data;
		
		Block();
		Block(unsigned int size, void *data);
		Block(BufferBlock bufferblock);
	};

	class ConstBlock
	{
	public:
		unsigned int size;
		const void *data;
		
		ConstBlock();
		ConstBlock(unsigned int size, const void *data);
		ConstBlock(Block block);
		ConstBlock(BufferBlock bufferblock);
	};
};

#if (defined (IR_BLOCK_IMPLEMENT) || defined(IR_IMPLEMENT))
	#include "implementation/ir_block_implementation.h"
#endif

#endif //#ifndef IR_BLOCK