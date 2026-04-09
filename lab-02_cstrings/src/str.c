#include "str.h"

int my_strlen (const char* my_string) {
    const char * i = my_string;
    int len = 0;
    while (*i != '\0') {
        ++i;
        ++len;
    }
    return len;
}

int my_strcmp (const char * lhs, const char * rhs) {
    int len_l = my_strlen(lhs);
    int len_r = my_strlen(rhs);
    int min_len = 0;
    if (len_l >= len_r) {
        min_len = len_r;
    } else {
        min_len = len_l;
    }

    for (int i = 0; i < min_len; ++i) {
        if (lhs[i] != rhs[i]) {
            return lhs[i] - rhs[i];
        }
    }
    return lhs[min_len] - rhs[min_len];
    
}

char *my_strcat (char * dest, const char * src) {
    int dest_len = my_strlen(dest);
    
    for (int i = dest_len; i < (dest_len + my_strlen(src)); ++i) {
        dest[i] = src[i - dest_len];
    }
    dest[dest_len + my_strlen(src)] = '\0';
    return dest;
}

char *my_strcpy (char *dest, const char *src) {
    char* ptr = dest;
    int len_dest = my_strlen(dest);
    for (int i = 0; i < my_strlen(src); ++i) {
        ptr[i + len_dest] = src[i];
    }
    ptr[len_dest + my_strlen(src)] = '\0';
    return dest;
}