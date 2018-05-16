#pragma once

#include <memory>
#include "../memory/datum_index.h"
#include "../tags/group/base.h"

namespace Yelo {
	namespace Render {
		namespace Sky {
			class c_sky_manager final {
				class s_sky_entry final {
					datum_index                   m_sky_tag_index;
					bool                          m_is_override;
															PAD24;
					std::shared_ptr <s_sky_entry> m_original_sky_entry;

				public:
					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Initializes a new instance of the s_sky_entry class. </summary>
					///
					/// <param name="sky_index">	Datum index of the sky tag. </param>
					s_sky_entry(const datum_index sky_tag_index) : m_is_override(false), m_sky_tag_index(sky_tag_index), m_original_sky_entry(nullptr) {}
					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Initializes a new instance of the s_sky_entry class that overrides another sky entry. </summary>
					///
					/// <param name="sky_index">	Datum index of the sky tag. </param>
					/// <param name="sky_entry">	The sky entry being overridden. </param>
					s_sky_entry(const datum_index sky_tag_index, const c_sky_manager::sky_entry_ptr_t sky_entry) : c_sky_manager::s_sky_entry::s_sky_entry(sky_tag_index) {
						m_original_sky_entry = sky_entry;
						m_is_override        = true;
					}

					s_sky_entry(const datum_index sky_tag_index, std::shared_ptr <s_sky_entry> sky_entry);

					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Query if this object is a sky override. </summary>
					///
					/// <returns>	true if overriding another sky, false if not. </returns>
					bool IsOverride() const {
						return m_is_override;
					}

					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Gets the sky datum index. </summary>
					///
					/// <returns>	A datum_index. </returns>
					datum_index GetTagIndex() const {
						return m_sky_tag_index;
					}

					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Gets the original sky pointer if set. </summary>
					///
					/// <returns>	A c_sky_manager::sky_entry_ptr_t. </returns>
					std::shared_ptr <s_sky_entry> OriginalSky() const {
						return m_original_sky_entry;
					}
				};

				typedef std::shared_ptr <s_sky_entry> sky_entry_ptr_t;
				typedef std::vector <sky_entry_ptr_t> sky_entry_list_t;

				sky_entry_list_t m_sky_list;

			public:
				/// <summary>	Resets the sky list, reverting all overrides. </summary>
				void Reset() {
					for(sky_entry_list_t::size_type i = 0; i < m_sky_list.size(); i++)
					{
						// If the sky entry is an override, replace it with the sky stored within
						if(m_sky_list[i]->IsOverride())
						{
							m_sky_list[i] = m_sky_list[i]->OriginalSky();
						}
					}
				}

				/// <summary>	Clears the sky list. </summary>
				void Clear() {
					m_sky_list.clear();
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////
				/// <summary>	Add's entries to the sky list for the skies listed in the scenario tag. </summary>
				///
				/// <param name="skies">	The scenario's skies block. </param>
				void SetScenarioSkies(const TagBlock <tag_reference> &skies) {
					for(auto sky : skies)
					{
						m_sky_list.emplace_back(std::make_shared<s_sky_entry>(sky.tag_index));
					}
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////
				/// <summary>	Sets a sky index to a different sky tag. </summary>
				///
				/// <param name="sky_index">	Zero-based index of the sky. </param>
				/// <param name="sky_datum">	The sky tag datum index. </param>
				void SetSkyIndex(const byte sky_index, const datum_index sky_tag_index) {
					if (sky_index == NONE)
					{
						return;
					}

					// If the chosen sky is an override, get the original sky entry
					// Otherwise use the sky entry in the list
					sky_entry_ptr_t original_sky;
					if(m_sky_list[sky_index]->IsOverride())
					{
						original_sky = m_sky_list[sky_index]->OriginalSky();
					}
					else
					{
						original_sky = m_sky_list[sky_index];
					}

					// Create a new sky entry to override the stock one
					m_sky_list[sky_index] = std::make_shared<s_sky_entry>(sky_tag_index, original_sky);
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////
				/// <summary>	Gets a sky's datum index. </summary>
				///
				/// <param name="sky_index">	Zero-based index of the sky. </param>
				///
				/// <returns>	The sky tag's datum index. </returns>
				datum_index c_sky_manager::GetSkyTagIndex(const byte sky_index) const
				{
					if(sky_index == (byte)NONE)
					{
						return datum_index::null();
					}
					if(sky_index >= m_sky_list.size())
					{
						return datum_index::null();
					}
					return m_sky_list[sky_index]->GetTagIndex();
				}
			};
		};
	};
};
