#include <iostream>
#include <fstream>
#include <sstream>
#include "life.h"

//TODO CHANGE NAME TO GLIFE


void render_welcome_msg(const Life& state)
{
    std::cout << "\n\nSome random welcome message!\n\n";
}

int main( int argc, char **argv )
{
    Life state;
    std::string line;
    std::string aux;

    std::cout << "You have entered " << argc
         << " arguments:" << "\n";

    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << "\n";

    for (int i = 0; i < argc; ++i) {
        if (strstr(*(argv + i), "--h") != nullptr)
        {
            std::cout << "\n\n\n\n\n\n\n\n\n\n";
            std::ifstream help;
            help.open ("../src/help.txt", std::ifstream::in);
            if (help.is_open())
            {
                while (getline(help, line))
                {
                    std::cout<< line << '\n';
                }
                help.close();
            }
        }

        if (strstr(*(argv + i), "--imgdir") != nullptr)
        {
            i++;

            std::ofstream imgdir;
            imgdir.open(*(argv + i), std::ifstream::out);

            if(!imgdir.is_open())
            {
                std::cout << "Unable to open file.\n";
            }

            std::cout << *(argv + i) << "\n";

            imgdir.close();
        }

        ///IF NOT INFORMED RUN UNTIL STABILITY OR EXTINCTION IS MEET
        if (strstr(*(argv + i), "--maxgen") != nullptr)
        {
            i++;

            state.max_gen = atoi(*(argv + i));

            std::cout << state.max_gen << "\n";

        }

        if (strstr(*(argv + i), "--fps") != nullptr)
        {
            i++;

            state.fps = atoi(*(argv + i));

            std::cout << state.fps << "\n";
        }

        if (strstr(*(argv + i), "--blocksize") != nullptr)
        {
            i++;

            state.blocksize = atoi(*(argv + i));

            std::cout << state.blocksize << "\n";
        }

        if (strstr(*(argv + i), "--bkgcolor") != nullptr)
        {
            i++;

            state.bkgcolor = *(argv + i);

            std::cout << state.bkgcolor << "\n";
        }

        if (strstr(*(argv + i), "--alivecolor") != nullptr)
        {
            i++;

            state.alivecolor = *(argv + i);

            std::cout << state.alivecolor << "\n";
        }

        if (strstr(*(argv + i), "--outfile") != nullptr)
        {
            i++;

            std::ofstream outfile;
            outfile.open(*(argv + i), std::ifstream::out);

            if(!outfile.is_open())
            {
                std::cout << "Unable to open file.\n";
            }

            std::cout << *(argv + i) << "\n";

            outfile.close();
        }
    }

    //TODO OPEN FILE

    render_welcome_msg( state );

    while( !state.over() )
    {
        state.process_events();
        state.update();
        state.render();
    }

    //send to log file?

    return EXIT_SUCCESS;
}