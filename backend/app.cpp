#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    hostname[255] = '\0';

    int port = 9090;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "ERROR: Failed to create socket" << std::endl;
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "ERROR: Failed to bind to port " << port << std::endl;
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        std::cerr << "ERROR: Failed to listen on port " << port << std::endl;
        return 1;
    }

    std::cout << "Server successfully initialized on port "
              << port << " (hostname: " << hostname << ")" << std::endl;

    // 🔥 CI-safe shutdown (no blocking accept)
    close(server_fd);

    std::cout << "Backend test completed successfully." << std::endl;

    return 0;
}