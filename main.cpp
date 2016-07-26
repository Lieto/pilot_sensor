#include <iostream>
#include "Application.h"

Application *app;

int DetectedPerson::m_idCounter = 0;

void sighandler(int signum) {


    cout << "Interrupt signal(" << signum << ") received. \n";

    app->WriteResults();

    exit(signum);
}

int main(int argc, char** argv) {


    app = new Application(argc, argv);

    signal(SIGINT, sighandler);

    if (!app->Init())
        return false;

    // Run detector
    app->Run();

    delete app;
    app = NULL;

    return 0;
}