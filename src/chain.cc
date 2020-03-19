#include "../include/chain.h"

Chain::Chain() {
  time_t tm;
  time(&tm);
  this->genesis_block = new Block(
    0,
    0,
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

long Chain::get_size() {
  return this->bc.size();
}

Block* Chain::get_latest_block() {
  return this->latest;
}

Block* Chain::generate_next_block(string data) {
  Block* prev_block = this->get_latest_block();
  long next_index = prev_block->get_index();
  time_t next_time = time(0);
  long difficulty = this->genesis_block->get_difficulty();
  // string next_hash = this->calculate_hash(next_index, prev_block->get_hash(), data, next_time);
  Block* new_block = this->find_block(next_index, prev_block->get_hash(), next_time, data, difficulty);
  this->add_block(new_block);
  return new_block;
}

void Chain::add_block(Block* new_block) {
  if (this->is_valid_new_block(new_block, this->latest)) {
    this->latest = new_block;
    this->bc.push_back(new_block);
  }
  this->print_block(new_block);
}

string Chain::calculate_hash_for_block(Block* b) {
  return this->calculate_hash(b->get_index(), b->get_previous_hash(), b->get_data(), b->get_time(), b->get_difficulty(), b->get_nonce());
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
  if (!this->is_valid_hash(next)) {
    // invalid hash
    return false;
  }
  if (!this->is_valid_time(next, prev)) {
    // invalid time
    return false;
  }
  return true;
}

int Chain::is_valid_chain(vector<Block*> chain) {
  if (chain.front()->get_hash().compare(this->genesis_block->get_hash()) != 0) {
    // invalid genesis block
    return false;
  }

  Block* prev = *chain.begin();
  for (vector<Block*>::iterator itvec = chain.begin(); itvec != chain.end(); itvec++) {
    if (*itvec == prev) {
      // skip the first block since it's already verified
      continue;
    }
    if (this->is_valid_new_block(*itvec, prev) == 0) {
      return false;
    }
    prev = *itvec;
  }
  return true;
}

int Chain::is_valid_hash(Block* b) {
  string calculated_hash = this->calculate_hash_for_block(b);
  return calculated_hash.compare(b->get_hash()) == 0;
}

void Chain::replace_chain(vector<Block*> new_chain) {
  if (this->is_valid_chain(new_chain) && new_chain.size() > this->bc.size()) {
    // accept the newer chain
    this->bc = new_chain; // TODO: memory leak?
    // broadcase_latest();
    // TODO: websocket
  }
  else {
    // the received blockchain is invalid
  }
}

int Chain::hash_matches_difficulty(string hash, long difficulty) {
  string hash_in_binary = hex_to_binary(hash);
  string required_prefix = "";
  for (long i = 0; i < difficulty; i++) {
    required_prefix += "0";
  }
  return hash.find(required_prefix) == 0;
}

Block* Chain::find_block(long index, string previous_hash, time_t time, string data, long difficulty) {
  long nonce = 0;
  string hash = "";
  do {
    hash = calculate_hash(index, previous_hash, data, time, difficulty, nonce);
  }
  while(!this->hash_matches_difficulty(hash, this->difficulty));
  return new Block(index, difficulty, nonce, hash, previous_hash, time, data);
}

string Chain::calculate_hash(
  long index,
  string previous_hash,
  string data,
  time_t time,
  long difficulty,
  long nonce
) {
  string block_data = to_string(index) + previous_hash + data + to_string(difficulty) + to_string(nonce);
  string hash = "";
  hash256_hex_string(block_data, hash);
  return hash;
}

long Chain::get_difficulty(vector<Block*> chain) {
  // calculate and update the difficulty of the blockchain
  Block* latest_block = chain.back();
  if (
    latest_block->get_index() % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 &&
    latest_block->get_index() != 0
  ) {
    return this->calculate_difficulty(latest_block, chain);
  }
  else {
    return latest_block->get_difficulty();
  }
}

long Chain::calculate_difficulty(Block* latest_block, vector<Block*> chain) {
  Block* prev_adjustment_block = chain.at(chain.size() - (DIFFICULTY_ADJUSTMENT_INTERVAL + 1));
  long time_expected = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL;
  long time_taken = latest_block->get_time() - prev_adjustment_block->get_time();
  if (time_taken < time_expected / 2) {
    return prev_adjustment_block->get_difficulty() + 1;
  }
  else if (time_taken > time_expected * 2) {
    return prev_adjustment_block->get_difficulty() - 1;
  }
  else {
    return prev_adjustment_block->get_difficulty();
  }
}

int Chain::is_valid_time(Block* next, Block* prev) {
  return (
    (prev->get_time() - 60 < next->get_time()) &&
    (next->get_time() - 60 < time(0))
  );
}

void Chain::print_block(Block* b) {
  // std::cout << b->get_hash() << std::endl;
}

void Chain::print_chain() {
  // TablePrinter tp(&std::cout);
  // tp.AddColumn("index", 10);
  // tp.AddColumn("hash", 20);
  // tp.AddColumn("data", 20);
  // tp.AddColumn("time", 10);
  // tp.AddColumn("difficulty", 10);
  // tp.PrintHeader();
  // for (vector<Block*>::iterator itvec = this->bc.begin(); itvec != this->bc.end(); itvec++) {
  //   tp << (*itvec)->get_index() << (*itvec)->get_hash() << (*itvec)->get_data() << (*itvec)->get_time() << (*itvec)->get_difficulty();
  // }
}