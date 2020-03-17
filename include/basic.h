#include <iostream>
#include <time.h>
#include <vector>

#include "../lib/PicoSHA2/picosha2.h"

using std::string;
using std::vector;
using std::to_string;
using picosha2::hash256_hex_string;

const int MAX_TRANSACTIONS_PER_BLOCK = 5;
const int MIN_TRANSACTIONS_AMOUNT = 1;
