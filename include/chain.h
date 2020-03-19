#include "block.h"

class Chain {
  private:
    Block* genesis_block;
    Block* latest;
    vector<Block*> bc;
    long difficulty;
  public:
    Chain();
    ~Chain();
    string calculate_hash(
      long index,
      string previous_hash,
      string data,
      time_t time,
      long difficulty,
      long nonce
    );
    long get_size();
    string calculate_hash_for_block(Block*);
    Block* generate_next_block(string block_data);
    Block* get_latest_block();
    void add_block(Block*);
    int is_valid_new_block(Block* next, Block* prev);
    int is_valid_chain(vector<Block*> chain);
    int is_valid_time(Block* next, Block* prev);
    int is_valid_hash(Block*);
    void replace_chain(vector<Block*> new_chain);
    int hash_matches_difficulty(string hash, long difficulty);
    Block* find_block(long index, string previous_hash, time_t time, string data, long difficulty);
    long get_difficulty(vector<Block*>);
    long calculate_difficulty(Block*, vector<Block*>);
    void print_block(Block*);
    void print_chain();
};

