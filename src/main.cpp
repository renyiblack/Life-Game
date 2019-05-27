#include "life.h"

int main( int argc, char **argv )
{
    Life state;
    std::string line;

    std::cout << "You have entered " << argc
         << " arguments:" << "\n";

    for (int i = 1; i < argc; ++i)
        std::cout << argv[i] << "\n";

    for (int i = 1; i < argc; ++i) {
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

        else if (strstr(*(argv + i), "--imgdir") != nullptr)
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
        else if (strstr(*(argv + i), "--maxgen") != nullptr)
        {
            i++;

            state.max_gen = atoi(*(argv + i));

            std::cout << state.max_gen << "\n";

        }

        else if (strstr(*(argv + i), "--fps") != nullptr)
        {
            i++;

            state.fps = atoi(*(argv + i));

            std::cout << state.fps << "\n";
        }

        else if (strstr(*(argv + i), "--blocksize") != nullptr)
        {
            i++;

            state.blocksize = atoi(*(argv + i));

            std::cout << state.blocksize << "\n";
        }

        else if (strstr(*(argv + i), "--bkgcolor") != nullptr)
        {
            i++;

            state.bkgcolor = *(argv + i);

            std::cout << state.bkgcolor << "\n";
        }

        else if (strstr(*(argv + i), "--alivecolor") != nullptr)
        {
            i++;

            state.alivecolor = *(argv + i);

            std::cout << state.alivecolor << "\n";
        }

        else if (strstr(*(argv + i), "--outfile") != nullptr)
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
        ///Read from a file and saves it's values on state.matrix
        else {
            std::ifstream dat;
            dat.open(*(argv + i), std::ifstream::in);

            if (!dat.is_open()) {
                std::cout << "Unable to open file.\n";
            }
            std::getline(dat, line);
            std::stringstream ss;

            /* Storing the whole string into string stream */
            ss << line;

            /* Running loop till the end of the stream */
            std::string temp;
            int found;
            for (int cont = 0; !ss.eof(); cont++) {
                /* extracting word by word from stream */
                ss >> temp;

                /* Checking the given word is integer or not */
                if (std::stringstream(temp) >> found) {
                    if (cont == 0) {
                        state.height = found;
                        std::cout << found << " ";
                    }
                    if (cont == 1) {
                        state.width = found;
                        std::cout << found << "\n";
                    }
                }
                /* To save from space at the end of string */
                temp = "";
            }

            dat >> state.symbol;
            std::getline(dat, line);

            std::vector<life::Point2> alives;

            for(auto l=0; l<state.height; l++) {
                std::getline(dat, line);

                for (auto c = 0; c < line.size(); c++) {
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

    render_welcome_msg( state );

    state.render();


    while( !state.over() )
    {
        state.process_events();
        state.update();
        state.render();
    }

    //send to log file?

    return EXIT_SUCCESS;
}