#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "ClientProxy.h"
#include <memory>
#include <atomic>
#include "../DataDefinitions.h"
#include "../common/Thread.h"
#include "instructions/Instruction.h"
#include "responses/Response.h"

class Instruction;
class ClientProxyRead;
class ClientProxy;

class ClientProxyWrite: public Thread {
  public:
    explicit ClientProxyWrite(ClientProxy& client);
    void run() override;

  private:
    ClientProxy& client;
    void handleInstruction(InstructionData& instruction);
    void sendResponse(std::unique_ptr<Response>);
};

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
    InstructionData getInstruction();
};

class ClientProxy {
  private:
    std::atomic<bool> running;
    std::atomic<bool> authenticated;
    std::atomic<size_t> playerId;
    ClientProxyRead readProxy;
    ClientProxyRead writeProxy;
    InstructionBQ &instructionQueue;
    ResponseBQ responseBQ;
    friend ClientProxyRead;
    friend ClientProxyWrite;
  public:
    explicit ClientProxy(InstructionBQ &instructionQueue);
    ~ClientProxy();
    ClientProxy(const ClientProxy&) = delete;
    ClientProxy& operator=(const ClientProxy&) = delete;
    void start();
    /**
     * @brief Maneja la escritura de informacion que va hacia del Cliente.
     * Socket.write
     */
    void setPlayerId(size_t id);
    ResponseBQ& getUpdateBQ();
    void stop();
};

#endif
