#include "shell.h"

/**
 * _memcpy - Function to copy information between void pointers.
 * @newptr: pointer to the return memory.
 * @ptr: pointer to the src memory.
 * @size: size of the memory in bytes.
 *
 * Return: no return (void).
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
char *src_ptr = (char *)ptr;
char *dest_ptr = (char *)newptr;
unsigned int j;
while (j < size)
{
dest_ptr[j] = src_ptr[j];
j++;
}

}

/**
 * _realloc - Function to reallocate a memory block.
 * @ptr: pointer to the previously allocated memory.
 * @ss_old: size, in bytes, of the allocated space of ptr.
 * @ss_new: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * If new_size is equal to old_size, returns ptr without changes.
 * If new_size is zero, frees ptr and returns NULL.
 */
void *_realloc(void *ptr, unsigned int ss_old, unsigned int ss_new)
{
void *newptr;

if (ptr == NULL)
return (malloc(ss_new));

if (ss_new == 0)
{
free(ptr);
return (NULL);
}

if (ss_new == ss_old)
return (ptr);

newptr = malloc(ss_new);
if (newptr == NULL)
return (NULL);

if (ss_new < ss_old)
_memcpy(newptr, ptr, ss_new);
else
_memcpy(newptr, ptr, ss_old);

free(ptr);
return (newptr);
}
/**
 * _reallocdp - Function to reallocate a memory block of a double pointer.
 * @ptr: double pointer to the previously allocated memory.
 * @ss_old: size, in bytes, of the allocated space of ptr.
 * @ss_new: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * If new_size is equal to old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int ss_old, unsigned int ss_new)
{
char **newptr;
unsigned int i;

if (ptr == NULL)
return (malloc(sizeof(char *) * ss_new));

if (ss_new == ss_old)
return (ptr);

newptr = malloc(sizeof(char *) * ss_new);
if (newptr == NULL)
return (NULL);

for (i = 0; i < ss_old; i++)
newptr[i] = ptr[i];

free(ptr);

return (newptr);
}
