#include "connection.hpp"
#include "packet/packet_factory.hpp"

Connection::Connection(std::unique_ptr<sf::TcpSocket>&& socket)
    : socket(std::move(socket))
{
    this->socket->setBlocking(false);
    connected = true;
}

Connection::Connection(sf::IpAddress remote_addr, unsigned short remote_port)
    : socket(std::make_unique<sf::TcpSocket>())
{
    auto result = socket->connect(remote_addr, remote_port);
    if(result != sf::Socket::Done)
        return;

    socket->setBlocking(false);
    connected = true;
}

Connection::Connection(Connection&& other)
    : socket(std::move(other.socket)), connected(other.connected)
{
    other.connected = false;
}

sf::IpAddress Connection::get_addr() const
{
    return socket->getRemoteAddress();
}

bool Connection::is_connected() const
{
    return connected;
}

void Connection::disconnect()
{
    socket->disconnect();
    connected = false;
}

bool Connection::send(const Packet& packet)
{
    if(!connected)
        return false;

    sf::Packet data;
    data << packet.get_id();
    packet.serialize(data);

    auto result = socket->send(data);
    if(result == sf::Socket::Disconnected)
        connected = false;

    return result == sf::Socket::Done;
}

std::unique_ptr<Packet> Connection::recv()
{
    if(!connected)
        return nullptr;

    sf::Packet data;
    auto result = socket->receive(data);
    if(result == sf::Socket::Disconnected)
        connected = false;
    if(result != sf::Socket::Done)
        return nullptr;

    uint16_t packet_id = 0;
    data >> packet_id;

    auto packet = PacketFactory::create(packet_id);
    if(packet == nullptr)
        return nullptr;

    packet->deserialize(data);
    return packet;
}

bool Connection::operator==(const Connection& other) const
{
    return socket == other.socket;
}

Connection& Connection::operator=(Connection&& other)
{
    socket = std::move(other.socket);
    connected = other.connected;
    other.connected = false;

    return *this;
}

