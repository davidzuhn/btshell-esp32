#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Register all btshell commands
void initialize_btshell();

void register_btshell();

struct kv_pair {
    char *key;
    int val;
};


#ifdef __cplusplus
}
#endif
