#ifndef SOCKET_H
#define SOCKET_H

#include <cstddef>

/**
 * @brief Socket Proxy class.
 */
class Socket {
  public:
    Socket();
    Socket(const Socket&) = delete;
    Socket(Socket&& other);
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&& other);
    /**
     * @brief Meant for server side. This method will resolve service and
     * establish a socket binding connection ready to listen for
     * incoming requests.
     * Throws std::system_error if failure.
     */
    void bind_and_listen(const char* service);
    /**
     * @brief Accept incoming connection requests and return peer_socket.
     * Blocking function until valid connection available.
     * @param self Properly binded and listen socket.
     * Throws std::system_error if failure.
    */
    Socket accept();
    /**
     * @brief Meant for client side. This method will resolve dns and
     * service to establish a valid connection.
     * Blocking function.
     * Throws std::system_error if failure.
    */
    void connect(const char* host_name, const char* service);
    /**
     * @brief Will end RD-RW full-duplex connections.
     */
    void shutdown();
    /**
     * @brief This function will handle inner communication from the socket.
     * A buffer will provide data to the network until length provided is
     * reached.
     * Throws std::system_error if failure.
     */
    void send(const char* buffer, size_t length);
    /**
     * @brief This function will handle inner communication from the socket.
     * A buffer will store data comming from network unitl length provided is reached.
     * If length is not reached then EOF will be placed after the last byte recv.
     * @return true - connection is open. false - connection is closed.
    */
    bool receive(char* buffer, size_t length);
    /**
     * @brief Checks if socket closed.
     * Close socket connection RD/RW. Free resources.
    */
    void close();
    /**
     * @brief Destructor will call this->close().
    */
    ~Socket();

  private:
    /** Constructor meant for Accept. Optimization mandatory by compiler,
     * no reason to move/copy.
     * https://en.cppreference.com/w/cpp/language/copy_elision **/
    explicit Socket(int fd);
    int fd;
};

#endif
