#include <SFML\Graphics.hpp>
#include <conio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <cmath>
#include "cube.h"
#include "ScreenConstants.h"    

using namespace std;

int main()
{
    // Constant block
    const int CUBE_COUNT = 30;
    const int CUBE_SIZE = 5;

    // Random block
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist_x(BORDERS, SCREEN_SIZE_X-BORDERS);
    uniform_int_distribution<> dist_y(BORDERS, SCREEN_SIZE_Y-BORDERS);

    vector<Cube> cubes;

    // Window settings block
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Simulation", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // Cube create block
    for (int i = 0; i < CUBE_COUNT; i++)
    {
        float rand1 = (float) (dist_x(gen));
        float rand2 = (float) (dist_y(gen));
        Cube cube = Cube(rand1, rand2, CUBE_SIZE, CUBE_SIZE, i);
        cubes.push_back(cube);

    }

    // Main loop block
    while (window.isOpen())
    {
        // Evenst (like as closind window etc)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Full black boy~
        window.clear(sf::Color(30,30,30,255));

        // Borders
        sf::Vector2f mainScreenSize(SCREEN_SIZE_X - (2 * BORDERS), SCREEN_SIZE_Y - (2 * BORDERS));
        sf::RectangleShape mainScreenRectangle(mainScreenSize);
        mainScreenRectangle.setPosition(sf::Vector2f(BORDERS, BORDERS));
        mainScreenRectangle.setFillColor(sf::Color::Black);
        window.draw(mainScreenRectangle);

        // Foreach for every cube draw
        for (int i = 0; i < cubes.size(); i++)
        {
            for (int y = i + 1; y < cubes.size(); y++) // Изменение начального значения y исключает сравнение куба с самим собой и избегает дублирования проверок.
            {
                float xRange = cubes[y].GetX() - cubes[i].GetX();
                float yRange = cubes[y].GetY() - cubes[i].GetY();

                float range = sqrt(xRange * xRange + yRange * yRange); // Используйте операции над числами с плавающей запятой напрямую, без вызова pow.

                cubes[i].ChangeDirection(cubes[y].GetVector());
                cubes[y].ChangeDirection(cubes[i].GetVector());
                cubes[i].Move();
                cubes[y].Move();
            }
            window.draw(cubes[i].GetShape());
        }


        window.display();
    }
    return 0;
}