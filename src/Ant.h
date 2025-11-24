#pragma once
#include <vector>

enum class AntDir
{
    UP = 0,
    DOWN = 1,
    RIGHT = 2,
    LEFT = 3
};


class Ant
{
private:
    int mX;
    int mY;
    AntDir mDir;
public:
    int GetX() const { return mX; }
    int GetY() const { return mY; }
    
    void Update(std::vector< std::vector<int> >& map);
    Ant(const int x, const int y, const AntDir dir);
    ~Ant();
};
