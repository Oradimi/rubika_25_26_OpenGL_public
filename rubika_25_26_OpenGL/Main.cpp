#include "Application.h"

int main(int argc, char *args[])
{
    Application app;

    app.Setup();
    app.Init();

    while (app.IsRunning())
    {
        app.Input();
        app.Update();
        app.Render();
    }

    app.Destroy();
    
    return 0;
}