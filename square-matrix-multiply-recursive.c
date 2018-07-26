#include <stdio.h>
typedef struct square_matrix
{
	int rows;
	int *element;
	int root_rows;
	int row_start;
	int column_start;

}square_matrix;


void set_square_matrix(square_matrix *sm, int rows, int *element)
{
	sm->root_rows = sm->rows = rows;
	sm->element = element;
	sm->row_start = 0;
	sm->column_start = 0;
}

void copy_form_c(square_matrix *c, int *ccopy)
{
	int i, j, k = 0;
	for (i = c->row_start; i < c->row_start + c->rows; i++)
	{
		for (j = c->column_start; j < c->column_start + c->rows; j++)
		{
			ccopy[k] = c->element[i*c->root_rows+j]; 
			k++;
		}
	}
}

void add_to_c(square_matrix *c, int *ccopy)
{

	int i, j, k = 0;
	for (i = c->row_start; i < c->row_start + c->rows; i++)
	{
		for (j = c->column_start; j < c->column_start + c->rows; j++)
		{
			c->element[i*c->root_rows+j] += ccopy[k];
			k++;
		}
	}

}

void print_square_matrix_element_by_root_rows(square_matrix *sm)
{

	int i,j;
	
	for (i = 0; i < sm->root_rows; i++)
	{
		for (j = 0; j < sm->root_rows; j++)
		{
			printf("%3d",sm->element[i*sm->root_rows+j]);
		}
		printf("\n");
	}
	printf("-----------------------------------------------\n");
}
void square_matrix_multiply_recursive(square_matrix *a, square_matrix *b, square_matrix *c)
{
	int n = a->rows;
	if (n == 1)
	{
		c->element[c->row_start * c->root_rows + c->column_start] = 
			a->element[a->row_start * a->root_rows + a->column_start] * b->element[b->row_start * b->root_rows + b->column_start];
	}
	else
	{
		int rowa = a->row_start, columna = a->column_start;
		int rowb = b->row_start, columnb = b->column_start;
		int rowc = c->row_start, columnc = c->column_start;
		a->rows /= 2;
		b->rows /= 2;
		c->rows /= 2;

		int ccopy[c->rows * c->rows]; // c copy

		int a11_row_start = rowa, a11_column_start = columna;
		int a12_row_start = rowa, a12_column_start = columna + a->rows;
		int a21_row_start = rowa + a->rows, a21_column_start = columna;
		int a22_row_start = rowa + a->rows, a22_column_start = columna + a->rows;

		int b11_row_start = rowb, b11_column_start = columnb;
		int b12_row_start = rowb, b12_column_start = columnb + b->rows;
		int b21_row_start = rowb + b->rows, b21_column_start = columnb;
		int b22_row_start = rowb + b->rows, b22_column_start = columnb + b->rows;


		int c11_row_start = rowc, c11_column_start = columnc;
		int c12_row_start = rowc, c12_column_start = columnc + c->rows;
		int c21_row_start = rowc + c->rows, c21_column_start = columnc;
		int c22_row_start = rowc + c->rows, c22_column_start = columnc + c->rows;

		c->row_start = c11_row_start;
		c->column_start = c11_column_start;
		a->row_start = a11_row_start;
		a->column_start = a11_column_start;
		b->row_start = b11_row_start;
		b->column_start = b11_column_start;
		
		square_matrix_multiply_recursive(a, b, c);

		print_square_matrix_element_by_root_rows(c); //

		copy_form_c(c, ccopy);

		a->row_start = a12_row_start;
		a->column_start = a12_column_start;
		b->row_start = b21_row_start;
		b->column_start = b21_column_start;

		square_matrix_multiply_recursive(a, b, c);

		print_square_matrix_element_by_root_rows(c); //

		add_to_c(c, ccopy);

		print_square_matrix_element_by_root_rows(c); //

		c->row_start = c12_row_start;
		c->column_start = c12_column_start;
		a->row_start = a11_row_start;
		a->column_start = a11_column_start;
		b->row_start = b12_row_start;
		b->column_start = b12_column_start;

		square_matrix_multiply_recursive(a, b, c);

		print_square_matrix_element_by_root_rows(c); //
		copy_form_c(c, ccopy);

		a->row_start = a12_row_start;
		a->column_start = a12_column_start;
		b->row_start = b22_row_start;
		b->column_start = b22_column_start;

		square_matrix_multiply_recursive(a, b, c);
		
		print_square_matrix_element_by_root_rows(c); //
		add_to_c(c, ccopy);

		print_square_matrix_element_by_root_rows(c); //
		c->row_start = c21_row_start;
		c->column_start = c21_column_start;
		a->row_start = a21_row_start;
		a->column_start = a21_column_start;
		b->row_start = b11_row_start;
		b->column_start = b11_column_start;

		square_matrix_multiply_recursive(a, b, c);

		print_square_matrix_element_by_root_rows(c); //
		copy_form_c(c, ccopy);

		a->row_start = a22_row_start;
		a->column_start = a22_column_start;
		b->row_start = b21_row_start;
		b->column_start = b21_column_start;

		square_matrix_multiply_recursive(a, b, c);
		
		print_square_matrix_element_by_root_rows(c); //
		add_to_c(c, ccopy);

		print_square_matrix_element_by_root_rows(c); //
        c->row_start = c22_row_start;                                                                                                                                                                    
		c->column_start = c22_column_start;
		a->row_start = a21_row_start;
		a->column_start = a21_column_start;
		b->row_start = b12_row_start;
		b->column_start = b12_column_start;


		square_matrix_multiply_recursive(a, b, c);
		
		print_square_matrix_element_by_root_rows(c); //
		copy_form_c(c, ccopy);

		a->row_start = a22_row_start;
		a->column_start = a22_column_start;
		b->row_start = b22_row_start;
		b->column_start = b22_column_start;


		square_matrix_multiply_recursive(a, b, c);
		
		print_square_matrix_element_by_root_rows(c); //
		add_to_c(c, ccopy);
		print_square_matrix_element_by_root_rows(c); //

		a->rows *= 2;
		b->rows *= 2;
		c->rows *= 2;
		a->row_start = rowa;
		b->row_start = rowb;
		c->row_start = rowc;
		a->column_start = columna;
		b->column_start = columnb;
		c->column_start = columnc;

	}

}



void test_square_matrix_multiply_recursive()
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
	int c_element[4][4] = { 0 };

	set_square_matrix(&a, 4, (int *)a_element);
	set_square_matrix(&b, 4, (int *)b_element);
	set_square_matrix(&c, 4, (int *)c_element);
 
	square_matrix_multiply_recursive(&a, &b, &c);

	//print_square_matrix_element(&a);
	//print_square_matrix_element(&b);
	//print_square_matrix_element(&c);
}

int main(int argc, const char *argv[])
{
	test_square_matrix_multiply_recursive();
	return 0;
}
