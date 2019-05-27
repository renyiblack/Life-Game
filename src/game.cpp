#include "life.h"

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

void render_welcome_msg(const Life& state)
{
    std::cout << "\n\nSome random welcome message!\n\n";
}