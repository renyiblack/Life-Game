//=== CONSTRUCTORS ===\\

Life::Life()
{
    H = 5;
    W = 5;
    matrix.reserve(H*W);
    current_gen = 0;
    max_gen = 0;
    fps = 1;
    blocksize = 5;
    bkgcolor = "GREEN";
    alivecolor = "RED";
    changed = true;
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

void Life::set_alive(Point const coord)
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