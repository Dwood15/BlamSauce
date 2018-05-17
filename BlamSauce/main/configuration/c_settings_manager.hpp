/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <YeloLib/configuration/i_configuration_file.hpp>
#include <YeloLib/configuration/i_configuration_leaf.hpp>
#include <YeloLib/configuration/c_configuration_file_factory.hpp>
#include <YeloLib/configuration/c_configuration_container.hpp>

namespace Yelo {
	namespace Settings {
		class c_settings_manager final {
			struct s_settings_container_entry {
				std::function<void()> m_pre_load_callback;
				std::function<void()> m_post_load_callback;
				std::function<void()> m_pre_save_callback;
				std::function<void()> m_post_save_callback;
				Configuration::c_configuration_container *m_container_ptr;
			};

			const std::string                        m_root_node_path;
			Configuration::configuration_file_ptr_t  m_settings;
			std::vector <s_settings_container_entry> m_settings_containers;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets the root configuration node. </summary>
			///
			/// <returns>	The configuration root node. </returns>
			std::unique_ptr <Configuration::i_configuration_leaf> GetRootNode(const std::string &root_node_path) const {
				auto root_node = m_settings->Root()->GetChild(root_node_path);
				if (!root_node) {
					root_node = m_settings->Root()->AddChild(root_node_path);
				}

				return root_node;
			}

		public:
			c_settings_manager(const std::string &root_node) : m_root_node_path(root_node), m_settings(nullptr), m_settings_containers() {}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Loads settings from the given file. </summary>
			///
			/// <param name="file_path">	The settings file to load. </param>
			void Load(const std::string &file_path) {
				// Load the configuration file.
				m_settings = c_configuration_file_factory::CreateConfigurationFile(file_path);

				if (!m_settings) {
					YELO_ASSERT("Failed to load or create a settings file.");
				}

				m_settings->Load();

				// Get the registered containers from the loaded settings
				auto root_node_ptr = GetRootNode(m_root_node_path);
				auto &root_node = *root_node_ptr;

				for (auto entry : m_settings_containers) {
					if (entry.m_pre_load_callback) {
						entry.m_pre_load_callback();
					}

					entry.m_container_ptr->GetValueFromParent(root_node);

					if (entry.m_post_load_callback) {
						entry.m_post_load_callback();
					}
				}
			}

			/// <summary>	Clears the current settings. </summary>
			void Clear() {
				m_settings->Clear();
			}

			/// <summary>	Saves the settings to file. </summary>
			void Save() {
				Clear();

				// Add the registered containers to the settings
				auto root_node_ptr = GetRootNode(m_root_node_path);
				auto &root_node = *root_node_ptr;

				for (const auto &entry : m_settings_containers) {
					if (entry.m_pre_save_callback) {
						entry.m_pre_save_callback();
					}

					entry.m_container_ptr->SetValueToParent(root_node);

					if (entry.m_post_save_callback) {
						entry.m_post_save_callback();
					}
				}

				// Save the settings to file
				m_settings->Save();
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Registers a configuration container with the settings system. </summary>
			///
			/// <param name="container">		 	The container to register. </param>
			/// <param name="pre_load_callback"> 	The pre load callback. </param>
			/// <param name="post_load_callback">	The post load callback. </param>
			/// <param name="pre_save_callback"> 	The pre save callback. </param>
			/// <param name="post_save_callback">	The post save callback. </param>
			void RegisterConfigurationContainer(Configuration::c_configuration_container &container, const std::function<void()> &pre_load_callback, const std::function<void()> &post_load_callback,
															const std::function<void()> &pre_save_callback, const std::function<void()> &post_save_callback) {
				s_settings_container_entry entry = {
					pre_load_callback,
					post_load_callback,
					pre_save_callback,
					post_save_callback,
					&container
				};

				m_settings_containers.push_back(entry);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Unregisters a configuration container from the settings system. </summary>
			///
			/// <param name="container">	The container to unregister. </param>
			void UnregisterConfigurationContainer(Configuration::c_configuration_container &container) {
				auto container_ptr = &container;

				// Find the containers' entry using it's pointer then remove it
				auto entry_iterator = find_if(m_settings_containers.begin(), m_settings_containers.end(),
														[container_ptr](s_settings_container_entry& entry)
														{
															return entry.m_container_ptr == container_ptr;
														}
				);

				if(entry_iterator != m_settings_containers.end())
				{
					m_settings_containers.erase(entry_iterator);
				}
			}
		};
	};
};
