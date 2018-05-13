/* See LICENSE.md for specific license information */
#pragma once

#include <d3dx9math.inl>
#include "hs.hpp"
#include "types_runtime.inl"

namespace Yelo {
	namespace Scripting {
		typedef s_hs_value_union (API_FUNC *proc_hs_typecast)(s_hs_value_union value);

		static proc_hs_typecast k_hs_typecasting_procedures[Enums::k_number_of_hs_types][Enums::k_number_of_hs_types];

		static void HsTypesInitializeTypeCastingProcedures() {
			using namespace Enums;
			using namespace blam;

			typedef proc_hs_typecast (&typecasting_procedures_t)[k_number_of_hs_types];

			typecasting_procedures_t
				void_procedures   = k_hs_typecasting_procedures[_hs_type_void],
				bool_procedures   = k_hs_typecasting_procedures[_hs_type_bool],
				real_procedures   = k_hs_typecasting_procedures[_hs_type_real],
				short_procedures  = k_hs_typecasting_procedures[_hs_type_short],
				long_procedures   = k_hs_typecasting_procedures[_hs_type_long],
				string_procedures = k_hs_typecasting_procedures[_hs_type_string],

				object_list_procedures = k_hs_typecasting_procedures[_hs_type_object_list];

#if 0
			// NOTE: non-standard
			for (_enum type = _hs_type_enum__first; type < _hs_type_enum__last+1; type++) {
				k_hs_typecasting_procedures[type][_hs_type_real] = hs_real_to_enum;
			}
#endif

			// _hs_type_void
			for (short type = _hs_type_data__first; type < _hs_type_data__last + 1; type++) {
				void_procedures[type] = hs_value_to_void;
			}

			// _hs_type_bool
			bool_procedures[_hs_type_real]   = hs_long_to_boolean; // yes long, (this is what the engine does)
			bool_procedures[_hs_type_short]  = hs_short_to_boolean;
			bool_procedures[_hs_type_long]   = hs_long_to_boolean;
			bool_procedures[_hs_type_string] = hs_string_to_boolean;

			// _hs_type_real
			real_procedures[_hs_type_bool]  = hs_bool_to_real;
			real_procedures[_hs_type_short] = hs_short_to_real;
			real_procedures[_hs_type_long]  = hs_long_to_real;
			//			real_procedures[_hs_type_string] =	hs_string_to_real;
			for (short type = _hs_type_enum__first; type < _hs_type_enum__last + 1; type++) {
				real_procedures[type] = hs_enum_to_real;
			}

			// _hs_type_short
			short_procedures[_hs_type_bool] = hs_bool_to_short;
			short_procedures[_hs_type_real] = hs_real_to_short;
			short_procedures[_hs_type_long] = hs_long_to_short;
			//			short_procedures[_hs_type_string] =	hs_string_to_short;

			// _hs_type_long
			long_procedures[_hs_type_bool]  = hs_bool_to_long;
			long_procedures[_hs_type_real]  = hs_real_to_long;
			// NOTE: due to a typo, the engine actually didn't support casting from short to long
			long_procedures[_hs_type_short] = hs_short_to_long;
			//			long_procedures[_hs_type_string] =	hs_string_to_long;

			// _hs_type_string

			// _hs_type_object_list
			object_list_procedures[_hs_type_ai] = object_list_from_ai_reference;
			for (short type = _hs_type_object__first; type < _hs_type_object__last + 1; type++) {
				object_list_procedures[type] = hs_object_to_object_list;
			}

			for (short type = _hs_type_object_name__first; type < _hs_type_object_name__last + 1; type++) {
				object_list_procedures[type] = hs_object_name_to_object_list;
			}
		}

		void HsTypesInitialize() {
			HsTypesInitializeTypeCastingProcedures();
		}

		void HsTypesDispose() {

		}

		typedef bool (API_FUNC *proc_hs_type_parse)(Enums::hs_type type, datum_index expression_index);

		typedef void (API_FUNC *proc_hs_type_inspect)(Enums::hs_type type, s_hs_value_union value, char *buffer, size_t buffer_size);

		struct c_hs_type_void_abi;
		class c_hs_type_abi;

		static const c_hs_type_abi * asb1 = &{k_hs_unparsed_abi, Yelo::Enums::_hs_unparsed;};
		static const c_hs_type_abi * asb2 = &{k_hs_special_form_abi, Yelo::Enums::_hs_special_form;};
		static const c_hs_type_abi * asb3 = &{k_hs_function_name_abi, Yelo::Enums::_hs_function_name;};
		static const c_hs_type_abi * asb4 = &{k_hs_passthrough_abi, Yelo::Enums::_hs_passthrough;};
		static const c_hs_type_abi * asb5 = &{k_hs_type_void_abi, Yelo::Enums::_hs_type_void;};
		static const c_hs_type_abi * asb6 = &{k_hs_type_bool_abi, Yelo::Enums::_hs_type_bool;};

		class c_hs_type_abi {
		public:
			static const c_hs_type_abi *Get(Enums::hs_type type) {
				static std::array<const c_hs_type_abi *, Enums::k_number_of_hs_types> hs_type_abis = {
					{asb1},
					{asb2},
					{asb3},
					{asb4},
					{asb5},
					{asb6}
				};

				return hs_type_abis[type];
			}

		protected:
			Enums::hs_type m_type;
			PAD16;

		public:
			c_hs_type_abi(Enums::hs_type type) : m_type(type) {}

			Enums::hs_type GetType() const { return m_type; }

			cstring GetTypeName() const { return blam::hs_type_names[m_type]; }

			virtual s_hs_value_union GetDefaultValue();

			virtual s_hs_value_union ReadValue(Enums::hs_type type, const s_hs_value_union *source) const;

			virtual void WriteValue(Enums::hs_type type, s_hs_value_union source, s_hs_value_union &destination) const;

			virtual size_t GetSize() const;

			virtual bool Parse(Enums::hs_type type, datum_index expression_index) const;

			virtual bool Inspectable() const;

			virtual void Inspect(Enums::hs_type type, s_hs_value_union value, char *buffer, size_t buffer_size) const;

			virtual bool CastableToValueUnion() const { return CastableTo_hs_type_long(); }

			virtual s_hs_value_union GetValue(s_hs_value_union value) { return GetValue(value.int32); }

			virtual bool CastableTo_hs_type_bool() const { return false; }

			virtual s_hs_value_union GetValue(bool value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_real() const { return false; }

			virtual s_hs_value_union GetValue(real value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_short() const { return false; }

			virtual s_hs_value_union GetValue(int16 value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_long() const { return false; }

			virtual s_hs_value_union GetValue(int32 value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_string() const { return false; }

			virtual s_hs_value_union GetValue(cstring value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_script() const { return false; }

			virtual s_hs_value_union GetValue(hs_script_index_t index) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_enum_game_difficulty() const { return false; }

			virtual s_hs_value_union GetValue(Enums::game_difficulty_level value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_enum_team() const { return false; }

			virtual s_hs_value_union GetValue(Enums::game_team value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_enum_ai_default_state() const { return false; }

			virtual s_hs_value_union GetValue(Enums::actor_default_state value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_enum_actor_type() const { return false; }

			virtual s_hs_value_union GetValue(Enums::actor_type value) const { return k_none_value_union; }

			virtual bool CastableTo_hs_type_enum_hud_corner() const { return false; }

			virtual s_hs_value_union GetValue(Enums::hud_anchor value) const { return k_none_value_union; }
		};

		// Yes, I declared as structs, to avoid having to explicitly say 'public' for inheritance and members

		struct c_hs_type_void_abi final : c_hs_type_abi {
			inline c_hs_type_void_abi(Enums::hs_type type) : c_hs_type_abi(type) {}

			s_hs_value_union GetDefaultValue() const override { return k_none_value_union; }

			s_hs_value_union ReadValue(Enums::hs_type type, const s_hs_value_union *source) const override { return k_none_value_union; }

			void WriteValue(Enums::hs_type type, s_hs_value_union source, s_hs_value_union &destination) const override {}

			size_t GetSize() const override { return 0; }

			bool Parse(Enums::hs_type type, datum_index expression_index) const override { return false; }

			bool Inspectable() const override { return false; }

			void Inspect(Enums::hs_type type, s_hs_value_union value, char *buffer, size_t buffer_size) const override {}
		};

		struct c_hs_type_value_abi : c_hs_type_abi {
		protected:
			s_hs_value_union     m_default_value;
			proc_hs_type_parse   m_parse;
			proc_hs_type_inspect m_inspect;

		public:
			c_hs_type_value_abi(Enums::hs_type type, s_hs_value_union default_value, proc_hs_type_parse parse, proc_hs_type_inspect inspect)
				: c_hs_type_abi(type), m_default_value(default_value), m_parse(parse), m_inspect(inspect) {}

			s_hs_value_union GetDefaultValue() const override {
				return m_default_value;
			}

			bool Parse(Enums::hs_type type, datum_index expression_index) const override {
				return m_parse(type, expression_index);
			}

			bool Inspectable() const override { return m_inspect != nullptr; }

			void Inspect(Enums::hs_type type, s_hs_value_union value, char *buffer, size_t buffer_size) const override {
				m_inspect(type, value, buffer, buffer_size);
			}
		};

		struct c_hs_type_bool_abi final : c_hs_type_value_abi {
			c_hs_type_bool_abi(Enums::hs_type type, s_hs_value_union default_value, proc_hs_type_parse parse, proc_hs_type_inspect inspect)
				: c_hs_type_value_abi(type, default_value, parse, inspect) {}

			size_t GetSize() const override { return sizeof(bool); }

			s_hs_value_union ReadValue(Enums::hs_type type, const s_hs_value_union *source) const override;

			void WriteValue(Enums::hs_type type, s_hs_value_union source, s_hs_value_union &destination) const override;
		};

	};
};
