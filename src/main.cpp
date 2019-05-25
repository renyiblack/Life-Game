#include <iostream>
#include <string>    // std::string
#include "life.h"

//TODO CHANGE NAME TO GLIFE


void render_welcome_msg(const Life& state)
{
    std::cout << "Some random welcome message!";
}

int main( int argc, char *argv[] )
{
    Life state;
    std::string argstr(*argv);

    std::cout << argstr;
    /*
    if (argstr.find("--h") != std::string::npos )
        //TODO PRINTS HELP
        ;
    if (memcmp("--imgdir", argv, 7))
        //TODO
        ;
    if (memcmp("--maxgen", argv, 7))
        //TODO /IF NOT INFORMED RUN UNTIL STABILITY OR EXTINCTION IS MEET
        ;
    if (memcmp("--fps", argv, 4))
        //TODO /IT ONLY CHANGES HOW MANY GENERATIONS ARE SHOW ON TERMINAL, DOESN'T AFFECT IF OUTPUT IS FILES
        ;
    if (memcmp("--blocksize", argv, 10))
        //TODO /DEFAULT 5
        ;
    if (memcmp("--bkgcolor", argv, 9))
        //TODO /DEFAULT GREEN
        ;
    if (memcmp("--alivecolor", argv, 11))
        //TODO /DEFAULT GREEN
        ;

    if (memcmp("--outfile", argv, 8))
        //TODO
        ;

    render_welcome_msg( state );

    //TODO OPEN FILE AND INITIALIZE STATE

    // The Game Loop.
    while( !state.over )
    {
        state.process_events;
        state.update;
        state.render;
    }

    //send to log file?
*/
    return EXIT_SUCCESS;
}