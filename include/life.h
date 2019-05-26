#ifndef LIFE_LIFE_H
#define LIFE_LIFE_H
///Developers:
/// Victor Ângelo Graça Morais
/// Heitor Pereira Paiva

/*Available colors are:
BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE
GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE
WHITE YELLOW*/

#include <string.h> //std::string
#include <vector>

struct Point
{
    int x, y;
};

class Life
{
public:
    //=== CONSTRUCTORS ===\\

    ///Basic constructor.
    Life();

    //=== DESTRUCTORS ===\\

    ///Basic destructor
    ~Life() = default;

    //=== METHODS GAME LOOP ===\\

    ///Returns if the simulations is over or not based on number of generation, if the generation is stable or if it is extinct.
    bool over();

    ///Process the simulation events.
    void process_events();

    ///Update the simulation state.
    void update();

    ///Render the simulation state.
    void render();

    ///Print the state.
    void print();

    //=== METHODS CELL ===\\

    ///Set an alive cel on coord(x,y).
    void set_alive(Point const coord);

    ///Returns if the generation is stable or not.
    bool stable();

    ///Returns if the generation is extinct or nor
    bool extinct();

    int H;                   //!< Height
    int W;                   //!< Width
    std::vector<char> matrix; //!< Matrix stored as a vector.
    int current_gen;         //!< Current generation number.
    int max_gen;             //!< Max number of generations to simulate.
    int fps;                 //!< How many generations are show per second on the terminal.It only changes how many generations are show on terminal, doesnt affect if output is a file.
    int blocksize;           //!< Pixel size of a cell. DEFAULT 5.
    std::string bkgcolor;    //!< Color name of the background. Default GREEN.
    std::string alivecolor;  //!< Color name of the background. Default RED.
    char c;                  //!< Character that indicates alive.
    bool changed;            //!< If generation changed or not.
};

#include "life.inl"

#endif //LIFE_LIFE_H
