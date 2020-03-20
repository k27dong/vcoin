#include "../include/chain.h"

void adder(int s);
Chain *c = new Chain();

int main(void) {
  adder(100);
  std::cout << c->get_size();
}

void adder(int s) {
  for (int i = 0; i < s; i++) {
    c->generate_next_block("hakla");
  }
}