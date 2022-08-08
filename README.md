# Game of Life.

This is an implementation of Conway's Game of Life written in C++11 using
std libraries and SFML that supports a 64-bit integer space.

Please download [SFML](https://www.sfml-dev.org/download.php) and compile with the path to SFML libraries.

This program has two modes, a CLI mode and a GUI mode. By default, given no arguments,
it inputs from `testInput.lif` (a standard ship generator), runs 10 steps, and outputs to `output.lif`.
Info on changing these options is found below.

# Arguments

This program accepts a few different flags and arguments.

## -o
The name of the output file. For example, `-o output` outputs to `output.lif`.

## -i
The name of the input file. For example, `-i input.ext` inputs from `input.ext`.

Input files must match the following file format:

```
#DESCRIPTOR
(0, 0)
(0, 1)
...
```

## -c
The number of iterations to run/steps to take. Must be greater than 10. For example, `-c 11` runs 10 steps.

## -t
Which type of the program you'd like to run. 

Types include the following:

```
gui
cli
```

For example, `-t gui` runs the GUI version of the program.

## -g
The g flag specifies whether or not to generate a file. It takes 4 arguments.

In order, `filename of generated file`, `lower bound`, `upper bound`, `number of live cells to generate`.

It generates 2 files, one in Life 1.06 format with the 
filename `LIFE106` + `filename of generated file`, and another with `filename of generated file.`.

For example, `-g filename -100 100 1000` produces two with 1000 randomly
generated coordinates in the range -100 to 100. The names are
`LIFE106filename.lif` and `filename.lif`.

The files generated can be used for input.

For example, `-g filename -100 100 1000 -i filename.lif` works as expected.

## -w & -h

Sets the width and height of the frame rendered if in GUI mode.

Width and height are overridden to 0 in CLI mode to improve performance.

For example, `-w 800 -h 600` renders an 800x600 frame.

1 cell = 4 pixels, so 800x600 pxels = 200x150 cells rendered.