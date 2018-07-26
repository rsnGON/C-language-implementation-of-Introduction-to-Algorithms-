#include "common.h"


void merge(int *sequence, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int lseq[n1+1];
	int rseq[n2+1];
	int i, m = 0, n = 0;
	for (i = 0; i < n1; i++)
	{
		lseq[i] = sequence[p+i];
	}
	for (i = 0; i < n2; i++)
	{
		rseq[i] = sequence[q+i+1];
	}
	lseq[n1] = SENTRY_VALUE_MAX(int);
	rseq[n2] = SENTRY_VALUE_MAX(int);
#ifdef TEST_MERGE	
	print(lseq, n1 + 1);
	print(rseq, n2 + 1);
#endif

	for (i = p; i < (r + 1); i++)
	{
		if (lseq[m] <= rseq[n])
		{
			sequence[i] = lseq[m];
			m++;
		}
		else
		{
			sequence[i] = rseq[n];
			n++;
		}
	}

}

void merge_sort(int *sequence,int p, int r)
{
	int q;
	if (p < r)
	{
		q = (p + r) / 2;
		merge_sort(sequence, p, q);
		merge_sort(sequence, q + 1, r);
		merge(sequence, p, q, r);
	}
		
}

void test_merge()
{
	int sequence[10] = { 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 };

	merge(sequence, 0, 4, 9);

	print(sequence, SEQUENCE_SIZE(sequence));

}

void test_merge_sort()
{
	int sequence[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	merge_sort(sequence, 0, SEQUENCE_SIZE(sequence) - 1);
	print(sequence, SEQUENCE_SIZE(sequence));
}

#define TEST_MERGE_SOFT

int main(int argc, const char *argv[])
{

#ifdef TEST_MERGE
	test_merge();
#endif
#ifdef TEST_MERGE_SOFT
	test_merge_sort();
#endif
	return 0;
}

