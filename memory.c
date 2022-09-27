#include "memory.h"
#include <stdio.h>

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
    for (size_t i=0; i < num_frames; i++){
      info_ptr[i] = '0';
    }

    // FINISH HERE
}

size_t memory_avail()
{
  for(size_t i = 0; i<num_frames; i++){
       printf("*** %c",info_ptr[i]);
    }
  size_t count = 0;
  for (size_t i=0; i < num_frames; i++){
    if (info_ptr[i] == '0')
      count++;
  }
  return count * FRAME_SIZE;
}

void* memory_alloc(size_t size)
{
  if (memory_avail() < size)
    return NULL;
  size_t frames  = round_up(size/FRAME_SIZE);
  for (size_t i = 0; i<num_frames; i++){
    if(info_ptr[i] == '0'){
      for (size_t j = 0; j<frames; j++){
	info_ptr[j] = '1';
      }
      return data_ptr + i * FRAME_SIZE;
    }
  }
  return NULL;
}
  

void memory_free(void* ptr)
{
  for (size_t i = (ptr-data_ptr)/FRAME_SIZE; i<num_frames; i++){
    info_ptr[i]='0';
  }
}

void test3()
{
}
