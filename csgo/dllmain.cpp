#include "inc.hpp"

#include "features/misc/misc.h"
#include "features/animations/anim.h"

c_csgo g_csgo{ };
c_netvars g_netvars{ };
c_renderer g_renderer{ };
c_menu g_menu{ };
c_config g_configs{ };
vars g_vars{ };
c_client g_cl{ };

static ulong_t __stdcall cheat_init( void *arg ) {
	while ( !GetModuleHandleA( "serverbrowser.dll" ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

	//console::allocate( "s" );

	g_configs.init( );
	g_configs.save( "default" );

	g_csgo.init( );

	g_events.setup( );

	g_netvars.init( );

	g_anim.Init( );

	g_hooks.init( );
	g_hooks.hook( );

	return 1;
}

static ulong_t __stdcall cheat_free( void *arg ) {
	while( !g_input.key_pressed( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

	console::detach( );

	// reset game brightness.
	g_misc.nightmode( 100 );
	g_misc.transparent_props( 100 );

	for( int i = 0; i < 64; i++ ) {
		if( g_anim.m_track[ i ].m_hooked )
			g_anim.m_track[ i ].m_vmt->unhook_all( );
	}

	if( OSHGui::Application::HasBeenInitialized( ) )
		g_renderer.get_renderer().PreD3DReset( );

	Beep( 500, 350 );

	g_hooks.release( );
	g_input.remove( );

	FreeLibraryAndExitThread( ( HMODULE )arg, 0 );
}

int __stdcall DllMain( HMODULE self, ulong_t reason_for_call, void *reserved ) {
	if( reason_for_call == DLL_PROCESS_ATTACH ) {
		HANDLE cheat_thread = CreateThread( nullptr, 0, &cheat_init, nullptr, 0, nullptr );
		if( !cheat_thread )
			return 0;

		HANDLE free_thread = CreateThread( nullptr, 0, &cheat_free, self, 0, nullptr );
		if( !free_thread )
			return 0;

		CloseHandle( cheat_thread );
		CloseHandle( free_thread );

		return 1;
	}

	return 0;
}
