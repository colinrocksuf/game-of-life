#include "gol.h"
#include <SFML/Graphics.hpp>

using namespace std;
 
int main(int argc, char **argv)
{
    //initialize and define default values
    string outputFile = "output.lif", inputFile = "testInput.lif", type = "cli", generatedFileName = "";
    unsigned int stepsToTake = 10, cellCount = 0, windowWidth = 800, windowHeight = 600;
    int lowerBound = 0, upperBound = 0;

    //scan for inputs
    for (int i = 1; i < argc; i++)
    {  
        if (i+1 != argc)
        {
            if (strcmp(argv[i], "-o") == 0)
            {                 
                outputFile = argv[i+1];
                outputFile += ".lif";
                i++;
            }
            if (strcmp(argv[i], "-i") == 0)
            {                 
                inputFile = argv[i+1];
                i++;
            }
            else if (strcmp(argv[i], "-c") == 0)
            {
                stepsToTake = stoi(argv[i+1]);
                i++;
            }
            else if (strcmp(argv[i], "-t") == 0)
            {
                type = argv[i+1];
                i++;
            }
            else if (strcmp(argv[i], "-g") == 0)
            {
                
                generatedFileName = argv[i+1];
                lowerBound = stoi(argv[i+2]);
                upperBound = stoi(argv[i+3]);
                cellCount = stoi(argv[i+4]);
                i+=4;
            }
            else if (strcmp(argv[i], "-w") == 0)
            {
                windowWidth = stoi(argv[i+1]);
                i++;
            }
            else if (strcmp(argv[i], "-h") == 0)
            {
                windowHeight = stoi(argv[i+1]);
                i++;
            }
        }
    }
    
    //in order to create a satisfactory output file, we need to take at least 10 steps
    if (stepsToTake < 10)
        throw invalid_argument("Invalid step count! Input a step count larger than 10.");

    if (generatedFileName != "")
    {
        if (lowerBound < upperBound)
        {
            GOL game;
            game.generateTestFile(generatedFileName, lowerBound, upperBound, cellCount);
        }
        else
        {
            throw invalid_argument("Lower bound must be less than the upper bound specified.");
        }
    }

    if (type == "cli")
    {
        GOL game;
        game.setWidth(0);
        game.setHeight(0);
        game.loadFile(inputFile);
        for (int i = 0; i < stepsToTake; i++)
        {
            game.step();

            if (i == 9) //@ step 10
                game.writeToFile(outputFile);
        }
    }
    else if (type == "gui")
    {
        GOL game;
        game.setHeight(windowHeight);
        game.setWidth(windowWidth);
        game.loadFile(inputFile);

        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");
        window.setFramerateLimit(100);
        int i = 0;
        while (window.isOpen())
        {
            window.clear();

            //create our image to display using a list of alive cells within the range (-200, 200) and (-150, 150). Each cell = 4 pixels.
            sf::Image screen;
            screen.create(windowWidth, windowHeight, sf::Color{0, 0, 0});
            for (pair<int64_t, int64_t> xy : game.getElementsInFrame())
                screen.setPixel(xy.first, xy.second, sf::Color{255, 255, 255});
            sf::Texture texture;
            texture.loadFromImage(screen);
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.scale(4, 4);

            window.draw(sprite);

            window.display();

            if (i < stepsToTake)
            {
                game.step();

                if (i == 9) //@ step 10
                    game.writeToFile(outputFile);
                i++;
            }
            
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();
        }
    }
}