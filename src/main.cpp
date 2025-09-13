#include <flecs.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <flecs/addons/cpp/mixins/pipeline/decl.hpp>

struct CircleRenderable {
  sf::CircleShape shape = sf::CircleShape(100.f, 3);
};

struct Transform {
  sf::Vector2f position;
  sf::Vector2f scale = {1.f, 1.f};
  float rotation = 0.f;
};

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;

  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project", sf::Style::None,
                                 sf::State::Fullscreen, settings);
  window.setFramerateLimit(144);

  // the unique flecs world
  const auto world = flecs::world();

  // circle with 100-pixel radius, green fill
  auto triangle = world.entity().set<CircleRenderable>({}).set<Transform>({{1920 / 2.f, 1080 / 2.f}});
  auto& shape = triangle.get_mut<CircleRenderable>().shape;
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin({100.f, 100.f});

  // add our systems to the world
  world.system<Transform>().each(
      [](const flecs::iter& it, size_t, Transform& t) { t.rotation += 90.f * it.delta_time(); });

  world.system<CircleRenderable, const Transform>()
      .kind(flecs::OnStore)
      .each([&window](CircleRenderable c, const Transform t) {
        c.shape.setRotation(sf::degrees(t.rotation));
        c.shape.setPosition(t.position);
        window.draw(c.shape);
      });

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

    window.clear();
    world.progress(elapsed);
    window.display();
  }

  return 0;
}
