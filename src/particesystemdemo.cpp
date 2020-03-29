#include "particesystemdemo.hpp"

ParticeSystemDemo::ParticeSystemDemo() :
  text("", *Engine::AssetManager::get().getFont("basic font"), 12),
  mousePos(0,0),
  lastMousePos(0,0),
  ps(mousePos),
  add(256)
{}

void ParticeSystemDemo::init()
{
  text.setPosition(
    static_cast<float>(p_game->getWindowSize().x) * 0.01f,
    static_cast<float>(p_game->getWindowSize().y) * 0.01f);
  mousePos = sf::Vector2f(p_game->getWindowSize().x/2.0f, p_game->getWindowSize().y/2.0f);
  ps.setCanvasSize(p_game->getWindowSize());

  ps.fuel(1000);
}

void ParticeSystemDemo::handleEvent(sf::Event e)
{
  switch(e.type)
  {
    case(sf::Event::Closed): // the X is pressed
      p_game->getWindow().close();
      break;

    case(sf::Event::KeyPressed): // a key is pressed
      switch(e.key.code){
        case sf::Keyboard::Escape:
          p_game->getWindow().close();
          break;

        case sf::Keyboard::X: // pop layer
          p_game->popLayer();
          break;

        case sf::Keyboard::Space: // toggle dissolution
          ps.setDissolve();
          break;

        case sf::Keyboard::A: // increase dissolution time
          if(ps.getDissolutionRate() > 0)
            ps.setDissolutionRate( ps.getDissolutionRate() - 1);
          break;

        case sf::Keyboard::S: // decrease dissolution time
          ps.setDissolutionRate( ps.getDissolutionRate() + 1);
          break;

        case sf::Keyboard::W: // increase particle speed
          ps.setParticleSpeed( ps.getParticleSpeed() + ps.getParticleSpeed() * 0.1);
          break;

        case sf::Keyboard::Q: // decrease particle speed
          if(ps.getParticleSpeed() > 0)
            ps.setParticleSpeed( ps.getParticleSpeed() - ps.getParticleSpeed() * 0.1);
          break;

        case sf::Keyboard::E: // toggle between distribution shapes (Circle and Quad)
          ps.setDistribution();
          break;

        case sf::Keyboard::J: // decrease the spawned quantity
          if(add < 32 ) add = 0; else add-=32;
          break;

        case sf::Keyboard::K: // increase the spawned quantity
          add+=32;
          break;

        default:
          break;
      }

      break;
    default:
      break;
  }

}

void ParticeSystemDemo::handleInput()
{
  mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(p_game->getWindow()));

  if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        ps.fuel(add);


  if(Engine::InputManager::get().isButtonPressed(sf::Mouse::Right))
  {
     lastMousePos = mousePos;
  }

  if(Engine::InputManager::get().isButtonReleased(sf::Mouse::Right))
  {
      sf::Vector2f newGravity = mousePos - lastMousePos;
      newGravity *= 0.05f;
      ps.setGravity(newGravity);
  }

  if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
      ps.setGravity(0.0f, 0.0f);

}

void ParticeSystemDemo::update(const float& dt)
{
  int fps = 1.0f / dt;
  std::ostringstream buffer;
      buffer << "Q/W to Decrease/Increase Particle Speed ( " << ps.getParticleSpeed() << " )\n"
             << "A/S to Decrease/Increase Dissolution Rate ( " << ps.getDissolutionRate() << " )\n"
             << "Right Click+Drag to Shift Gravity ( x: " << ps.getGravity().x << ", y: " << ps.getGravity().y << " )\n"
             << "E to Change Distribution Type ( " << (ps.getShape()? "Quad":"Circle") <<" )\n"
             << "Space to Toggle Dissolution ( " << (ps.isDissolving()?"On": "Off") << " )\n"
             << "J/K to Decrease/Increase the spawning quantity ( " << add << " )\n"
             << "Your Mouse position is ( x: " << ps.getBindedPosition().x << ", y: " << ps.getBindedPosition().y << " )\n"
             << "Middle Click clears Gravity\n"
             << "Left Click to Add\n"
             << "Particles: " << ps.getNumberOfParticles() << "\n"
             << "FPS: "<<fps;
  text.setString(buffer.str());
  ps.update(dt);
}

void ParticeSystemDemo::render(sf::RenderTarget& window)
{
  window.draw(text);
  window.draw(ps);
}
