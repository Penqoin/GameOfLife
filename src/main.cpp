#include "Application.hpp"
int main (int argc, char *argv[]) {
    engine::Application* app = new engine::Application();
    app->run();

    return 0;
}
