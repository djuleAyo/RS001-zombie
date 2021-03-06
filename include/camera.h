#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <array>

class Camera
{
public:
  Camera(double x = 0, double y = 0, double z = 0);
  //variant with no params makes the camera look based on curren state of the camera
  void look() const;
  void setAim();
  void aimFi(int x);
  void aimTheta(int y);

  
  void forward();
  void left();
  void right();
  void back();
  void up();
  void down();
  //this class may be inherited by different types of camera, so use protected
protected:
  std::array<double, 3> m_position;
  std::array<double, 3> m_aim;
  std::array<double, 2> m_aimSpherical;
  double m_rotationSpeed = .001;
  double m_movSpeed = .5;
};

#endif // CAMERA_H
