
#include "servicebase/Process.h"
#include "diagd.h"

int main() {

    nesat::Process process;
    nutshell::DiagD::instantiate();
    process.run();


    return 0;
}
