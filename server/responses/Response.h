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
    explicit Response(ResponseTypeT type) : type(type) {}
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;
    Response&& operator=(Response&& other) = delete;
    virtual std::string getModelPacked() = 0;
    virtual ~Response() = default;
  protected:
    ResponseTypeT type;
};

class PlayerGameResponse: public Response {
  public:
    explicit PlayerGameResponse(PlayerGameModelData model);
    PlayerGameResponse(const PlayerGameResponse&) = delete;
    PlayerGameResponse& operator=(const PlayerGameResponse&) = delete;
    PlayerGameResponse&& operator=(PlayerGameResponse&& other) = delete;
    std::string getModelPacked() override;
  private:
    std::string modelPacked;
};

class MapResponse: public Response {
  public:
    explicit MapResponse(MapData model);
    MapResponse(const MapResponse&) = delete;
    MapResponse& operator=(const MapResponse&) = delete;
    MapResponse&& operator=(MapResponse&& other) = delete;
    std::string getModelPacked() override;
  private:
    std::string modelPacked;
};


#endif
