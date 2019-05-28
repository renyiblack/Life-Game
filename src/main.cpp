///Developers:
/// Victor Ângelo Graça Morais

#include "life.h"

int main( int argc, char **argv )
{
    Life state;
    std::string line;


//=== READING FROM TERMINAL ===\


    for (int i = 1; i < argc; i++)
    {
        if(argv[i][0] == 'B' and argv[i][2] == '/' and argv[i][3] == 'S')
        {
            state.rule = *(argv + i);
        }
        else if (strstr(*(argv + i), "--help") != nullptr)
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
        else if (strstr(*(argv + i), "--imgdir") != nullptr)
        {
            i++;

            state.imgdir = *(argv + i);
        }
        ///IF NOT INFORMED RUN UNTIL STABILITY OR EXTINCTION IS MET
        else if (strstr(*argv, "--maxgen") != nullptr) ///DOESNT WORK
        {
            i++;
            state.max_gen = atoi(*(argv + i));
        }
        else if (strstr(*(argv + i), "--fps") != nullptr)
        {
            i++;

            state.fps = atoi(*(argv + i));
        }
        else if (strstr(*(argv + i), "--blocksize") != nullptr)
        {
            i++;

            state.blocksize = atoi(*(argv + i));
        }
        else if (strstr(*(argv + i), "--bkgcolor") != nullptr)
        {
            i++;

            if(strstr(*(argv + i), "BLACK") != nullptr)
            {
                state.bkgcolor = life::BLACK;
            }
            else if(strstr(*(argv + i), "CRIMSON") != nullptr)
            {
                state.bkgcolor = life::CRIMSON;
            }
            else if(strstr(*(argv + i), "DARK_GREEN") != nullptr)
            {
                state.bkgcolor = life::DARK_GREEN;
            }
            else if(strstr(*(argv + i), "DEEP_SKY_BLUE") != nullptr)
            {
                state.bkgcolor = life::DEEP_SKY_BLUE;
            }
            else if(strstr(*(argv + i), "DODGER_BLUE") != nullptr)
            {
                state.bkgcolor = life::DODGER_BLUE;
            }
            else if(strstr(*(argv + i), "GREEN") != nullptr)
            {
                state.bkgcolor = life::GREEN;
            }
            else if(strstr(*(argv + i), "LIGHT_BLUE") != nullptr)
            {
                state.bkgcolor = life::LIGHT_BLUE;
            }
            else if(strstr(*(argv + i), "LIGHT_GREY") != nullptr)
            {
                state.bkgcolor = life::LIGHT_GREY;
            }
            else if(strstr(*(argv + i), "LIGHT_YELLOW") != nullptr)
            {
                state.bkgcolor = life::LIGHT_YELLOW;
            }
            else if(strstr(*(argv + i), "RED") != nullptr)
            {
                state.bkgcolor = life::RED;
            }
            else if(strstr(*(argv + i), "STEEL_BLUE") != nullptr)
            {
                state.bkgcolor = life::STEEL_BLUE;
            }
            else if(strstr(*(argv + i), "WHITE") != nullptr)
            {
                state.bkgcolor = life::WHITE;
            }
            else if(strstr(*(argv + i), "YELLOW") != nullptr)
            {
                state.bkgcolor = life::YELLOW;
            }
        }
        else if (strstr(*(argv + i), "--alivecolor") != nullptr)
        {
            i++;

            if(strstr(*(argv + i), "BLACK") != nullptr)
            {
                state.alivecolor = life::BLACK;
            }
            else if(strstr(*(argv + i), "CRIMSON") != nullptr)
            {
                state.alivecolor = life::CRIMSON;
            }
            else if(strstr(*(argv + i), "DARK_GREEN") != nullptr)
            {
                state.alivecolor = life::DARK_GREEN;
            }
            else if(strstr(*(argv + i), "DEEP_SKY_BLUE") != nullptr)
            {
                state.alivecolor = life::DEEP_SKY_BLUE;
            }
            else if(strstr(*(argv + i), "DODGER_BLUE") != nullptr)
            {
                state.alivecolor = life::DODGER_BLUE;
            }
            else if(strstr(*(argv + i), "GREEN") != nullptr)
            {
                state.alivecolor = life::GREEN;
            }
            else if(strstr(*(argv + i), "LIGHT_BLUE") != nullptr)
            {
                state.alivecolor = life::LIGHT_BLUE;
            }
            else if(strstr(*(argv + i), "LIGHT_GREY") != nullptr)
            {
                state.alivecolor = life::LIGHT_GREY;
            }
            else if(strstr(*(argv + i), "LIGHT_YELLOW") != nullptr)
            {
                state.alivecolor = life::LIGHT_YELLOW;
            }
            else if(strstr(*(argv + i), "RED") != nullptr)
            {
                state.alivecolor = life::RED;
            }
            else if(strstr(*(argv + i), "STEEL_BLUE") != nullptr)
            {
                state.alivecolor = life::STEEL_BLUE;
            }
            else if(strstr(*(argv + i), "WHITE") != nullptr)
            {
                state.alivecolor = life::WHITE;
            }
            else if(strstr(*(argv + i), "YELLOW") != nullptr)
            {
                state.alivecolor = life::YELLOW;
            }
        }
        else if (strstr(*(argv + i), "--outfile") != nullptr)
        {
            i++;

            state.outfile = *(argv + i);
        }
        ///Read from a file and saves it's values on state.matrix
        else{
            std::ifstream dat;
            dat.open(*(argv + i), std::ifstream::in);

            if (!dat.is_open())
            {
                std::cout << "Unable to open file.\n";
            }
            std::getline(dat, line);
            std::stringstream ss;

            ss << line;

            std::string temp;
            int found;
            for (int cont = 0; !ss.eof(); cont++)
            {
                ss >> temp;

                if (std::stringstream(temp) >> found)
                {
                    if (cont == 0)
                    {
                        state.height = found;
                    }
                    if (cont == 1)
                    {
                        state.width = found;
                    }
                }
                temp = "";
            }

            dat >> state.symbol;
            std::getline(dat, line);

            std::vector<life::Point2> alives;

            for(auto l=0; l<state.height; l++)
            {
                std::getline(dat, line);

                for (auto c = 0; c < line.size(); c++)
                {
                    if (c ==state.width)
                    {
                        break;
                    }
                    if (line.at(c) == state.symbol)
                    {
                        alives.push_back(life::Point2(c, l));
                    }
                }
            }

            dat.close();

            state = Life{state.height, state.width, state.symbol};

            state.setalive(alives);
        }
    }


    //=== THE GAME ===\\


    render_welcome_msg( state );

    state.render(); //Renders gen 1(first gen passed by file).

    while( !state.over() )
    {
        state.process_events(); //Kill, let live or create new cells.
        state.update(); //Update simulation.
        state.render(); //Drawn the images on files or terminal.
    }

    return EXIT_SUCCESS;
}