#include "../include/block.h"

Block::Block(
  unsigned int index,
  string hash,
  string previous_hash,
  time_t timestamp,
  string data
) {
  this->index = index;
  this->hash = hash;
  this->previous_hash = previous_hash;
  this->timestamp = timestamp;
  this->data = data;
}

unsigned int Block::get_index() {
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

