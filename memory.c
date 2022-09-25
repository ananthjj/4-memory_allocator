#include "memory.h"

size_t round_up(size_t size)
{
    return (size + FRAME_SIZE - 1) / FRAME_SIZE * FRAME_SIZE;
}

size_t num_frames = 0;
char* info_ptr = NULL;
void* data_ptr = NULL;

void memory_init(void* buffer, size_t size)
{
    // UPDATE THIS
    size_t info_per_frame = sizeof(char);

    num_frames = size / FRAME_SIZE; // initial estimate
    info_ptr = buffer;
    data_ptr = (void*)info_ptr + round_up(info_per_frame * num_frames);
    num_frames = (buffer + size - data_ptr) / FRAME_SIZE; // real value

    // FINISH HERE
}

size_t memory_avail()
{
    return 0;
}

void* memory_alloc(size_t size)
{
    return NULL;
}

void memory_free(void* ptr)
{
}

void test3()
{
}
