/*
example implementation of the transformation in-class exercise
**/

#include <GL/Angel.h>
#include <math.h>
#pragma comment(lib, "glew32.lib")

//store window width and height
int ww=500, wh=500;

#define M_PI 3.14159265358979323846

//these are the extra variables needed for the exercise
GLfloat tx, ty, tz;
GLfloat rx, ry, rz;

//need some arrays to store cube attributes
//GLuint vao[1];
//GLuint vbo[2];
GLuint vao[2];
GLuint vbo[4];

//our modelview and perspective matrices
mat4 mv, p;

//and we'll need pointers to our shader variables
GLuint model_view;
GLuint projection;
GLuint vPosition;
GLuint vColor;

vec4 carVerts[6];
vec4 carColors[6];
void generateCar() {
	for(int i=0; i<6; i++){
		carColors[i] = vec4(1.0, 1.0, 1.0, 1.0); //front
	}
	carVerts[0] = vec4(1.0f, -1.0f, 1.0f, 1.0);
	carVerts[1] = vec4(1.0f, 1.0f, 1.0f, 1.0);
	carVerts[2] = vec4(-1.0f, 1.0f, 1.0f, 1.0);
	carVerts[3] = vec4(-1.0f, 1.0f, 1.0f, 1.0);
	carVerts[4] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	carVerts[5] = vec4(1.0f, -1.0f, 1.0f, 1.0);
}

vec4 cubeVerts[36];
vec4 cubeColors[36];
void generateCube(){
	for(int i=0; i<6; i++){
		cubeColors[i] = vec4(0.0, 1.0, 1.0, 1.0); //front
	}
	cubeVerts[0] = vec4(1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[1] = vec4(1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[2] = vec4(-1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[3] = vec4(-1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[4] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[5] = vec4(1.0f, -1.0f, 1.0f, 1.0);


	for(int i=6; i<12; i++){
		cubeColors[i] = vec4(1.0, 0.0, 1.0, 1.0); //back
	}
	cubeVerts[6] = vec4(-1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[7] = vec4(-1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[8] = vec4(1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[9] = vec4(1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[10] = vec4(1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[11] = vec4(-1.0f, -1.0f, -1.0f, 1.0);

	for(int i=12; i<18; i++){
		cubeColors[i] = vec4(1.0, 1.0, 0.0, 1.0); //left
	}
	cubeVerts[12] = vec4(1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[13] = vec4(1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[14] = vec4(1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[15] = vec4(1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[16] = vec4(1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[17] = vec4(1.0f, 1.0f, 1.0f, 1.0);

	for(int i=18; i<24; i++){
		cubeColors[i] = vec4(1.0, 0.0, 0.0, 1.0); //right
	}
	cubeVerts[18] = vec4(-1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[19] = vec4(-1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[20] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[21] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[22] = vec4(-1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[23] = vec4(-1.0f, 1.0f, -1.0f, 1.0);

	for(int i=24; i<30; i++){
		cubeColors[i] = vec4(0.0, 0.0, 1.0, 1.0); //top
	}
	cubeVerts[24] = vec4(1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[25] = vec4(1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[26] = vec4(-1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[27] = vec4(-1.0f, 1.0f, -1.0f, 1.0);
	cubeVerts[28] = vec4(-1.0f, 1.0f, 1.0f, 1.0);
	cubeVerts[29] = vec4(1.0f, 1.0f, 1.0f, 1.0);

	for(int i=30; i<36; i++){
		cubeColors[i] = vec4(0.0, 1.0, 0.0, 1.0); //bottom
	}
	cubeVerts[30] = vec4(1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[31] = vec4(1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[32] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[33] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	cubeVerts[34] = vec4(-1.0f, -1.0f, -1.0f, 1.0);
	cubeVerts[35] = vec4(1.0f, -1.0f, -1.0f, 1.0);
}



void Keyboard(unsigned char key, int x, int y) {
	/*exit when the escape key is pressed*/
	if (key == 27)
		exit(0);

	if(key == 'a')
		tz += 0.1;
	else if(key == 'z')
		tz -= 0.1;
	else if(key == 'i'){
		rx += 5;
		if(rx > 360)
			rx -= 360;
	}
	else if(key == 'j'){
		rx -= 5;
		if(rx < 0)
			rx += 360;
	}
	else if(key == 'o'){
		ry += 5;
		if(ry > 360)
			ry -= 360;
	}
	else if(key == 'k'){
		ry -= 5;
		if(ry < 0)
			ry += 360;
	}else if(key == 'p'){
		rz += 5;
		if(rz > 360)
			rz -= 360;
	}else if(key == 'l'){
		rz -= 5;
		if(rz < 0)
			rz += 360;
	}
	//don't forget to request a new frame since parameters have changed
	glutPostRedisplay();

}

void special(int key, int x, int y){
	if(key == GLUT_KEY_UP)
		ty += 0.1;
	else if(key == GLUT_KEY_DOWN)
		ty -= 0.1;
	else if(key == GLUT_KEY_LEFT)
		tx -= 0.1;
	else if(key == GLUT_KEY_RIGHT)
		tx += 0.1;

	//don't forget to request a new frame since parameters have changed
	glutPostRedisplay();
}

void init() {

	/*select clearing (background) color*/
	glClearColor(0.0, 0.0, 0.0, 0.0);


	//populate our arrays
	generateCube();
	generateCar();
	//set up transformation defaults
	//start with no translation or rotation
	tx = ty = tz = rx = ry = rz = 0;

	// Load shaders and use the resulting shader program
	GLuint program = InitShader( "vshader-transform.glsl", "fshader-transform.glsl" );
	glUseProgram( program );

	// Create a vertex array object
	glGenVertexArrays( 1, &vao[0] );

	// Create and initialize any buffer objects
	glBindVertexArray( vao[0] );
	glGenBuffers( 2, &vbo[0] );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//and now our colors for each vertex
	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(carColors), carColors, GL_STATIC_DRAW );
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);


	/*********************************************************
	* CAR
	*
	*********************************************************/
	// Create and initialize **CAR** buffer objects
	// Create a vertex array object
	glGenVertexArrays( 1, &vao[1] );
	glBindVertexArray( vao[1] );
	glGenBuffers( 2, &vbo[2] );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[2] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(carVerts), carVerts, GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//and now our colors for each vertex
	glBindBuffer( GL_ARRAY_BUFFER, vbo[3] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(carColors), carColors, GL_STATIC_DRAW );
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);


	//grab pointers for our modelview and perspecive uniform matrices
	model_view = glGetUniformLocation(program, "model_view");
	projection = glGetUniformLocation(program, "projection");

	//Only draw the things in the front layer
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	/*clear all pixels*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mv = LookAt(vec4(0, 0, 20, 1.0), vec4(0, 0, 0, 1.0), vec4(0, 1, 0, 0.0));

	mv = mv * Translate(-4,-4,0);
	mv = mv * Translate(tx, ty, tz);

	mv = mv *RotateX(rx);
	mv = mv * RotateY(ry);
	mv = mv * RotateZ(rz);

	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glUniformMatrix4fv(projection, 1, GL_TRUE, p);

	glBindVertexArray( vao[0] );
	glDrawArrays( GL_TRIANGLES, 0, 36 );    // draw the cube 

	/* second cube */
	mv = LookAt(vec4(0, 0, 20, 1.0), vec4(0, 0, 0, 1.0), vec4(0, 1, 0, 0.0));
	mv = mv * Translate(4, 4, 0);
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glUniformMatrix4fv(projection, 1, GL_TRUE, p);

	glBindVertexArray( vao[0] );
	glDrawArrays( GL_TRIANGLES, 0, 36 );    // draw the cube 


	/* draw car */
	mv = LookAt(vec4(0, 0, 20, 1.0), vec4(0, 0, 0, 1.0), vec4(0, 1, 0, 0.0));
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glUniformMatrix4fv(projection, 1, GL_TRUE, p);

	glBindVertexArray( vao[1] );
	glDrawArrays( GL_TRIANGLES, 0, 6 );    // draw the cube


	glFlush();
	/*start processing buffered OpenGL routines*/
	glutSwapBuffers();
}


void reshape(int width, int height){
	ww= width;
	wh = height;
	//field of view angle, aspect ratio, closest distance from camera to object, largest distanec from camera to object
	p = Perspective(45.0, (float)width/(float)height, 1.0, 100.0);

	glViewport( 0, 0, width, height );
}

int main(int argc, char **argv)
{
	/*set up window for display*/
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0); 
	glutInitWindowSize(ww, wh);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Transformations Exercise");  

	glewExperimental = GL_TRUE;

	glewInit();
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	//glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}