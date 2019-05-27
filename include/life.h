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
#include "../include/lodepng.h"
#include "../include/canvas.h"

class Cell {
private:
    bool alive; //!< Records if cell is alive or not.
    life::Point2 point; //!< Where cell is located.

public:
    //=== CONSTRUCTORS ===\\

    Cell(int x=0, int y=0, bool other_alive=false) : point{life::Point2(x,y)}, alive{other_alive} { }

    /// Basic Destructor.
    virtual ~Cell() { }


    bool isalive() const { return alive; }

    void set(bool other_alive) { alive = other_alive; }

    life::Point2 get() const { return point; }

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
    int stable();

    ///Returns if the generation is extinct or nor
    bool extinct();

    std::vector<life::Point2> getalives();

    //std::vector<std::vector<life::Point2>> *getlifes() const { return gens; }


    int height;                                  //!< Height
    int width;                                   //!< Width
    std::vector<std::vector<Cell>> matrix;       //!< Matrix stored as a vector.
    int current_gen;                             //!< Current generation number.
    int max_gen;                                 //!< Max number of generations to simulate.
    int fps;                                     //!< How many generations are show per second on the terminal.It only changes how many generations are show on terminal, doesnt affect if output is a file.
    int blocksize;                               //!< Pixel size of a cell. DEFAULT 5.
    std::string bkgcolor;                        //!< Color name of the background. Default GREEN.
    std::string alivecolor;                      //!< Color name of the background. Default RED.
    char symbol;                                 //!< Character that indicates alive.
    std::vector<std::vector<life::Point2>> *gens; //!<Saves gen log.
};

#include "life.inl"

#endif //LIFE_LIFE_H
