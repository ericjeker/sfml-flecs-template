#include <SFML/Graphics.hpp>

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(144);

  // circle with 100-pixel radius, green fill
  sf::CircleShape circle(100.f);
  circle.setFillColor(sf::Color::Green);
  circle.setPosition({1920 / 2.f - 100, 1080 / 2.f - 100}); // centre it

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    window.draw(circle);
    window.display();
  }

  return 0;
}
