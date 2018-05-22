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
			TAG_FIELD(long, plane);
			TAG_FIELD(long, back_child);
			TAG_FIELD(long, front_child);
		}; static_assert( sizeof(bsp3d_node) == 0xC );

		struct collision_leaf
		{
			TAG_FIELD(unsigned short, flags);
			TAG_FIELD(short, reference_count);
			TAG_FIELD(long, first_reference, bsp2d_reference);
		}; static_assert( sizeof(collision_leaf) == 0x8 );

		struct bsp2d_reference
		{
			TAG_FIELD(long, plane);
			TAG_FIELD(long, bsp2d_node);
		}; static_assert( sizeof(bsp2d_reference) == 0x8 );

		struct bsp2d_node
		{
			TAG_FIELD(real_plane2d, plane);
			TAG_FIELD(long, left_child);
			TAG_FIELD(long, right_child);
		}; static_assert( sizeof(bsp2d_node) == 0x14 );

		struct collision_surface
		{
			TAG_FIELD(long, plane);
			TAG_FIELD(long, first_edge);
			TAG_FIELD(Flags::collision_surface_flags, flags);
			TAG_FIELD(sbyte, breakable_surface);
			TAG_FIELD(short, material);
		}; static_assert( sizeof(collision_surface) == 0xC );

		struct collision_edge
		{
			TAG_FIELD(long, start_vertex);
			TAG_FIELD(long, end_vertex);
			TAG_FIELD(long, forward_edge);
			TAG_FIELD(long, reverse_edge);
			TAG_FIELD(long, left_surface);
			TAG_FIELD(long, right_surface);
		}; static_assert( sizeof(collision_edge) == 0x18 );

		struct collision_vertex
		{
			TAG_FIELD(real_point3d, point);
			TAG_FIELD(long, first_edge);
		}; static_assert( sizeof(collision_vertex) == 0x10 );

		struct collision_bsp
		{
			Yelo::TagBlock<bsp3d_node> bsp3d_nodes;
			TAG_TBLOCK(planes, real_plane3d);
			TAG_TBLOCK(leaves, collision_leaf);
			struct {
				TAG_TBLOCK(references, bsp2d_reference);
				TAG_TBLOCK(nodes, bsp2d_node);
			}bsp2d;
			TAG_TBLOCK(surfaces, collision_surface);
			TAG_TBLOCK(edges, collision_edge);
			TAG_TBLOCK(vertices, collision_vertex);
		}; static_assert( sizeof(collision_bsp) == 0x60 );
	};
};
