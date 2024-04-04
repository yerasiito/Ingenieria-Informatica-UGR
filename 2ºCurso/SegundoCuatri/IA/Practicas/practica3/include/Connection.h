#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <SFML/Network.hpp>
#include "Attributes.h"
#include "Board.h"
#include <list>
#include <memory>
#include <set>
#include <deque>

using namespace sf;
using namespace std;

// Para control de versiones y obligar a actualizar a versiones incompatibles con el online.
# define NINJA_VERSION 2
# define ONLINE_VERSION 6

enum MessageKind{
    NOP = 0,
    //1xx - Connection messages.
    HELLO = 100,
    GAME_PARAMETERS = 101,
    TEST_ALIVE = 102,
    HELLO_MASTER = 103,
    HOW_R_U = 104,
    QUEUED = 105,
    RESERVE_IP = 106,
    KILL = 107,
    RANDOM_GAME = 108,
    PRIVATE_GAME = 109,
    WAITING_FOR_PLAYERS = 110,

    //2xx - OK messages.
    OK = 200,
    OK_MOVED = 201,
    NINJA_STATUS = 202,
    NINJA_ACCEPTED = 203,
    ACCEPTED = 204,
    OK_RESERVED = 205,
    OK_START_GAME = 206,
    OK_RANDOM_START = 207,
    OK_PRIVATE_START = 208,
    OK_RANDOM_PRIVATE_START = 209,

    //3xx - Game messages.
    TEST_MESSAGE = 300,
    MOVED = 301,

    //4xx - Error messages.
    ERROR_DISCONNECTED = 400,
    ERR_INVALID_MESSAGE = 401,
    ERR_COULDNT_RESERVE = 402,
    ERR_NO_NINJAS = 403,
    ERR_UNAUTHORIZED = 404,
    ERR_UPDATE = 405,
    ERR_FULL_ROOM = 406,

};

class ParchisRemote{
    protected:
        TcpSocket socket;

        ParchisRemote();
        inline ~ParchisRemote(){socket.disconnect();}

    public:
        bool isConnected();

        void sendHello(const vector<string> & args);

        void sendGameParameters(int player, string name, BoardConfig init_board, int ai_id = 0);

        void sendTestAlive();

        void sendHelloMaster(string ip, int port);

        void sendHowAreYou();

        void sendQueued(int queue_pos);

        void sendReserveIp(string ip, int port);

        void sendRandomGame(string name);

        void sendPrivateGame(string room_name, string name);

        void sendWaitingForPlayers();

        void sendOK();

        void sendOKMoved();

        void sendOKStartGame(string player_name);

        void sendNinjaStatus(int ninja_games, int random_games, int private_games);

        void sendAcceptNinjaMessage();

        void sendAcceptedMessage(string ip_addr, int port);

        void sendOKReserved();

        void sendOKRandomPrivateStart(int theplayer, string rival_name, BoardConfig config);

        void sendTestMessage(string message);

        void sendParchisMove(int turn, color c_piece, int id_piece, int dice);

        void sendErrorMessage(MessageKind msgkind, string message = "");



        MessageKind receive(Packet & packet);

        static void analyzePacket(Packet & packet, const MessageKind & kind);

        static void packet2Hello(Packet & packet, int & version, vector<string> & args);

        static void packet2HelloMaster(Packet & packet, string & ip, int & port, int & online_version, int & ninja_version);

        static void packet2gameParameters(Packet & packet, int & player, string & name, BoardConfig & init_board, int & ai_id);
        
        static int packet2queuePos(Packet & packet);

        static void packet2reservedIp(Packet & packet, string & ip, int & port);

        static void packet2randomGame(Packet & packet, string & name);

        static void packet2privateGame(Packet & packet, string & room_name, string & name);

        static void packet2ninjaStatus(Packet & packet, int & ninja_games, int & random_games, int & private_games);

        static void packet2OKRandomPrivateStart(Packet & packet, int & my_player, string & rival_name, BoardConfig & config);

        static void packet2acceptedIp(Packet & packet, string & ip_addr, int & port);

        static string packet2message(Packet & packet);

        static void packet2move(Packet & packet, int & turn, color & c_piece, int & id_piece, int & dice);

        static string packet2errorMessage(Packet & packet);

        inline IpAddress getRemoteAddress() const{return socket.getRemoteAddress();}

        inline unsigned short getRemotePort() const{return socket.getRemotePort();}
};

class ParchisClient: public ParchisRemote{
    public:
        ParchisClient();
        /**
         * @brief Inicia una conexión con el servidor remoto indicado.
         * 
         * @param ip_addr Dirección IP o nombre del servidor.
         * @param port Puerto de conexión.
         */
        void startClientConnection(const string & ip_addr, const int & port);

};


class ParchisServer: public ParchisRemote{
    private:
        //TcpListener listener;

    public:
        ParchisServer();

        //void startListening(const int & port);

        void acceptConnection(TcpListener & listener);

};

struct server_connection
{
    string ip_addr;
    int port;
    inline bool operator<(const server_connection &b) const
    {
        return this->ip_addr < b.ip_addr; //or this->ip_addr == b.ip_addr and this->port < b.port;
    }
};

class NinjaServer{
    private:
        string my_contact_ip;

        // Para partidas contra los ninjas.
        struct ninja_game{
            shared_ptr<ParchisServer> connection; // Gracias Mario :)
            shared_ptr<Thread> thread;
        };
        list<ninja_game> ninja_games;

        // Para partidas "aleatorias".
        struct random_match_game{
            shared_ptr<ParchisServer> connection_p1;
            string name_p1;
            shared_ptr<ParchisServer> connection_p2;
            string name_p2;
            shared_ptr<Thread> aux_thread;
            shared_ptr<Thread> thread;
            bool waiting_for_players;
        };
        list<random_match_game> random_match_games;

        // Para partidas privadas.
        struct private_room_game{
            string room_id;
            shared_ptr<ParchisServer> connection_p1;
            string name_p1;
            shared_ptr<ParchisServer> connection_p2;
            string name_p2;
            shared_ptr<Thread> aux_thread;
            shared_ptr<Thread> thread;
            bool waiting_for_players;

            inline bool operator<(const private_room_game &b)
            {
                return this->room_id < b.room_id;
            }
        };

        // Hebras sin asignar.
        vector<shared_ptr<Thread>> idle_threads;

        // Hebras para destruir (tienen que destruitse desde una hebra distinta).
        list<shared_ptr<Thread>> dead_threads;

        map<string, private_room_game> private_room_games;
        
        Thread reviser;

        Thread master_thread;
        ParchisClient master_connection;
        string master_ip;
        int master_port;


        //Thread console_reader_thread;

        TcpListener listener;
        int listener_port;

        volatile bool is_running;

        Mutex ninja_games_mutex;
        Mutex random_match_games_mutex;
        Mutex private_room_games_mutex;
        Mutex thread_mutex;

        set<server_connection> reserved_ips;
        Mutex reserved_ips_mutex;

        void reviseNinjaThreadsStep();
        void reviseNinjaThreadsLoop();

        void reviseRandomMatchThreadsStep();
        void reviseRandomMatchThreadsLoop();

        void revisePrivateRoomThreadsStep();
        void revisePrivateRoomThreadsLoop();

        void reviseDeadThreadsStep();

        void reviserLoop();

        void consoleReader();

        void masterReceiver();

        void acceptationLoop();
        void acceptationStep(shared_ptr<ParchisServer> server);


        void newNinjaGame(shared_ptr<ParchisServer> server, Packet & packet, shared_ptr<Thread> thread);
        void queueRandomMatchGame(shared_ptr<ParchisServer> server, Packet &packet, shared_ptr<Thread> thread);
        void queuePrivateRoomGame(shared_ptr<ParchisServer> server, Packet &packet, shared_ptr<Thread> thread);

        void connectToMaster();
        

    public:

        NinjaServer(const int & port, const string & my_contact_ip = "127.0.0.1");

        void startServer();

        void stopServer();

        void setMaster(const string & ip_addr, const int & port);

        void printStatus();
     
};

/**
 * @brief Servidor maestro que se encarga de gestionar y repartir las conexiones a los servidores ninja.
 * 
 */
class MasterServer{
    private:
        static const int MAX_ALLOWED_NINJA_GAMES = 10;
        bool is_running;

        int listener_port;
        TcpListener listener;

        set<string> allowed_ninja_ips;

        Thread reviser_thread;

        struct NinjaConnection{
            shared_ptr<ParchisServer> connection;
            string ip_addr;
            int port;
        };

        list<NinjaConnection> ninja_connections;

        struct MasterConnection{
            shared_ptr<ParchisServer> connection;
            shared_ptr<Thread> thread;
        };

        struct NinjaOccupation{
            int ninja_games;
            int private_games;
            int random_games;
        };

        list<MasterConnection> client_connections;

        deque<shared_ptr<ParchisServer>> queued_connections;

        vector<shared_ptr<Thread>> idle_threads;

        NinjaConnection * last_random_assigned_connection;

        map<string, NinjaConnection*> private_room_connections;

        Mutex queue_insert_mutex;
        Mutex instant_send_receive_mutex1;
        Mutex instant_send_receive_mutex2;
        Mutex random_assign_mutex;
        Mutex private_room_connections_mutex;

        void reviseNinjaConnectionsStep();
        void reviseNinjaConnectionsLoop();

        void reviseClientConnectionsStep();
        void reviseClientConnectionsLoop();

        void reviserLoop();

        void consoleReader();

        void acceptationLoop();

        void acceptationStep(shared_ptr<ParchisServer> server);

        void handleNinjaConnection(shared_ptr<ParchisServer> server, Packet & packet);

        void handleClientConnection(shared_ptr<ParchisServer> server, Packet & packet);

        void reserveNinjaGame(shared_ptr<ParchisServer> server);

        void reserveRandomGame(shared_ptr<ParchisServer> server);

        void reservePrivateGame(shared_ptr<ParchisServer> server, const string & room_name);

    public:
        MasterServer(const int & port);

        void startServer();

        void stopServer();

        void addAllowedNinja(string ip);

        void printStatus();


};




#endif