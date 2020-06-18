#include "ServerProxyWrite.h"
#include <iostream>
#include <string>
#include <sstream>
#include <syslog.h>

ServerProxyWrite::ServerProxyWrite(ServerProxy& server, 
BlockingQueueWrite &writeBQ): 
  continuePlaying(true),
  server(server),
  writeBQ(writeBQ) {}

ServerProxyWrite::~ServerProxyWrite(){}

void ServerProxyWrite::run(){  
  try{
    while (continuePlaying){
      InstructionData instructionToSend;

      getInstruction(instructionToSend);
      std::stringstream buffer = packInstruction(instructionToSend);
      sendInstruction(buffer);

      /* Código para mockear */
      std::string str(buffer.str());
      msgpack::object_handle oh =
        msgpack::unpack(str.data(), str.size());
      msgpack::object deserialized = oh.get();
      std::cout << deserialized << std::endl;
    }
  } catch(const std::system_error& e) {
    /** This error codes gey by-passed. In Linux when a blocking socket.accept
     * is being called and the bind socket get's closed an errno is thrown with
     * EINVAL. This is common logic so it shouldn't be handled as an error.
    */
    if (e.code().value() != ECONNABORTED && e.code().value() != EINVAL) {
      syslog(
        LOG_CRIT,
        "[Crit] Error!: \n Error Code: %i \n Message: %s",
        e.code().value(), e.what());
    }
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
  }  
}

void ServerProxyWrite::close(){
  continuePlaying = false;
}

void ServerProxyWrite::getInstruction(InstructionData &instruction){
  writeBQ.try_front_pop(instruction);
}

std::stringstream ServerProxyWrite::packInstruction(InstructionData 
  &instruction){
  std::stringstream buffer;
  msgpack::pack(buffer, instruction);
  return std::move(buffer);
}

void ServerProxyWrite::sendInstruction(std::stringstream &buffer){  
  std::string str(buffer.str());
  
  uint32_t length = to_big_end<uint32_t>(str.length());

  str.insert(0, (char *) &length, 4);

  server.socket.send(str.c_str(), str.length());
}
