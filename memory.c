#include "shell.h"

/**
 * _custommemorycopy - copies byte from the src to the dest pointer.
 * @newptr: where to copy to pointer.
 * @ptr: where to copy from pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _custommemorycopy(void *newptr, const void *ptr, unsigned int size)
{
	char *c_r = (char *)ptr;
	char *c_n_r = (char *)newptr;
	unsigned int i;

	while (i < size) {
        c_n_r[i] = c_r[i];
        i++;
    }
}

/**
 * _memallocate - change the memory block.
 * @ptr: old pointer to memory.
 * @bytend: bytes of allocated mem.
 * @bytcur: bytes to the new mem.
 *
 * Return: pointer of the ptr
 */
void *_memallocate(void *ptr, unsigned int bytend, unsigned int bytcur)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(bytcur));

	if (bytcur == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (bytcur == bytend)
		return (ptr);

	newptr = malloc(bytcur);
	if (newptr == NULL)
		return (NULL);

	if (bytcur < bytend)
		_custommemorycopy(newptr, ptr, bytcur);
	else
		_custommemorycopy(newptr, ptr, bytend);

	free(ptr);
	return (newptr);
}

/**
 * _memallocatedouble - change the memory block of double pointer.
 * @ptr: old pointer to memory.
 * @bytend: bytes of allocated mem.
 * @bytcur: bytes to the new mem.
 *
 * Return: pointer of the ptr
 */
char **_memallocatedouble(char **ptr, unsigned int bytend, unsigned int bytcur)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * bytcur));

	if (bytcur == bytend)
		return (ptr);

	newptr = malloc(sizeof(char *) * bytcur);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < bytend; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
