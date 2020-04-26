#pragma once

#include <vector>

#include "player.hpp"
#include "camera_renderer.hpp"

class PlayerRenderer : public CameraRenderer<std::vector<Player>>
{
private:
    const float TILE_SIZE = 40;

    sf::Sprite player_sprite;

public:
    PlayerRenderer(sf::RenderWindow& window, ResourceManagers resources);

    void render(const std::vector<Player>& players, const float dt) override;
};