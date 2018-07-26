#include "common.h"

typedef struct maximum_subarray
{
	int low, high;
	int sum;
}maximum_subarray;


maximum_subarray find_maximum_subarray_linear(int *array, int length)
{
	int i;
	maximum_subarray ret = { 0, 0, array[0] };
	maximum_subarray boundry = { 0, 0, array[0] };
	for (i = 1; i < length; i++)
	{
		if ((boundry.sum + array[i]) >= array[i])
		{
			boundry.sum += array[i];
			boundry.high = i;
		}
		else
		{
			boundry.sum = array[i];
			boundry.low = boundry.high = i;
		}
		if (boundry.sum > ret.sum)
		{
			ret.sum = boundry.sum;
			ret.low = boundry.low;
			ret.high = boundry.high;
		}
	}
	return ret;
}


maximum_subarray find_max_corssing_subarray(int *array, int low, int mid, int high)
{
	int i;
	int sum = 0;
	int left_sum = SENTRY_VALUE_MIN(int);
	int right_sum = SENTRY_VALUE_MIN(int);
	maximum_subarray ret = { 0, 0, 0 };

	for (i = mid; i >= low; i--)
	{
		sum = sum + array[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			ret.low = i;
		}
	}
	sum = 0;
	for (i = mid + 1; i <= high; i++)
	{
		sum = sum + array[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			ret.high = i;
		}
	}

	ret.sum = left_sum + right_sum;

	return ret;
}

maximum_subarray find_maximum_subarray(int *array, int low, int high)
{
	maximum_subarray left_ret, right_ret, cross_ret;
	int mid;
	if (high == low)
	{
		return (maximum_subarray){ low, high, array[low] };
	}
	else
	{
		mid = (low + high) / 2;
		left_ret = find_maximum_subarray(array, low, mid);
		right_ret = find_maximum_subarray(array, mid + 1, high);
		cross_ret = find_max_corssing_subarray(array, low, mid, high);
		if (left_ret.sum >= right_ret.sum && left_ret.sum >= cross_ret.sum)
		{
			return left_ret;
		}
		else if (right_ret.sum >= left_ret.sum && right_ret.sum >= cross_ret.sum)
		{
			return right_ret;
		}
		else
		{
			return cross_ret;
		}

	}

}


void test_find_maximum_subarray()
{
	int array[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	maximum_subarray ret;
	ret = find_maximum_subarray(array, 0, SEQUENCE_SIZE(array) - 1);
	printf("low:%d,high:%d\n", ret.low, ret.high);
}

void test_find_maximum_subarray_linear()
{
	int array[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	maximum_subarray ret;
	ret = find_maximum_subarray_linear(array, SEQUENCE_SIZE(array));
	printf("low:%d,high:%d\n", ret.low, ret.high);
}



int main(int argc, const char *argv[])
{
	test_find_maximum_subarray();
	test_find_maximum_subarray_linear();
	return 0;
}
