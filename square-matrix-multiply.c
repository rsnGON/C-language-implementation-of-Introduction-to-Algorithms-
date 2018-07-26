#include <stdio.h>
typedef struct square_matrix
{
	int rows;
	int *element;

}square_matrix;


void print_square_matrix_element(square_matrix *sm)
{

	int i,j;
	
	for (i = 0; i < sm->rows; i++)
	{
		for (j = 0; j < sm->rows; j++)
		{
			printf("%3d",sm->element[i*sm->rows+j]);
		}
		printf("\n");
	}
	printf("----------------------------------\n");
}

void set_square_matrix(square_matrix *sm, int rows, int *element)
{
	sm->rows = rows;
	sm->element = element;
}


void square_matrix_multiply(square_matrix *a, square_matrix *b, square_matrix *c)
{
	int i,j,k;
	int n = c->rows = a->rows;
	for (i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			c->element[i*n+j] = 0;
			for (k = 0; k < a->rows; k++)
			{
				c->element[i*n+j] += a->element[i*n+k] * b->element[k*n+j];
			}
		}
	}
}


void test_square_matrix_multiply()
{
	square_matrix a;
	int a_element[4][4] = { 1, 2, 3, 4,
							5, 6, 7, 8,
							9,10,11,12,
							13,14,15,16 };
	square_matrix b;
	int b_element[4][4] = { 1, 1, 1, 1,
							1, 1, 1, 1,
							1, 1, 1, 1,
							1, 1, 1, 1 };
	square_matrix c;
	int c_element[4][4];

	set_square_matrix(&a, 4, (int *)a_element);
	set_square_matrix(&b, 4, (int *)b_element);
	set_square_matrix(&c, 4, (int *)c_element);
 
	square_matrix_multiply(&a, &b, &c);

	print_square_matrix_element(&a);
	print_square_matrix_element(&b);
	print_square_matrix_element(&c);


}

int main(int argc, const char *argv[])
{
	test_square_matrix_multiply();
	return 0;
}
