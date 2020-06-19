#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <memory>
#include "../../common/BlockingQueue.h"
#include "../../DataDefinitions.h"

class Response;
using ResponseBQ = BlockingQueue<std::unique_ptr<Response>>;

class Response {
  public:
    Response() = default;
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;
    Response&& operator=(Response&& other) = delete;
    virtual std::string pack() = 0;
    virtual ~Response() = default;
  protected:
    ResponseTypeT type;
};

class PlayerGameResponse: public Response {
  public:
    PlayerGameResponse(PlayerGameModelData model);
    PlayerGameResponse(const PlayerGameResponse&) = delete;
    PlayerGameResponse& operator=(const PlayerGameResponse&) = delete;
    PlayerGameResponse&& operator=(PlayerGameResponse&& other) = delete;
    std::string pack() override;
  private:
    PlayerGameModelData model;
};


#endif
