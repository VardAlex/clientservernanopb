#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include "pb_decode.h"
#include "msg.pb.h"

int main() {
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(listening, (sockaddr *) &hint, sizeof(hint));

    listen(listening, 1);

    int clientSocket = accept(listening, NULL, NULL);
    close(listening);

    SimpleMessage message = SimpleMessage_init_zero;
    uint8_t buffer[128];
    int bytesRecv = recv(clientSocket, &buffer, sizeof(buffer), 0);

    pb_istream_t stream = pb_istream_from_buffer(buffer, bytesRecv);
    pb_decode(&stream, SimpleMessage_fields, &message);

    std::cout << message.number << " " << message.message << std::endl;

    close(clientSocket);
    return 0;
}