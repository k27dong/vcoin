#include "block.h"

class Chain {
  private:
    Block* genesis_block;
    Block* latest;
    vector<Block*> bc;
  public:
    Chain();
    ~Chain();
    string calculate_hash(
      unsigned int index,
      string previous_hash,
      string data,
      time_t time
    );
    string calculate_hash_for_block(Block*);
    Block* generate_next_block(string block_data);
    Block* get_latest_block();
    int is_valid_new_block(Block* next, Block* prev);
    int is_valid_chain();
};

