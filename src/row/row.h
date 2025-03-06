#ifndef ROW_H
#define ROW_H

#include <stdint.h>
#include <stdio.h>

#define USERNAME_MAX_SIZE 32
#define EMAIL_MAX_SIZE 255

#define size_of_attribute(Struct, Attriute) sizeof(((Struct*)0)->Attriute)

typedef struct {
    uint32_t id;
    char username[USERNAME_MAX_SIZE + 1];
    char email[EMAIL_MAX_SIZE + 1];
} Row;

#define ID_SIZE ((uint32_t)size_of_attribute(Row, id))
#define USERNAME_SIZE ((uint32_t)size_of_attribute(Row, username))
#define EMAIL_SIZE ((uint32_t)size_of_attribute(Row, email))
#define ID_OFFSET ((uint32_t)0)
#define USERNAME_OFFSET ((uint32_t)ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET ((uint32_t)USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE ((uint32_t)ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

void print_row(Row*);

#endif