#define _POSIX_C_SOURCE 201112L
#define ERROR -1
#define SUCCESS 0
#define PARTIAL_SUCCESS 1
#define LISTEN_BACKLOG 50

#include "common_socket.h"
#include "stdio.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "stdlib.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <system_error>

#define check_error(res, err, err_code, err_msg) \
  if ((res) == (err)) { \
    throw std::system_error( \
      std::error_code(err_code, std::system_category()), \
      err_msg); \
    }

#define check_success(res, suc, err_code, err_msg) \
  if ((res) != (suc)) { \
    throw std::system_error( \
      std::error_code((err_code), std::system_category()), \
      (err_msg)); \
    }

Socket::Socket() {
  fd = socket(AF_INET, SOCK_STREAM, 0);
  check_error(fd, -1, errno, "Socket creation error");
}

Socket::Socket(int fd) : fd(fd) {
  check_error(fd, -1, errno, "Socket creation error here");
}

Socket::Socket(Socket&& other) {
  this->fd = other.fd;
  other.fd = -1;
}

Socket::~Socket() {
  this->close();
}

void Socket::bind_and_listen(const char* service) {
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int res;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;    /* Allow IPv4 */
  hints.ai_socktype = SOCK_STREAM; /* TCP socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  res = getaddrinfo(NULL, service, &hints, &result);
  check_success(res, 0, 0, gai_strerror(res));

  int flag = 1;
  check_error(
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)),
    -1, 0, "Socket could not set options");

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    if (::bind(fd, result->ai_addr, result->ai_addrlen) != -1) break;
  }

  freeaddrinfo(result);
  check_error(rp, NULL, 0, "Socket could not bind to host");


  res = listen(fd, LISTEN_BACKLOG);
  check_error(res, -1, 0, "Socket could not listen");
}

Socket Socket::accept() {
  int ac_fd = ::accept(
    fd,
    NULL,
    NULL);
  check_error(ac_fd, -1, errno, "Socket could not be accepted");
  return Socket(ac_fd);
}

void Socket::connect(const char* host_name, const char* service) {
  struct addrinfo hints, *result, *rp;
  int res;

  /* Obtain address(es) matching host/port */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;    /* Allow IPv4 */
  hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
  hints.ai_flags = 0;
  hints.ai_protocol = 0;          /* Any protocol */

  res = getaddrinfo(host_name, service, &hints, &result);
  check_success(res, 0, 0, gai_strerror(res));

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    if (::connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) break;
  }

  check_error(rp, NULL, 0, "Socket could not connect to host");
  freeaddrinfo(result);
}

void Socket::send(const char* buffer, size_t length) {
  size_t sent_length = 0;
  int res;

  while (sent_length < length){
    res = write(fd, &buffer[sent_length], length - sent_length);

    check_error(res, -1, errno, "Socket send message error");
    sent_length += res;
  }
}

bool Socket::receive(char* buffer, size_t length) {
  size_t read_length = 0;
  int res;

  while (read_length < length){
    res = read(fd, &buffer[read_length], length - read_length);

    if (res == 0) {
      if (read_length > 0) {
        buffer[read_length + 1] = EOF;
        return true;
      } else {
        return false;
      }
    }

    check_error(res, -1, errno, "Socket receive message error");
    read_length += res;
  }
  return true;
}

void Socket::shutdown() {
  if (fd == -1) return;
  ::shutdown(fd, SHUT_RDWR);
}

void Socket::close() {
  if (fd == -1) return;
  ::close(fd);
  fd = -1;
}
