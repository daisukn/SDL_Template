#include "Ant.h"
#include <random>
#include <iostream>

Ant::Ant(const int x, const int y, const AntDir dir)
: mDir(dir)
, mX(x)
, mY(y)
{

}

Ant::~Ant()
{
    
}

void Ant::Update(std::vector< std::vector<int> >& map)
{
    /*
    switch (mDir)
    {
        case AntDir::UP:
            if ( mY > 0)
            {
                mY--;
            }
            break;
        case AntDir::DOWN:
            if (mY < map.size()-1)
            {
                mY++;
            }
            break;
        case AntDir::RIGHT:
            if ( mX < map[mY].size()-1)
            {
                mX++;
            }
            break;
        case AntDir::LEFT:
            if ( mX > 0)
            {
                mX--;
            }
            break;
        default:
            break;
    }
*/
 
     switch (mDir)
     {
         case AntDir::UP:
             if ( mY > 0)
             {
                 mY--;
             }
             if (map[mY][mX] == 1)
             {
                 mDir = AntDir::RIGHT;
                 map[mY][mX] = 0;
             }
             else
             {
                 mDir = AntDir::LEFT;
                 map[mY][mX] = 1;
             }

             break;
         case AntDir::DOWN:
             if (mY < map.size()-1)
             {
                 mY++;
             }
             if (map[mY][mX] == 1)
             {
                 mDir = AntDir::LEFT;
                 map[mY][mX] = 0;
             }
             else
             {
                 mDir = AntDir::RIGHT;
                 map[mY][mX] = 1;
             }


             break;
         case AntDir::RIGHT:
             if ( mX < map[mY].size()-1)
             {
                 mX++;
             }
             if (map[mY][mX] == 1)
             {
                 mDir = AntDir::DOWN;
                 map[mY][mX] = 0;
             }
             else
             {
                 mDir = AntDir::UP;
                 map[mY][mX] = 1;
             }

             break;
         case AntDir::LEFT:
             if ( mX > 0)
             {
                 mX--;
             }
             if (map[mY][mX] == 1)
             {
                 mDir = AntDir::UP;
                 map[mY][mX] = 0;
             }
             else
             {
                 mDir = AntDir::DOWN;
                 map[mY][mX] = 1;
             }

             break;
         default:
             break;
     }
     
}
