#include <iostream>
#include <memory>
#include <vector>

#include "EngineV2/game.hpp"
#include "EngineV2/assetmanager.hpp"
#include "particesystemdemo.hpp"

int main()
{
  Engine::Game game(800, 800, "Particle system demo");

  Engine::AssetManager::get().loadFont("basic font", "Fixedsys500c.ttf");

  game.pushStarterLayer(new ParticeSystemDemo());

  game.run();

  return 0;
}
