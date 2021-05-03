#include <iostream>

#include "random.h"
#include "utils.h"
#include "args.h"
#include "randomgraphs.h"

int main(int argc, char **argv) {
    auto rnd = Random(13);

    auto gen = RandomGraphGenerator(rnd, 10, 20, 500);

    

    return 0;
}
