//=== CONSTRUCTORS ===\\

Life::Life(int height, int width, char other_symbol) : height{height+2}, width{width+2}, symbol{other_symbol} {
    matrix.resize(height);

    for (auto i = 0; i < height; i++) {
        matrix[i].resize(width);

        for (auto j = 0; j < width; j++)
            matrix[i][j] = Cell(i, j);
    }

    current_gen = 1;
    max_gen = 0;
    fps = 1;
    blocksize = 5;
    bkgcolor = "GREEN";
    alivecolor = "RED";
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

    for (auto i = 1; i < other.matrix.size() - 2; i++) {
        for (auto j = 1; j < other.matrix[0].size() - 2; j++) {
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
                os << ".";
        }
        os << "]\n";
    }
    os << "\n";

    return os;
}

//=== METHODS GAME LOOP ===\\

bool Life::over()
{
    if (current_gen == max_gen || extinct())
        return true;
    else
        return false;
}

void Life::process_events() {

    std::vector<std::vector<Cell>> gen_aux = matrix;

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
    //do something
}

void Life::render()
{

}

//=== METHODS CELL ===\\

int Life::stable() {//TODO MAKE IT WORK

    std::vector<life::Point2> points;
    std::vector<life::Point2> cells = getalives();
    int generation = -1;

    for (auto i = 0; i < gens->size() - 1; i++) {

        //points = getlifes()[i];

        bool equal = true;

        if (points.size() == cells.size()) {
            for (auto j = 0; j < points.size(); j++) {
                if (points[j] != cells[j]) {
                    equal = false;
                    break;
                }

            }

            if (equal) {
                generation = i + 1;
                break;
            }
        }
    }

    return generation;
}

bool Life::extinct() {
    for (auto i = 1; i < matrix.size() - 1; i++) {
        for (auto j = 1; j <= matrix[0].size() - 1; j++) {
            if (matrix[i][j].isalive())
                return false;
        }
    }

    return true;
}



std::vector<life::Point2> Life::getalives() {
    std::vector<life::Point2> points;

    for (auto i = 1; i <= matrix.size() - 2; i++) {
        for (auto j = 1; j <= matrix[0].size() - 2; j++) {
            if (matrix[i][j].isalive())
                points.push_back(matrix[i][j].get());
        }
    }

    return points;
}

void Life::setalive(const std::vector<life::Point2>& points) {
    for(auto i=0; i<points.size(); i++) {
        matrix[points[i].y][points[i].x].set(true);
    }
}