#include "map.h"

Map::Map(std::string seed, int visibility, worldCoords worldOrigin)
  : m_seed(seed),
    m_visibility(visibility),
    m_worldOrigin(worldOrigin)
{
  //init memory origin
  m_memoryOrigin[0] = 0;
  m_memoryOrigin[1] = 0;
  m_memoryOrigin[2] = 0;
  
  //init m_data
  for(int x = 0; x < m_visibility; x++) {
    for(int y = 0; y < m_visibility; y++) {
      for(int z = 0; z < m_visibility; z++) {
	m_data[x][y][z] = Chunk(m_worldOrigin[0] + x,
				m_worldOrigin[1] + y,
				m_worldOrigin[2] + z);
      }
    }
  }

  //init verts and colors
  for(int x = 0; x < m_visibility; x++) {
    for(int y = 0; y < m_visibility; y++) {
      for(int z = 0; z < m_visibility; z++) {
	m_data[x][y][z].visibleBlocks(m_visibleFaces[x][y][z]);
	m_data[x][y][z].toVertArray(m_visibleFaces[x][y][z],
				    m_verts[x][y][z],
				    m_colors[x][y][z]
				    );
      }
    }
  }
}



void Map::draw(const Camera& c) const
{
  c.look();
  for(int x = 0; x < m_visibility; x++) {
    for(int y = 0; y < m_visibility; y++) {
      for(int z = 0; z < m_visibility; z++) {
	(m_data[x][y][z]).drawArrays(m_verts[x][y][z], m_colors[x][y][z]);
      }
    }
  }

}
