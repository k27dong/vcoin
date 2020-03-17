#include "../include/chain.h"

Chain::Chain() {
  time_t tm;
  time(&tm);
  this->genesis_block = new Block(
    0,
    "",
    "",
    tm,
    "and it was so"
  );
  this->latest = this->genesis_block;
  bc.push_back(this->genesis_block);
}

Chain::~Chain() {
  // delete this->genesis_block;
  // this->genesis_block = nullptr;
}

Block* Chain::get_latest_block() {
  return this->latest;
}

Block* Chain::generate_next_block(string data) {
  Block* prev_block = this->get_latest_block();
  unsigned int next_index = prev_block->get_index();
  time_t next_time = time(0);
  string next_hash = this->calculate_hash(next_index, prev_block->get_hash(), data, next_time);
  Block* new_block = new Block(next_index, next_hash, prev_block->get_hash(), next_time, data);
  this->latest = new_block;
  this->bc.push_back(new_block);
  return new_block;
}

string Chain::calculate_hash_for_block(Block* b) {
  return this->calculate_hash(b->get_index(), b->get_previous_hash(), b->get_data(), b->get_time());
}

int Chain::is_valid_new_block(Block* next, Block* prev) {
  if (prev->get_index() + 1 != next->get_index()) {
    // invalid index
    return false;
  }
  if (prev->get_hash() != next->get_previous_hash()) {
    // invalid hash match
    return false;
  }
  if (this->calculate_hash_for_block(next) != next->get_hash()) {
    // invalid hash content
    return false;
  }
  return true;
}

int Chain::is_valid_chain() {
  if (this->bc.front()->get_hash().compare(this->genesis_block->get_hash()) != 0) {
    return false;
  }
  for (vector<Block*>::iterator itvec = this->bc.begin(); itvec != this->bc.end(); itvec++) {
    if (this->is_valid_new_block(*itvec, *itvec) == 0) {
      return false;
    }
  }
  return true;
}

string Chain::calculate_hash(
  unsigned int index,
  string previous_hash,
  string data,
  time_t time
) {
  string block_data = to_string(index) + previous_hash + data;
  string hash = "";
  hash256_hex_string(block_data, hash);
  return hash;
}