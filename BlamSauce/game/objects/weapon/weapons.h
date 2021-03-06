#pragma once

#include <precompile.h>

namespace Yelo::Objects::Weapon {
	class c_settings_container : public Configuration::c_configuration_container {
	public:
		class c_weapon_position : public Configuration::c_configuration_container {
		public :
			Configuration::c_configuration_value <std::string> m_name;
			Configuration::c_real_vector3d_container           m_position;

			c_weapon_position() : Configuration::c_configuration_container("Weapon"), m_name("Name", ""), m_position("Position") {}

			bool HasOffset() {
				return m_position.Get().Magnitude() > 0.0f;
			}

		protected:
			const std::vector<i_configuration_value *const> GetMembers() final override {
				return std::vector<i_configuration_value *const>{&m_name, &m_position};
			}
		};

		Configuration::c_configuration_container_list <c_weapon_position> m_weapon_positions;

		c_settings_container() : Configuration::c_configuration_container("Objects.Weapon.Positions"), m_weapon_positions("Weapon", []() { return c_weapon_position(); }) {

		}

	protected:
		const std::vector<i_configuration_value *const> GetMembers() final override {
			return std::vector<i_configuration_value *const>{&m_weapon_positions};
		}
	};

	class c_settings_weapons : public Settings::c_settings_singleton<c_settings_container, c_settings_weapons> {};

	struct s_weapon_globals {
		datum_index weapon_index_from_last_update;

		c_settings_container::c_weapon_position *AddPreset(const char * name) {
			auto &settings_instance = c_settings_weapons::Instance().Get();
			if (Enums::k_weapon_view_max_weapon_presets == settings_instance.m_weapon_positions.Get().size())
				return nullptr;

			c_settings_container::c_weapon_position &weapon_position = settings_instance.m_weapon_positions.AddEntry();
			weapon_position.m_name.Get() = name;
			weapon_position.m_position.Get().Set(.0f, .0f, .0f);

			return &weapon_position;
		}

	private:
		s_item_datum *GetCurrentWeapon(datum_index &return_weapon_index) {
			const GameUI::s_first_person_weapon &fp_weapon = GameUI::FirstPersonWeapons()->local_players[0];
			return_weapon_index = *fp_weapon.GetWeaponIndex();
			if (!return_weapon_index.IsNull())
				return Objects::ObjectHeader()[return_weapon_index]->_item;

			return nullptr;
		}

		static const char * GetWeaponName(s_item_datum *weapon) {
			static char weapon_name[Enums::k_weapon_view_name_length + 1];

			datum_index definition_index = weapon->object.definition_index;
			if (!definition_index.IsNull()) {
				const auto *definition = blam::tag_get<TagGroups::s_item_definition>(definition_index);
				if (definition != nullptr) // WTF! HOW? idk. also, lazy :(
				{
					short msg_index = definition->item.message_index;

					wconst char * msg = blam::hud_get_item_string(msg_index);

					wstring_to_string_lazy(weapon_name, Enums::k_weapon_view_name_length + 1, msg);
				} else return nullptr;
			} else return nullptr;

			return weapon_name;
		}

		const char * GetCurrentWeaponName(datum_index &return_weapon_index) {
			s_item_datum *weapon = GetCurrentWeapon(return_weapon_index);

			if (weapon != nullptr)
				return GetWeaponName(weapon);

			return nullptr;
		}

	public:
		c_settings_container::c_weapon_position *GetCurrentPreset(datum_index &return_weapon_index, const char * &return_name) {
			return_weapon_index = datum_index::null();
			return_name         = GetCurrentWeaponName(return_weapon_index);

			auto &settings_instance = c_settings_weapons::Instance().Get();
			if (settings_instance.m_weapon_positions.Get().size() == 0) return nullptr;

			if (return_name != nullptr) {
				auto found_value = std::find_if(settings_instance.m_weapon_positions.begin(), settings_instance.m_weapon_positions.end(),
														  [return_name](c_settings_container::c_weapon_position &entry) {
															  return entry.m_name.Get() == std::string(return_name);
														  }
				);

				if (found_value != settings_instance.m_weapon_positions.end()) {
					return &(*found_value);
				}
			}

			return nullptr;
		}
	};

	static s_weapon_globals g_weapon_globals = {datum_index::null};

	static void __cdecl ApplyWeaponPreset() {
		static const uintptr_t FIRST_PERSON_WEAPON_RENDER_UPDATE = GET_FUNC_PTR(FIRST_PERSON_WEAPON_RENDER_UPDATE);

		datum_index weapon_index;
		const char *     name;
		c_settings_container::c_weapon_position *preset = g_weapon_globals.GetCurrentPreset(weapon_index, name);

		if (preset != nullptr) {
			auto                     *position = CAST(real_vector3d*, Render::RenderGlobals()->camera.point);
			const Camera::s_observer *obs      = Camera::Observer();

			real_vector3d right_vec;
			obs->GetRightVector(right_vec);
			*position +=
				obs->origin.forward * preset->m_position.Get().i +
				right_vec * preset->m_position.Get().j +
				obs->origin.up * preset->m_position.Get().k;
		}

		__asm {
		push   edx
		call   FIRST_PERSON_WEAPON_RENDER_UPDATE
		pop    edx
		}
	}

	void Initialize() {
		c_settings_weapons::Register(Settings::Manager());

		Memory::WriteRelativeCall(ApplyWeaponPreset,
										  GET_FUNC_VPTR(RENDER_WINDOW_CALL_HOOK_FIRST_PERSON_WEAPON_RENDER_UPDATE));
	}

	void Dispose() {
		c_settings_weapons::Unregister(Settings::Manager());
	}

	real_vector3d GetWeaponPosition() {
		datum_index weapon_index;
		const char *     weapon_name;

		auto *preset = g_weapon_globals.GetCurrentPreset(weapon_index, weapon_name);
		if (preset) {
			return preset->m_position;
		}

		return real_vector3d{0.0f, 0.0f, 0.0f};
	}

	void SetWeaponPosition(const real_vector3d &position) {
		datum_index weapon_index;
		const char *     weapon_name;

		auto *preset = g_weapon_globals.GetCurrentPreset(weapon_index, weapon_name);
		if (preset) {
			// If a preset is available update the position
			preset->m_position.Get() = position;
		} else {
			// If no preset is available but their is an offset, add a new preset for the current weapon
			if (position.Magnitude() > 0.0f) {
				preset = g_weapon_globals.AddPreset(weapon_name);
				preset->m_position.Get() = position;
			}
		}
	}
};
