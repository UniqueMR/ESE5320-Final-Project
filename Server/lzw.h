unsigned int my_hash(unsigned long key);
void hash_lookup(unsigned long* hash_table, unsigned int key, bool* hit, unsigned int* result);
void hash_insert(unsigned long* hash_table, unsigned int key, unsigned int value, bool* collision);
void assoc_insert(assoc_mem* mem,  unsigned int key, unsigned int value, bool* collision);
void assoc_lookup(assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);
void insert(unsigned long* hash_table, assoc_mem* mem, unsigned int key, unsigned int value, bool* collision);
void lookup(unsigned long* hash_table, assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);
void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code);
void decoding(std::vector<int> op);
