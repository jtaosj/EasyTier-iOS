#ifndef EASYTIER_FFI_H
#define EASYTIER_FFI_H

#include <stdint.h>
#include <stddef.h>

/**
 * Represents a key-value pair where both are C-style strings.
 * Note: Strings returned in this struct from Rust should be freed
 * using free_string to avoid memory leaks.
 */
typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the tun file descriptor for a specific instance.
 * Returns 0 on success, -1 on failure.
 */
int set_tun_fd(const char *inst_name, int fd);

/**
 * Get the last error message.
 * Rust allocates a new CString; you must call free_string on the output pointer.
 */
void get_error_msg(const char **out);

/**
 * Frees a string that was allocated by the Rust side (e.g., from get_error_msg
 * or collect_network_infos).
 */
void free_string(const char *s);

/**
 * Parse a TOML configuration string.
 * Returns 0 on success, -1 on failure.
 */
int parse_config(const char *cfg_str);

/**
 * Starts a network instance with the provided TOML configuration.
 * Returns 0 on success, -1 on failure.
 */
int run_network_instance(const char *cfg_str);

/**
 * Retains only the instances specified in the array.
 * Instances not in the list will be stopped.
 */
int retain_network_instance(const char *const *inst_names, size_t length);

/**
 * Collects network info into the provided array.
 * Returns the number of items written or -1 on error.
 * IMPORTANT: The 'key' and 'value' strings in KeyValuePair must be manually freed.
 */
int collect_network_infos(KeyValuePair *infos, size_t max_length);

#ifdef __cplusplus
}
#endif

#endif /* EASYTIER_FFI_H */
