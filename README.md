# Life-Game
Simulation of the life game, by Conway

# Img

The default path where the images created are saved.

# Include

Where the *.h and *.inl are located.

# Src

Where the *.cpp files are located.

# Build

To build this project you can compile via terminal going to the folder where the project is located, then compile the project using `g++ -Wall -std=c++11 -I include src/main.cpp src/lodepng.cpp glife`

Or you can use cmake. This is the recomended method.

Supposing you put Life-Game in the directory `${LIFE_DIR}`:

    mkdir mybuild       # Create a directory to hold the build output.
    cd mybuild
    cmake ${LIFE_DIR}  # Generate native build scripts

# Limitations

The file provided by the user must follow **strictly** the following structure. This project doesn't correct user errors, please carefully make the file and use the terminal commands with care.

```
<nLin> <nCol>
<caractere_vivo>
<linha_de_dado_1_de_comprimento_nCol>
<linha_de_dado_2_de_comprimento_nCol>
<linha_de_dado_3_de_comprimento_nCol>
...
<linha_de_dado_nLin_de_comprimento_nCol>

```
* For some reason the --maxgen is not working properly, still needs debuging.
* This version still needs improvement when processing the generation, it doesn't properly update cells on the edge.
* This version still needs improvement in the stable() function, it just compares the current generation and the previous one.

# Bonus

This program takes custom rules for evolution in the format `B3/S23`. 
Ex.:

    $./glife  virus.dat --fps 10 B3/23

# Developer

Victor Ângelo Graça Morais(git - https://github.com/bllackangell/Life-Game)


ps.: This git will be private until the project due date is met.
