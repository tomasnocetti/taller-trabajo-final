#include "BlockingQueue.h"

BlockingQueue::BlockingQueue() : isClosed(false){}

void BlockingQueue::push(InstructionData instruction){
    std::unique_lock<std::mutex> lk(this->m);
    queue.push(instruction);
    cv.notify_all();
}

InstructionData BlockingQueue::pop(){
    std::unique_lock<std::mutex> lk(this->m);
    while (queue.empty()){
        if (isClosed){
            break;
        }
        cv.wait(lk); // función bloqueante, evito Busy Wait
    }
    InstructionData instruction = queue.front(); 
    queue.pop(); // quito el próximo elemento de la queue
    return instruction;
}

void BlockingQueue::close(){
    std::unique_lock<std::mutex> lk(this->m);
    /*
    Cuando no haya mas nada por sacar, el consumidor debe saberlo, por eso
    lo despierto y le aviso.
    */
    isClosed = true;
    cv.notify_all();
}

BlockingQueue::~BlockingQueue(){}
