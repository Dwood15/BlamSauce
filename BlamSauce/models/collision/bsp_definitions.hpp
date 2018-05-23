#pragma once
#include <precompile.h>

namespace Yelo
{
	namespace Flags
	{
		enum collision_surface_flags : byte_flags
		{
			_collision_surface_two_sided_bit,
			_collision_surface_invisible_bit,
			_collision_surface_climbable_bit,
			_collision_surface_breakable_bit,
		};
	};

	namespace TagGroups
	{
		struct bsp3d_node
		{
			long plane;
			long back_child;
			long front_child;
		}; static_assert( sizeof(bsp3d_node) == 0xC );

		struct collision_leaf
		{
			unsigned short flags;
			short reference_count;
			long first_reference;
		}; static_assert( sizeof(collision_leaf) == 0x8 );

		struct bsp2d_reference
		{
			long plane;
			long bsp2d_node;
		}; static_assert( sizeof(bsp2d_reference) == 0x8 );

		struct bsp2d_node
		{
			real_plane2d plane;
			long left_child;
			long right_child;
		}; static_assert( sizeof(bsp2d_node) == 0x14 );

		struct collision_surface
		{
			long plane;
			long first_edge;
			Flags::collision_surface_flags flags;
			sbyte breakable_surface;
			short material;
		}; static_assert( sizeof(collision_surface) == 0xC );

		struct collision_edge
		{
			long start_vertex;
			long end_vertex;
			long forward_edge;
			long reverse_edge;
			long left_surface;
			long right_surface;
		}; static_assert( sizeof(collision_edge) == 0x18 );

		struct collision_vertex
		{
			real_point3d point;
			long first_edge;
		}; static_assert( sizeof(collision_vertex) == 0x10 );

		struct collision_bsp
		{
			Yelo::TagBlock<bsp3d_node> bsp3d_nodes;
			Yelo::TagBlock<const real_plane3d> planes;
			Yelo::TagBlock<const collision_leaf> leaves;
			struct {
				Yelo::TagBlock<const bsp2d_reference> references;
				Yelo::TagBlock<const bsp2d_node> nodes;
			}bsp2d;
			Yelo::TagBlock<const collision_surface> surfaces;
			Yelo::TagBlock<const collision_edge> edges;
			Yelo::TagBlock<const collision_vertex> vertices;
		}; static_assert( sizeof(collision_bsp) == 0x60 );
	};
};
