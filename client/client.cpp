#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "pb_encode.h"
#include "msg.pb.h"

int main()
{
    int client = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    // connecting to "server" using "client" socket
    connect(client,(sockaddr *) &server,sizeof(server));

    uint8_t buffer[128];
    size_t message_length;
    bool status;

    SimpleMessage message = SimpleMessage_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    message.number = 13;
    strcpy(message.message, "hello");

    status = pb_encode(&stream, SimpleMessage_fields, &message);
    message_length = stream.bytes_written;
    send(client, &buffer, message_length, 0);
    close(client);
    return 0;
}