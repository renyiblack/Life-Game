#include "life.h"

//=== CONSTRUCTORS ===\\

Life::Life(int height, int width, char other_symbol) : height{height+2}, width{width+2}, symbol{other_symbol} {
    matrix.resize(height);

    for (auto i = 0; i < height; i++) {
        matrix[i].resize(width);

        for (auto j = 0; j < width; j++)
            matrix[i][j] = Cell(i, j);
    }

    current_gen = 1;
    max_gen = 20;
    fps = 1;
    blocksize = 5;
    bkgcolor = "GREEN";
    alivecolor = "RED";
    gameover = false;
}

//=== OVERLOADED OPERATORS ===\\\

Life& Life::operator=(const Life& other) {
    width = other.width;
    height = other.height;
    matrix = other.matrix;
    symbol = other.symbol;

    return *this;
}

bool Life::operator==(const Life& other) const {

    if (width != other.width)
        return false;

    if (height != other.height)
        return false;

    for (auto i = 1; i < other.matrix.size() - 1; i++) {
        for (auto j = 1; j < other.matrix[0].size() - 1; j++) {
            if (matrix[i][j].isalive() != other.matrix[i][j].isalive())
                return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Life &other) {
    os << "Gen " << other.current_gen << ":\n";

    for (auto i = 0; i < other.matrix.size(); i++) {
        os << "[";
        for (auto j = 0; j < other.matrix[0].size(); j++) {
            if (other.matrix[i][j].isalive())
                os << other.symbol;
            else
                os << " ";
        }
        os << "]\n";
    }
    os << "\n";

    return os;
}

//=== METHODS GAME LOOP ===\\

bool Life::over()
{
    return gameover;
}

void Life::process_events() {

    std::vector<std::vector<Cell>> gen_aux = matrix;
    gens = gen_aux;

    int cont;

    for (auto i = 1; i < matrix.size() - 1; i++) { //TODO IMPROVE BOUNDARIES
        for (auto j = 1; j < matrix[0].size() - 1; j++) {

            cont = 0;

            if (gen_aux[i - 1][j - 1].isalive())
                cont++;
            if (gen_aux[i - 1][j].isalive())
                cont++;
            if (gen_aux[i - 1][j + 1].isalive())
                cont++;
            if (gen_aux[i][j - 1].isalive())
                cont++;
            if (gen_aux[i][j + 1].isalive())
                cont++;
            if (gen_aux[i + 1][j - 1].isalive())
                cont++;
            if (gen_aux[i + 1][j].isalive())
                cont++;
            if (gen_aux[i + 1][j + 1].isalive())
                cont++;

            if (gen_aux[i][j].isalive()) {
                if (!(cont == 2 || cont == 3))
                    matrix[i][j].set(false);
            }
            else {
                if (cont == 3)
                    matrix[i][j].set(true);
            }
        }
    }

    current_gen++;
}

void Life::update()
{
    if(max_gen == current_gen)
        gameover = true;
    stable();
    extinct();
}

void Life::render()
{
    std::cout<<*this;

    std::string filenamepng = "../img/gen ";

    filenamepng += std::to_string(current_gen);

    std::string filenameppm = filenamepng;

    filenamepng.append(".png");
    filenameppm.append(".ppm");

    const char* png = &filenamepng[0];

    //generate some image
    unsigned w = matrix[0].size() , h = matrix.size();//WORKS ON w=20 h=15 bl=40 (800x600); w=2 h=2 bl=2 (4x4); w=48 h=27 bl=40 (1920x1080)
    short block_size = blocksize;

    life::Canvas image( w, h, block_size );


    for (auto i = 0; i < matrix.size(); i++) {
        for (auto j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j].isalive())
                image.pixel(life::Point2(j, i), life::RED);
            else
                image.pixel(life::Point2(j, i), life::GREEN);
        }
    }

    encode_png(png, image.pixels(), image.width(), image.height() );
    save_ppm3( image.pixels(), image.width(), image.height(), 4, filenameppm);
}


//=== METHODS CELL ===\\


void Life::stable() {//TODO NEEDS MORE TESTS

    for (auto i = 1; i < matrix.size() - 1; i++) {
        for (auto j = 1; j < matrix[0].size() - 1; j++) {
            if (matrix[i][j].isalive() != gens[i][j].isalive()) {
                gameover = false;
                return;
            }
        }
    }
    gameover = true;
}

void Life::extinct() {
    gameover = true;
    for (auto i = 1; i < matrix.size() - 1; i++) {
        for (auto j = 1; j < matrix[0].size() - 1; j++) {
            if (matrix[i][j].isalive()) {
                gameover = false;
                return;
            }
        }
    }
}

void Life::setalive(const std::vector<life::Point2>& points) {
    for(auto i=0; i<points.size(); i++) {
        matrix[points[i].y][points[i].x].set(true);
    }
}

//=== ENCODING ===\\


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
