#ifndef LIFE_LIFE_H
#define LIFE_LIFE_H
///Developers:
/// Victor Ângelo Graça Morais
/// Heitor Pereira Paiva

/*Available colors are:
BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE
GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE
WHITE YELLOW*/

struct Dot
{
    int x, y;
};

class Life
{
public:
    //=== CONSTRUCTORS ===\\

    ///Basic constructor.
    Life();

    ///Constructor with params.
    Life(int lin, int col);

    //=== DESTRUCTORS ===\\

    ///Basic destructor
    ~Life();

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
    void set_alive(Dot const coord);

    ///Returns if the generation is stable or not.
    bool stable();

    ///Returns if the generation is extinct or nor
    bool extinct();

private:
    int H;           //!< Height
    int W;           //!< Width
    int *M;          //!< Number of lines the matrix have
    int *N;          //!< Number of columns the matrix have
    int current_gen; //!< Current generation number.
    int max_gen;     //!< Max generations can be born.
    bool changed;
};

#include "life.inl"

#endif //LIFE_LIFE_H
