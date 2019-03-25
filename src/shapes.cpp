#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926

void shift_shape(GLfloat shape[], int off, int len, float shift_x, float shift_y, float shift_z)
{
	
	for(int i = off, j = off+1, k = off+2; i < len && j < len && k < len; i+=3, j+=3, k+=3){
		shape[i] += shift_x;
		shape[j] += shift_y;
		shape[k] += shift_z;
	}
}

void color_shape(GLfloat color_data[], int off, int len, const float color[])
{
	for(int i = off; i < len; i+=3){
		color_data[i] = color[0];
		color_data[i+1] = color[1];
		color_data[i+2] = color[2];
	}
}
void create_triangle(GLfloat shape[], int i, float x[], float y[], float z[])
{
	shape[i] = x[0];
	shape[i + 1] = x[1];
	shape[i + 2] = x[2];
	shape[i + 3] = y[0];
	shape[i + 4] = y[1];
	shape[i + 5] = y[2];
	shape[i + 6] = z[0];
	shape[i + 7] = z[1];
	shape[i + 8] = z[2];
}

int create_regular_poly(GLfloat shape[], int len, int n, float r, float depth)
{
	float theta = 360.0/n, x = 0.0, y = r;
	int i;
	
	for(i = len; i < 9*n + len; i += 9){
		float up_x = x * cos((PI/180) * theta) - y * sin((PI/180) * theta);
		float up_y = x * sin((PI/180) * theta) + y * cos((PI/180) * theta);

		float p1[] = {x, depth, y};
		float p2[] = {up_x, depth, up_y};
		float p3[] = {0.0, depth, 0.0};
		create_triangle(shape, i, p1, p2, p3);
		x = up_x; y = up_y;

	}
	//shift_shape(shape, len, 9*n, pos_x, pos_y);
	return i;
}

int create_regular_poly(GLfloat shape[], int len, int n, float r)
{
	float theta = 360.0/n, x = 0.0, y = r;
	int i;
	
	for(i = len; i < 9*n + len; i += 9){
		float up_x = x * cos((PI/180) * theta) - y * sin((PI/180) * theta);
		float up_y = x * sin((PI/180) * theta) + y * cos((PI/180) * theta);

		float p1[] = {x, y, 0.0};
		float p2[] = {up_x, up_y, 0.0};
		float p3[] = {0.0, 0.0, 0.0};
		create_triangle(shape, i, p1, p2, p3);
		x = up_x; y = up_y;

	}
	//shift_shape(shape, len, 9*n, pos_x, pos_y);
	return i;
}

int create_frustum(GLfloat shape[], int len, float r1, float r2, float h)
{
	float incr = (r2 - r1)/h, i, j;
	if(!incr){
		printf("Upper and lower radius of frustum same\n");
		return 0;
	}
	int off = len;
	for(i = r2, j = 0; i > r1 && j < h; i-=incr*0.08, j+=incr*0.08){
		len = create_regular_poly(shape, off, 20, i, j);
		off = len;
		//printf("i = %f\n", i);
	}
	return len;
}

int create_cylinder(GLfloat shape[], int len, float r, float h)
{
	int off = len;
	for(float i = 0; i < h; i+=0.1){
		len = create_regular_poly(shape, off, 20, r, i);
		off = len;
	}
	return len;
}

int drawRectangle(GLfloat shape[], int i, float l, float b)
{
	float p1[] = {0.0, b, 0.0};
	float p2[] = {0.0, 0.0, 0.0};
	float p3[] = {l, b, 0.0};
	float p4[] = {l, 0.0, 0.0};

	create_triangle(shape, i, p1, p2, p3);
	create_triangle(shape, i+9, p4, p3, p2);
	//shift_shape(shape, 0, 18, x, y);

	/*for(int i = 0; i < 18; i+=3)
		printf("%f %f %f\n", shape[i], shape[i+1], shape[i+2]);
*/	
	return (18);
}

int drawRectangle(GLfloat shape[], int i, float l, float b, float z)
{
	float p1[] = {-l/2, z, -b/2};
	float p2[] = {-l/2, z, b/2};
	float p3[] = {l/2, z, -b/2};
	float p4[] = {l/2, z, b/2};

	create_triangle(shape, i, p1, p2, p3);
	create_triangle(shape, i+9, p4, p3, p2);

	return 18;
}

int create_cuboid(GLfloat shape[], int len, float l, float b, float h)
{
	int off = len;
	for(float i = 0; i < h; i+=0.03){
		len += drawRectangle(shape, off, l, b, i);
		off = len;
	}
	return len;
}
int draw_ring(GLfloat shape[], int len, float r, float size, float k)
{
	for(float theta = 0.0; theta < 360.0; theta+=k){
		float x = (r)*cos((PI/180) * theta);
		float y = r*sin((PI/180) * theta);

		int off = len;
		//printf("%d\n", off); 	
		len += drawRectangle(shape, off, size, size/5);
		shift_shape(shape, off, len, x, y, 0.0);
	}
	return len;
}
