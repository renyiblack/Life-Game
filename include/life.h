#ifndef LIFE_LIFE_H
#define LIFE_LIFE_H
///Developers:
/// Victor Ângelo Graça Morais

/*Available colors are:
BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE
GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE
WHITE YELLOW*/

#include <string.h>             //std::string
#include <vector>               //std::vector
#include "../include/lodepng.h" //encoding
#include "../include/canvas.h"  //creating canvas
#include <iostream>             //basic in/out operations
#include <fstream>              //file operation
#include <sstream>              //string stream operations
#include <thread>               //sleep

class Cell {
private:
    bool alive; //!< Records if cell is alive or not.
    life::Point2 point; //!< Where cell is located.

public:
    //=== CONSTRUCTORS ===\\


    Cell(int x=0, int y=0, bool other_alive=false) : point{life::Point2(x,y)}, alive{other_alive} { }


    //=== DESTRUCTORS ===\\


    /// Basic Destructor.
    virtual ~Cell() { }


    //=== METHODS ===\\


    /// Returns true if cell is alive false otherwise.
    bool isalive() const { return alive; }

    /// Kill cell or let it live.
    void set(bool other_alive) { alive = other_alive; }

    /// Returns cell position (x,y).
    life::Point2 get() const { return point; }

    /// Sets cell position (x,y).
    void setpos(const life::Point2 &other_point) { point = other_point; }
};

class Life
{
public:
    //=== CONSTRUCTORS ===\\


    ///Basic constructor.
    Life(int height=0, int width=0, char symbol='*');


    //=== DESTRUCTORS ===\\


    ///Basic destructor
    ~Life() = default;


    //=== OVERLOADED OPERATORS ===\\\


    ///Copy operator.
    Life& operator=( const Life& );

    ///Compare operator.
    bool operator==( const Life& ) const;

    ///Output operator
    friend std::ostream& operator<<(std::ostream&, const Life &);


    //=== METHODS GAME LOOP ===\\


    ///Returns if the simulations is over or not based on number of generation, if the generation is stable or if it is extinct.
    bool over();

    ///Process the simulation events.
    void process_events();

    ///Update the simulation state.
    void update();

    ///Render the simulation state.
    void render();


    //=== METHODS CELL ===\\


    ///Set an alive cel on coord(x,y).
    void setalive(const std::vector<life::Point2>&);

    ///Returns if the generation is stable or not.
    void stable();

    ///Returns if the generation is extinct or nor
    void extinct();


    //=== CLASS VARIABLES ===\\


    int height;                                  //!< Height
    int width;                                   //!< Width
    std::vector<std::vector<Cell>> matrix;       //!< Matrix stored as a vector.
    int current_gen;                             //!< Current generation number.
    int max_gen;                                 //!< Max number of generations to simulate.
    int fps;                                     //!< How many generations are show per second on the terminal.It only changes how many generations are show on terminal, doesnt affect if output is a file.
    int blocksize;                               //!< Pixel size of a cell. DEFAULT 5.
    life::Color bkgcolor;                        //!< Color name of the background. Default GREEN.
    life::Color alivecolor;                      //!< Color name of the background. Default RED.
    char symbol;                                 //!< Character that indicates alive.
    std::vector<std::vector<Cell>> gens;         //!< Saves gen log.
    bool gameover;                               //!< Records if game is over or not.
    std::string imgdir;                          //!< User defined folder where images are saved.
    std::string outfile;                         //!< User defined file where the game output is saved.
    std::string rule;                            //!< Rule to apply on cells;
};


//=== ENCODING METHODS ===\\


bool save_ppm3( const unsigned char * data, size_t w, size_t h, size_t d,  const std::string & file_name_ );

void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height);

void render_welcome_msg(const Life& state);

#include "life.inl"

#endif //LIFE_LIFE_H
