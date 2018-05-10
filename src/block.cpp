#include "block.h"


void Block::drawVisibleFaces(short faces)
{

  //NOTE: in ogl positive z goes to camera
  //meaning north and south are fliped!
  if(faces & Block::VisibleFace::UP) {
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3i(0, 1, 0);
    glVertex3i(0, 1, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 1, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::DOWN) {
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 1);
    glVertex3i(1, 0, 1);
    glVertex3i(1, 0, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::NORTH) {
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 1, 0);
    glVertex3i(1, 1, 0);
    glVertex3i(1, 0, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::SOUTH) {
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 1);
    glVertex3i(0, 1, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 0, 1);
    glEnd();
  }
  if(faces & Block::VisibleFace::WEST) {
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 1);
    glVertex3i(0, 1, 1);
    glVertex3i(0, 1, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::EAST) {
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3i(1, 0, 0);
    glVertex3i(1, 0, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 1, 0);
    glEnd();
  }

}

void Block::toVertArray(int originX, int originY, int originZ, short faces,
		     std::vector<int> &verts_out, std::vector<float>&colors_out)
{
  std::vector<int> *verts = new std::vector<int>;
  
  if(faces & Block::VisibleFace::UP) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::DOWN) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::NORTH) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::SOUTH) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::WEST) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::EAST) {
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(1);
  }

}


