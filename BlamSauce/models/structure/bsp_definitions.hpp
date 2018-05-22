#include <precompile.h>
#pragma once
#include "../../tags/group/markup.h"
#include "../../render/rasterizer/geometry.hpp"
#include "../../game/objects/object_lights.hpp"
#include "../../cache/predicted_resources.hpp"

namespace Yelo::TagGroups {
	struct structure_collision_material {
		TAG_FIELD(tag_reference, shader, 'shdr');
		struct {
					unsigned short : 16;
			short shader_material_type; // Enums::material_type or NONE if shdr is null
		}                        runtime;
	};
	struct structure_node {
		short skip[3];
	};
	struct structure_leaf {
		byte             skip[6];
							  unsigned short : 16;
		TAG_FIELD(short, cluster);
		TAG_FIELD(short, reference_count, "surface");
		TAG_FIELD(long, first_reference, "surface");
	};
	struct structure_surface_reference {
		TAG_FIELD(long, surface);
		TAG_FIELD(long, index);
	};
	struct structure_surface {
		TAG_FIELD(short, a)[3];
	};
	struct structure_bsp_material {
		TAG_FIELD(tag_reference, shader, 'shdr');
		TAG_FIELD(short, shader_permutation);
		TAG_FIELD(word_flags, flags);
		TAG_FIELD(long, surfaces, structure_surface);
		TAG_FIELD(long, surface_count);
		TAG_FIELD(real_point3d, centroid);
		Objects::s_object_lighting object_lighting;
		TAG_FIELD(real_plane3d, plane);
		TAG_FIELD(short, breakable_surface);
		unsigned short : 16;

		Rasterizer::rasterizer_vertex_buffer
			vertices, lightmap_vertices;
		TAG_FIELD(tag_data, uncompressed_vertices);
		TAG_FIELD(tag_data, compressed_vertices);
	}; static_assert(sizeof(structure_bsp_material) == 0x100);
	struct structure_bsp_lightmap {
		TAG_FIELD(short, bitmap);
		unsigned short : 16;
		TAG_PAD(sbsp_pad0B,long, 4);
		TAG_TBLOCK(materials, structure_bsp_material);
	};

	struct structure_subcluster {
		struct {
			real_bounds x, y, z;
		}                           world_bounds;
		TAG_TBLOCK(surface_indices, long);
	};
	struct structure_mirror {
		TAG_FIELD(real_plane3d, plane);
		TAG_PAD(sbsp_pad0A,long, 5);
		TAG_FIELD(tag_reference, shader);
		TAG_TBLOCK(vertices, real_point3d);
	};
	struct structure_cluster {
		TAG_FIELD(short, sky);
		TAG_FIELD(short, fog);
		TAG_FIELD(short, background_sound); // block index
		TAG_FIELD(short, sound_environment); // block index
		TAG_FIELD(short, weather); // block index
		TAG_FIELD(short, transition_structure_bsp);
		TAG_PAD(sbsp_pad09,long, 1 + 6);
		TAG_TBLOCK(predicted_resources, predicted_resource);
		TAG_TBLOCK(subclusters, structure_subcluster);
		TAG_FIELD(short, first_lens_flare_marker_index);
		TAG_FIELD(short, lens_flare_marker_count);
		TAG_TBLOCK(surface_indices, long);
		TAG_BLOCK(mirrors, structure_mirror);
		TAG_BLOCK(portals, short);
	}; static_assert(sizeof(structure_cluster) == 0x68);

	struct s_structure_fog_plane {
		TAG_FIELD(short, front_region, s_structure_fog_region);
		short runtime_material_type; // NONE or _material_type_water
		TAG_FIELD(real_plane3d, plane);
		TAG_TBLOCK(vertices, real_vector3d);
	};
	struct s_structure_fog_region {
		TAG_PAD(sbsp_pad08,long, 9);
		TAG_FIELD(short, fog_palette); // block index
		TAG_FIELD(short, weather_palette); // block index
	};
	struct s_structure_fog_palette {
		TAG_FIELD(tag_string, name);
		TAG_FIELD(tag_reference, fog, 'fog ');
		TAG_PAD(sbsp_pad06,long, 1);
		TAG_FIELD(tag_string, fog_scale_function);
		TAG_PAD(sbsp_pad07,long, 11 + 2);
	};
	struct structure_weather_palette_entry {
		TAG_FIELD(tag_string, name);
		TAG_FIELD(tag_reference, particle_system, 'rain');
		TAG_PAD(sbsp_pad02,long, 1);
		TAG_FIELD(tag_string, particle_system_scale_function);
		TAG_PAD(sbsp_pad03,long, 11);
		TAG_FIELD(tag_reference, wind, 'wind');
		TAG_FIELD(real_vector3d, wind_direction);
		TAG_FIELD(real, wind_magnitude);
		TAG_PAD(sbsp_pad04, long, 1);
		TAG_FIELD(tag_string, wind_scale_function);
		TAG_PAD(sbsp_pad05,long, 11);
	};

	struct structure_background_sound_palette_entry {
		TAG_FIELD(tag_string, name);
		TAG_FIELD(tag_reference, background_sound, 'lsnd');
		TAG_PAD(sbsp_pad0, long, 1);
		TAG_FIELD(tag_string, scale_function);
		TAG_PAD(sbsp_pad01, tag_string, 1);
	};
	struct structure_sound_environment_palette_entry {
		TAG_FIELD(tag_string, name);
		TAG_FIELD(tag_reference, sound_environment, 'snde');
		TAG_PAD(sbsp_pad0,tag_string, 1);
	};

	// TODO: move to structures\leaf_map.hpp
	struct s_leaf_map {
		TagGroups::collision_bsp *collision; // initialized by postprocess proc, only valid in tags builds
		TAG_BLOCK(leaves, map_leaf);
		TAG_BLOCK(portals, leaf_connection);
	}; static_assert(sizeof(s_leaf_map) == 0x1C);

	struct structure_bsp {
		enum { k_group_tag = 'sbsp' };

		TAG_FIELD(tag_reference, lightmap_bitmaps, 'bitm');
		TAG_FIELD(real_bounds, vehicle_heights, "floor", "ceiling");
		TAG_PAD(sbsp_pad0, long, 5); // Useless? Removed in H2

		Objects::s_object_lighting default_lighting; // doesn't expose distant_light_count
											unsigned long : 32; // Useless? Wasn't removed in H2, but can't find any code references in H1

		TAG_TBLOCK(collision_materials, structure_collision_material);
		TAG_TBLOCK(collision_bsp, collision_bsp);
		TAG_TBLOCK(nodes, structure_node);

		struct {
			real_bounds x, y, z;
		}                          world_bounds;

		TAG_TBLOCK(leafs, structure_leaf);
		TAG_TBLOCK(leaf_surfaces, structure_surface_reference);
		TAG_TBLOCK(surfaces, structure_surface);

		TAG_TBLOCK(lightmaps, structure_bsp_lightmap);
		PAD_TYPE(tag_block); // Useless? Removed in H2

		TAG_BLOCK(lens_flares, structure_bsp_lens_flare_block);
		TAG_BLOCK(lens_flare_markers, structure_bsp_lens_flare_marker_block);

		TAG_TBLOCK_(clusters, structure_cluster);
		TAG_FIELD(tag_data, cluster_data);
		TAG_BLOCK(cluster_portals, cluster_portal);
		PAD_TYPE(tag_block); // Useless? Removed in H2

		TAG_BLOCK(breakable_surfaces, structure_breakable_surface);
		TAG_BLOCK(fog_planes, s_structure_fog_plane);
		TAG_TBLOCK(fog_regions, s_structure_fog_region);
		TAG_TBLOCK(fog_palette, s_structure_fog_palette);
		PAD_TYPE(tag_block); // Useless? Removed in H2
		PAD_TYPE(tag_block); // Useless? Removed in H2

		TAG_TBLOCK(weather_palette, structure_weather_palette_entry);
		TAG_BLOCK(weather_polyhedra, structure_weather_polyhedron);
		PAD_TYPE(tag_block); // Useless? Removed in H2 (new block was added)
		PAD_TYPE(tag_block); // Useless? Removed in H2 (new block was added)

		TAG_TBLOCK(pathfinding_surfaces, byte);
		TAG_TBLOCK(pathfinding_edges, byte);

		TAG_TBLOCK(background_sound_palette, structure_background_sound_palette_entry);
		TAG_TBLOCK(sound_environment_palette, structure_sound_environment_palette_entry);
		TAG_FIELD(tag_data, sound_pas_data);
		PAD_TYPE(tag_block); // Useless? Removed in H2
		PAD_TYPE(tag_block); // Useless? Removed in H2

		TAG_BLOCK(markers, structure_marker);
		TAG_BLOCK(detail_objects, structure_detail_object_data);
		TAG_BLOCK(runtime_decals, structure_runtime_decal);
					 unsigned __int64 : 64; // Useless? Removed in H2
		s_leaf_map leaf_map;

	}; static_assert(sizeof(structure_bsp) == 0x288);

	struct structure_bsp_header {
		structure_bsp *bsp;
		//////////////////////////////////////////////////////////////////////////
		// only used\initialized for Xbox targets
		struct {
			long count;
			void *address;
		} vertex_buffer, lightmap_vertex_buffer;

		tag signature;
	}; static_assert(sizeof(structure_bsp_header) == 0x18);
};
