#include "app.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    engine::App app {};

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}