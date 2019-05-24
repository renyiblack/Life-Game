#include <iostream>

//TODO CHANGE NAME TO GLIFE

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
	
	Life();
	Life(int lin, int col);

	//=== DESTRUCTORS ===\\

	~Life();

	//=== METHODS GAME LOOP ===\\

	bool over() const;
	void process_events();
	void update();
	void render();
	void print();

	//=== METHODS CELL ===\\

	void set_alive(Dot const coord);
	bool stable();
	bool extinct();

private:
	int H;
	int W;
	int M[W][H]; //why???
	int current_gen;
	int max_gen;
	bool changed;
};

//=== CONSTRUCTORS ===\\

Life::Life()
{
	//empty
}

Life::Life(int lin, int col)
{
	W = lin;
	H = col;
	changed = 1;
}

//=== DESTRUCTORS ===\\

Life::~Life()
{
	//empty
}

//=== METHODS GAME LOOP ===\\

bool Life::over() const
{
	if (stable || current_gen == max_gen || extinct)
		return true;
	else
		return false;
}

void Life::process_events()
{
	//do something
}

void Life::update()
{
	//do something
}

void Life::render()
{
	//do something
}

//=== METHODS CELL ===\\





void render_welcome_msg(const Life& state)
{
	std::cout << "Some random welcome message!";
}

int main( int argc, char *argv[] )
{
    Life state;

	if (memcmp("--h", argv, 2)) //use something to find the substring instead of memcmp
		//TODO PRINTS HELP
		;
	if (memcmp("--imgdir", argv, 7))
		//TODO
		;
	if (memcmp("--maxgen", argv, 7))
		//TODO /IF NOT INFORMED RUN UNTIL STABILITY OR EXTINCTION IS MEET
		;
	if (memcmp("--fps", argv, 4))
		//TODO /IT ONLY CHANGES HOW MANY GENERATIONS ARE SHOW ON TERMINAL, DOESN'T AFFECT IF OUTPUT IS FILES
		;
	if (memcmp("--blocksize", argv, 10))
		//TODO /DEFAULT 5
		;
	if (memcmp("--bkgcolor", argv, 9))
		//TODO /DEFAULT GREEN
		;
	if (memcmp("--alivecolor", argv, 11))
		//TODO /DEFAULT GREEN
		;

	if (memcmp("--outfile", argv, 8))
		//TODO
		;

    render_welcome_msg( state );

	//TODO OPEN FILE AND INITIALIZE STATE

    // The Game Loop.
    while( !state.over )
    {
        state.process_events;
        state.update;
        state.render;
    }

	//send to log file?

    return EXIT_SUCCESS;
}