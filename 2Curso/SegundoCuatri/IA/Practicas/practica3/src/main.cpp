# include "ParchisGUI.h"
# include "Parchis.h"
# include "Connection.h"
# include "GUIPlayer.h"
# include "RemotePlayer.h"
# include "AIPlayer.h"
# include "Ninja.h"
# include "IncludesSFML.h"
# include "cout_colors.h"
# include "GameSelector.h"

#include <cstring>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALLOWED_NINJAS_FILE "config/allowed_ninjas.txt"
#define MASTER_ADDRESSES_FILE "config/master_addresses.txt"
#define MY_PUBLIC_IP_FILE "config/my_public_ip.txt"

using namespace sf;
using namespace std;

/**
 * @brief Función auxiliar que lee las máquinas disponibles para ser masters.
 * Definidas en el fichero de configuración MASTER_ADDRESSES_FILE.
 * 
 * @param file_name 
 * @param ips 
 * @param ports 
 */
void readAllowedMasters(string file_name, vector<string> &ips, vector<int> &ports)
{
    // Leer file_name. Cada línea tiene una dirección ip y un puerto. Se añaden los valores
    // a las variables pasadas por referencia.
    ifstream file(file_name);
    string line;
    while (getline(file, line))
    {
        string ip;
        int port;
        stringstream ss(line);
        ss >> ip;
        ss >> port;
        ips.push_back(ip);
        ports.push_back(port);
    }
    file.close();
}

/**
 * @brief Toma de contacto entre el cliente y los masters.
 * Se especifica la ip y el puerto de la máquina máster y los argumentos de la partida.
 * 
 * @param ip_addr 
 * @param port 
 * @param args 
 */
void clientMasterHandshake(string & ip_addr, int & port, const vector<string> & args){
    vector<string> ips;
    vector<int> ports;
    //Se obtienen los masters disponhibles
    readAllowedMasters(MASTER_ADDRESSES_FILE, ips, ports);
    int i;
    //Se recorren las ips 
    for(i = 0; i < ips.size(); i++){
        //Se prueba a establecer conexión
        try{
            cout << "Trying " << ips[i] << ":" << ports[i] << endl;
            shared_ptr<ParchisClient> client_master = make_shared<ParchisClient>();
            // Comienzo de conexión al ip y puertos del master i
            client_master->startClientConnection(ips[i], ports[i]);
            Packet packet;
            MessageKind message_kind;
            // Cliente manda primer mensaje
            client_master->sendHello(args);
            do
            {
                // El cliente se queda esperando un mensaje de aceptación
                message_kind = client_master->receive(packet);
                if (message_kind > 400) // Si recibe un mensaje de error, se sale.
                {
                    cout << COUT_RED_BOLD << client_master->packet2errorMessage(packet) << COUT_NOCOLOR << endl;
                    if(message_kind == ERR_UPDATE){
                        exit(1);
                    }
                    else throw runtime_error("Could not connect to master server: " + to_string(message_kind));
                }
                else if (message_kind == QUEUED) // Si está encolado, sigue esperando y se especifica el lugar en la cola de espera.
                {
                    cout << "Lo sentimos. El servidor está completo en este momento. Se te ha puesto en cola." << endl;
                    int queue_pos = client_master->packet2queuePos(packet);
                    cout << "Tu posición en la cola es: #" << queue_pos << endl;
                }
            } while (message_kind != ACCEPTED);
            client_master->packet2acceptedIp(packet, ip_addr, port);
            break;
        }
        // Si no se puede conectar al servidor
        catch(...){
            cout << COUT_RED_BOLD << "Could not connect to master server: " << ips[i] << ":" << ports[i] << COUT_NOCOLOR << endl;
        }
    }
    // Si no ha sido posible conectarse con ningún servidor...
    if(i == ips.size()){
        cout << COUT_RED_BOLD << "No se ha podido conectar a ningún servidor. Avisa a tus profesores cuanto antes." << COUT_NOCOLOR << endl;
    }
}

/**
 * @brief Función auxiliar que lee los ninjas disponibles para ser ninjas.
 * Devuelve las ips de los ninjas.
 * 
 * @param file_name 
 * @return vector<string> 
 */
vector<string> readAllowedNinjas(string file_name){
    // Leer el fichero. Cada línea contiene un string con la dirección ip. Se añade cada línea al vector devuelto.
    vector<string> ips;
    ifstream file(file_name);
    string line;
    while (getline(file, line))
    {
        ips.push_back(line);
    }
    file.close();
    return ips;
}



int main(int argc, char const *argv[]){
    // Initialize the random number generator
    srand(428);

    // Definimos los valors por defecto:
    // Tipos de los jugadores
    string type_j1 = "GUI", type_j2 = "GUI";
    // IDs de los jugadores 
    int id_j1 = 0, id_j2 = 0;
    // Puerto 
    int port = 8888;
    // IP localhost
    string ip = "localhost";
    // Nombres de los jugadores
    string name_j1 = "J1", name_j2 = "J2";
    // Variables booleanas para controlar el tipo de partida.
    bool gui = true;
    bool server = false;
    bool ninja_server = false;
    bool master_server = false;

    bool random = false;
    bool privateroom = false;

    // Configuración inicial del juego
    BoardConfig config = BoardConfig::GROUPED;

    /* Parse the command line arguments in the following way:
     * --p1 <type=GUI|AI|Remote|Ninja> (id=0) (name=J1)
     * --p2 <type=GUI|AI|Remote|Ninja> (id=0) (name=J2)
     * --ip <ip>  [Optional]
     * --port <port>  [Optional]
     * --board <config=GROUPED>
     * --no-gui  [Optional]
     * --server  [Optional]
     * --ninja-server [Optional]
     * --random <type=GUI|AI> (id=0) (name=myName)
     * --private <room_name> <type=GUI|AI> (id=0) (name=myName)
     *
     * Default parameters:
     * --p1 GUI 0 J1 --p2 GUI 0 J2 
     */
    for(int i = 1; i < argc; i++){
        // Capturo el tipo, id y nombre del jugador 1
        if(strcmp(argv[i], "--p1") == 0){
            i++;
            type_j1 = argv[i];
            i++;
            id_j1 = atoi(argv[i]);
            i++;
            name_j1 = argv[i];
        }
        // Capturo el tipo, id y nombre del jugador 2
        else if(strcmp(argv[i], "--p2") == 0){
            i++;
            type_j2 = argv[i];
            i++;
            id_j2 = atoi(argv[i]);
            i++;
            name_j2 = argv[i];
        }
        // Capturo la ip
        else if(strcmp(argv[i], "--ip") == 0){
            i++;
            ip = argv[i];
        }
        // Capturo el puerto
        else if(strcmp(argv[i], "--port") == 0){
            i++;
            port = atoi(argv[i]);
        }
        // Capturo la configuración inicial
        else if(strcmp(argv[i], "--board") == 0){
            i++;
            if(strcmp(argv[i], "GROUPED") == 0){
                config = BoardConfig::GROUPED;
            }
            if(strcmp(argv[i], "ALTERNED") == 0){
                config = BoardConfig::ALTERNED;
            }
        }
        // Capturo si se quiere ejecutar sin GUI
        else if(strcmp(argv[i], "--no-gui") == 0){
            gui = false;
        }
        // Capturo tipo, id y nombre del servidor
        else if(strcmp(argv[i], "--server") == 0){
            server = true;
            i++;
            type_j1 = argv[i];
            i++;
            id_j1 = atoi(argv[i]);
            i++;
            name_j1 = argv[i];
        }
        // Capturo si se quiere jugar contra un ninja
        else if(strcmp(argv[i], "--ninja-server") == 0){
            ninja_server = true;
        }
        // Capturo si se quiere acceder a un servidor master
        else if(strcmp(argv[i], "--master") == 0){
            master_server = true;
        }
        // Capturo si se quiere jugar al emparejamiento "aleatorio"
        else if(strcmp(argv[i], "--random") == 0){
            random = true;
            i++;
            type_j1 = argv[i];
            i++;
            id_j1 = atoi(argv[i]);
            i++;
            name_j1 = argv[i];
        }
        // Capturo si se quiere jugar en una sala privada.
        else if(strcmp(argv[i], "--private") == 0){
            privateroom = true;
            i++;
            ip = argv[i]; //Ip stores the room name in this mode.
            i++;
            type_j2 = argv[i];
            i++;
            id_j2 = atoi(argv[i]);
            i++;
            name_j2 = argv[i];
            i++;
        }
        // Si los argumentos no son correctos....
        else{
            cout << "Error parsing command line arguments" << endl;
            cout << "Usage: " << argv[0] << " --p1 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J1) --p2 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J2) --ip <ip>  [Optional] --port <port>  [Optional] --board <config=GROUPED> --no-gui  [Optional]" << endl;
            return -1;
        }
    }

    if(argc == 1){
        // Si no se pasan argumentos se crea la ventana para la selección de modo de juego, que se encargará de asignar los parámetros del juego a las variables.
        cout << "No se pasaron argumentos, mostrando ventana de selección de juego..." << endl;
        GameSelector game_selector;
        game_selector.run();

        // Capturo todos los parámetros de lo seleccionado en la interfaz.
        GameParameters params = game_selector.getGameParameters();
        type_j1 = params.type_j1;
        id_j1 = params.id_j1;
        name_j1 = params.name_j1;
        type_j2 = params.type_j2;
        id_j2 = params.id_j2;
        name_j2 = params.name_j2;
        ip = params.ip;
        port = params.port;
        config = params.config;
        gui = params.gui;
        server = params.server;
        ninja_server = params.ninja_server;
        random = params.random;
        privateroom = params.private_room;
    }

    // Make type_j1 and type_j2 uppercase.
    transform(type_j1.begin(), type_j1.end(), type_j1.begin(), ::toupper);
    transform(type_j2.begin(), type_j2.end(), type_j2.begin(), ::toupper);

    bool is_remote = (type_j1 == "REMOTE" || type_j1 == "SERVER" || type_j1 == "NINJA") or (type_j2 == "REMOTE" || type_j2 == "SERVER" || type_j2 == "NINJA");

    // Thanks Mario ;)
    shared_ptr<Player> p1, p2;

    if(master_server){
        MasterServer master_server(port);
        // Leo las máquinas que están autorizaas para ser ninjas e inicializo el servidor.
        vector<string> ips = readAllowedNinjas(ALLOWED_NINJAS_FILE);
        for(string ip : ips){
            master_server.addAllowedNinja(ip);
        }
        master_server.startServer();
    }
    else if(ninja_server){
        // Leo MY_PUBLIC_IP_FILE y cojoel primer string (ip_address)
        ifstream file(MY_PUBLIC_IP_FILE);
        string my_ip;
        file >> my_ip;
        file.close();
        // Inicializo un servidor ninja en my_ip
        NinjaServer server(port, my_ip);
        vector<string> ips;
        vector<int> ports;
        // Leo las máquinas autorizadas para ser master
        readAllowedMasters(MASTER_ADDRESSES_FILE, ips, ports);
        for(int i = 0; i < ips.size(); i = (i+1)%ips.size()){
            server.setMaster(ips[i], ports[i]);
            try{
                server.startServer();
                cout << COUT_RED_BOLD << "Cortado servidor ninja" << COUT_NOCOLOR << endl;
            }
            catch(...){
                cout << COUT_RED_BOLD << "No se pudo contactar con el master en " << ips[i] << ":" << ports[i] << COUT_NOCOLOR << endl;
            }
        }
        
    }
    // Si soy servidor
    else if(server){
        // Escucho en el puerto fijado
        TcpListener listener;
        if(listener.listen(port) != Socket::Done){
            throw runtime_error("Could not listen to port");
        }
        cout << "Listening on port " << port << endl;
        // Inicializo un servidor de Parchis
        shared_ptr<ParchisServer> server = make_shared<ParchisServer>();
        server->acceptConnection(listener);
        Packet packet;
        MessageKind message_kind;
        // Espero recibir los parámetros de juego por parte del cliente
        do{
            message_kind = server->receive(packet);
            sleep(milliseconds(10));
        }while(message_kind != GAME_PARAMETERS);

        // Inicializo los parámetros según lo recibido
        int player;
        string name;
        BoardConfig init_board;
        int ai_id; // Ignorado por el server, lo elige él mismo su id.
        server->packet2gameParameters(packet, player, name, init_board, ai_id);

        type_j2 = "REMOTE";

        // Si player == 0, el J1 es remoto
        if (player == 0){
            //J1 remoto.
            p1 = make_shared<RemotePlayer>(name, server); 
            server->sendOKStartGame(p1->getName());

            // Inicializo p2 según los parámetros elegidos por mi
            if(type_j1 == "GUI"){
                p2 = make_shared<GUIPlayer>(name_j1, id_j1);
            }
            else if(type_j1 == "AI"){
                p2 = make_shared<AIPlayer>(name_j1, id_j1);
            }        
        }
        // Si player == 1, el J2 es remoto
        else{
            p2 = make_shared<RemotePlayer>(name, server);
            server->sendOKStartGame(p2->getName());

            // Inicializo a p1 según los parámetros elegidos por mi
            if(type_j1 == "GUI"){
                p1 = make_shared<GUIPlayer>(name_j1, id_j1);
            }
            else if(type_j1 == "AI"){
                p1 = make_shared<AIPlayer>(name_j1, id_j1);
            }
        }
    }
    else if(random || privateroom){
        string ip_ninja;
        int port_ninja;

        // Se establece conexión con el ninja
        if(random){
            clientMasterHandshake(ip_ninja, port_ninja, {"randomgame"});
        }
        else{
            clientMasterHandshake(ip_ninja, port_ninja, {"privateroom", ip});
        }
        shared_ptr<ParchisClient> client = make_shared<ParchisClient>();
        client->startClientConnection(ip_ninja, port_ninja);

        if(random){
            client->sendRandomGame(name_j1);
        }
        else{
            client->sendPrivateGame(ip, name_j1);
        }
        Packet packet;
        MessageKind msg;
        int my_player;
        string rival_name;

        type_j2 = "Remote";
        do{
            msg = client->receive(packet);
            if(msg == WAITING_FOR_PLAYERS){
                cout << "Esperando jugadores..." << endl;
            }
            else if(msg == OK_RANDOM_PRIVATE_START){
                client->packet2OKRandomPrivateStart(packet, my_player, rival_name, config);
                cout << "Listos para jugar!" << endl;
                cout << "Soy el jugador " << my_player << endl;
            }
            else if(msg == TEST_ALIVE){
            }
            else if(msg == ERR_FULL_ROOM){
                string msg = client->packet2errorMessage(packet);
                cout << COUT_RED_BOLD << "Error: " << msg << COUT_NOCOLOR << endl;
            }
            else{
                throw runtime_error("Error al iniciar el juego. Esto no debería haber pasado.");
            }
        }while(msg != OK_RANDOM_PRIVATE_START);

        if(my_player == 0){
            if(type_j1 == "GUI"){
                p1 = make_shared<GUIPlayer>(name_j1, id_j1);
            }
            else if(type_j1 == "AI"){
                p1 = make_shared<AIPlayer>(name_j1, id_j1);
            }
            p2 = make_shared<RemotePlayer>(rival_name, client);
        }
        else{
            if(type_j1 == "GUI"){
                p2 = make_shared<GUIPlayer>(name_j1, id_j1);
            }
            else if(type_j1 == "AI"){
                p2 = make_shared<AIPlayer>(name_j1, id_j1);
            }
            p1 = make_shared<RemotePlayer>(rival_name, client);
        }
    }
    else{
        if(type_j1 == "GUI"){ // Inicializo jugador 1 GUI
            p1 = make_shared<GUIPlayer>(name_j1, id_j1);
        }
        else if(type_j1 == "AI"){ // Inicializo jugador 1 AI
            p1 = make_shared<AIPlayer>(name_j1, id_j1);
        }
        else if(type_j1 == "REMOTE"){ // Inicializo j1 a cliente remoto
            shared_ptr<ParchisClient> client= make_shared<ParchisClient>();
            // Comienzo la conexión al puerto e ip especificadas.
            client->startClientConnection(ip, port);
            // Mando los parámetros del juego
            client->sendGameParameters(1, name_j2, config);
            Packet packet;
            MessageKind msg = client->receive(packet);
            if(msg != OK_START_GAME){
                throw runtime_error("Error al iniciar juego. Esto no debería haber pasado.");
            }
            string remote_name = client->packet2message(packet);
            p1 = make_shared<RemotePlayer>(remote_name, client);
        }
        else if(type_j1 == "NINJA"){ // El j1 es ninja
            string ip_ninja;
            int port_ninja;
            // Se establece conexión con el ninja
            clientMasterHandshake(ip_ninja, port_ninja, {"ninjagame"});
            shared_ptr<ParchisClient> client = make_shared<ParchisClient>();
            // Se conecta al servidor de ninjas establecido
            client->startClientConnection(ip_ninja, port_ninja);
            // Le manda los parámetros del juego
            client->sendGameParameters(1, name_j2, config, id_j1);
            Packet packet;
            MessageKind msg = client->receive(packet);
            if (msg != OK_START_GAME)
            {
                throw runtime_error("Error al iniciar juego. Esto no debería haber pasado.");
            }
            string remote_name = client->packet2message(packet);
            p1 = make_shared<RemotePlayer>(remote_name, client);
        }


        if(type_j2 == "GUI"){ // Inicializo el jugador 2 GUI
            p2 = make_shared<GUIPlayer>(name_j2, id_j2);
        }
        else if(type_j2 == "AI"){ // Inicializo el jugador 2 AI
            p2 = make_shared<AIPlayer>(name_j2, id_j2);
        }
        else if(type_j2 == "REMOTE"){ // Inicializo j2 a cliente remoto
            shared_ptr<ParchisClient> client= make_shared<ParchisClient>();
            // Comienzo la conexión al puerto e ip especificadas.
            client->startClientConnection(ip, port);
            // Mando los parámetros del juego
            client->sendGameParameters(0, name_j1, GROUPED);
            Packet packet;
            MessageKind msg = client->receive(packet);
            if (msg != OK_START_GAME)
            {
                throw runtime_error("Error al iniciar juego. Esto no debería haber pasado.");
            }
            string remote_name = client->packet2message(packet);
            p2 = make_shared<RemotePlayer>(remote_name, client);
        }
        else if (type_j2 == "NINJA") // El j1 es ninja
        {
            string ip_ninja;
            int port_ninja;
            // Se establece conexión con el ninja
            clientMasterHandshake(ip_ninja, port_ninja, {"ninjagame"});
            shared_ptr<ParchisClient> client = make_shared<ParchisClient>();
            // Se conecta al servidor de ninjas que establezcamos
            client->startClientConnection(ip_ninja, port_ninja);
            client->sendGameParameters(0, name_j1, config, id_j2);
            Packet packet;
            MessageKind msg = client->receive(packet);
            if (msg != OK_START_GAME)
            {
                throw runtime_error("Error al iniciar juego. Esto no debería haber pasado.");
            }
            string remote_name = client->packet2message(packet);
            p2 = make_shared<RemotePlayer>(remote_name, client);
        }
    }

    // Una vez creados los jugadores, se crea el objeto parchís con la configuración incial establecida.
    Parchis parchis(config, p1, p2);
    
    // Si jugamos con interfaz...
    if(gui){
        // Se crea la interfaz y se le asigna al jugador que sea GUI
        ParchisGUI parchis_gui(parchis);
        shared_ptr<GUIPlayer> gui_p1 = dynamic_pointer_cast<GUIPlayer>(p1);
        if(gui_p1){
            gui_p1->setGUI(parchis_gui);
        }
        shared_ptr<GUIPlayer> gui_p2 = dynamic_pointer_cast<GUIPlayer>(p2);
        if(gui_p2){
            gui_p2->setGUI(parchis_gui);
        }
        // Si ninguno de los 2 es GUI, se crea un viewer al cual se le asigna la interfaz.
        if(type_j1 != "GUI" && type_j2 != "GUI"){
            shared_ptr<GUIPlayer> viewer = make_shared<GUIPlayer>("Viewer");  
            viewer->setGUI(parchis_gui);
            parchis.addViewer(viewer); 
        }
        // Se inicia
        parchis_gui.run();
    }
    // Si no hay interfaz, directamente se lanza el juego
    else{
        parchis.gameLoop();
    }



    return 0;

   
}