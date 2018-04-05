#ifndef MAP_H
#define MAP_H

#include "include/block.h"

class Map
{
public:
    Map();
    void draw(/*pozicija kamere pravac gledanja*/) const;
    bool hasBlock() const;
    //od vidljivih lica pravi nizove koji se salju na graficku
    void toArray();
    //od podataka koje mapa cuva racuna koja lica kojih blokova se vide
    void toVisible();
    void updateMatrix();

    Block::Type vectorCast() const;
};

#endif // MAP_H
