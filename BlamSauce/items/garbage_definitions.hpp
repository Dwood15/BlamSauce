#pragma once
#include <precompile.h>
#include "item_definitions.hpp"

namespace Yelo::TagGroups
	{
		struct _garbage_definition
		{
			long:8 * sizeof(long) * 42;
		}; static_assert( sizeof(_garbage_definition) == 0xA8 );

		struct s_garbage_definition : s_item_definition
		{
			enum { k_group_tag = 'garb' };

			_garbage_definition garbage;
		};
	};

