#include <iostream>
#include <string>
#include "board/board.h"

int main() {
    Board board;

    std::string line;

    board = Board();
    board.print(-1);
    // The UCI loop: we read one command per line from stdin and respond to stdout.
    // A GUI like Arena or Cute Chess launches your engine as a subprocess and
    // communicates exactly this way — plain text in, plain text out.
    while (std::getline(std::cin, line)) {
        if (line == "uci") {
            // The GUI asks: "do you speak UCI?"
            // We reply with our name/author and signal we're ready.
            std::cout << "id name MyEngine\n";
            std::cout << "id author YourName\n";
            std::cout << "uciok\n";
        } else if (line == "isready") {

            std::cout << "readyok\n";
        } else if (line == "ucinewgame") {

            board = Board();
        } else if (line.rfind("position", 0) == 0) {

        } else if (line.rfind("go", 0) == 0) {

            std::cout << "bestmove 0000\n"; // "0000" = null move, signals no move yet
        } else if (line == "quit") {
            // Clean exit — the GUI is shutting down.
            break;
        }
        std::cout.flush();
    }

    return 0;
}
