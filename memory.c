#include "shell.h"

/**
 * _memcpy - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @ss_old: size, in bytes, of the allocated space of ptr.
 * @ss_new: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if ss_new == ss_old, returns ptr without changes.
 * if malloc fails, returns NULL.
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
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @ss_old: size, in bytes, of the allocated space of ptr.
 * @ss_new: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if ss_new == ss_old, returns ptr without changes.
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
