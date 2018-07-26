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


void square_matrix_multiply_strassen(square_matrix *a, square_matrix *b, square_matrix *c);

void set_square_matrix(square_matrix *sm, int rows, int *element)
{
	sm->root_rows = sm->rows = rows;
	sm->element = element;
	sm->vec = INIT_VECTOR;
}

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
	printf("-----------------------------------\n");
}

void zero_square_matrix(square_matrix *sm)
{
	int i,j;
	for (i = sm->vec.row_start; i < sm->vec.row_start + sm->rows; i++)
	{
		for (j = sm->vec.column_start; j < sm->vec.column_start + sm->rows; j++)
		{
			sm->element[i*sm->root_rows+j] = 0;
		}
	
	}

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

void minus_from_c(square_matrix *c, int *ccopy)
{

	int i, j, k = 0;
	for (i = c->vec.row_start; i < c->vec.row_start + c->rows; i++)
	{
		for (j = c->vec.column_start; j < c->vec.column_start + c->rows; j++)
		{
			c->element[i*c->root_rows+j] -= ccopy[k];
			k++;
		}
	}

}


void child_square_matrix_add(square_matrix * sm, vector vec1, vector vec2, square_matrix * result)
{
	int i,j;
	for (i = vec1.row_start; i < vec1.row_start + sm->rows; i++)
	{ 
		for (j = vec1.column_start; j < vec1.column_start + sm->rows; j++)
		{
			int m,n;
			m = i - vec1.row_start;
			n = j - vec1.column_start;
			result->element[m * result->root_rows + n] = 
				sm->element[i*sm->root_rows+j] + sm->element[(vec2.row_start+m) * sm->root_rows + (vec2.column_start + n)];

		}

	}

}

void child_square_matrix_minus(square_matrix * sm, vector vec1, vector vec2, square_matrix * result)
{
	int i,j;
	for (i = vec1.row_start; i < vec1.row_start + sm->rows; i++)
	{ 
		for (j = vec1.column_start; j < vec1.column_start + sm->rows; j++)
		{
			int m,n;
			m = i - vec1.row_start;
			n = j - vec1.column_start;
			result->element[m * result->root_rows + n] = 
				sm->element[i*sm->root_rows+j] - sm->element[(vec2.row_start+m) * sm->root_rows + (vec2.column_start + n)];

		}

	}
}



void print_square_matrix_element_by_root_rows(square_matrix *sm)
{
#ifdef CONFIG_PRINT_BY_ROOT_ROWS
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
#endif
}


void square_matrix_multiply_strassen(square_matrix *a, square_matrix *b, square_matrix *c)
{
	int n = a->rows;
	zero_square_matrix(c);
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

//2

		square_matrix s1;
		int s1_element[a->rows][a->rows];
		square_matrix s2;
		int s2_element[a->rows][a->rows];
		square_matrix s3;
		int s3_element[a->rows][a->rows];
		square_matrix s4;
		int s4_element[a->rows][a->rows];
		square_matrix s5;
		int s5_element[a->rows][a->rows];
		square_matrix s6;
		int s6_element[a->rows][a->rows];
		square_matrix s7;
		int s7_element[a->rows][a->rows];
		square_matrix s8;
		int s8_element[a->rows][a->rows];
		square_matrix s9;
		int s9_element[a->rows][a->rows];
		square_matrix s10;
		int s10_element[a->rows][a->rows];

		square_matrix p1;
		int p1_element[a->rows][a->rows];
		square_matrix p2;
		int p2_element[a->rows][a->rows];
		square_matrix p3;
		int p3_element[a->rows][a->rows];
		square_matrix p4;
		int p4_element[a->rows][a->rows];
		square_matrix p5;
		int p5_element[a->rows][a->rows];
		square_matrix p6;
		int p6_element[a->rows][a->rows];
		square_matrix p7;
		int p7_element[a->rows][a->rows];


		set_square_matrix(&s1, a->rows, (int *)s1_element);
		set_square_matrix(&s2, a->rows, (int *)s2_element);
		set_square_matrix(&s3, a->rows, (int *)s3_element);
		set_square_matrix(&s4, a->rows, (int *)s4_element);
		set_square_matrix(&s5, a->rows, (int *)s5_element);
		set_square_matrix(&s6, a->rows, (int *)s6_element);
		set_square_matrix(&s7, a->rows, (int *)s7_element);
		set_square_matrix(&s8, a->rows, (int *)s8_element);
		set_square_matrix(&s9, a->rows, (int *)s9_element);
		set_square_matrix(&s10, a->rows, (int *)s10_element);

		set_square_matrix(&p1, a->rows, (int *)p1_element);
		set_square_matrix(&p2, a->rows, (int *)p2_element);
		set_square_matrix(&p3, a->rows, (int *)p3_element);
		set_square_matrix(&p4, a->rows, (int *)p4_element);
		set_square_matrix(&p5, a->rows, (int *)p5_element);
		set_square_matrix(&p6, a->rows, (int *)p6_element);
		set_square_matrix(&p7, a->rows, (int *)p7_element);



		child_square_matrix_minus(b, b12, b22, &s1);
		
		print_square_matrix_element_by_root_rows(&s1);

		child_square_matrix_add(a, a11, a12, &s2);
		print_square_matrix_element_by_root_rows(&s2);
		child_square_matrix_add(a, a21, a22, &s3);
		print_square_matrix_element_by_root_rows(&s3);
		child_square_matrix_minus(b, b21, b11, &s4);
		print_square_matrix_element_by_root_rows(&s4);
		child_square_matrix_add(a, a11, a22, &s5);
		print_square_matrix_element_by_root_rows(&s5);
		child_square_matrix_add(b, b11, b22, &s6);
		print_square_matrix_element_by_root_rows(&s6);
		child_square_matrix_minus(a, a12, a22, &s7);
		print_square_matrix_element_by_root_rows(&s7);
		child_square_matrix_add(b, b21, b22, &s8);
		print_square_matrix_element_by_root_rows(&s8);
		child_square_matrix_minus(a, a11, a21, &s9);
		print_square_matrix_element_by_root_rows(&s9);
		child_square_matrix_add(b, b11, b12, &s10);
		print_square_matrix_element_by_root_rows(&s10);


//3
		a->vec = a11;
		square_matrix_multiply_strassen(a, &s1, &p1);

		print_square_matrix_element(&p1);

		b->vec = b22;
		square_matrix_multiply_strassen(&s2, b, &p2);

		print_square_matrix_element(&p2);

		b->vec = b11;
		square_matrix_multiply_strassen(&s3, b, &p3);
		print_square_matrix_element(&p3);

		a->vec = a22;
		square_matrix_multiply_strassen(a, &s4, &p4);
		print_square_matrix_element(&p4);

		square_matrix_multiply_strassen(&s5, &s6, &p5);
		print_square_matrix_element(&p5);

		square_matrix_multiply_strassen(&s7, &s8, &p6);
		print_square_matrix_element(&p6);

		square_matrix_multiply_strassen(&s9, &s10, &p7);
		print_square_matrix_element(&p7);

//4
		c->vec = c11;
		add_to_c(c, p5.element);
		add_to_c(c, p4.element);
		minus_from_c(c, p2.element);
		add_to_c(c, p6.element);

		c->vec = c12;
		add_to_c(c, p1.element);
		add_to_c(c, p2.element);
			

		c->vec = c21;
		add_to_c(c, p3.element);
		add_to_c(c, p4.element);

		c->vec = c22;
		add_to_c(c, p5.element);
		add_to_c(c, p1.element);
		minus_from_c(c, p3.element);
		minus_from_c(c, p7.element);


		a->rows *= 2;
		b->rows *= 2;
		c->rows *= 2;
		a->vec = vectora;
		b->vec = vectorb;
		c->vec = vectorc;
	}

}



void test_square_matrix_multiply_strassen()
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
 
	square_matrix_multiply_strassen(&a, &b, &c);

	print_square_matrix_element(&a);
	print_square_matrix_element(&b);
	print_square_matrix_element(&c);
}

int main(int argc, const char *argv[])
{
	test_square_matrix_multiply_strassen();
	return 0;
}
