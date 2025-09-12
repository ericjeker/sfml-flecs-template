#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project",
                       sf::Style::None, sf::State::Fullscreen);
  window.setFramerateLimit(144);

  // circle with 100-pixel radius, green fill
  sf::CircleShape circle(100.f);
  circle.setFillColor(sf::Color::Green);
  circle.setPosition({1920 / 2.f - 100, 1080 / 2.f - 100}); // centre it

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto *keyPressed =
                     event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }

    window.clear();
    window.draw(circle);
    window.display();
  }

  return 0;
}
