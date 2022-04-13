#pragma once
#include "../SDL2_net-2.0.1/include/SDL_net.h"

#include <vector>
#include <thread>
#include <iostream>
#include <mutex>

class Game;
class Player;

enum EPacketType {
	EPT_START,
	EPT_ACCEPT,
	EPT_DENY,
	EPT_NAME,
	EPT_UPDATE,
	EPT_SYNCPLAYER,
	EPT_QUIT
};

enum EInputType {
	EIT_UP,
	EIT_DOWN,
	EIT_RIGHT,
	EIT_LEFT,
	EIT_NONE
};

// Currently testing
struct PacketSyncPlayer {
	Uint8 packet_type;
	Uint8 player_id;
	Sint16 posX;
	Sint16 posY;
};


struct PacketSend {
	Uint8 packet_type;
	Uint8 player_id;
	Sint8 player_horizontal;
	Sint8 player_vertical;
};

// Paquete que recibe el servidor, lo mandan los clientes
struct PacketRecv {
	Uint8 packet_type;
	Sint8 player_horizontal;
	Sint8 player_vertical;
};

// Paquete que manda el servidor cuando acepta a un juegador
struct PacketAccept {
	Uint8 packet_type;
	Uint8 player_id;
	char player_name[15];
};

// Paquete para mandar nombres
struct PacketName {
	Uint8 packet_type;
	char player_name[15];
};

struct PacketStartGame {
	Uint8 packet_type;
	Uint8 num_jornada;
};


class NetworkManager
{
private:

	std::vector<TCPsocket> player_sockets;
	std::vector<IPaddress> player_ips;
	std::vector<int> player_ids;

	// SERVER

	std::thread* accept_t;
	std::thread* receiveplayers_t;
	std::thread* sendplayers_t;

	void acceptPlayers();
	void receivePlayers();
	void sendPlayers();

	// CLIENT

	int client_id;

	std::thread* updateclient_t;

	void updateClient();

	// UTILS

	int getClientID(const IPaddress& addr);

	bool compareAddress(const IPaddress& addr1, const IPaddress& addr2);

	// VARIABLES

	char nType;

	const int MAX_PLAYERS = 15;

	int id_count;
	Game* game_;

	bool exitThread;

	std::string myName;
	std::string otherName;

	// For clients ip=server_address, for host ip=local_address
	IPaddress ip;

	// For clients socket=socket_server, for host socket=local_socket
	TCPsocket socket;

	float accept_frequency;
	float send_frequency;
	float recv_frequency;

	float client_frequency;

	// Timer
	Uint32 lastUpdate_; //tiempo desde el �ltimo update
	Uint32 updateTime_ = 500; //los segundos que tarda en actualizarse el reloj

public:
	NetworkManager(Game* game);
	~NetworkManager();

	bool init(char type, const char* ip_addr = nullptr, std::string name = "");
	void update();

	void close();

	Player* addPlayerHost();
	Player* addPlayerClient(int id);

	std::string getOtherName() { return otherName;}
	std::string getMyName() { return myName; }


	void sendStartGame(int numJornada);
};