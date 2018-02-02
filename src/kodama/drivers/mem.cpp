#include "mem.h"

extern Mem mem;

extern unsigned int __data_start__;
extern unsigned int __ram_size__;
extern unsigned int __heap_start__;

Mem::Mem(unsigned int external_ram_adr)
{
  (void)external_ram_adr;
  mem_ptr = (unsigned char*)(&__heap_start__);
}

Mem::~Mem()
{

}

void *Mem::malloc(unsigned int size)
{
  unsigned char *mem_res = mem_ptr;
  mem_ptr+= size;
  return (void*)mem_res;
}

void Mem::free(void *p)
{
    (void)p;
}

void Mem::clean()
{
  mem_ptr = (unsigned char*)(&__heap_start__);
}

void * operator new(unsigned int size)
{
    return mem.malloc(size);
}

void operator delete(void *p)
{
  mem.free(p);
}

void* operator new[](unsigned int size)
{
    return operator new(size); // Same as regular new
}

void operator delete[](void *p)
{
    operator delete(p); // Same as regular delete
}
