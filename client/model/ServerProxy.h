#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include <string>
#include <vector>
#include <atomic>
#include "Response.h"
#include "../../common/BlockingQueue.h"
#include "../../common/Thread.h"
#include "../../common/common_socket.h"

using BlockingQueueWrite = BlockingQueue<InstructionData>;

class Socket;
class ServerProxy;

class ServerProxyRead : public Thread {
  public:
    explicit ServerProxyRead(ServerProxy &server);
    ServerProxyRead(const ServerProxyRead&) = delete;
    ServerProxyRead& operator=(const ServerProxyRead&) = delete;
    void run();
    void handleResponse();
  private:
    ServerProxy &server;
};

class ServerProxyWrite : public Thread {
  public:
    ServerProxyWrite(ServerProxy &server, BlockingQueueWrite &readBQ);
    ServerProxyWrite(const ServerProxyWrite&) = delete;
    ServerProxyWrite& operator=(const ServerProxyWrite&) = delete;
    void run();
    std::stringstream packInstruction(InstructionData &instruction);
    void sendInstruction(std::stringstream &buffer);

  private:
    ServerProxy &server;
    BlockingQueueWrite &writeBQ;
};

class ServerProxy{
  public:
    ServerProxy(std::string& host, std::string& port);
    ServerProxy(const ServerProxy&) = delete;
    ServerProxy& operator=(const ServerProxy&) = delete;
    ServerProxy&& operator=(ServerProxy&& other);
    void init();
    void update();
    bool isAuthenticated() const;
    bool isInCreationMode() const;
    bool isMapSet() const;

    /** Client ACTIONS */
    void authentificate(std::string& alias, std::string& password);
    void setInCreationMode();
    void move(int xDir, int yDir);
    void attack(int xPos, int yPos);
    void equip(int inventoryPosition);
    void resurrect();
    void meditate();
    void throwObject(std::string inventoryPosition);
    void pickUp();
    void list();
    void buy(std::string itemNumber);
    void sell(std::string itemNumber);
    void heal();
    void depositGold(std::string amount);
    void depositItem(std::string inventoryPos);
    void withDrawGold(std::string amount);
    void withDrawItem(std::string inventoryPos);
    void createPlayer(
      std::string nick, 
      std::string password, 
      std::string race,
      std::string typeClass);
    void sendMessageToPlayer(std::string nick, std::string message);
    
    /** Client GETTERS */
    const MapData& getMapData() const;
    const MainPlayerData& getMainPlayerData() const;
    const std::vector<EnemyData>& getNPCData() const;
    const std::vector<OtherPlayersData>& getOtherPlayersData() const;
    const std::vector<DropItemData>& getDrops() const;

    /** Server SETTERS */
    void setGameModelData(PlayerGameModelData &gameModelData);
    void setMapData(MapData& map);
    void close();

  private:
    friend class ServerProxyWrite;
    friend class ServerProxyRead;
    std::atomic<bool> running;
    std::atomic<bool> authentificated;
    std::atomic<bool> creationMode;
    bool mapSet = false;
    MapData map;
    MainPlayerData mainPlayer;
    std::vector<EnemyData> npcs;
    std::vector<OtherPlayersData> otherPlayers;
    std::vector<DropItemData> drops;
    BlockingQueueWrite writeBQ;
    ResponseQ readBQ;
    /** IMPORTANTE **/
    /** El orden en estos items es muy importante.
     * Necesitamos que se destruya primero el socket y luego los threads
     * sino quedaran joineando infinitamente en los destructores **/
    ServerProxyWrite serverProxyWrite;
    ServerProxyRead serverProxyRead;
    Socket socket;
    /** -------- **/
    ResponseQ responseQ;
};

#endif
