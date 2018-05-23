#Yeah, I know, I got lazy. But holey moley is it a pain to do so many of these different CMakeLists files.

set(N_CLIENT_H
	${CMAKE_CURRENT_SOURCE_DIR}/client/manager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/client/manager_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/client/time.hpp)

set(N_GAME_H
	${CMAKE_CURRENT_SOURCE_DIR}/game/globals.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/manager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/manager_structures.hpp)

set(N_MESSAGES_H
	${CMAKE_CURRENT_SOURCE_DIR}/messages/delta_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/messages/delta_parameters_protocol.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/messages/messages.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/messages/messages_structures.hpp)

set(N_PLAYER_UPDATE_H
	${CMAKE_CURRENT_SOURCE_DIR}/player_update/client.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/player_update/history.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/player_update/server.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/player_update/update.hpp)

set(N_SERVER_H
	${CMAKE_CURRENT_SOURCE_DIR}/server/network_server_manager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/server/server.h
	${CMAKE_CURRENT_SOURCE_DIR}/server/network_server_manager_structures.hpp)

set(N_TRANSPORT_H
	${CMAKE_CURRENT_SOURCE_DIR}/transport/address.h
	${CMAKE_CURRENT_SOURCE_DIR}/transport/endpoint_set_winsock.h
	${CMAKE_CURRENT_SOURCE_DIR}/transport/endpoint_winsock.h)

set(NETWORK_H
	${N_CLIENT_H}
	${N_GAME_H}
	${N_MESSAGES_H}
	${N_PLAYER_UPDATE_H}
	${N_SERVER_H}
	${N_TRANSPORT_H}
	${CMAKE_CURRENT_SOURCE_DIR}/connections.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/message_header.h
	PARENT_SCOPE)
