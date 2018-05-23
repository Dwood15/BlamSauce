/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <precompile.h>
#include "object_types.h"
#include "../../cseries/base.h"
#include "../../memory/datum_index.h"
#include "../../math/matrix_math.h"
#include "../../memory/data.h"
#include "../../scenario/structures.h"
#include "../../memory/array.h"
#include "../../memory/memory_pool.h"
#include "../../scenario/scenario.h"
#include "object_definitions.hpp"
#include "../../models/animations/definitions.hpp"
#include "object_structures.h"

namespace Yelo {
	namespace Enums {
		enum {
			// Stock game state allocation size for the object memory pool
			// When running in editor tools, this and the max number of objects is increased by 5x
				k_object_memory_pool_allocation_size = 0x200000,
		};
	};

	namespace Flags {
		enum object_header_flags : byte_flags {
			_object_header_active_bit,
			_object_header_visible_bit,
			_object_header_newly_created_bit, // true until after the first call to the 
			_object_header_being_deleted_bit,
			_object_header_child_bit, // attached to another object (at a marker/node)
			_object_header_connected_to_map_bit,
			_object_header_automatic_deactivation_bit,
			_object_header_unk7_bit,
		};

		enum objects_find_flags : unsigned long {
			_objects_find_collideable_bit,
			_objects_find_noncollideable_bit,
		};
	};
};

namespace Yelo::Objects {
	struct s_object_header_datum : Memory::s_datum_base {
		Flags::object_header_flags flags;
		byte_enum                  object_type;
		short                      cluster_index;
		short                      data_size;
		union {
			void *address;

			s_object_data *_object; // Note: since 's_object_data' is the base of all object datums, we can do this

			// Allows us to implicitly treat 'address' as an specific object type ptr
			// in situations where we're programming for something more specific (eg, unit types only)
			struct s_scenery_datum       *_scenery;
			struct s_sound_scenery_datum *_sound_scenery;
			struct s_garbage_datum       *_garbage;
			struct s_projectile_datum    *_projectile;
			struct s_placeholder_datum   *_placeholder;

			struct s_device_datum              *_device;
			struct s_device_machine_datum      *_machine;
			struct s_device_control_datum      *_control;
			struct s_device_lightfixture_datum *_lightfixture;

			struct s_item_datum      *_item;
			struct s_weapon_datum    *_weapon;
			struct s_equipment_datum *_equipment;

			struct s_unit_datum    *_unit;
			struct s_biped_datum   *_biped;
			struct s_vehicle_datum *_vehicle;
		};
	}; static_assert(sizeof(s_object_header_datum) == 0xC);

	typedef Memory::DataArray<s_object_header_datum, 2048> object_header_data_t;

	struct s_objects_pool_data {
		Memory::s_memory_pool header;

		byte data[Enums::k_object_memory_pool_allocation_size];
	};

	struct s_object_globals_data {
		bool object_is_being_placed;
		bool object_marker_initialized;
		bool garbage_collect_now;
		UNKNOWN_TYPE(bool);
		short object_type_being_placed; // hs type
		UNKNOWN_TYPE(short);
		UNKNOWN_TYPE(datum_index);
		unsigned long pvs[BIT_VECTOR_SIZE_IN_DWORDS(512)];
		unsigned long pvs2[BIT_VECTOR_SIZE_IN_DWORDS(512)];
		long      last_garbage_collection_tick;               // 0x8C
		// none = 0
		// object = 1
		// cluster = 2
		short      pvs_activator_type;                     // 0x90
		unsigned short : 16;
		union {                                    // 0x94
			datum_index pvs_activating_object_index;
			short       pvs_activating_cluster_index;
		};
	}; static_assert(sizeof(s_object_globals_data) == 0x98);

	struct s_object_name_list_data {
		std::array<datum_index, Enums::k_maximum_object_names_per_scenario> object_name_to_datum_table;
	};

	struct s_object_iterator {
		enum { k_signature = 0x86868686 };

		long_flags                 type_mask;                  // object types to iterate
		Flags::object_header_flags ignore_flags;   // When any of these bits are set, the object is skipped
		unsigned char : 8;
		short       next_index;
		datum_index object_index;
		tag         signature;

		void SetEndHack() { signature = Memory::s_data_iterator::k_end_hack_signature; }

		bool IsEndHack() const { return signature == Memory::s_data_iterator::k_end_hack_signature; }
	};

	struct s_object_marker {
		short node_index;
		unsigned short : 16;
		real_matrix4x3 matrix;
		real_matrix4x3 transformed_matrix;
	}; static_assert(sizeof(s_object_marker) == 0x6C);

	object_header_data_t &ObjectHeader();

	s_objects_pool_data *ObjectsPool();

	s_object_globals_data *ObjectGlobals();

	s_object_name_list_data *ObjectNameList();

	TagGroups::s_object_definition const *GetObjectDefinition(datum_index object_index) {
		if(!object_index.IsNull())
		{
			const auto* object = Yelo::blam::object_get(object_index);

			return blam::tag_get<TagGroups::s_object_definition>(object->definition_index);
		}

		return nullptr;
	}

	template <typename TObjectDefinition>
	inline
	TObjectDefinition const *GetObjectDefinition(datum_index object_index) {
		return CAST_PTR(TObjectDefinition const*, GetObjectDefinition(object_index));
	}

	TagGroups::model_animation_graph const *GetObjectAnimations(datum_index object_index) {
		if(!object_index.IsNull())
		{
			const auto* object = blam::object_get(object_index);
			auto tag_index = object->animation.definition_index;

			return blam::tag_get<TagGroups::model_animation_graph>(tag_index);
		}

		return nullptr;
	}

};

namespace Yelo::blam {
	using namespace Yelo::Objects;

	s_object_data *object_get(datum_index object_index);

	static void object_name_list_clear() {
		Objects::ObjectNameList()->object_name_to_datum_table.fill(datum_index::null());
	}

	static void object_name_list_remove_object_index(datum_index object_index) {
		auto *object = object_get(object_index);
		if (object->name_list_index == NONE || Scenario::Scenario()->object_names.Count)
			return;

		object->name_list_index = NONE;
		// no object names in this scenario, no need to update the list
		if (Scenario::Scenario()->object_names.Count <= 0)
			return;

		// multiple object names can refer to a single object datum
		for (datum_index &index : Objects::ObjectNameList()->object_name_to_datum_table) {
			if (index == object_index)
				index = datum_index::null();
		}
	}

	static datum_index object_name_list_lookup(short name_index) {
		if (name_index < 0 || name_index > Enums::k_maximum_object_names_per_scenario)
			return datum_index::null();

		return Objects::ObjectNameList()->object_name_to_datum_table[name_index];
	}

	datum_index object_index_from_name_index(short name_index) {
		return object_name_list_lookup(name_index);
	}

	void object_set_object_index_for_name_index(short name_index, datum_index object_index) {
		if (name_index < 0 || name_index >= Scenario::Scenario()->object_names.Count) {
			return;
		}

		Objects::ObjectNameList()->object_name_to_datum_table[name_index] = object_index;
	}

	void __cdecl object_reset(datum_index object_index);

	// precondition: [object_index] is a valid object index, everything else can be null
	// Recomputes the node matrices and reconnects the object to the map after updating the position data

	void __cdecl object_set_position(datum_index object_index,
												__in_opt real_point3d *new_position = nullptr,
												__in_opt real_vector3d *new_forward = nullptr,
												__in_opt real_vector3d *new_up = nullptr);

	void __cdecl object_set_position_network(datum_index object_index, real_point3d *new_position);

	void __cdecl object_translate(datum_index object_index, const real_point3d &new_position, __in_opt const Yelo::Scenario::s_scenario_location *new_location = nullptr);

	void __cdecl object_placement_data_new(s_object_placement_data &data, datum_index object_definition_index, datum_index owner_object_index = datum_index::null());

	datum_index __cdecl object_new(s_object_placement_data &data);

	datum_index __cdecl object_new_with_role(s_object_placement_data &data, Enums::networked_datum role);

	// Sends a message_object_deletion packet for [object_index], deleting it in the process
	void __cdecl object_delete_to_network(datum_index object_index);

	void __cdecl object_delete(datum_index object_index);

	void __cdecl object_reconnect_to_map(datum_index object_index, __in_opt Yelo::Scenario::s_scenario_location *location_reference = nullptr);

	void __cdecl object_disconnect_from_map(datum_index object_index);

	short __cdecl object_get_marker_by_name(const datum_index object_index, cstring marker_name, s_object_marker *markers, const short maximum_marker_count);

	// Attaches the object to the target_object (marker names can be empty strings)
	void __cdecl object_attach_to_marker(datum_index target_object_index, cstring target_marker_name, datum_index object_index, cstring marker_name);

	// Detaches the object from its parent
	void __cdecl object_detach(datum_index object_index); //{
	// 	Yelo::Engine::Objects::Detach(object_index);
	// }

	// Get the origin of [object_index]. Takes the parent object (if there is one) into account.
	real_point3d &__cdecl object_get_origin(datum_index object_index, __out real_point3d &return_origin); // {
	// 	return Yelo::Engine::Objects::GetOrigin(object_index, return_origin);
	// }

	// Get the orientation of [object_index]. Takes the parent object (if there is one) into account.
	void __cdecl object_get_orientation(datum_index object_index, __out_opt real_vector3d *return_forward, __out_opt real_vector3d *return_up);

	// Get the scenario location of [object_index]
	Yelo::Scenario::s_scenario_location &__cdecl object_get_location(datum_index object_index, __out Yelo::Scenario::s_scenario_location &return_location);

	void __cdecl object_start_interpolation(datum_index object_index, long interpolation_frame_count);

	s_object_data *__cdecl object_try_and_get_and_verify_type(datum_index object_index, unsigned long expected_types) {
		s_object_data *object = object_get(object_index);

		return object && object->VerifyType(expected_types) ? object : nullptr;
	}

	template <typename T>
	T *object_try_and_get_and_verify_type(datum_index object_index) {
		return CAST_PTR(T*, object_try_and_get_and_verify_type(object_index, T::k_object_types_mask));
	}

	s_object_iterator &object_iterator_new(s_object_iterator &iter, unsigned long type_mask, Flags::object_header_flags ignore_flags) {
		iter.signature    = s_object_iterator::k_signature;
		iter.type_mask    = type_mask;
		iter.ignore_flags = ignore_flags;
		iter.next_index   = 0;
		iter.object_index = datum_index::null();

		return iter;
	}

	s_object_data *__cdecl object_iterator_next(s_object_iterator &iter);

	short __cdecl objects_in_sphere(Flags::objects_find_flags find_flags,
											  unsigned long object_type_flags,
											  const Yelo::Scenario::s_scenario_location &location,
											  const real_point3d &center,
											  real radius,
											  datum_index object_indices[],
											  short maximum_object_indices);

	// Loads the predicted resources defined in [object_index]'s tag definition (if they're not already loaded)
	void __cdecl object_definition_predict(datum_index object_index);

	bool __cdecl object_header_block_allocate(datum_index object_index, size_t block_reference_offset, size_t size);

	// Sets the scale of an object over a duration of time (game ticks)
	void __cdecl objects_scripting_set_scale(datum_index object_index, real scale, long ticks);

	real __cdecl object_get_level_of_detail_pixels(datum_index object_index);

	void __cdecl object_render_state_refresh(datum_index object_render_state_index, datum_index object_index, real level_of_detail_pixels, byte arg4);

	void __cdecl objects_update();

	void __cdecl object_update(datum_index object_index);

	s_object_data *object_get_and_verify_type(datum_index object_index, unsigned long expected_types) {
		s_object_data *object = object_get(object_index);
		YELO_ASSERT_DISPLAY(object->VerifyType(expected_types), "got an object type we didn't expect (expected one of 0x%08x but got #%d).", expected_types, (long_enum) object->type);

		return object;
	}

	template <typename T>
	inline T *object_get_and_verify_type(datum_index object_index) {
		return CAST_PTR(T*, object_get_and_verify_type(object_index, T::k_object_types_mask));
	}

	void __cdecl object_destroy(const datum_index object_index);
};

namespace Yelo::Objects {
	class c_object_iterator {
		s_object_iterator m_state;
		s_object_data     *m_object;

		c_object_iterator(const void *endHackDummy) : m_object(nullptr) { m_state.SetEndHack(); }

	public:
		c_object_iterator(unsigned long type_mask, Flags::object_header_flags ignore_flags = (Flags::object_header_flags) 0) : m_object(nullptr) {
			blam::object_iterator_new(m_state, type_mask, ignore_flags);
		}

		static c_object_iterator all() { return c_object_iterator(Enums::_object_type_mask_all); }

		s_object_data *Next() { return m_object = blam::object_iterator_next(m_state); }

		bool operator !=(const c_object_iterator &other) const {
			if (other.m_state.IsEndHack())
				return this->m_object != nullptr;
			else if (this->m_state.IsEndHack())
				return other.m_object != nullptr;

			return this->m_object != other.m_object;
		}

		c_object_iterator &operator ++() {
			Next();
			return *this;
		}

		Memory::DataArrayIteratorResult<s_object_data> operator *() const {
			return Memory::DataArrayIteratorResult<s_object_data>(m_state.object_index, m_object);
		}

		c_object_iterator &begin() {
			this->Next();
			return *this;
		}

		static const c_object_iterator end() { return c_object_iterator(nullptr); }
	};

	// Checks to see if [object_index_to_test] is an enemy of [object_index]
	bool ObjectIsEnemy(datum_index object_index, datum_index object_index_to_test) {
		if (object_index.IsNull() || object_index_to_test.IsNull()) {
			return false;
		}

		s_object_data *object         = Yelo::blam::object_get(object_index);
		s_object_data *object_to_test = Yelo::blam::object_get(object_index_to_test);

		return blam::game_team_is_enemy(object->owner_team, object_to_test->owner_team);
	}

};
