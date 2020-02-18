#include "block.h"

class Chain {
  private:
    vector<Block> c;
    const Block* genesis_block;
  public:
    Chain();
    ~Chain();
    string calculate_hash(
      unsigned int index,
      string previous_hash,
      string data,
      time_t timestamp
    );
    string calculate_hash_for_block(Block);
    Block* generate_next_block(string block_data);
    Block get_latest_block();
    int is_valid_new_block(Block next, Block prev);
};

