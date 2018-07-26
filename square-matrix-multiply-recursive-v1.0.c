#include <stdio.h>


typedef struct vector
{
	int row_start;
	int column_start;
}vector;

typedef struct child_square_matrix
{
	int rows;
	int root_rows;
	int *element;
	vector vec;
	
}square_matrix;

#define INIT_VECTOR (vector){ 0, 0 }


void square_matrix_multiply_recursive(square_matrix *a, square_matrix *b, square_matrix *c);

void set_square_matrix(square_matrix *sm, int rows, int *element)
{
	sm->root_rows = sm->rows = rows;
	sm->element = element;
	sm->vec = INIT_VECTOR;
}

void copy_form_c(square_matrix *c, int *ccopy)
{
	int i, j, k = 0;
	for (i = c->vec.row_start; i < c->vec.row_start + c->rows; i++)
	{
		for (j = c->vec.column_start; j < c->vec.column_start + c->rows; j++)
		{
			ccopy[k] = c->element[i*c->root_rows+j]; 
			k++;
		}
	}
}

void add_to_c(square_matrix *c, int *ccopy)
{

	int i, j, k = 0;
	for (i = c->vec.row_start; i < c->vec.row_start + c->rows; i++)
	{
		for (j = c->vec.column_start; j < c->vec.column_start + c->rows; j++)
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


void child_square_matrix_multiply_and_add(square_matrix *c, square_matrix *a, square_matrix *b,
		vector vecc, vector vec1, vector vec2, vector vec3, vector vec4)
{

		int ccopy[c->rows * c->rows]; // c copy
	
		c->vec = vecc;
		a->vec = vec1;
		b->vec = vec2;
		
		square_matrix_multiply_recursive(a, b, c);

		print_square_matrix_element_by_root_rows(c); //

		copy_form_c(c, ccopy);


		a->vec = vec3;
		b->vec = vec4;

		square_matrix_multiply_recursive(a, b, c);

		print_square_matrix_element_by_root_rows(c); //

		add_to_c(c, ccopy);

		print_square_matrix_element_by_root_rows(c); //


}

void square_matrix_multiply_recursive(square_matrix *a, square_matrix *b, square_matrix *c)
{
	int n = a->rows;
	if (n == 1)
	{
		c->element[c->vec.row_start * c->root_rows + c->vec.column_start] = 
			a->element[a->vec.row_start * a->root_rows + a->vec.column_start] * b->element[b->vec.row_start * b->root_rows + b->vec.column_start];
	}
	else
	{
		vector vectora = a->vec;
		vector vectorb = b->vec;
		vector vectorc = c->vec;

		a->rows /= 2;
		b->rows /= 2;
		c->rows /= 2;
		
		int ccopy[c->rows * c->rows]; // c copy

		vector a11 = { vectora.row_start, vectora.column_start };
		vector a12 = { vectora.row_start, vectora.column_start + a->rows };
		vector a21 = { vectora.row_start + a->rows, vectora.column_start };
		vector a22 = { vectora.row_start + a->rows, vectora.column_start + a->rows };
	
		vector b11 = { vectorb.row_start, vectorb.column_start };
		vector b12 = { vectorb.row_start, vectorb.column_start + b->rows };
		vector b21 = { vectorb.row_start + b->rows, vectorb.column_start };
		vector b22 = { vectorb.row_start + b->rows, vectorb.column_start + b->rows };


		vector c11 = { vectorc.row_start, vectorc.column_start };
		vector c12 = { vectorc.row_start, vectorc.column_start + c->rows };
		vector c21 = { vectorc.row_start + c->rows, vectorc.column_start };
		vector c22 = { vectorc.row_start + c->rows, vectorc.column_start + c->rows };



		child_square_matrix_multiply_and_add(c, a, b, c11, a11, b11, a12, b21);

		
		child_square_matrix_multiply_and_add(c, a, b, c12, a11, b12, a12, b22);


		child_square_matrix_multiply_and_add(c, a, b, c21, a21, b11, a22, b21);


		child_square_matrix_multiply_and_add(c, a, b, c22, a21, b12, a22, b22);

		a->rows *= 2;
		b->rows *= 2;
		c->rows *= 2;
		a->vec = vectora;
		b->vec = vectorb;
		c->vec = vectorc;
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
