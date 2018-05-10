#include "camera.h"
#include <iostream>
#include <cmath>


Camera::Camera(double x, double y, double z)
{
  m_position[0] = x;
  m_position[1] = y;
  m_position[2] = z;

  m_aimSpherical[0] = M_PI / 2;
  m_aimSpherical[1] = 0;

  setAim();
}

void Camera::look() const
{
  glLoadIdentity();
  gluLookAt(m_position[0],
	    m_position[1],
	    m_position[2],
	    m_aim[0] + m_position[0],
	    m_aim[1] + m_position[1],
	    m_aim[2] + m_position[2],
	    0, 1, 0
	    );

}

void Camera::forward()
{
  m_position[0] += m_movSpeed * m_aim[0];
  m_position[1] += m_movSpeed * m_aim[1];
  m_position[2] += m_movSpeed * m_aim[2];
}
void Camera::left()
{
  m_position[0] += m_movSpeed * sin(m_aimSpherical[0]);
  m_position[2] -= m_movSpeed * cos(m_aimSpherical[0]);

}
void Camera::right()
{
  m_position[0] -= m_movSpeed * sin(m_aimSpherical[0]);
  m_position[2] += m_movSpeed * cos(m_aimSpherical[0]);
}
void Camera::back()
{
  m_position[0] -= m_movSpeed * m_aim[0];
  m_position[1] -= m_movSpeed * m_aim[1];
  m_position[2] -= m_movSpeed * m_aim[2];
}

void Camera::setAim()
{
  m_aim[0] = cos(m_aimSpherical[1]) * cos(m_aimSpherical[0]);
  m_aim[1] = sin(m_aimSpherical[1]);
  m_aim[2] = cos(m_aimSpherical[1]) * sin(m_aimSpherical[0]);
}

void Camera::aimFi(int x)
{
  m_aimSpherical[0] += m_rotationSpeed * x;

}
void Camera::aimTheta(int y)
{
  m_aimSpherical[1] += m_rotationSpeed * y;
  if(m_aimSpherical[1] < -M_PI / 2) m_aimSpherical[1] = -M_PI / 2;
  if(m_aimSpherical[1] > M_PI / 2) m_aimSpherical[1] = M_PI / 2;
}

void Camera::up()
{
  m_position[1] += m_movSpeed;
}

void Camera::down()
{
  m_position[1] -= m_movSpeed;
}
