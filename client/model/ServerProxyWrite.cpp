#include "ServerProxy.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../../common/common_utils.h"

ServerProxyWrite::ServerProxyWrite(ServerProxy& server,
BlockingQueueWrite &writeBQ):
  server(server),
  writeBQ(writeBQ) {}

void ServerProxyWrite::run(){
  try{
    while (server.running){
      InstructionData instructionToSend;

      bool succcess = writeBQ.try_front_pop(instructionToSend);
      if (!succcess) return;

      std::stringstream buffer = packInstruction(instructionToSend);
      sendInstruction(buffer);
    }
  } catch(const std::system_error& e) {
    /** This error codes gey by-passed. In Linux when a blocking socket.accept
     * is being called and the bind socket get's closed an errno is thrown with
     * EINVAL. This is common logic so it shouldn't be handled as an error.
    */
      if (server.running == false && e.code().value() == EBADF) return;
    std::cerr << "Error ServerProxy WRITE: \n" <<
      " Codigo: " << e.code().value() <<
      " Error: " << e.what() << std::endl;
  } catch(const std::exception& e) {
    std::cerr << "Error en ServerProxy WRITE: \n" <<
      " Error: " << e.what() << std::endl;
  } catch(...) {
    std::cerr << "Error en ClientProxy WRITE: \n" <<
      " Error Invalido" << std::endl;
  }
}

std::stringstream ServerProxyWrite::packInstruction(InstructionData
  &instruction){
  std::stringstream buffer;
  msgpack::pack(buffer, instruction);
  return buffer;
}

void ServerProxyWrite::sendInstruction(std::stringstream &buffer){
  std::string str(buffer.str());

  size_t length = to_big_end<uint32_t>(str.length());
  str.insert(0, (char *) &length, 4);
  
  server.socket.send(str.c_str(), str.length());
}
