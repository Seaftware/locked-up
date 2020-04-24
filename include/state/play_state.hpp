#pragma once

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "game_state.hpp"
#include "game_board.hpp"
#include "player.hpp"
#include "resource_manager.hpp"
#include "network/connection.hpp"

class PlayState : public GameState
{
private:
    const sf::IpAddress SERVER_ADDR = "127.0.0.1";
    const unsigned short SERVER_PORT = 2704;

    GameBoard game_board;
    int camera_pos_x;
    int camera_pos_y;

    int current_player_id;
    std::vector<Player> players;

    Connection server_connection;

    ResourceManager<sf::Texture> textures;

    void packet_received(std::unique_ptr<Packet> packet);

public:
    PlayState(sf::RenderWindow& window);

    std::unique_ptr<GameState> handle_input(sf::Event event) override;

    std::unique_ptr<GameState> update(float dt) override;

    void render(float dt) override;
};
