/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/rasterizer/rasterizer_geometry.hpp>

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_regions_per_model = 8,

			k_maximum_nodes_per_model = 64,
			k_maximum_nodes_per_model_halo_stock = 44, // 'Cause Xbox1 has limits

			k_maximum_nodes_per_model_geometry_part = 22,

			k_number_of_rows_per_node_matrix = 4,
		};
	};

	namespace TagGroups
	{
		struct model_marker_instance
		{
			sbyte region_index;
			sbyte permutation_index;
			sbyte node_index;
			unsigned char : 8;
			real_point3d translation;
			real_quaternion rotation;
		}; static_assert( sizeof(model_marker_instance) == 0x20 ); // max count: 32
		struct model_markers
		{
			tag_string name;
			short magic_identifier;
			unsigned short : 16;
			long:8 * sizeof(long) * 4;
			Yelo::TagBlock<const model_marker_instance> instances;
		}; static_assert( sizeof(model_markers) == 0x40 ); // max count: 256

		struct model_node
		{
			tag_string name;
			short next_sibling_node_index;
			short first_child_node_index;
			short parent_node_index;
			unsigned short : 16;
			//TAG_FIELD(real_point3d, default_translation);
			//TAG_FIELD(real_quaternion, default_rotation);
			//TAG_FIELD(real, node_distance_from_parent);
			real_orientation3d orientation;
			long:8 * sizeof(long) * 8;
			real_matrix4x3 inverse_matrix;
		}; static_assert( sizeof(model_node) == 0x9C ); // max count: 64

		struct model_region_permutation_marker
		{
			tag_string name;
			short node_index;
			unsigned short : 16;
			real_quaternion rotation;
			real_point3d translation;
			long:8 * sizeof(long) * 4;
		}; static_assert( sizeof(model_region_permutation_marker) == 0x50 ); // max count: 64
		struct gbxmodel_region_permutation
		{
			struct __flags
			{
				unsigned long cannot_be_chosen_randomly_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			tag_string name;
			__flags flags;
			long:8 * sizeof(long) * 7;
			short detail_geometry_index[Enums::k_number_of_geometry_detail_levels];
			unsigned short : 16;
			Yelo::TagBlock<const model_region_permutation_marker> markers;
		}; static_assert( sizeof(gbxmodel_region_permutation) == 0x58 ); // max count: 32
		struct gbxmodel_region
		{
			tag_string name;
			long:8 * sizeof(long) * 8;
			Yelo::TagBlock<const gbxmodel_region_permutation> permutations;
		}; static_assert( sizeof(gbxmodel_region) == 0x4C ); // max count: 32


		struct model_triangle
		{
			short vertex0_index;
			short vertex1_index;
			short vertex2_index;
		}; static_assert( sizeof(model_triangle) == 0x6 ); // max count: 65535
		struct gbxmodel_geometry_part
		{
			struct __flags
			{
				unsigned long stripped_internal_bit:1;
				unsigned long zoner_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			__flags flags;
			short shader_index;
			sbyte prev_filthy_part_index;
			sbyte next_filthy_part_index;
			short centroid_primary_node;
			short centroid_secondary_node;
			real_fraction centroid_primary_weight;
			real_fraction centroid_secondary_weight;
			real_point3d centroid;
			Yelo::TagBlock<const Rasterizer::model_vertex_uncompressed> uncompressed_vertices; // max count: 65535
			Yelo::TagBlock<const Rasterizer::model_vertex_compressed> compressed_vertices; // max count: 65535
			Yelo::TagBlock<const model_triangle> triangles;
			Rasterizer::rasterizer_triangle_buffer triangle_buffer;
			Rasterizer::rasterizer_vertex_buffer vertex_buffer;
			byte:8 * sizeof(byte) * 1;
			byte:8 * sizeof(byte) * 1;
			byte:8 * sizeof(byte) * 1;
			sbyte num_nodes;

			sbyte node_table[Enums::k_maximum_nodes_per_model_geometry_part];
			unsigned short : 16;
		}; static_assert( sizeof(gbxmodel_geometry_part) == 0x84 ); // max count: 32
		struct gbxmodel_geometry
		{
			struct __flags
			{
				unsigned long unused_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			__flags flags;
			long:8 * sizeof(long) * 8;
			Yelo::TagBlock<const gbxmodel_geometry_part> parts;
		}; static_assert( sizeof(gbxmodel_geometry) == 0x30 ); // max count: 256

		struct model_shader_reference
		{
			tag_reference shader;
			short permutation;
			unsigned short : 16;
			long:8 * sizeof(long) * 3;
		}; static_assert( sizeof(model_shader_reference) == 0x20 ); // max count: 64
		struct gbxmodel_definition
		{
			enum { k_group_tag = 'mod2' };

			struct __flags
			{
				unsigned long blend_shared_normals_bit:1;
				unsigned long parts_have_local_nodes_bit:1;
				unsigned long ignore_skinning_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			__flags flags;
			long node_list_checksum;
			real detail_level_cutoffs[Enums::k_number_of_geometry_detail_levels];
			short detail_level_node_counts[Enums::k_number_of_geometry_detail_levels];
			unsigned short : 16;
			long:8 * sizeof(long) * 2;
			real base_map_u_scale;
			real base_map_v_scale;
			long:8 * sizeof(long) * 29;
			Yelo::TagBlock<const model_markers> markers;
			Yelo::TagBlock<const model_node> nodes;
			Yelo::TagBlock<const gbxmodel_region> regions;
			Yelo::TagBlock<const gbxmodel_geometry> geometries;
			Yelo::TagBlock<const model_shader_reference> shaders;
		}; static_assert( sizeof(gbxmodel_definition) == 0xE8 ); // max count: 1

		struct model_definition
		{
			enum { k_group_tag = 'mode' };
		};
	};
};
