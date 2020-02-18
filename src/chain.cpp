#include "../include/chain.h"

Chain::Chain() {
  this->genesis_block = new Block(
    0,
    "",
    NULL,
    NULL,
    "and it was so"
  );
}

Chain::~Chain() {
  delete this->genesis_block;
  this->genesis_block = nullptr;
}

Block Chain::get_latest_block() {
  return this->c.back();
}

Block* Chain::generate_next_block(string data) {
  Block prev_block = this->get_latest_block();
  unsigned int next_index = prev_block.get_index();
  time_t next_time = time(0);
  string next_hash = this->calculate_hash(next_index, prev_block.get_hash(), data, next_time);
  Block* new_block = new Block(next_index, next_hash, prev_block.get_hash(), next_time, data);
  return new_block;
}

string Chain::calculate_hash_for_block(Block b) {
  return this->calculate_hash(b.get_index(), b.get_previous_hash(), b.get_data(), b.get_time());
}

int Chain::is_valid_new_block(Block next, Block prev) {
  if (prev.get_index() + 1 != next.get_index()) {
    // invalid index
    return 0;
  }
  if (prev.get_hash() != next.get_previous_hash()) {
    // invalid hash match
    return 0;
  }
  if (this->calculate_hash_for_block(next) != next.get_hash()) {
    // invalid hash content
    return 0;
  }
  return 1;
}
