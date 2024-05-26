#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <cstring>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

void setNonCanonicalMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

bool kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

void readKeyPresses() {
    char buffer[1024];
    int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "You pressed: " << buffer << std::endl;

        // Check for specific keys in the buffer
        if (strchr(buffer, 27)) { // 27 is the ASCII code for the Esc key
            std::cout << "Escape is pressed. Exiting..." << std::endl;
            exit(0);
        }
        if (strchr(buffer, 'A')) {
            std::cout << "A is pressed" << std::endl;
        }
        if (strchr(buffer, 'B')) {
            std::cout << "B is pressed" << std::endl;
        }
    }
}

int main() {
    setNonCanonicalMode(true);
    std::cout << "Press any keys. Press 'Esc' to exit." << std::endl;

    while (true) {
        if (kbhit()) {
            readKeyPresses();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Add a small delay to avoid high CPU usage
    }

    setNonCanonicalMode(false);
    std::cout << "Exiting..." << std::endl;
    return 0;
}
