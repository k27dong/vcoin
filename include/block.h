#include "basic.h"

class Block {
  private:
    unsigned int index;
    string hash, previous_hash, data;
    time_t timestamp;
  public:
    Block(
      unsigned int index,
      string hash,
      string previous_hash,
      time_t timestamp,
      string data
    );
    unsigned int get_index();
    string get_data();
    string get_hash();
    string get_previous_hash();
    time_t get_time();
};