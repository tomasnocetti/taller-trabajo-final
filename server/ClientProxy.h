#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "ClientProxy.h"
#include <memory>
#include <atomic>
#include "../DataDefinitions.h"
#include "../common/BlockingQueue.h"
#include "../common/Thread.h"
#include "instructions/Instruction.h"

class Instruction;
class ClientProxyRead;
class ClientProxy;

using InstructionDataBQ = BlockingQueue<std::unique_ptr<Instruction>>;
using UpdateClientsBQ = FixedBlockingQueue<PlayerGameModelData>;


/**
   * @brief Maneja las instrucciones que vienen del Cliente.
   * Socket.read
*/
class ClientProxyRead: public Thread {
  public:
    explicit ClientProxyRead(ClientProxy& client);
    void run() override;

  private:
    ClientProxy& client;
    void handleInstruction(InstructionData& instruction);
};

class ClientProxy {
  private:
    std::atomic<bool> running;
    std::atomic<size_t> playerId;
    ClientProxyRead readProxy;
    InstructionDataBQ &instructionQueue;
    UpdateClientsBQ clientBQ;
    friend ClientProxyRead;
  public:
    explicit ClientProxy(InstructionDataBQ &instructionQueue);
    ~ClientProxy();
    ClientProxy(const ClientProxy&) = delete;
    ClientProxy& operator=(const ClientProxy&) = delete;
    void start();
    /**
     * @brief Maneja la escritura de informacion que va hacia del Cliente.
     * Socket.write
     */
    void setPlayerId(size_t id);
    UpdateClientsBQ& getUpdateBQ();
    void stopPlaying();
};

#endif
