#ifndef PARTICESYSTEMDEMO_H
#define PARTICESYSTEMDEMO_H

#include <sstream>

#include <SFML/Graphics.hpp>

#include "../EngineV2/game.hpp"
#include "../EngineV2/particlesystem.hpp"
#include "../EngineV2/inputmanager.hpp"


class ParticeSystemDemo : public Engine::Layer
{
  public:
  /* Layer functionalities */
    virtual ~ParticeSystemDemo() = default;

    virtual void handleEvent(sf::Event e) override;
    virtual void handleInput() override;

    virtual void update(const float& dt) override;
    virtual void fixedUpdate(const float& dt) {}

    virtual void render(sf::RenderTarget& window) override;

    virtual void init() override;
  /* custom variables */

    sf::Text text;
    sf::Vector2f mousePos;
    sf::Vector2f lastMousePos;
    Engine::ParticleSystem ps;
    int add;

  /* custom functionalities */
    ParticeSystemDemo();

};

#endif // PARTICESYSTEMDEMO_H
