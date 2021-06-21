#include "Application.h"


int main() {
    Application::GetInstance().Start();
    Application::DeleteInstance();
    return 0;
}
