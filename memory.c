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
  size_t count = 0;
  for (size_t i = 0; i<num_frames; i++){
    if(info_ptr[i] == '0')
      count += FRAME_SIZE;
  }
  return count;

}

void* memory_alloc(size_t size)
{
  if (memory_avail() < size)
    return NULL;
  size_t frames  = (size + FRAME_SIZE - 1) / FRAME_SIZE;
  for (size_t i = 0; i<num_frames; i++){
    if(info_ptr[i] == '0'){
	info_ptr[i] = '1';
	for (size_t j = 1; j<frames; j++)
	  info_ptr[i+j] = '2';
	return data_ptr + i * FRAME_SIZE;
    }
  }
  return NULL;
}
  

void memory_free(void* ptr)
{
  size_t i = (ptr-data_ptr)/FRAME_SIZE;
  if (i<num_frames && info_ptr[i] == '1' && i>=0){
    info_ptr[i]='0';
    for (size_t j = i+1; j  < num_frames && info_ptr[j] == '2'; j++){
      info_ptr[i+j] = '0';
    }
  }
}

void test3()
{
  printf("TEST 3 STARTED\n");
  
  size_t LENGTH = FRAME_SIZE * 2;
  
  char* ptr1 = memory_alloc(LENGTH);
  printf("allocated %ld memory at %p\n", LENGTH, ptr1);

  char* ptr2 = memory_alloc(LENGTH);
  printf("allocated %ld memory at %p\n", LENGTH, ptr2);
  
  char* ptr3 = memory_alloc(LENGTH);
  printf("allocated %ld memory at %p\n", LENGTH, ptr3);

  size_t len1 = memory_avail();
  printf("available memory after alloc is %ld\n", len1);

  memory_free(ptr2);
  printf("memory is freed at %p\n", ptr2);

  size_t len2 = memory_avail();
  printf("available memory after free is %ld\n", len2);

  if (len2 == 3*LENGTH)
    printf("TEST 3 PASSED\n");
  else
    printf("TEST 3 FAILED\n");
}
