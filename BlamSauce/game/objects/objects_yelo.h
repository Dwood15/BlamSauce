#pragma once

#include <precompile.h>
#include "object_types.h"
#include "objects.h"
#include "units/unit_structures.hpp"

namespace Yelo::Objects {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Object iterator next. </summary>
	///
	/// <typeparam name="ObjectType">	The object type parameter. </typeparam>
	/// <param name="iter">	[out] The iterator. </param>
	///
	/// <returns>	null if it fails, else a object data pointer. </returns>
	template <typename ObjectType>
	ObjectType *IteratorNext(const s_object_iterator &iter) {
		YELO_ASSERT_DISPLAY(TEST_FLAG(iter.type_mask, ObjectType::k_object_type), "Wrong object_type given to IteratorNext<T>");

		return CAST_PTR(ObjectType*, blam::object_iterator_next(iter));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a new copy of an object's placement data. </summary>
	///
	/// <param name="data">				  	[in] The sourcedata. </param>
	/// <param name="source_object_index">	Datum index of the source object. </param>
	/// <param name="tag_index_override"> 	(Optional) the tag index override. </param>
	/// <param name="owner_object_index"> 	(Optional) the object that owns this item. </param>
	void PlacementDataNewAndCopy(s_object_placement_data &data, const datum_index source_object_index, datum_index tag_index_override = datum_index::null(),
										  const datum_index owner_object_index = datum_index::null()) {
		const auto *source_object = blam::object_get(source_object_index);

		if (tag_index_override.IsNull()) {
			tag_index_override = source_object->definition_index;
		}

		blam::object_placement_data_new(data, tag_index_override, owner_object_index);
		source_object->CopyToPlacementData(data);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Walks the parent object datums of [object_index] until it gets to the upper most parent
	/// 	and returns that parent's datum index.
	/// </summary>
	///
	/// <param name="object_index">	Datum index of the object. </param>
	///
	/// <returns>	The ultimate object. </returns>
	datum_index GetUltimateObject(const datum_index object_index) {
		if (!object_index.IsNull()) {
			const auto *object_header_datums = Objects::ObjectHeader().Datums();
			const auto *current_obj          = object_header_datums[object_index.index]._object;

			datum_index parent_index;
			while (!(parent_index = current_obj->parent_object_index).IsNull()) {
				current_obj = object_header_datums[parent_index.index]._object;
			}
		}

		return object_index;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Walks the next object datums of [object_index] [step_count] amount of times, and returns
	/// 	the result datum_index.
	/// </summary>
	///
	/// <remarks>
	/// 	Say, if [step_count] is zero, it will return the datum_index that is returned by
	/// 	[object_index]'s GetNextObjectIndex.
	/// </remarks>
	///
	/// <param name="object_index">	Datum index of the object. </param>
	/// <param name="step_count">  	(Optional) the step count to walk down the object tree. </param>
	///
	/// <returns>	The next object after the specified steps. </returns>
	datum_index GetNextObjectN(datum_index object_index, int32 step_count = 0) {
		if (!object_index.IsNull()) {
			const auto *object_header_datums = Objects::ObjectHeader().Datums();
			const auto *current_obj          = object_header_datums[object_index.index]._object;

			for (object_index = current_obj->next_object_index;
				  !object_index.IsNull() && step_count > 0;
				  object_index = current_obj->next_object_index, --step_count) {
				current_obj = object_header_datums[object_index.index]._object;
			}
		}

		return step_count == 0 ? object_index : datum_index::null();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the object distance from a point. </summary>
	///
	/// <param name="object_index">			Datum index of the object. </param>
	/// <param name="destination_point">	Destination point. </param>
	///
	/// <returns>	The object distance from point. </returns>
	real GetObjectDistanceFromPoint(const datum_index object_index, const real_vector3d &destination_point) {
		real dist = -1.0f;

		if (!object_index.IsNull()) {
			real_vector3d object_origin;
			blam::object_get_origin(object_index, object_origin);

			real_vector3d relative_pos = object_origin - destination_point;
			dist = relative_pos.Magnitude();
		}

		return dist;
	}

	static void PerformActionOnChildrenByType(const datum_index parent, const long_flags object_type_mask, const std::function<void(const datum_index)> &action_performer) {
		const auto    *object_header_datums = Objects::ObjectHeader().Datums();
		const auto    *parent_object        = object_header_datums[parent.index]._object;
		s_object_data *child_object;

		for (datum_index child_index = parent_object->first_object_index; !child_index.IsNull(); child_index = child_object->next_object_index) {
			child_object = object_header_datums[child_index.index]._object;

			if (child_object->VerifyType(object_type_mask)) {
				action_performer(child_index);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Delete all children of the specified type(s) on the parent object. </summary>
	///
	/// <param name="parent">		   	The parent. </param>
	/// <param name="object_type_mask">	The object type mask. </param>
	void DeleteChildrenByType(const datum_index parent, const long_flags object_type_mask) {
		PerformActionOnChildrenByType(parent, object_type_mask, [](const datum_index object_index) { blam::object_delete(object_index); });
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Detach all children of the specified type(s) from the parent object. </summary>
	///
	/// <param name="parent">		   	The parent. </param>
	/// <param name="object_type_mask">	The object type mask. </param>
	void DetachChildrenByType(const datum_index parent, const long_flags object_type_mask) {
		PerformActionOnChildrenByType(parent, object_type_mask, [](const datum_index object_index) { blam::object_detach(object_index); });
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Delete all child actors on the parent object. </summary>
	///
	/// <param name="parent">		   	The parent. </param>
	void DeleteChildActors(const datum_index parent) {

		//not the most readable shit ever, but it's better than it was...
		auto callable = [](const datum_index object_index) {
			const auto *unit_datum = blam::object_try_and_get_and_verify_type<s_unit_datum>(object_index);
			if (unit_datum && (!unit_datum->unit.actor_index.IsNull() || !unit_datum->unit.swarm_actor_index.IsNull())) {
				blam::object_delete(object_index);
			}
		};

		PerformActionOnChildrenByType(parent, Enums::_object_type_mask_unit, callable);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Detach all child actors from the parent object. </summary>
	///
	/// <param name="parent">		   	The parent. </param>
	void DetachChildActors(const datum_index parent) {
		auto callable = [](const datum_index object_index) {
			const auto *unit_datum = blam::object_try_and_get_and_verify_type<s_unit_datum>(object_index);
			if (unit_datum
				 && (!unit_datum->unit.actor_index.IsNull() || !unit_datum->unit.swarm_actor_index.IsNull())) {
				blam::object_detach(object_index);
			}
		};

		PerformActionOnChildrenByType(parent, Enums::_object_type_mask_unit, callable);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Destroys all children of the specified definition type from the parent object.
	/// </summary>
	///
	/// <param name="parent">	 	The parent. </param>
	/// <param name="definition">	The object definition index. </param>
	void DestroyChildrenByDefinition(const datum_index parent, const datum_index definition) {
		PerformActionOnChildrenByType(parent, Enums::_object_type_mask_all,
												[&](const datum_index object_index) {
													auto *object_datum = blam::object_get(object_index);
													if (object_datum && (object_datum->definition_index == definition)) {
														blam::object_destroy(object_index);
													}
												});
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Deletes all children of the specified definition type from the parent object.
	/// </summary>
	///
	/// <param name="parent">	 	The parent. </param>
	/// <param name="definition">	The object definition index. </param>
	void DeleteChildrenByDefinition(const datum_index parent, const datum_index definition) {
		PerformActionOnChildrenByType(parent, Enums::_object_type_mask_all,
												[&](const datum_index object_index) {
													auto *object_datum = blam::object_get(object_index);
													if (object_datum && (object_datum->definition_index == definition)) {
														blam::object_delete(object_index);
													}
												});
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Detach all children of the specified definition type from the parent object.
	/// </summary>
	///
	/// <param name="parent">	 	The parent. </param>
	/// <param name="definition">	The object definition index. </param>
	void DetachChildrenByDefinition(const datum_index parent, const datum_index definition) {

		auto callback = [&](const datum_index object_index) {
			auto *object_datum = blam::object_get(object_index);
			if (object_datum && (object_datum->definition_index == definition)) {
				blam::object_detach(object_index);
			}
		};

		PerformActionOnChildrenByType(parent, Enums::_object_type_mask_all, callback);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Predict the object memory pool usage. </summary>
	///
	/// <param name="type">						The object type. </param>
	/// <param name="node_count">				Number of nodes. </param>
	/// <param name="include_yelo_upgrades">	(Optional) include yelo upgrades. </param>
	///
	/// <returns>	The memory usage for the specified type. </returns>
	size_t PredictMemoryPoolUsage(const Enums::object_type type, const int32 node_count, const bool include_yelo_upgrades = false) {
		size_t total_headers_size     = sizeof(Memory::s_memory_pool_block);
		size_t total_node_memory_size = (sizeof(real_orientation3d) * 2) + sizeof(real_matrix4x3);
		total_node_memory_size *= node_count;

		size_t object_type_size = 0;
		switch (type) {
			case Enums::_object_type_biped:
				object_type_size = Enums::k_object_size_biped;
				break;
			case Enums::_object_type_vehicle:
				object_type_size = Enums::k_object_size_vehicle;
				break;

			case Enums::_object_type_weapon:
				object_type_size = Enums::k_object_size_weapon;
				break;
			case Enums::_object_type_equipment:
				object_type_size = Enums::k_object_size_equipment;
				break;
			case Enums::_object_type_garbage:
				object_type_size = Enums::k_object_size_garbage;
				break;

			case Enums::_object_type_projectile:
				object_type_size = Enums::k_object_size_projectile;
				break;
			case Enums::_object_type_scenery:
				object_type_size = Enums::k_object_size_scenery;
				break;

			case Enums::_object_type_machine:
				object_type_size = Enums::k_object_size_machine;
				break;
			case Enums::_object_type_control:
				object_type_size = Enums::k_object_size_control;
				break;
			case Enums::_object_type_light_fixture:
				object_type_size = Enums::k_object_size_light_fixture;
				break;

			case Enums::_object_type_placeholder:
				object_type_size = Enums::k_object_size_placeholder;
				break;
			case Enums::_object_type_sound_scenery:
				object_type_size = Enums::k_object_size_sound_scenery;
				break;

			default:
				return 0;
		}

		return object_type_size + total_node_memory_size + total_headers_size;
	}
};
