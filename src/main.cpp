#include "unlibc++/calls.hpp"

int main(int argc, char* argv[]) {
    low::write(1, "Hi mum\n", 7);
    return 0;
}
