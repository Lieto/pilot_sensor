#include <iostream>
#include "Application.h"

int DetectedPerson::m_idCounter = 0;


int main(int argc, char** argv) {

    Application *app = new Application(argc, argv);

    if (!app->Init())
        return false;

    // Run detector
    app->Run();

    delete app;
    app = NULL;

    return 0;
}