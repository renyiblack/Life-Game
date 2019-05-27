#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/lodepng.h"
#include "../include/canvas.h"
#include "life.h"

//TODO CHANGE NAME TO GLIFE


void render_welcome_msg(const Life& state)
{
    std::cout << "\n\nSome random welcome message!\n\n";
}

/// Saves an image as a **ascii** PPM file.
bool save_ppm3( const unsigned char * data, size_t w, size_t h, size_t d,  const std::string & file_name_ )
{
    std::ofstream ofs_file( file_name_, std::ios::out  );
    if ( not ofs_file.is_open() )
        return false;

    ofs_file << "P3\n"
             << w << " " << h << "\n"
             << "255\n";

    size_t i{0};
    while ( i < (w*h*d) )
    {
        // depth traversal, usually 3.
        for( auto id{0u} ; id < 3 ; id++ )
            ofs_file << (int) *(data + i++ ) << " ";
        ofs_file << std::endl;
        i++; // to skip alpha channel.
    }

    // Did it not fail?
    auto result = not ofs_file.fail();

    ofs_file.close();

    return result;
}

// Example 1
// Encode from raw pixels to disk with a single function call
// The image argument has width * height RGBA pixels or width * height * 4 bytes
void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height)
{
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

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

    const char* filename = "test.png";

    //generate some image
    unsigned w = state.matrix[0].size() , h = state.matrix.size();//WORKS ON w=20 h=15 bl=40 (800x600); w=2 h=2 bl=2 (4x4); w=48 h=27 bl=40 (1920x1080)
    short block_size = state.blocksize;

    life::Canvas image( w, h, block_size );

    render_welcome_msg( state );

    std::cout<<state;

    for (auto i = 0; i < state.matrix.size(); i++) {
        for (auto j = 0; j < state.matrix[0].size(); j++) {
            if (state.matrix[i][j].isalive())
                image.pixel(life::Point2(j, i), life::RED);
            else
                image.pixel(life::Point2(j, i), life::GREEN);
        }
    }



    encode_png(filename, image.pixels(), image.width(), image.height() );
    save_ppm3( image.pixels(), image.width(), image.height(), 4, "test.ppm");

    /*
    state.process_events();
    std::cout<<state;
    state.process_events();
    std::cout<<state;
    state.process_events();
    std::cout<<state;
    state.process_events();
    std::cout<<state;
    state.process_events();
    std::cout<<state;
*/
//TODO FINISH GAME LOOP
    while( !state.over() )
    {
        state.process_events();
        state.update();
        state.render();
    }

    //send to log file?

    return EXIT_SUCCESS;
}