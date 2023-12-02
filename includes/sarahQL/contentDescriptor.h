#ifndef CONTENT_DESCRIPTOR_H
#define CONTENT_DESCRIPTOR_H

#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef enum {
    INT,
    DOUBLE,
    STRING,
} FieldType;

typedef struct {
    const char *name;
    FieldType type;
    size_t offset;
} FieldDescriptor;

typedef struct {
    const FieldDescriptor *fields;
    size_t numFields;
} ContentDescriptor;
#endif