#ifndef MAP_H
#define MAP_H

#include "block.h"
#include "camera.h"
#include "chunk.h"

#include <vector>
#include <array>
#include <string>

typedef std::array<int, 3> worldCoords;

class Map
{
public:
  explicit Map(std::string seed, int visibility, worldCoords worldOrigin);

  Map(const Map& m) = delete;
  Map& operator=(const Map& m) = delete;

  void draw(const Camera& c) const;
  bool hasBlock(const worldCoords& coords) const;

  Block::Type vectorCast(const worldCoords& origin,
			 const std::array<int, 3>& aim,
			 const double range) const;

  
private:
  const std::string m_seed;
  const int m_visibility = 2;
  Chunk m_data[2][2][2];

  std::vector<int> m_visibleFaces[2][2][2];

  std::vector<int> m_verts[2][2][2];
  std::vector<float> m_colors[2][2][2];
  
  //south west corner of the map in the world
  worldCoords m_worldOrigin;

  //rolling effect of the data structure needs memory origin
  // defines position in memory of first south west chunk
  std::array<int, 3> m_memoryOrigin;
  


  //od podataka koje mapa cuva racuna koja lica kojih blokova se vide
  void toVisible();

  //od vidljivih lica pravi nizove koji se salju na graficku
  void toArray();

    
};

#endif // MAP_H
