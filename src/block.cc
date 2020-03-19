#include "../include/block.h"

Block::Block(
  long index,
  long difficulty,
  long nonce,
  string hash,
  string previous_hash,
  time_t timestamp,
  string data
) {
  this->index = index;
  this->difficulty = difficulty;
  this->nonce = nonce;
  this->hash = hash;
  this->previous_hash = previous_hash;
  this->timestamp = timestamp;
  this->data = data;
}

long Block::get_index() {
  return this->index;
}

string Block::get_data() {
  return this->data;
}

string Block::get_hash() {
  return this->hash;
}

string Block::get_previous_hash() {
  return this->previous_hash;
}

time_t Block::get_time() {
  return this->timestamp;
}

long Block::get_difficulty() {
  return this->difficulty;
}

long Block::get_nonce() {
  return this->nonce;
}