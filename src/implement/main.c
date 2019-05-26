#include "./../headers/process.h"

/*  // Old version
int main(int argc, char **argv) {
    int run_result;

    if (allegro_init_work() < 0) {
        fprintf(stderr, "Error: Failed to load Allegro library");
        return -1;
    }

    run_result = engine_run();

    allegro_end_work();
    return run_result;
}
*/

int main(int argc, char **argv) {
    return proc_routine();
}
