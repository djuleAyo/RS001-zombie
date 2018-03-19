
#include <iostream>
#include <cstdlib>

#include <vector>

#include "entity.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "chunk.hpp"

#ifdef __OLD_GL

#include <GL/glut.h>

std::vector<Entity*> entities;
Camera camera(30, 50, 170);
Input input;
std::vector<Chunk*> chunks;
  



void onKeyboardUp(unsigned char c, int x, int y);
void onKeyboard(unsigned char c, int x, int y);
void onMouse(int x, int y);
void display();
void reshape(int x, int y);

int main(int argc, char** argv)
{  
  //init a simple scene
  //entities.push_back(new Entity(0, 0, 0));
  for(int i = 0; i < 10; i++)
    for(int j = 0; j < 10; j++)
      for(int k = 0; k < 10; k++) {
	if(i + j + k < 10)
	  chunks.push_back(new Chunk(i * 16, j * 16, k * 16));
      }
      

  glutInit(&argc, argv);

  glutInitWindowPosition(10, 10);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("minecraftCpp");

  glutInitDisplayMode(GL_DOUBLE | GL_DEPTH);

  //init drawing state
  glClearColor(.1, .4, .8, 0);
  glColor4f(.5, .0, .5, .0);
  glEnable(GL_DEPTH_TEST);
  
  //init misc
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutFullScreen();
  glutSetCursor(GLUT_CURSOR_NONE);

  
  //init perspective
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1, 1, 100);
  glMatrixMode(GL_MODELVIEW);

  camera.look();



  //callbacks
  glutDisplayFunc(display);
  glutKeyboardFunc(onKeyboard);
  glutKeyboardUpFunc(onKeyboardUp);
  glutReshapeFunc(reshape);
  glutPassiveMotionFunc(onMouse);
  
  glutMainLoop();
  return EXIT_SUCCESS;
}



void onMouse(int x, int y)
{

  if(x == input.windowW() / 2 && y == input.windowH() / 2){
    input.mouseX(0);
    input.mouseY(0);
    return;
  }

  input.mouseX(x - input.windowW() / 2 );
  input.mouseY(-(y - input.windowH() / 2) );

}

void reshape (int w, int h)
{
  input.windowW(w);
  input.windowH(h);
  
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60, w / (float) h, 1, 1000);
  glMatrixMode (GL_MODELVIEW);

}


void onKeyboard(unsigned char c, int x, int y)
{
  input.store(c, x, y);
}
void onKeyboardUp(unsigned char c, int x, int y)
{
  input.release(c, x, y);
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*
  for(auto entity : entities) {
    entity->draw();
  }
  */
  
  //call actions
  for( auto c : input.keys()) {
    switch(c) {
    case '.':
      camera.forward();
      break;
    case 'e':
      camera.back();
      break;
    case 'o':
      camera.left();
      break;
    case 'u':
      camera.right();
      break;
    case ' ':
      camera.up();
      break;
    case 'j':
      camera.down();
      break;
    }
  }

  //mouse input
  camera.aimFi(input.mouseX());
  camera.aimTheta(input.mouseY());

  //stop mouse leaving window
  glutWarpPointer(input.windowW() / 2, input.windowH() / 2);
  
  camera.setAim();  
  camera.look();

  //after the camera is set do draws
  //c.draw();



  std::vector<int> verts;
  std::vector<float> colors;
  cubeToVertArray(0, 0, 0, 0b1, verts, colors);

  /*
  int *vertsPtr = verts.data();
  float *colorsPtr = colors.data();

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glVertexPointer(3, GL_INT, 0, vertsPtr);
  glColorPointer(3, GL_FLOAT, 0, colorsPtr);

  glDrawArrays(GL_QUADS, 0, verts.size() / 3);
  */
  //c.drawArrays();

  for(auto chunk : chunks)
    chunk->drawArrays();
  
  glutSwapBuffers();
  glutPostRedisplay();
}


#endif // end __OLD_GL
