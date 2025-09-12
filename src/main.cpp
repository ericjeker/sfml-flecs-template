#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;

  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project", sf::Style::None,
                                 sf::State::Fullscreen, settings);
  window.setFramerateLimit(60);

  // circle with 100-pixel radius, green fill
  sf::CircleShape circle(100.f, 3);
  circle.setFillColor(sf::Color::Green);
  circle.setOrigin({100.f, 100.f});
  circle.setPosition({1920 / 2.f, 1080 / 2.f});

  sf::Clock clock;
  while (window.isOpen()) {
    const float elapsed = clock.restart().asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }

    circle.setRotation(circle.getRotation() + sf::degrees(100.f * elapsed));

    window.clear();
    window.draw(circle);
    window.display();
  }

  return 0;
}
