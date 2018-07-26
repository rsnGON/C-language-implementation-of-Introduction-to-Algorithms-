#include "common.h"

void insertion_sort(int *sequence, int length)
{
	int i, j;
	int	key;
	for (j = 1; j < length; j++)
	{
		key = sequence[j];
		i = j - 1;
		while (i >= 0 && sequence[i] > key)
		{
			sequence[i+1] = sequence[i];
			i = i - 1;
		}
		sequence[i+1] = key;
	}
}


int main(int argc, const char *argv[])
{
	int i;

	int sequence[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	insertion_sort(sequence, SEQUENCE_SIZE(sequence));
    
	print(sequence, SEQUENCE_SIZE(sequence));

	return 0;
}
