//=== CONSTRUCTORS ===\\

Life::Life()
{
    H = 0;
    W = 0;
    current_gen = 0;
    max_gen = 0;
    changed = true;
}

Life::Life(int lin, int col)
{
    W = lin;
    H = col;
    changed = true;
}

//=== DESTRUCTORS ===\\

Life::~Life()
{
    //empty
}

//=== METHODS GAME LOOP ===\\

bool Life::over()
{
    if (stable() || current_gen == max_gen || extinct())
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

void Life::set_alive(Dot const coord)
{

}

bool Life::stable()
{
    return changed;
}

bool Life::extinct()
{
    return false;
}