# include "Connection.h"
# include <iostream>
# include <string>
# include "cout_colors.h"
# include "Parchis.h"
# include "RemotePlayer.h"
# include "Ninja.h"
# include <functional>

using namespace std;
using namespace sf;

ParchisRemote::ParchisRemote(){}

ParchisClient::ParchisClient(): ParchisRemote(){
}

ParchisServer::ParchisServer(): ParchisRemote(){
}

void ParchisRemote::sendHello(const vector<string> & args){
    Packet packet;
    packet << HELLO;
    packet << ONLINE_VERSION;
    packet << (int) args.size();
    for(auto & arg : args)
        packet << arg;

    Socket::Status status = socket.send(packet);
    if (status != Socket::Done)
    {
        cout << "Error sending HELLO message: " << status << endl;
        socket.disconnect();
    }
    else{
        cout << "HELLO sent." << endl;
        cout << "version: " << ONLINE_VERSION << endl;
        cout << "args: ";
        for(auto & arg : args)
            cout << arg << " ";
    }
    cout << endl;
}

void ParchisRemote::sendGameParameters(int player, string name, BoardConfig init_board, int ai_id){
    Packet packet;
    packet << GAME_PARAMETERS;
    packet << player;
    packet << name;
    packet << init_board;
    packet << ai_id;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        throw runtime_error("Error sending message");
    }
    cout << "GAME_PARAMETERS sent" << endl;
    cout << "player: " << player << " name: " << name << " init_board: " << init_board << " ai_id: " << ai_id << endl;
}

void ParchisRemote::sendTestAlive(){
    Packet packet;
    packet << TEST_ALIVE;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending TEST_ALIVE. Maybe not alive :(" << COUT_NOCOLOR << endl;
    }
    else cout << "TEST_ALIVE sent" << endl;
}

void ParchisRemote::sendHelloMaster(string ip, int port){
    Packet packet;
    packet << HELLO_MASTER;
    packet << ip;
    packet << port;
    packet << ONLINE_VERSION;
    packet << NINJA_VERSION;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending HELLO_MASTER." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "HELLO_MASTER sent" << endl;
        cout << "ip: " << ip << " port: " << port << " online_version: " << ONLINE_VERSION << " ninja_version: " << NINJA_VERSION << endl;

    }
}

void ParchisRemote::sendHowAreYou(){
    Packet packet;
    packet << HOW_R_U;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending HOW_R_U." << COUT_NOCOLOR << endl;
    }
    else cout << "HOW_R_U sent" << endl;
}

void ParchisRemote::sendQueued(int queue_pos){
    Packet packet;
    packet << QUEUED;
    packet << queue_pos;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending QUEUED." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "QUEUED sent" << endl;
        cout << "queue_pos: " << queue_pos << endl;
    }
}


void ParchisRemote::sendReserveIp(string ip, int port){
    Packet packet;
    packet << RESERVE_IP;
    packet << ip;
    packet << port;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending RESERVE_IP." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "RESERVE_IP sent" << endl;
        cout << "ip: " << ip << " port: " << port << endl;
    }
}

void ParchisRemote::sendRandomGame(string name){
    Packet packet;
    packet << RANDOM_GAME;
    packet << name;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending RANDOM_GAME." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "RANDOM_GAME sent" << endl;
        cout << "name: " << name << endl;
    }
}

void ParchisRemote::sendPrivateGame(string room_name, string name){
    Packet packet;
    packet << PRIVATE_GAME;
    packet << room_name;
    packet << name;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending PRIVATE_GAME." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "PRIVATE_GAME sent" << endl;
        cout << "room_name: " << room_name << " name: " << name << endl;
    }
}

void ParchisRemote::sendWaitingForPlayers(){
    Packet packet;
    packet << WAITING_FOR_PLAYERS;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending WAITING_FOR_PLAYERS." << COUT_NOCOLOR << endl;
    }
    else cout << "WAITING_FOR_PLAYERS sent" << endl;
}

void ParchisRemote::sendOK(){
    Packet packet;
    packet << OK;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending OK." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "OK sent" << endl;
    }
}

void ParchisRemote::sendOKMoved(){
    Packet packet;
    packet << OK_MOVED;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending OK_MOVED." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "OK_MOVED sent" << endl;
    }
}

void ParchisRemote::sendOKStartGame(string name){
    Packet packet;
    packet << OK_START_GAME;
    packet << name;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending OK_START_GAME." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "OK_START_GAME sent" << endl;
        cout << "name: " << name << endl;
    }
}

void ParchisRemote::sendNinjaStatus(int ninja_games, int random_games, int private_games){
    Packet packet;
    packet << NINJA_STATUS;
    packet << ninja_games;
    packet << random_games;
    packet << private_games;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending NINJA_STATUS." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "NINJA_STATUS sent" << endl;
        cout << "ninja_games: " << ninja_games << " random_games: " << random_games << " private_games: " << private_games << endl;
    }
}

void ParchisRemote::sendAcceptNinjaMessage(){
    Packet packet;
    packet << NINJA_ACCEPTED;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending NINJA_ACCEPTED." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "NINJA_ACCEPTED sent" << endl;
    }
}

void ParchisRemote::sendAcceptedMessage(string ip_addr, int port){
    Packet packet;
    packet << ACCEPTED;
    packet << ip_addr;
    packet << port;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending ACCEPTED." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "ACCEPTED sent" << endl;
        cout << "ip_addr: " << ip_addr << " port: " << port << endl;
    }
}

void ParchisRemote::sendOKReserved(){
    Packet packet;
    packet << OK_RESERVED;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending OK_RESERVED." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "OK_RESERVED sent" << endl;
    }
}

void ParchisRemote::sendOKRandomPrivateStart(int theplayer, string rival_name, BoardConfig config){
    Packet packet;
    packet << OK_RANDOM_PRIVATE_START;
    packet << theplayer;
    packet << rival_name;
    packet << config;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << COUT_RED_BOLD << "Error sending OK_RANDOM_PRIVATE_START." << COUT_NOCOLOR << endl;
    }
    else{
        cout << "OK_RANDOM_PRIVATE_START sent" << endl;
        cout << "theplayer: " << theplayer << " rival_name: " << rival_name << " config: " << config << endl;
    }
}

void ParchisRemote::sendTestMessage(string message)
{
    Packet packet;
    packet << TEST_MESSAGE;
    packet << message;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        throw runtime_error("Error sending message");
    }
    cout << "TEST_MESSAGE sent" << endl;
    cout << "Message: " << message << endl;
}

void ParchisRemote::sendParchisMove(int turn, color c_piece, int id_piece, int dice){
    Packet packet;
    packet << MOVED;
    packet << turn;
    packet << c_piece;
    packet << id_piece;
    packet << dice;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << "Error sending message" << endl;
        socket.disconnect();
    }
    else{
        cout << "301 MOVED sent" << endl;
        cout << "Move: " << turn << " " << str(c_piece) << " " << id_piece << " " << dice << endl;
    }
}

void ParchisRemote::sendErrorMessage(MessageKind msgkind, string message){
    Packet packet;
    packet << msgkind;
    packet << message;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
        cout << "Error sending message" << endl;
        socket.disconnect();
    }
    else{
        cout << "Error message sent" << endl;
    }
}


MessageKind ParchisRemote::receive(Packet & packet)
{
    if(!isConnected()) return ERROR_DISCONNECTED;
    packet.clear();
    Socket::Status status = socket.receive(packet);

    if(status != Socket::Done)
    {
        cout << "Error receiving message" << endl;
        socket.disconnect();
    }
    
    int type;
    packet >> type;

    Packet p2(packet);
    switch(type)
    {
        case NOP:
        break;
        case HELLO:
        {
            cout << "100 HELLO received" << endl;
            break;
        }
        case GAME_PARAMETERS:
        {
            cout << "101 GAME_PARAMETERS received" << endl;
            break;
        }
        case TEST_ALIVE:
        {
            cout << "102 TEST_ALIVE received" << endl;
            break;
        }
        case HELLO_MASTER:
        {
            cout << "103 HELLO_MASTER received" << endl;
            break;
        }
        case HOW_R_U:
        {
            cout << "104 HOW_R_U received" << endl;
            break;
        }
        case QUEUED:
        {
            cout << "105 QUEUED received" << endl;
            break;
        }
        case RESERVE_IP:
        {
            cout << "106 RESERVE_IP received" << endl;
            break;
        }
        case KILL:
        {
            cout << "107 KILL received" << endl;
            break;
        }
        case RANDOM_GAME:
        {
            cout << "108 RANDOM_GAME received" << endl;
            break;
        }
        case PRIVATE_GAME:
        {
            cout << "109 PRIVATE_GAME received" << endl;
            break;
        }
        case WAITING_FOR_PLAYERS:
        {
            cout << "110 WAITING_FOR_PLAYERS received" << endl;
            break;
        }
        case OK:
        {
            cout << "200 OK received" << endl;
            break;
        }
        case OK_MOVED:
        {
            cout << "201 OK_MOVED received" << endl;
            break;
        }
        case NINJA_STATUS:
        {
            cout << "202 NINJA_STATUS received" << endl;
            break;
        }
        case NINJA_ACCEPTED:
        {
            cout << "203 NINJA_ACCEPTED received" << endl;
            break;
        }
        case ACCEPTED:
        {
            cout << "204 ACCEPTED received" << endl;
            break;
        }
        case OK_RESERVED:
        {
            cout << "205 OK_RESERVED received" << endl;
            break;
        }
        case OK_START_GAME:
        {
            cout << "206 OK_START_GAME received" << endl;
            break;
        }
        case OK_RANDOM_PRIVATE_START:
        {
            cout << "209 OK_RANDOM_PRIVATE_START received" << endl;
            break;
        }
        case TEST_MESSAGE:
        {
            cout << "300 TEST_MESSAGE received" << endl;
            break;
        }
        case MOVED:
        {
            cout << "301 MOVED received" << endl;
            break;
        }
        case ERROR_DISCONNECTED:
        {
            cout << "400 ERROR_DISCONNECTED received" << endl;
            break;
        }
        case ERR_INVALID_MESSAGE:
        {
            cout << "401 ERR_INVALID_MESSAGE received" << endl;
            break;
        }
        case ERR_COULDNT_RESERVE:
        {
            cout << "402 ERR_COULDNT_RESERVE received" << endl;
            break;
        }
        case ERR_NO_NINJAS:
        {
            cout << "403 ERR_NO_NINJAS received" << endl;
            break;
        }
        case ERR_UNAUTHORIZED:
        {
            cout << "404 ERR_UNAUTHORIZED received" << endl;
            break;
        }
        case ERR_UPDATE:
        {
            cout << "405 ERR_UPDATE received" << endl;
            break;
        }
        case ERR_FULL_ROOM:
        {
            cout << "406 ERR_FULL_ROOM received" << endl;
            break;
        }
        default:
        {
            cout << "Received unknown message: " << type << endl;
            break;
        }
    }

    return (MessageKind)type;

}

void ParchisRemote::analyzePacket(Packet & packet, const MessageKind & kind)
{
   switch(kind)
    {
        case TEST_MESSAGE:
        {
            string message = ParchisRemote::packet2message(packet);
            cout << "300 TEST_MESSAGE received: " << message << endl;
            break;
        }
        case MOVED:
        {
            color c_piece;
            int id_piece;
            int dice;
            int turn;
            
            ParchisRemote::packet2move(packet, turn, c_piece, id_piece, dice);
            cout << "301 MOVED received: " << turn << " " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        }
        default:
        {
            cout << "Received unknown message" << endl;
        }
    }
}

void ParchisRemote::packet2Hello(Packet & packet, int & version, vector<string> & args)
{
    packet >> version;
    int size;
    packet >> size;
    for(int i = 0; i < size; i++)
    {
        string arg;
        packet >> arg;
        args.push_back(arg);
    }
    cout << "version: " << version << " args: ";
    for(int i = 0; i < size; i++)
    {
        cout << args[i] << " ";
    }
    cout << endl;
}

void ParchisRemote::packet2HelloMaster(Packet & packet, string & ip_addr, int & port, int & online_version, int & ninja_version){
    packet >> ip_addr;
    packet >> port;
    packet >> online_version;
    packet >> ninja_version;
    cout << "ip_addr: " << ip_addr << " port: " << port << " online_version: " << online_version << " ninja_version: " << ninja_version << endl;
}

int ParchisRemote::packet2queuePos(Packet & packet)
{
    int queuePos;
    packet >> queuePos;
    cout << "queuePos: " << queuePos << endl;
    return queuePos;
}

void ParchisRemote::packet2reservedIp(Packet & packet, string & ip_addr, int & port)
{
    packet >> ip_addr;
    packet >> port;
    cout << "ip_addr: " << ip_addr << " port: " << port << endl;
}

void ParchisRemote::packet2randomGame(Packet & packet, string & name){
    packet >> name;
    cout << "name: " << name << endl;
}

void ParchisRemote::packet2privateGame(Packet & packet, string & room_name, string & name){
    packet >> room_name;
    packet >> name;
    cout << "room_name: " << room_name << " name: " << name << endl;
}

void ParchisRemote::packet2ninjaStatus(Packet & packet, int & ninja_games, int & random_games, int & private_games){
    packet >> ninja_games;
    packet >> random_games;
    packet >> private_games;
    cout << "ninja_games: " << ninja_games << " random_games: " << random_games << " private_games: " << private_games << endl;
}

void ParchisRemote::packet2OKRandomPrivateStart(Packet & packet, int & myplayer, string & rival_name, BoardConfig & config){
    packet >> myplayer;
    packet >> rival_name;
    int int_config;
    packet >> int_config;
    config = (BoardConfig)int_config;
    cout << "myplayer: " << myplayer << " rival_name: " << rival_name << endl;
    cout << "config: " << config << endl;
}

void ParchisRemote::packet2acceptedIp(Packet &packet, string &ip_addr, int &port)
{
    packet >> ip_addr;
    packet >> port;
    cout << "ip_addr: " << ip_addr << " port: " << port << endl;
}

string ParchisRemote::packet2message(Packet & packet)
{
    string message;
    packet >> message;
    cout << "Message: " << message << endl;
    return message;
}

void ParchisRemote::packet2move(Packet & packet, int & turn, color & c_piece, int & id_piece, int & dice)
{
    packet >> turn;
    int cint_piece;
    packet >> cint_piece;
    c_piece = (color)cint_piece;
    packet >> id_piece;
    packet >> dice;
    cout << "Move: " << turn << " " << str(c_piece) << " " << id_piece << " " << dice << endl;
}

void ParchisRemote::packet2gameParameters(Packet & packet, int & player, string & name, BoardConfig & init_board, int & ai_id){
    packet >> player;
    packet >> name;
    int cint_board;
    packet >> cint_board;
    init_board = (BoardConfig) cint_board;
    packet >> ai_id;
    cout << "player: " << player << " name: " << name << " init_board: " << init_board << " ai_id: " << ai_id << endl;
}

string ParchisRemote::packet2errorMessage(Packet & packet)
{
    string message;
    packet >> message;
    cout << "Error message: " << message << endl;
    return message;
}

bool ParchisRemote::isConnected()
{
    /*
    Packet packet;
    packet << TEST_ALIVE;
    Socket::Status status = socket.send(packet);

    return (status == Socket::Done);
    */
   return socket.getRemoteAddress() != IpAddress::None;
}


void ParchisClient::startClientConnection(const string & ip_addr, const int & port){
    Socket::Status status = socket.connect(ip_addr, port);

    if(status != Socket::Done){
        throw runtime_error("Could not connect to server");
    }

    cout << "Connected to server " << ip_addr << ":" << port << endl;

}
/*
void ParchisServer::startListening(const int & port){
    if(listener.listen(port) != Socket::Done){
        throw runtime_error("Could not listen to port");
    }

    cout << "Listening on port " << port << endl;
}
*/
void ParchisServer::acceptConnection(TcpListener & listener){
    //TcpSocket *socket = new TcpSocket();
    //cout << socket << endl;
    if(listener.accept(socket) != Socket::Done){
        throw runtime_error("Could not accept connection");
    }

    cout << "Accepted connection from " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << endl;
}

NinjaServer::NinjaServer(const int &myport, const string & my_contact_ip) : reviser(&NinjaServer::reviserLoop, this),
                                                                            //console_reader_thread(&NinjaServer::reviserLoop, this), //&NinjaServer::consoleReader, this)
                                                                            master_thread(&NinjaServer::masterReceiver, this)  // & NinjaServer::masterReceiver, this)
{
    this->listener_port = myport;
    this->my_contact_ip = my_contact_ip;
}

void NinjaServer::setMaster(const string & master_ip, const int & master_port){
    this->master_ip = master_ip;
    this->master_port = master_port;
}

void NinjaServer::startServer(){
    is_running = true;

    
    //master_thread.launch();

    this->listener.listen(listener_port);

    if (listener.listen(listener_port) != Socket::Done)
    {
        throw runtime_error("Could not listen to port");
    }

    cout << "Listening on port " << listener_port << endl;

    // Connect to master.
    connectToMaster();

    // Initialize threads.
    reviser.launch();
    //console_reader_thread.launch();
    master_thread.launch();
    this->acceptationLoop();

}

void NinjaServer::stopServer(){
    is_running = false;

    cout << "Stopping listener..." << endl;
    listener.close();
    for(auto ninja_game_it = ninja_games.begin(); ninja_game_it != ninja_games.end(); ++ninja_game_it){
        cout << "Finalizando conexión con partida " << (*ninja_game_it).connection->getRemoteAddress() << endl;
        ninja_game_it->connection->sendErrorMessage(ERROR_DISCONNECTED, "Problemas internos.");
        ninja_game_it->thread->wait();
    }

    cout << "Cerrando hebra revisora..." << endl;
    reviser.wait();
    //console_reader_thread.wait();
    //cout << "Cerrando conexión con master..." << endl;
    //master_thread.wait();
    ParchisClient client;
    client.startClientConnection("localhost", this->listener_port);
    client.sendTestAlive();
}

void NinjaServer::acceptationLoop(){
    while(is_running){
        shared_ptr<ParchisServer> server = make_shared<ParchisServer>();

        server->acceptConnection(listener);

        shared_ptr<Thread> thread;
        //shared_ptr<Thread> * thread_addr = &thread;
        thread = make_shared<Thread>(std::bind(&NinjaServer::acceptationStep, this, server));
        idle_threads.push_back(thread);
        thread->launch();
        while(!idle_threads.empty()){
            sleep(milliseconds(1));
        }
    }
}

void NinjaServer::acceptationStep(shared_ptr<ParchisServer> server){
    while(idle_threads.empty()){
        sleep(milliseconds(1));
    }
    shared_ptr<Thread> thread = idle_threads.back();
    idle_threads.pop_back();

    server_connection con;
    con.ip_addr = server->getRemoteAddress().toString();
    con.port = server->getRemotePort();
    if(reserved_ips.find(con) == reserved_ips.end()){
        cout << COUT_RED_BOLD << "Connection from " << server->getRemoteAddress() << ":" << server->getRemotePort() << " is not allowed." << COUT_NOCOLOR << endl;
        server->sendErrorMessage(ERR_UNAUTHORIZED, "Esta máquina no ha sido autorizada para jugar.");
        return;
    }
    else{
        reserved_ips.erase(con);
    }

    // Receive the game_mode
    Packet packet;
    MessageKind message_kind;

    do{
        message_kind = server->receive(packet);
        sleep(milliseconds(10));
    } while (message_kind != GAME_PARAMETERS && message_kind != RANDOM_GAME && message_kind != PRIVATE_GAME);

    if(message_kind == GAME_PARAMETERS){
        newNinjaGame(server, packet, thread);
    }
    else if(message_kind == RANDOM_GAME){
        queueRandomMatchGame(server, packet, thread);
    }
    else if(message_kind == PRIVATE_GAME){
        queuePrivateRoomGame(server, packet, thread);
    }
    else{
        throw runtime_error("Invalid message kind");
    }
}

void NinjaServer::newNinjaGame(shared_ptr<ParchisServer> server, Packet &packet, shared_ptr<Thread> thread)
{
    int player;
    string name;
    BoardConfig init_board;
    int ai_id;
    server->packet2gameParameters(packet, player, name, init_board, ai_id);

    ninja_game new_game;
    new_game.connection = server;
    new_game.thread = thread;
    ninja_games_mutex.lock();
    ninja_games.push_back(new_game);
    ninja_games_mutex.unlock();

    if (player == 0)
    {
        // J1 remoto.
        shared_ptr<RemotePlayer> p1 = make_shared<RemotePlayer>(name, server);
        // J2 Ninja.
        shared_ptr<Ninja> p2 = make_shared<Ninja>("J2", ai_id);
        server->sendOKStartGame(p2->getName());

        // Inciar juego.
        Parchis parchis(init_board, p1, p2);

        parchis.gameLoop();
    }
    else
    {
        // J2 remoto.
        shared_ptr<RemotePlayer> p2 = make_shared<RemotePlayer>(name, server);
        // J1 ninja.
        shared_ptr<Ninja> p1 = make_shared<Ninja>("J1", ai_id);

        server->sendOKStartGame(p1->getName());

        // Inciar juego
        Parchis parchis(init_board, p1, p2);
        parchis.gameLoop();
    }
}

void NinjaServer::queueRandomMatchGame(shared_ptr<ParchisServer> server, Packet &packet, shared_ptr<Thread> thread){
    string name;
    BoardConfig init_board = GROUPED;
    server->packet2randomGame(packet, name);

    random_match_games_mutex.lock();

    if(!random_match_games.empty() && random_match_games.back().waiting_for_players){
        random_match_games.back().connection_p2 = server;
        random_match_games.back().name_p2 = name;
        random_match_games.back().thread = thread;
        random_match_games.back().waiting_for_players = false;

        // Los dos jugadores remotos.
        shared_ptr<RemotePlayer> p1 = make_shared<RemotePlayer>(random_match_games.back().name_p1, random_match_games.back().connection_p1);
        shared_ptr<RemotePlayer> p2 = make_shared<RemotePlayer>(random_match_games.back().name_p2, random_match_games.back().connection_p2);

        random_match_games.back().connection_p1->sendOKRandomPrivateStart(0, p2->getName(), init_board);
        random_match_games.back().connection_p2->sendOKRandomPrivateStart(1, p1->getName(), init_board);

        random_match_games_mutex.unlock();

        // Inciar juego.
        Parchis parchis(init_board, p1, p2);
        parchis.gameLoop();
    }
    else{
        random_match_games.push_back(random_match_game());
        random_match_games.back().connection_p1 = server;
        random_match_games.back().name_p1 = name;
        random_match_games.back().waiting_for_players = true;
        random_match_games.back().aux_thread = thread; // Para evitar que se intente destruir a sí misma cuando se libere el shared_ptr.

        random_match_games_mutex.unlock();

        server->sendWaitingForPlayers();
    }

    
}

void NinjaServer::queuePrivateRoomGame(shared_ptr<ParchisServer> server, Packet &packet, shared_ptr<Thread> thread){
    string name;
    string room_name;
    BoardConfig init_board = GROUPED;
    server->packet2privateGame(packet, room_name, name);

    private_room_games_mutex.unlock();

    auto curr_room = private_room_games.find(room_name);

    if(curr_room != private_room_games.end()){
        private_room_game * room = &curr_room->second;
        if(room->waiting_for_players){
            room->connection_p2 = server;
            room->name_p2 = name;
            room->thread = thread;
            room->waiting_for_players = false;

            // Los dos jugadores remotos.
            shared_ptr<RemotePlayer> p1 = make_shared<RemotePlayer>(room->name_p1, room->connection_p1);
            shared_ptr<RemotePlayer> p2 = make_shared<RemotePlayer>(room->name_p2, room->connection_p2);

            room->connection_p1->sendOKRandomPrivateStart(0, p2->getName(), init_board);
            room->connection_p2->sendOKRandomPrivateStart(1, p1->getName(), init_board);

            private_room_games_mutex.unlock();

            // Inciar juego.
            Parchis parchis(init_board, p1, p2);
            parchis.gameLoop();

        }
        else{
            server->sendErrorMessage(ERR_FULL_ROOM, "La sala indicada ya existe y está completa. Por favor, indica otro nombre de sala.");
            dead_threads.push_back(thread);
        }
    }
    else{
        private_room_games[room_name] = private_room_game();
        private_room_games[room_name].connection_p1 = server;
        private_room_games[room_name].name_p1 = name;
        private_room_games[room_name].waiting_for_players = true;
        private_room_games[room_name].aux_thread = thread; // Para evitar que se intente destruir a sí misma cuando se libere el shared_ptr.
        private_room_games_mutex.unlock();

        server->sendWaitingForPlayers();
    }


    
}

void NinjaServer::reviserLoop()
{
    while (is_running)
    {
        reviseNinjaThreadsStep();
        reviseRandomMatchThreadsStep();
        revisePrivateRoomThreadsStep();
        reviseDeadThreadsStep();
        sleep(seconds(10));
    }
}

void NinjaServer::reviseNinjaThreadsStep(){
    cout << COUT_BLUE_BOLD + "Checking ninja threads..." + COUT_NOCOLOR << endl;
    auto it_ninja_games = ninja_games.begin();
    int nremoves = 0;

    for (; it_ninja_games != ninja_games.end();)
    {
        (*it_ninja_games).connection->sendTestAlive();
        if (!(*it_ninja_games).connection->isConnected())
        {
            (*it_ninja_games).thread->wait();
            it_ninja_games = ninja_games.erase(it_ninja_games);
            nremoves++;
            // delete (*it_threads);
            // delete (*it_servers);
        }
        else
        {
            ++it_ninja_games;
        }
    }
    cout << COUT_BLUE_BOLD + "Current connections: " << ninja_games.size() << " (" << nremoves << " removed)" + COUT_NOCOLOR << endl;
}

void NinjaServer::reviseRandomMatchThreadsStep(){
    cout << COUT_BLUE_BOLD + "Checking random match threads..." + COUT_NOCOLOR << endl;
    auto it_random_match_games = random_match_games.begin();
    int nremoves = 0;

    random_match_games_mutex.lock();
    for (; it_random_match_games != random_match_games.end();)
    {
        (*it_random_match_games).connection_p1->sendTestAlive();
        if(!(*it_random_match_games).connection_p1->isConnected()){
            (*it_random_match_games).thread->wait();
            it_random_match_games = random_match_games.erase(it_random_match_games);
            nremoves++;
            // delete (*it_threads);
            // delete (*it_servers);
        }
        else if(!(*it_random_match_games).waiting_for_players){
            (*it_random_match_games).connection_p2->sendTestAlive();
            if (!(*it_random_match_games).connection_p2->isConnected())
            {
                (*it_random_match_games).thread->wait();
                it_random_match_games = random_match_games.erase(it_random_match_games);
                nremoves++;
                // delete (*it_threads);
                // delete (*it_servers);
            }
            else
            {
                ++it_random_match_games;
            }
        }
        else{
            ++it_random_match_games;
        }
    }
    random_match_games_mutex.unlock();
    cout << COUT_BLUE_BOLD + "Current connections: " << random_match_games.size() << " (" << nremoves << " removed)" + COUT_NOCOLOR << endl;
}

void NinjaServer::revisePrivateRoomThreadsStep(){
    cout << COUT_BLUE_BOLD + "Checking private room threads..." + COUT_NOCOLOR << endl;
    auto it_private_room_games = private_room_games.begin();
    int nremoves = 0;

    private_room_games_mutex.lock();
    for (; it_private_room_games != private_room_games.end();)
    {
        private_room_game * theroom = &it_private_room_games->second;
        (*theroom).connection_p1->sendTestAlive();
        if(!(*theroom).connection_p1->isConnected()){
            (*theroom).thread->wait();
            it_private_room_games = private_room_games.erase(it_private_room_games);
            nremoves++;
            // delete (*it_threads);
            // delete (*it_servers);
        }
        else if(!(*theroom).waiting_for_players){
            (*theroom).connection_p2->sendTestAlive();
            if (!(*theroom).connection_p2->isConnected())
            {
                (*theroom).thread->wait();
                it_private_room_games = private_room_games.erase(it_private_room_games);
                nremoves++;
                // delete (*it_threads);
                // delete (*it_servers);
            }
            else
            {
                ++it_private_room_games;
            }
        }
        else{
            ++it_private_room_games;
        }
    }
    private_room_games_mutex.unlock();
    cout << COUT_BLUE_BOLD + "Current connections: " << private_room_games.size() << " (" << nremoves << " removed)" + COUT_NOCOLOR << endl;
}

void NinjaServer::reviseDeadThreadsStep(){
    cout << COUT_BLUE_BOLD + "Checking dead threads..." + COUT_NOCOLOR << endl;
    auto it_dead_threads = dead_threads.begin();
    int nremoves = 0;

    for (; it_dead_threads != dead_threads.end();)
    {
        (*it_dead_threads)->wait();
        it_dead_threads = dead_threads.erase(it_dead_threads);
        nremoves++;
        // delete (*it_threads);
        // delete (*it_servers);
    }
    cout << COUT_BLUE_BOLD + "Current connections: " << dead_threads.size() << " (" << nremoves << " removed)" + COUT_NOCOLOR << endl;
}

void NinjaServer::connectToMaster(){
    this->master_connection.startClientConnection(master_ip, master_port);
    master_connection.sendHelloMaster(my_contact_ip, listener_port);
    Packet packet;
    MessageKind message_kind;
    message_kind = master_connection.receive(packet);
    if(message_kind == NINJA_ACCEPTED){
        cout << COUT_GREEN_BOLD << "Ninja accepted by master" << COUT_NOCOLOR << endl;
    }
    else if(message_kind >= 400){
        string error_message = master_connection.packet2errorMessage(packet);
        cout << COUT_RED_BOLD << "Ninja rejected by master: " << error_message << COUT_NOCOLOR << endl;
        exit(1);
    }
    else{
        cout << COUT_RED_BOLD << "Unexpected message received." << COUT_NOCOLOR << endl;
        exit(1);
    }
}

void NinjaServer::masterReceiver(){
    while(is_running){
        Packet packet;
        MessageKind message_kind;

        message_kind = master_connection.receive(packet);

        switch(message_kind){
            case RESERVE_IP:
            {
                string ip_addr;
                int port;
                master_connection.packet2reservedIp(packet, ip_addr, port);
                server_connection con;
                con.ip_addr = ip_addr;
                con.port = port;
                reserved_ips_mutex.lock();
                reserved_ips.insert(con);
                reserved_ips_mutex.unlock();
                cout << "Reserved IP: " << ip_addr << ":" << port << endl;
                master_connection.sendOKReserved();
            }
                break;
            
            case HOW_R_U:
            {
                int ninja_games_size = ninja_games.size();
                int random_games_size = random_match_games.size();
                int private_rooms_size = private_room_games.size();

                master_connection.sendNinjaStatus(ninja_games_size, random_games_size, private_rooms_size);
            }
            break;

            case ERROR_DISCONNECTED:
            {
                cout << COUT_RED_BOLD << "Master disconnected" << COUT_NOCOLOR << endl;
                stopServer();
                return;
            }

            default:
                cout << COUT_RED_BOLD << "Unexpected/unknown message kind: " << message_kind << COUT_NOCOLOR << endl;
                break;
        }

    }
}
    



MasterServer::MasterServer(const int &myport) : reviser_thread(&MasterServer::reviserLoop, this)
{
    this->listener_port = myport;
    //this->allowed_ninja_ips.insert(ip_addr);
    this->last_random_assigned_connection = nullptr;
}

void MasterServer::addAllowedNinja(string ip){
    this->allowed_ninja_ips.insert(ip);
}

void MasterServer::startServer(){
    is_running = true;

    // master_thread.launch();

    this->listener.listen(listener_port);

    if (listener.listen(listener_port) != Socket::Done)
    {
        throw runtime_error("Could not listen to port");
    }

    cout << "Listening on port " << listener_port << endl;

    // Initialize threads.
    reviser_thread.launch();
    // console_reader_thread.launch();
    // master_thread.launch();
    this->acceptationLoop();

}

void MasterServer::acceptationLoop(){
    while (is_running)
    {
        shared_ptr<ParchisServer> server = make_shared<ParchisServer>();

        server->acceptConnection(listener);

        shared_ptr<Thread> thread;
        // shared_ptr<Thread> * thread_addr = &thread;
        thread = make_shared<Thread>(std::bind(&MasterServer::acceptationStep, this, server));
        //idle_threads.push_back(thread);
        thread->launch();
        //while (!idle_threads.empty())
        //{
        //    sleep(milliseconds(1));
        //}
    }
}

void MasterServer::acceptationStep(shared_ptr<ParchisServer> server){
    // Wait for the greeting.
    Packet packet;
    MessageKind message_kind;

    message_kind = server->receive(packet);

    if (message_kind != HELLO && message_kind != HELLO_MASTER){
        server->sendErrorMessage(ERR_INVALID_MESSAGE, "Mensaje inesperado.");
        return;
    }
    else if(message_kind == HELLO){
        handleClientConnection(server, packet);
    }
    else if(message_kind == HELLO_MASTER){
        handleNinjaConnection(server, packet);
    }
}

void MasterServer::handleNinjaConnection(shared_ptr<ParchisServer> server, Packet & packet){
    // Consultar si la ip recibida y el puerto están en la lista de ninjas permitidos.
    string ip_addr;
    int port;
    int online_version;
    int ninja_version;
    server->packet2HelloMaster(packet, ip_addr, port, online_version, ninja_version);
    if(ninja_version != NINJA_VERSION){
        server->sendErrorMessage(ERR_UPDATE, "Hay una versión más reciente del servidor ninja. Es necesario actualizar el repositorio.");
        return;
    }
    if (online_version != ONLINE_VERSION)
    {
        server->sendErrorMessage(ERR_UPDATE, "Hay una actualización disponible del juego y del modo online. Es necesario actualizar el repositorio.");
        return;
    }
    if(ip_addr != server->getRemoteAddress().toString() && ip_addr != "127.0.0.1"){
        server->sendErrorMessage(ERR_UNAUTHORIZED, "La IP de contacto no se corresponde con la real.");
    }
    else if(allowed_ninja_ips.find(ip_addr) != allowed_ninja_ips.end()){
        server->sendAcceptNinjaMessage();
        cout << COUT_GREEN_BOLD << "New ninja added from " << server->getRemoteAddress() << ":" << server->getRemotePort() << COUT_NOCOLOR << endl;
        NinjaConnection ninja_connection;
        ninja_connection.connection = server;
        ninja_connection.ip_addr = ip_addr;
        ninja_connection.port = port;
        ninja_connections.push_back(ninja_connection);
    }
    else
    {
        server->sendErrorMessage(ERR_UNAUTHORIZED, "Este servidor no está autorizado para ser un ninja.");
    }
}

void MasterServer::handleClientConnection(shared_ptr<ParchisServer> server, Packet & packet){
    // vector<NinjaOccupation> ninja_occupations;
    //  Consultar con todos los servidores ninja la ocupación, y asignarle el menos ocupado.
    int version;
    vector<string> args;
    server->packet2Hello(packet, version, args);

    if(version != ONLINE_VERSION){
        server->sendErrorMessage(ERR_UPDATE, "Hay una versión más reciente del juego. Es necesario actualizar el repositorio para jugar online, y también recomendable para el juego local. Recuerda: git pull upstream main (tras haber seguido los pasos del tutorial).");
        return;
    }

    if(args.size() == 1 && args[0] == "ninjagame"){
        this->reserveNinjaGame(server);
    }
    else if(args.size() == 1 && args[0] == "randomgame"){
        this->reserveRandomGame(server);
    }
    else if(args.size() == 2 && args[0] == "privateroom"){
        this->reservePrivateGame(server, args[1]);
    }
    else{
        server->sendErrorMessage(ERR_INVALID_MESSAGE, "No entendí el modo de juego que me enviaste.");
    }

}

void MasterServer::reserveNinjaGame(shared_ptr<ParchisServer> server){
    int lowest_occupation = 999999;
    auto lowest_occupation_it = ninja_connections.end();
    for (auto it = ninja_connections.begin(); it != ninja_connections.end(); ++it)
    {
        instant_send_receive_mutex1.lock();
        (*it).connection->sendHowAreYou();
        if ((*it).connection->isConnected())
        {
            Packet packet;
            MessageKind message_kind;
            message_kind = (*it).connection->receive(packet);
            if (message_kind == NINJA_STATUS)
            {
                int ninja_games;
                int random_games;
                int private_games;
                (*it).connection->packet2ninjaStatus(packet, ninja_games, random_games, private_games);
                if (ninja_games < lowest_occupation)
                {
                    lowest_occupation = ninja_games;
                    lowest_occupation_it = it;
                }
            }
            else
            {
                cout << COUT_RED_BOLD << "Error: El servidor ninja ha enviado un mensaje inesperado." << COUT_NOCOLOR << endl;
            }
        }
        else
        {
            cout << COUT_RED_BOLD << "Conexión perdida con servidor ninja." << COUT_NOCOLOR << endl;
        }
        instant_send_receive_mutex1.unlock();
    }
    if (lowest_occupation_it != ninja_connections.end())
    {
        if (lowest_occupation < MAX_ALLOWED_NINJA_GAMES)
        {

            // Asignarle el servidor ninja.
            instant_send_receive_mutex1.lock();
            (*lowest_occupation_it).connection->sendReserveIp(server->getRemoteAddress().toString(), server->getRemotePort());
            // Wait for the OK
            Packet packet;
            MessageKind message_kind;
            message_kind = (*lowest_occupation_it).connection->receive(packet);
            instant_send_receive_mutex1.unlock();
            if (message_kind == OK_RESERVED)
            {
                server->sendAcceptedMessage((*lowest_occupation_it).ip_addr, (*lowest_occupation_it).port);
            }
            else
            {
                server->sendErrorMessage(ERR_COULDNT_RESERVE, "No se ha podido asignar un servidor ninja. Inténtalo de nuevo, por favor. Si el problema persiste avisa a tus profesores.");
            }
        }
        else
        {
            // Se encola el servidor.
            queue_insert_mutex.lock();
            queued_connections.push_back(server);
            int queue_pos = queued_connections.size();
            queue_insert_mutex.unlock();
            server->sendQueued(queue_pos);
        }
    }
    else
    {
        server->sendErrorMessage(ERR_NO_NINJAS, "No hay servidores ninja disponibles. Avisa a tus profesores.");
    }
}


void MasterServer::reserveRandomGame(shared_ptr<ParchisServer> server){
    // Si la última conexión random es no nula, reservo allí.
    random_assign_mutex.lock();
    if(last_random_assigned_connection != nullptr){
        instant_send_receive_mutex1.lock();
        last_random_assigned_connection->connection->sendReserveIp(server->getRemoteAddress().toString(), server->getRemotePort());
        // Wait for the OK
        Packet packet;
        MessageKind message_kind;
        message_kind = last_random_assigned_connection->connection->receive(packet);
        instant_send_receive_mutex1.unlock();
        if (message_kind == OK_RESERVED)
        {
            server->sendAcceptedMessage(last_random_assigned_connection->ip_addr, last_random_assigned_connection->port);
            last_random_assigned_connection = nullptr;
        }
        else
        {
            server->sendErrorMessage(ERR_COULDNT_RESERVE, "No se ha podido asignar un servidor. Inténtalo de nuevo, por favor. Si el problema persiste avisa a tus profesores.");
            last_random_assigned_connection = nullptr;
        }
    }
    else{
        // Busco el servidor menos ocupado.
        int lowest_occupation = 999999;
        auto lowest_occupation_it = ninja_connections.end();
        for (auto it = ninja_connections.begin(); it != ninja_connections.end(); ++it)
        {
            instant_send_receive_mutex1.lock();
            (*it).connection->sendHowAreYou();
            if ((*it).connection->isConnected())
            {
                Packet packet;
                MessageKind message_kind;
                message_kind = (*it).connection->receive(packet);
                if (message_kind == NINJA_STATUS)
                {
                    int ninja_games;
                    int random_games;
                    int private_games;
                    (*it).connection->packet2ninjaStatus(packet, ninja_games, random_games, private_games);
                    if (random_games < lowest_occupation)
                    {
                        lowest_occupation = random_games;
                        lowest_occupation_it = it;
                    }
                }
                else
                {
                    cout << COUT_RED_BOLD << "Error: El servidor ninja ha enviado un mensaje inesperado." << COUT_NOCOLOR << endl;
                }
            }
            else
            {
                cout << COUT_RED_BOLD << "Conexión perdida con servidor ninja." << COUT_NOCOLOR << endl;
            }
            instant_send_receive_mutex1.unlock();
        }
        if (lowest_occupation_it != ninja_connections.end())
        {
            if (true) // TODO: Encolar también cuando la ocupación sube, pero hay que tener en cuenta el modo de juego.
            {

                // Asignarle el servidor ninja.
                instant_send_receive_mutex1.lock();
                (*lowest_occupation_it).connection->sendReserveIp(server->getRemoteAddress().toString(), server->getRemotePort());
                // Wait for the OK
                Packet packet;
                MessageKind message_kind;
                message_kind = (*lowest_occupation_it).connection->receive(packet);
                instant_send_receive_mutex1.unlock();
                if (message_kind == OK_RESERVED)
                {
                    last_random_assigned_connection = &(*lowest_occupation_it);
                    server->sendAcceptedMessage((*lowest_occupation_it).ip_addr, (*lowest_occupation_it).port);
                }
                else
                {
                    server->sendErrorMessage(ERR_COULDNT_RESERVE, "No se ha podido asignar un servidor ninja. Inténtalo de nuevo, por favor. Si el problema persiste avisa a tus profesores.");
                }
            }
            else
            {
                // Se encola el servidor.
                queue_insert_mutex.lock();
                queued_connections.push_back(server);
                int queue_pos = queued_connections.size();
                queue_insert_mutex.unlock();
                server->sendQueued(queue_pos);
            }
        }
        else
        {
            server->sendErrorMessage(ERR_NO_NINJAS, "No hay servidores ninja disponibles. Avisa a tus profesores.");
        }

    }
    random_assign_mutex.unlock();
}


void MasterServer::reservePrivateGame(shared_ptr<ParchisServer> server, const string & room_name){
    // Si la sala ya está creada en algún servidor ninja, reservo allí.
    private_room_connections_mutex.lock();
    auto curr_room = private_room_connections.find(room_name);
    if (curr_room != private_room_connections.end())
    {
        instant_send_receive_mutex1.lock();
        (*curr_room).second->connection->sendReserveIp(server->getRemoteAddress().toString(), server->getRemotePort());
        // Wait for the OK
        Packet packet;
        MessageKind message_kind;
        message_kind = (*curr_room).second->connection->receive(packet);
        instant_send_receive_mutex1.unlock();
        if (message_kind == OK_RESERVED)
        {
            server->sendAcceptedMessage((*curr_room).second->ip_addr, (*curr_room).second->port);
            private_room_connections.erase(curr_room);
        }
        else
        {
            server->sendErrorMessage(ERR_COULDNT_RESERVE, "No se ha podido asignar un servidor ninja. Inténtalo de nuevo, por favor. Si el problema persiste avisa a tus profesores.");
            private_room_connections.erase(curr_room);
        }
    }
    else{
        // Busco el servidor menos ocupado.
        int lowest_occupation = 999999;
        auto lowest_occupation_it = ninja_connections.end();
        for (auto it = ninja_connections.begin(); it != ninja_connections.end(); ++it)
        {
            instant_send_receive_mutex1.lock();
            (*it).connection->sendHowAreYou();
            if ((*it).connection->isConnected())
            {
                Packet packet;
                MessageKind message_kind;
                message_kind = (*it).connection->receive(packet);
                if (message_kind == NINJA_STATUS)
                {
                    int ninja_games;
                    int random_games;
                    int private_games;
                    (*it).connection->packet2ninjaStatus(packet, ninja_games, random_games, private_games);
                    if (private_games < lowest_occupation)
                    {
                        lowest_occupation = private_games;
                        lowest_occupation_it = it;
                    }
                }
                else
                {
                    cout << COUT_RED_BOLD << "Error: El servidor ninja ha enviado un mensaje inesperado." << COUT_NOCOLOR << endl;
                }
            }
            else
            {
                cout << COUT_RED_BOLD << "Conexión perdida con servidor ninja." << COUT_NOCOLOR << endl;
            }
            instant_send_receive_mutex1.unlock();
        }
        if (lowest_occupation_it != ninja_connections.end())
        {
            if (true)  // TODO: Encolar también cuando la ocupación sube, pero hay que tener en cuenta el modo de juego.
            {

                // Asignarle el servidor ninja.
                instant_send_receive_mutex1.lock();
                (*lowest_occupation_it).connection->sendReserveIp(server->getRemoteAddress().toString(), server->getRemotePort());
                // Wait for the OK
                Packet packet;
                MessageKind message_kind;
                message_kind = (*lowest_occupation_it).connection->receive(packet);
                instant_send_receive_mutex1.unlock();
                if (message_kind == OK_RESERVED)
                {
                    private_room_connections.insert({room_name, &(*lowest_occupation_it)});
                    server->sendAcceptedMessage((*lowest_occupation_it).ip_addr, (*lowest_occupation_it).port);
                }
                else
                {
                    server->sendErrorMessage(ERR_COULDNT_RESERVE, "No se ha podido asignar un servidor ninja. Inténtalo de nuevo, por favor. Si el problema persiste avisa a tus profesores.");
                }
            }
            else
            {
                // Se encola el servidor.
                queue_insert_mutex.lock();
                queued_connections.push_back(server);
                int queue_pos = queued_connections.size();
                queue_insert_mutex.unlock();
                server->sendQueued(queue_pos);
            }
        }
        else
        {
            server->sendErrorMessage(ERR_NO_NINJAS, "No hay servidores ninja disponibles. Avisa a tus profesores.");
        }
    }
    private_room_connections_mutex.unlock();
}

void MasterServer::reviserLoop(){
    while (is_running)
    {
        cout << COUT_BLUE_BOLD + "Checking ninjas..." + COUT_NOCOLOR << endl;
        auto it_ninjas = ninja_connections.begin();
        int nremoves = 0;

        for (; it_ninjas != ninja_connections.end();)
        {
            instant_send_receive_mutex1.lock();
            (*it_ninjas).connection->sendHowAreYou();
            if (!(*it_ninjas).connection->isConnected())
            {
                it_ninjas = ninja_connections.erase(it_ninjas);
                nremoves++;

                cout << COUT_RED_BOLD << "Conexión perdida con servidor ninja." << COUT_NOCOLOR << endl;
                // delete (*it_threads);
                // delete (*it_servers);
            }
            else
            {
                Packet packet;
                MessageKind message_kind;
                message_kind = (*it_ninjas).connection->receive(packet);
                if (message_kind == NINJA_STATUS)
                {
                    int ninja_games;
                    int random_games;
                    int private_games;
                    (*it_ninjas).connection->packet2ninjaStatus(packet, ninja_games, random_games, private_games);
                    if (ninja_games < MAX_ALLOWED_NINJA_GAMES && queued_connections.size() > 0)
                    {
                        // Asignarle el servidor ninja.
                        instant_send_receive_mutex1.lock();
                        (*it_ninjas).connection->sendReserveIp(queued_connections.front()->getRemoteAddress().toString(), queued_connections.front()->getRemotePort());
                        // Wait for the OK
                        Packet packet;
                        MessageKind message_kind;
                        message_kind = (*it_ninjas).connection->receive(packet);
                        instant_send_receive_mutex1.unlock();
                        if (message_kind == OK_RESERVED)
                        {
                            queue_insert_mutex.lock();
                            queued_connections.front()->sendAcceptedMessage((*it_ninjas).ip_addr, (*it_ninjas).port);
                            queued_connections.pop_front();
                            if(queued_connections.size() > 0){
                                for (int i = 0; i < queued_connections.size(); i++)
                                {
                                    queued_connections.at(i)->sendQueued(i + 1);
                                }
                            }
                            queue_insert_mutex.unlock();
                        }
                        else
                        {
                            cout << COUT_RED_BOLD << "Ha fallado la asignación de un servidor ninja al cliente encolado." << COUT_NOCOLOR << endl;
                        }
                    }
                }
                else
                {
                    cout << COUT_RED_BOLD << "Error: El servidor ninja ha enviado un mensaje inesperado." << COUT_NOCOLOR << endl;
                }
                ++it_ninjas;
            }
            instant_send_receive_mutex1.unlock();
        }
        cout << COUT_BLUE_BOLD + "Current connections: " << ninja_connections.size() << " (" << nremoves << " removed)" + COUT_NOCOLOR << endl;
        sleep(seconds(10));
    }
}