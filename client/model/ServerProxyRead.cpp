#include "ServerProxyRead.h"
#include <iostream>

ServerProxyRead::ServerProxyRead(BlockingQueueRead &readBQ) : 
  readBQ(readBQ), continueReading(true){}

ServerProxyRead::~ServerProxyRead(){}

void ServerProxyRead::run(){
  while (continueReading){
    continueReading = false;
    // keep reading
    /* si me viene un modelo que dice que desapareci, 
    dejo de leer y cierro. */
  }
}
