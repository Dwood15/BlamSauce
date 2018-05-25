#include <enginelayout/Game.inl>
#include "../../memory/function_interface/function_interface_test.inl"

typedef void (__cdecl* game_state_proc)();

// stock engine numbers
enum {
	k_number_of_game_state_before_save_procs = 1,
	k_number_of_game_state_before_load_procs = 1,
	k_number_of_game_state_after_load_procs = 13,
};

//////////////////////////////////////////////////////////////////////////
// before save
static game_state_proc game_state_before_save_procs_yelo[] = {
	HandleBeforeSaveLifeCycle,
};
static game_state_proc game_state_before_save_procs_new[k_number_of_game_state_before_save_procs + std::size(game_state_before_save_procs_yelo)] = {};

//////////////////////////////////////////////////////////////////////////
// before load
static game_state_proc game_state_before_load_procs_yelo[] = {
	HandleBeforeLoadLifeCycle,
};
static game_state_proc game_state_before_load_procs_new[k_number_of_game_state_before_load_procs + std::size(game_state_before_load_procs_yelo)] = {};

//////////////////////////////////////////////////////////////////////////
// after load
static game_state_proc game_state_after_load_procs_yelo[] = {
	HandleAfterLoadLifeCycle,
};
static game_state_proc game_state_after_load_procs_new[k_number_of_game_state_after_load_procs + std::size(game_state_after_load_procs_yelo)] = {};

//////////////////////////////////////////////////////////////////////////
// impl
static void __cdecl game_state_call_before_save_procs_new()
{
	for(auto proc : game_state_before_save_procs_new)
		proc();
}
static void __cdecl game_state_call_before_load_procs_new()
{
	for(auto proc : game_state_before_load_procs_new)
		proc();
}

//////////////////////////////////////////////////////////////////////////
// initialization
static void InitializeNewProcsArrays()
{
	using namespace Enums;
	//////////////////////////////////////////////////////////////////////////
	// before save
	{
		// Get the one-and-only save proc from the first call address
		game_state_proc* before_save_proc = *reinterpret_cast<game_state_proc **>(K_GAME_STATE_BEFORE_SAVE_PROCS_CALLS[0] + sizeof(_x86_opcode_call_abs));

		// Copy the game's proc to the 'new' proc array
		game_state_before_save_procs_new[0] = *before_save_proc;
		// Copy our Yelo procs to the 'new' proc array
		for(int x = 0; x < std::size(game_state_before_save_procs_yelo); x++)
			game_state_before_save_procs_new[x+k_number_of_game_state_before_save_procs] = 
				game_state_before_save_procs_yelo[x];
	}
	//////////////////////////////////////////////////////////////////////////
	// before load
	{
		// Get the one-and-only load proc from the first call address
		game_state_proc* before_load_proc = *reinterpret_cast<game_state_proc **>(K_GAME_STATE_BEFORE_LOAD_PROCS_CALLS[0] + sizeof(_x86_opcode_call_abs));

		// Copy the game's proc to the 'new' proc array
		game_state_before_load_procs_new[0] = *before_load_proc;
		// Copy our Yelo procs to the 'new' proc array
		for(int x = 0; x < std::size(game_state_before_load_procs_yelo); x++)
			game_state_before_load_procs_new[x+k_number_of_game_state_before_load_procs] = 
			game_state_before_load_procs_yelo[x];
	}
	//////////////////////////////////////////////////////////////////////////
	// after load
	{
		// Get the address of the first element of the game's after load procs
		game_state_proc* after_load_procs = *reinterpret_cast<game_state_proc **>(K_GAME_STATE_AFTER_LOAD_PROCS_REFS[0]);

		// Copy the game's procs to the 'new' proc array
		for(int x = 0; x < k_number_of_game_state_after_load_procs; x++)
			game_state_after_load_procs_new[x] = after_load_procs[x];
		// Copy our Yelo procs to the 'new' proc array
		for(int x = 0; x < std::size(game_state_after_load_procs_yelo); x++)
			game_state_after_load_procs_new[x+k_number_of_game_state_after_load_procs] = 
			game_state_after_load_procs_yelo[x];
	}
}

static void InitializeProcs()
{
	InitializeNewProcsArrays();
	//////////////////////////////////////////////////////////////////////////
	// before save
	{
		for(auto ptr : K_GAME_STATE_BEFORE_SAVE_PROCS_CALLS)
			Memory::CreateHookRelativeCall(&game_state_call_before_save_procs_new,
													 reinterpret_cast<void *>(ptr), Enums::_x86_opcode_nop);
	}
	//////////////////////////////////////////////////////////////////////////
	// before load
	{
		for(auto ptr : K_GAME_STATE_BEFORE_LOAD_PROCS_CALLS)
			Memory::CreateHookRelativeCall(&game_state_call_before_load_procs_new,
													 reinterpret_cast<void *>(ptr), Enums::_x86_opcode_nop);
	}
	//////////////////////////////////////////////////////////////////////////
	// after load
	{
		static_assert( std::size(K_GAME_STATE_AFTER_LOAD_PROCS_REFS) == std::size(K_GAME_STATE_AFTER_LOAD_PROCS_COUNTS) );

		for(int x = 0; x < std::size(K_GAME_STATE_AFTER_LOAD_PROCS_REFS); x++)
		{
			game_state_proc** procs_ref = reinterpret_cast<game_state_proc **>(K_GAME_STATE_AFTER_LOAD_PROCS_REFS[x]);
			size_t* count_ref = reinterpret_cast<size_t *>(K_GAME_STATE_AFTER_LOAD_PROCS_COUNTS[x]);

			*procs_ref = game_state_after_load_procs_new;
			*count_ref = std::size(game_state_after_load_procs_new);
		}
	}
}
