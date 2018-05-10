#include "manu.h"
#include <iostream>
#include <cstdlib>

void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
    std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
    std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
}

Manu::Manu()
  : m_window(sf::VideoMode(400, 300), "Zombie"),
    m_gui(m_window)
{
  try {
    loadWidgets(m_gui);
  }
  catch (const tgui::Exception & e) {
    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Manu::loadWidgets(tgui::Gui & gui)
{
  auto picture = tgui::Picture::create("../res/zombie_manu.jpg");
  picture->setSize({"100%", "100%"});
  gui.add(picture);  

  auto editBoxUsername = tgui::EditBox::create();
  editBoxUsername->setSize({"66.67%", "12.5%"});
  editBoxUsername->setPosition({"16.67%", "16.67%"});
  editBoxUsername->setDefaultText("Username");
  m_gui.add(editBoxUsername);
  
  auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
  editBoxPassword->setPosition({"16.67%", "41.6%"});
  editBoxPassword->setPasswordCharacter('*');
  editBoxPassword->setDefaultText("Password");
  m_gui.add(editBoxPassword);
  
  auto button = tgui::Button::create("Login");
  button->setSize({"50%", "16.67%"});
  button->setPosition({"25%", "70%"});
  m_gui.add(button);

  button->connect("pressed", login, editBoxUsername, editBoxPassword);
}

void Manu::show()
{
  while (m_window.isOpen()) {
    sf::Event event;

    while (m_window.pollEvent(event)) {
      
      if (event.type == sf::Event::Closed)
	m_window.close();
      else if (event.type == sf::Event::Resized) {
	m_window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
	m_gui.setView(m_window.getView());
      }
      
      m_gui.handleEvent(event);
    }
    
    m_window.clear();
    m_gui.draw();
    m_window.display();
  }
}
