#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include <string>
#include <memory>
#include "../../common/Queue.h"
#include "../../DataDefinitions.h"

class ServerProxy;
class Response;
using ResponseQ = Queue<std::unique_ptr<Response>>;

#include "ServerProxy.h"

class Response {
  public:
    explicit Response(ResponseTypeT type) : type(type) {}
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;
    Response&& operator=(Response&& other) = delete;
    virtual void run(ServerProxy& server) = 0;
    virtual ~Response() = default;
  protected:
    ResponseTypeT type;
};

class PlayerGameResponse: public Response {
  public:
    explicit PlayerGameResponse(std::string buffer);
    PlayerGameResponse(const PlayerGameResponse&) = delete;
    PlayerGameResponse& operator=(const PlayerGameResponse&) = delete;
    PlayerGameResponse&& operator=(PlayerGameResponse&& other) = delete;
    void run(ServerProxy& server) override;
  private:
    PlayerGameModelData model;
};


#endif
