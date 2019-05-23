#include <iostream>

int main( void )
{
    GameState state;

    initialize_game( state );

    render_welcome_msg( state );

    // The Game Loop.
    while( !game_over( state ) )
    {
        process_events( state );
        update( state );
        render( state );
    }

    render_log( state );

    return EXIT_SUCCESS;
}