#include "Application.h"
#include <memory>

int main(int argc, char** argv)
{
    std::unique_ptr<Application> app = std::make_unique<Application>();
    app->Execute();
    return 0;
}


