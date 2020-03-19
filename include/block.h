#include "basic.h"

class Block {
  private:
    long index, difficulty, nonce;
    string hash, previous_hash, data;
    time_t timestamp;
  public:
    Block(
      long index,
      long difficulty,
      long nonce,
      string hash,
      string previous_hash,
      time_t timestamp,
      string data
    );
    long get_index();
    string get_data();
    string get_hash();
    string get_previous_hash();
    time_t get_time();
    long get_difficulty();
    long get_nonce();
};