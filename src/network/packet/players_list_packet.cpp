#include "network/packet/players_list_packet.hpp"

PlayersListPacket::PlayersListPacket()
        : Packet(PACKET_ID)
{}

PlayersListPacket::PlayersListPacket(uint16_t player_id, const std::vector<Player>& players_list)
        : Packet(PACKET_ID), player_id(player_id), players_list(players_list)
{}

uint16_t PlayersListPacket::get_player_id() const
{
    return player_id;
}

std::vector<Player> PlayersListPacket::get_players_list() const
{
    return players_list;
}

void PlayersListPacket::serialize(sf::Packet& data) const
{
    uint16_t players_count = players_list.size();
    data << player_id << players_count;
    for(auto& player : players_list)
        data << player.get_nickname() << player.get_position().x << player.get_position().y << player.get_avatar_name();
}

void PlayersListPacket::deserialize(sf::Packet& data)
{
    uint16_t players_count = 0;
    data >> player_id >> players_count;
    players_list.reserve(players_count);
    for(int i = 0; i < players_count; ++i)
    {
        std::string nickname;
        std::string avatar_name;
        int x, y;
        data >> nickname >> x >> y >> avatar_name;

        players_list.emplace_back(nickname, avatar_name);
        players_list[players_list.size() - 1].set_position(x, y);
    }
}






