#pragma once

#include <precompile.h>
#include "../main/configuration/c_settings_singleton.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum gamespy_qr_field : long_enum
		{
			_gamespy_qr_field_reserved,
			_gamespy_qr_field_hostname,
			_gamespy_qr_field_gamename,
			_gamespy_qr_field_gamever,
			_gamespy_qr_field_hostport,
			_gamespy_qr_field_mapname,
			_gamespy_qr_field_gametype,
			_gamespy_qr_field_gamevariant,
			_gamespy_qr_field_numplayers,
			_gamespy_qr_field_numteams,
			_gamespy_qr_field_maxplayers,
			_gamespy_qr_field_gamemode,
			_gamespy_qr_field_teamplay,
			_gamespy_qr_field_fraglimit,
			_gamespy_qr_field_team_fraglimit,
			_gamespy_qr_field_timeelapsed,
			_gamespy_qr_field_timelimit,
			_gamespy_qr_field_roundtime,
			_gamespy_qr_field_roundelapsed,
			_gamespy_qr_field_password,
			_gamespy_qr_field_groupid,
			_gamespy_qr_field_player,
			_gamespy_qr_field_score,
			_gamespy_qr_field_skill,
			_gamespy_qr_field_ping,
			_gamespy_qr_field_team,
			_gamespy_qr_field_deaths,
			_gamespy_qr_field_pid,
			_gamespy_qr_field_team_t,
			_gamespy_qr_field_score_t,
			_gamespy_qr_field_reserved1,
			_gamespy_qr_field_reserved2,
			_gamespy_qr_field_reserved3,
			_gamespy_qr_field_reserved4,
			_gamespy_qr_field_reserved5,
			_gamespy_qr_field_reserved6,
			_gamespy_qr_field_reserved7,
			_gamespy_qr_field_reserved8,
			_gamespy_qr_field_reserved9,
			_gamespy_qr_field_reserved10,
			_gamespy_qr_field_reserved11,
			_gamespy_qr_field_reserved12,
			_gamespy_qr_field_reserved13,
			_gamespy_qr_field_reserved14,
			_gamespy_qr_field_reserved15,
			_gamespy_qr_field_reserved16,
			_gamespy_qr_field_reserved17,
			_gamespy_qr_field_reserved18,
			_gamespy_qr_field_reserved19,
			_gamespy_qr_field_reserved20,
			_gamespy_qr_field_reserved21,

			_gamespy_qr_field_dedicated,
			_gamespy_qr_field_player_flags,
			_gamespy_qr_field_game_flags,
			_gamespy_qr_field_game_classic,

			//////////////////////////////////////////////////////////////////////////
			// OS fields
			_gamespy_qr_field_open_sauce_version,	// string
			// 0 - no (.map)
			// 1 - .yelo
			_gamespy_qr_field_open_sauce_map,		// int

			_gamespy_qr_field,
			k_max_gamespy_qr_registered_keys = 254,
		}; static_assert( _gamespy_qr_field <= k_max_gamespy_qr_registered_keys );

		enum gamespy_qr_key_type : long_enum {
			_gamespy_qr_key_type_server,
			_gamespy_qr_key_type_player,
			_gamespy_qr_key_type_team,

			k_number_of_gamespy_qr_key_types,
		};

		enum gamespy_connection_state : long_enum
		{
			GTI2AwaitingServerChallenge,
			GTI2AwaitingAcceptance,
			GTI2AwaitingClientChallenge,
			GTI2AwaitingClientResponse,
			GTI2AwaitingAcceptReject,
			GTI2Connected,
			GTI2Closing,
			GTI2Closed,
		};

		enum gamespy_connection_result : long_enum
		{
			GT2Success,
			GT2OutOfMemory,
			GT2Rejected,
			GT2NetworkError,
			GT2AddressError,
			GT2DuplicateAddress,
			GT2TimedOut,
			GT2NegotiationError,
			GT2InvalidConnection,
			GT2InvalidMessage,
			GT2SendFailed
		};

		enum e_gamespy_update_status : long
		{
			_gamespy_update_status_invalid = NONE,

			_gamespy_update_status_none = 0,
			_gamespy_update_status_searching,
			_gamespy_update_status_no_update,
			_gamespy_update_status_found_update,
			_gamespy_update_status_updating,
		};
	};

	namespace Networking
	{

		static bool* GsPatchCheckForUpdates();		//						PTR_IMP_GET2(g_gamespy_patch_check_for_updates);

		struct s_gamespy_buffer // GTI2Buffer, gt\gt2Main.h
		{
			byte* buffer;
			uint buffer_size;
			uint length;
		};

		struct s_gamespy_socket // GTI2Socket, gt\gt2Main.h
		{
			SOCKET socket;
			in_addr address;
			short port; unsigned short : 16;
			void* connections;
			void* closedConnections;
			BOOL close;
			BOOL error;
			void* connectAttemptCallback;
			void* socketErrorCallback;
			void* sendDumpCallback;
			void* receiveDumpCallback;
			void* unrecognizedMessageCallback;
			void* user_data; // 0x30, engine treats this as s_transport_endpoint*
			long incomingBufferSize;
			long outgoingBufferSize;
			long protocolOffset;
			UNKNOWN_TYPE(long); // 0x40, I believe I saw some code treat this as a s_transport_endpoint* ...
			BOOL broadcastEnabled;
		}; static_assert( sizeof(s_gamespy_socket) == 0x48 );
		struct s_gamespy_connection // GTI2Connection, gt\gt2Main.h
		{
			in_addr address;
			short port; unsigned short : 16;

			s_gamespy_socket* socket;
			Enums::gamespy_connection_state state;
			BOOL initiated;
			BOOL freeAtAcceptReject;
			Enums::gamespy_connection_result connectionResult;

			uint startTime, timeout;

			long callbackLevel;
			void* connectedCallback;
			void* receivedCallback;
			void* closedCallback;
			void* pingCallback;

			char* initialMessage;
			long initialMessageLen;

			void* user_data;

			s_gamespy_buffer incomingBuffer, outgoingBuffer;
			void* incomingBufferMessages;
			void* outgoingBufferMessages;

			unsigned short serialNumber, expectedSerialNumber;

			char response[32];

			uint lastSend;
			uint challengeTime;

			PAD(1, sizeof(long)*4);
			void* sendFilters;
			void* receiveFilters;
			PAD(2, sizeof(byte)*4);
			PAD(3, sizeof(byte)*28);
			PAD(4, sizeof(char)*32);
			PAD(5, sizeof(char)*32);
			PAD(6, sizeof(char)*32);
			PAD(7, sizeof(char)*20);
			PAD(8, sizeof(char)*16);
			UNKNOWN_TYPE(long);
		}; static_assert( sizeof(s_gamespy_connection) == 0x150 );

		struct s_gamespy_qr_data // (query/response) qr2_implementation_s, qr2\qr2.h
		{
			SOCKET heartbeat_socket;
			char game_name[64];
			char priv_key[64];
			char runtime_key[4];
			void* proc_server_key;
			void* proc_player_key;
			void* proc_team_key;
			void* proc_key_list;
			void* proc_player_team_count;
			void* proc_adderror;
			void* nn_callback;
			void* cm_callback;
			uint last_heartbeat_time;
			uint last_keepalive_time;
			long_enum listed_state;
			BOOL is_public;
			long query_port;
			long read_socket;
			long nat_negotiate;
			sockaddr_in heartbeat_addr;
			void* proc_process_cdkey; // void (__cdecl*)(char* buffer, size_t buffer_size, sockaddr* src_addr)
			long client_msg_keys[10];
			long client_msg_key_index;
			void* user_data;
		}; static_assert( sizeof(s_gamespy_qr_data) == 0x108 );


		struct s_gamespy_client_node // gsnode_s, gcdkey\gcdkeys.c
		{
			struct s_gamespy_client* client;
			s_gamespy_client_node* next, * prev;
		};
		struct s_gamespy_client // gsclient_s, gcdkey\gcdkeys.c
		{
			long id;					// 0x0
			char cd_hash[33];			// 0x4
			unsigned char : 8; unsigned short : 16;
			uint skey;				// 0x28, (GetTickCount ^ rand) & 0x3FFF
			long ip;
			uint sent_req_time;		// 0x30, GetTickCount
			long number_of_retries;	// 0x34
			long_enum state;			// 0x38, 0 = sent request, 1 = ok, 2 = not ok, 3 = done;
			unsigned long : 32;						// 0x3C, void* proc_unk
			void* authenticate_proc;	// 0x40
			char* errmsg;				// 0x44
			// \auth\\pid\%d\ch\%s\resp\%s\ip\%d\skey\%dd
			char* req_str;				// 0x48, malloc'd char*
			uint req_str_length;		// 0x4C
		}; static_assert( sizeof(s_gamespy_client) == 0x50 );

		__declspec(naked) s_gamespy_client* GsGetClient(long client_id)
		{
			static const uintptr_t FUNCTION = PTR_GAMESPY_GET_CLIENT_KEY_HASH;

			__asm{
			__asm push ebp __asm mov ebp, esp
			push	ecx

			mov		eax, client_id
			call	FUNCTION
			cmp		eax, PTR_compiler_null_string
			jnz		_return
			mov		eax, 4 // will cause us to return NULL. Yes, I r a hacka

			_return:
			sub		eax, 4

			pop		ecx
			__asm pop ebp __asm retn(1*4) }
		}


		struct s_gamespy_product // gsproduct_s, gcdkey\gcdkeys.c
		{
			long game_pid;
			s_gamespy_client_node clients;
		};
		s_gamespy_product* GsProducts(); // TODO: PTR_IMP_GET2 implementation										PTR_IMP_GET2(gamespy_products_list);


		struct s_gamespy_qr2_keybuffer // qr2_keybuffer_s, qr2\qr2.c
		{
			byte keys[Enums::k_max_gamespy_qr_registered_keys];
			unsigned short : 16;
			long numkeys;

			bool add(Enums::gamespy_qr_field keyid) {
				if(numkeys >= Enums::k_max_gamespy_qr_registered_keys)
					return false;
				if(	keyid <= Enums::_gamespy_qr_field_reserved ||
						keyid > Enums::k_max_gamespy_qr_registered_keys)
					return false;

				keys[numkeys++] = keyid;
				return true;
			}

		}; static_assert( sizeof(s_gamespy_qr2_keybuffer) == 0x104 );
		struct s_gamespy_qr2_buffer // qr2_buffer_s, qr2\qr2.c
		{
			enum { k_max_data_size = 2048 };

			byte buffer[k_max_data_size];
			long len;

			bool add(cstring value) {
				long copylen = (long)strlen(value)+1;
				if(copylen > std::size(buffer))
					copylen = std::size(buffer);
				if(copylen <= 0)
					return false;

				bool result = true;

				if (k_errnone == memcpy_s(buffer + len, std::size(buffer) - len, value, (size_t)copylen))
				{
					len += copylen;
					buffer[len - 1] = '\0';
				}
				else
					result = false;

				return result;
			}

			bool add(long value) {
				char buffer[20];
				bool result = sprintf_s(buffer, "%d", value) != -1;
				return result && add(buffer);
			}

		}; static_assert( sizeof(s_gamespy_qr2_buffer) == 0x804 );
		struct s_gamespy_qr2 // qr2_implementation_s, qr2\qr2.h
		{
			enum {
				k_request_key_length = 4,
				k_recent_client_messages_to_track = 10,
			};

			typedef void (__cdecl* serverkeycallback_t)(int keyid, s_gamespy_qr2_buffer* outbuf, void *userdata);
			typedef void (__cdecl* playerteamkeycallback_t)(int keyid, int index, s_gamespy_qr2_buffer outbuf, void *userdata);
			typedef void (__cdecl* keylistcallback_t)(Enums::gamespy_qr_key_type keytype, s_gamespy_qr2_keybuffer* keybuffer, void *userdata);
			typedef void (__cdecl* keylistcallback_t)(Enums::gamespy_qr_key_type keytype, s_gamespy_qr2_keybuffer* keybuffer, void *userdata);	
			typedef long(__cdecl* countcallback_t)(Enums::gamespy_qr_key_type keytype, void *userdata);
			typedef void (__cdecl* adderrorcallback_t)(long_enum error, char *errmsg, void *userdata);
			typedef void (__cdecl* natnegcallback_t)(int cookie, void *userdata);	
			typedef void (__cdecl* clientmessagecallback_t)(char *data, int len, void *userdata);

			typedef void (__cdecl* cdkey_process_t)(char *buf, int len, sockaddr *fromaddr);

			SOCKET hbsock;
			char gamename[64];
			char secret_key[64];
			char instance_key[k_request_key_length];
 			serverkeycallback_t server_key_callback;
 			playerteamkeycallback_t player_key_callback;
 			playerteamkeycallback_t team_key_callback;
 			keylistcallback_t key_list_callback;
 			countcallback_t playerteam_count_callback;
 			adderrorcallback_t adderror_callback;
 			natnegcallback_t nn_callback;
 			clientmessagecallback_t cm_callback;
			uint lastheartbeat;
			uint lastka;
			long listed_state;
			long ispublic;
			long qport;
			long read_socket;
			long nat_negotiate;
			sockaddr_in hbaddr;
			cdkey_process_t cdkeyprocess;
			long client_message_keys[k_recent_client_messages_to_track];
			long cur_message_key;
			void* udata;
		}; static_assert( sizeof(s_gamespy_qr2) == 0x108 );


		struct s_gamespy_config
		{
			long game_pid;
			bool is_public_server;
			unsigned char : 8; unsigned short : 16;
			Enums::e_gamespy_update_status check_for_updates_status;
		};
		struct s_gamespy_globals
		{
			char game_name[8];
			char game_priv_key[8];
			PAD128; // just another (unused) copy of the priv key
			long server_port;

			struct {
				bool initialized;
				unsigned char : 8; unsigned short : 16;
				void* mutex_reference;
				void* thread_reference;
				bool update_check_complete;
				unsigned char : 8; unsigned short : 16;
				unsigned long : 32; // unused space...
				char proxy_server[256];
				bool proxy_server_initialized;
				unsigned char : 8; unsigned short : 16;

				long file_id;
				char download_url[256];
				char version_name[64];
			}game_patch;

			struct {
				long_enum state;
				bool server_is_exiting;
				unsigned char : 8; unsigned short : 16;
				s_gamespy_qr_data* obj;
				uint last_state_change_heartbeat_time;
				char temp_key_buffer[256];
			}qr2;
		}; static_assert( sizeof(s_gamespy_globals) == 0x390 );
		struct s_gamespy_server_browser_globals
		{
			struct {
				s_gamespy_server* server;
				bool has_password;
				unsigned char : 8; unsigned short : 16;
				wchar_t password[10]; // password provided by the user
			}selected_server;

			s_gamespy_server_browser* server_browser;
			bool initialized;
			unsigned char : 8; unsigned short : 16;
			long total_number_of_players; // total number of players on all servers in the current game version
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(byte); // bool
			UNKNOWN_TYPE(byte); // bool
			unsigned short : 16;
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(bool);
			byte_enum server_sort_mode;
			UNKNOWN_TYPE(bool);
			byte_enum dedicated_filter;
			byte_enum game_classic_filter;
			byte_enum custom_maps_filter; // stock is yes/no
			byte_enum game_type_filter;
			byte_enum team_count_filter; // stock only checks for 1 or 2
			byte_enum ping_filter;
			UNKNOWN_TYPE(bool);
			unsigned short : 16; unsigned long : 32;
			wchar_t unknown[256]; // ticker message?
			UNKNOWN_TYPE(long); // probably some kind of state value
			UNKNOWN_TYPE(uint); // flags
			UNKNOWN_TYPE(long);
			long server_browser_update_error;
			struct {
				void* thread_mutex;
				void* thread;
				unsigned long : 32;
			}query_server_list;
			UNKNOWN_TYPE(byte); // bool
			unsigned char : 8; unsigned short : 16;
			UNKNOWN_TYPE(uint); // time
			struct {
				s_gamespy_server** list;
				long count;
			}server_list;
			unsigned long : 32; // set to zero, but never used

			// NOTE: this structure seems to have one less DWORD in it in dedi builds. 
			// However, this structure shouldn't even be accessed in dedi builds so I'm not researching further!
		}; static_assert( sizeof(s_gamespy_server_browser_globals) == 0x27C );


		s_gamespy_socket* GsSocket() 	DPTR_IMP_GET(gs_Socket);
		s_gamespy_socket* GsLoopbackSocket() 		DPTR_IMP_GET(gs_LoopbackSocket);
		s_gamespy_config* GsConfig() 	PTR_IMP_GET2(gamespy_config);
		s_gamespy_globals* GsGlobals() 		PTR_IMP_GET2(gamespy_globals);
		s_gamespy_server_browser_globals* GsServerBrowserGlobals() PTR_IMP_GET2(gamespy_server_browser_globals);
		s_gamespy_qr2* GsQr2() DPTR_IMP_GET(gamespy_qr2);

		// If this is a server, returns all the machines connected to this machine on a specific pid
		s_gamespy_product* GsProducts(); // [4]

		s_gamespy_client* GsGetClient(long client_id);


		namespace GameSpy
		{
#pragma region Settings
			class c_settings_container : public Configuration::c_configuration_container
			{
			public:
				Configuration::c_configuration_value<bool> m_no_update_check;
				c_settings_container() : Configuration::c_configuration_container("Networking.GameSpy") , m_no_update_check("NoUpdateCheck", true)
				{ }

			protected:
				const std::vector<i_configuration_value* const> GetMembers() final override {
					return std::vector<i_configuration_value* const> { &m_no_update_check };
				}

			};

			class c_settings_gamespy
				: public Settings::c_settings_singleton<c_settings_container, c_settings_gamespy>
			{
			public:
				void PostLoad() final override {
					if(Get().m_no_update_check)
					{
						TurnOffUpdateCheck();
					}
				}
			};
#pragma endregion
			static void InitializeForNewQr2()
			{
				// TODO: override key callbacks
			}

#if 0 // PLATFORM_VERSION <= 0x1090
			// Change the old GameSpy URLs to whichever is best for the community these days (should be Bungie's hosthpc.com)
			static void InitializeGameSpyEmulatorUrls()
			{
				GET_PTR(Matchup1Hostname) =
				// natneg1.gamespy.com
				R"(natneg1.hosthpc.com)";
				GET_PTR(Matchup2Hostname) =
				// natneg2.gamespy.com
				R"(natneg2.hosthpc.com)";

				GET_PTR(MASTER_ADDR_REFERENCE) =
				// %s.master.gamespy.com
				R"(s1.master.hosthpc.com)";
				GET_PTR(MASTER_ADDR_SB_REFERENCE) =
				// %s.ms%d.gamespy.com
				R"(s1.ms01.hosthpc.com)";

				GET_PTR(PTA_DEFAULT_VERCHECK_URL_REFERENCE) =
				// http://motd.gamespy.com/motd/vercheck.asp?productid=%d&versionuniqueid=%s&distid=%d
				R"(http://hpcup.bungie.net/motd/vercheck.asp?productid=%d&versionuniqueid=%s&distid=%d)";
			}
#endif

			game_build_string_t& GetGameVer()
			{
				static game_build_string_t g_game_ver;

				return g_game_ver;
			}

			static bool Qr2GetGameVer(char* buffer)
			{
				return k_errnone == strcpy_s(buffer, 0x100, GetGameVer());
			}

			static int __cdecl Qr2StringMatchesGameVer(const char* buffer)
			{
				return strcmp(buffer, GetGameVer())==0;
			}

			static long gamespy_patch_check_for_updates_sans_check()
			{
				return GsConfig()->check_for_updates_status = Enums::_gamespy_update_status_no_update;
			}
			void TurnOffUpdateCheck()
			{
				*GsPatchCheckForUpdates() = false; // pretend we've checked for updates already

				Memory::WriteRelativeCall(&gamespy_patch_check_for_updates_sans_check, GET_DATA_VPTR(GAMESPY_PATCH_SPAWN_CHECK_FOR_UPDATES_THREAD_CALL));
			}

			void Initialize() {
				// TODO: populate GetGameVer()

				c_settings_gamespy::Register(Yelo::Settings::Manager());

#if 0 //PLATFORM_VERSION <= 0x1090
				InitializeGameSpyEmulatorUrls();
#endif
				//Commented out be dwood b/c get_func_vptr needs a comparable implementation rn.
				//Memory::CreateHookRelativeCall(&InitializeForNewQr2, GET_FUNC_VPTR(CREATE_GAMESPY_QR2_HOOK), Enums::_x86_opcode_ret);

#if FALSE // TODO
				qr2_register_key(Enums::_gamespy_qr_field_open_sauce_version, "os_ver");
				qr2_register_key(Enums::_gamespy_qr_field_open_sauce_map, "os_map");
#endif
			}

			void Dispose() {
				c_settings_gamespy::Unregister(Yelo::Settings::Manager());
			}

			// Register a key with the engine's gamespy qr2 API. This tells the SDK that the application will report values for this key
			// [keyid] - Id of the key
			// [key] - Name of the key. Player keys should end in "_" (such as "score_") and team keys should end in "_t"
			// Remarks: GameSpy SDK says all custom keys should be registered prior to (the engine) calling (its gamespy) qr2_init
			// However, I don't see anything in its code that would suggest later registration could bork things up
			void qr2_register_key(Enums::gamespy_qr_field keyid, cstring key) {
				static const uintptr_t FUNCTION = GET_FUNC_PTR(QR2_REGISTER_KEY);

				API_FUNC_NAKED_START()
				push	key
				push	keyid
				call	FUNCTION
				API_FUNC_NAKED_END_CDECL(2)
			}

			bool	SBServerGetBoolValue(s_gamespy_server* server, const char* key, bool def) {
				static const uintptr_t FUNCTION = GET_FUNC_PTR(SBSERVER_GET_BOOL_VALUE);

				API_FUNC_NAKED_START()
				push	def
				push	key
				push	server
				call	FUNCTION
				API_FUNC_NAKED_END_CDECL(3)
			}

			int		SBServerGetIntValue(s_gamespy_server* server, const char* key, int def) {
				static const uintptr_t FUNCTION = GET_FUNC_PTR(SBSERVER_GET_INT_VALUE);

				API_FUNC_NAKED_START()
				push	def
				push	key
				push	server
				call	FUNCTION
				API_FUNC_NAKED_END_CDECL(3)
			}

			cstring	SBServerGetStringValue(s_gamespy_server* server, const char* key, cstring def) {
				static const uintptr_t FUNCTION = GET_FUNC_PTR(SBSERVER_GET_STRING_VALUE);

				API_FUNC_NAKED_START()
				push	def
				push	key
				push	server
				call	FUNCTION
				API_FUNC_NAKED_END_CDECL(3)
			}
		};
	};
};
