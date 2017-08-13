#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	GLuint MatrixID;
} Matrices;
struct obj
{
  float x;
  float y;
  float z;
  VAO *block;
  int orientation;
  float xangle;
  float zangle;
  int frag;
  int flag;

};
struct obj block;
struct obj tiles[100];
GLuint programID;
/*int gameplay [10][10]
={
  1,0,1,1,1,1,1,0,1,1,
  1,1,0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,0,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,0,0,1,1,0,0,0,1,1,
  1,1,0,1,1,0,0,1,1,0,
  1,0,0,1,1,0,0,0,1,1,
  1,1,1,1,1,1,1,0,1,1,
  0,0,0,1,1,1,0,0,0,1,
};*/
float xcm=0,zcm=0;
int tog=0;
int gameplay[10][10]
=
{
  1,1,1,1,1,1,1,3,1,5,
  1,1,1,1,1,1,1,1,1,1,
  1,2,1,1,1,1,1,1,1,1,
  1,2,1,1,1,1,0,0,1,1,
  1,2,1,1,0,5,0,0,0,1,
  1,2,1,1,1,1,0,0,0,1,
  1,0,1,1,1,1,1,1,1,1,
  1,1,1,1,0,1,1,1,1,1,
  4,1,1,1,0,0,0,0,1,1,
  1,1,1,1,1,1,1,0,0,1,
};
//int gameplay[10][10];
float xprev=0,zprev=0;
void level1( ){
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			gameplay[i][j]=1;
	for(int i=0;i<2;i++)
		for(int j=0;j<10;j++)
			gameplay[i][j]=0;
	for(int i=9;i>=8;i--)
		for(int  j=0;j<10;j++)
			gameplay[i][j]=0;
	gameplay[6][7]=4;
	gameplay[6][0]=0;
	gameplay[6][2]=0;
	gameplay[6][1]=0;
	gameplay[6][3]=0;
	gameplay[6][4]=0;
	int i=7;
	for(int j=0;j<6;j++)
		gameplay[i][j]=0;
	gameplay[i][9]=0;
	gameplay[5][0]=0;
	i=2;
	for(int j=3;j<10;j++)
		gameplay[i][j]=0;
	i=3;
	for(int j=6;j<10;j++)
		gameplay[i][j]=0;
	gameplay[4][9]=0;
	for(int i=0;i<10;i++)
		for(int j=10;j<15;j++)
			gameplay[i][j]=0;
}
/*int l2tog=0,l2f=0;
int l2togl=0,l2r=0;
int l3=0,r3=0;
int r4=0;
*/
void level2(){
	for(int i=0;i<10;i++)
		for(int j=0;j<15;j++)
			gameplay[i][j]=1;
	for(int i=0;i<3;i++)
		for(int j=0;j<15;j++)
			gameplay[i][j]=0;
	for(int i=8;i<10;i++)
		for(int j=0;j<15;j++)
			gameplay[i][j]=0;
	for(int i=3;i<8;i++){
		gameplay[i][4]=0;
		gameplay[i][5]=0;
	}
	int i=2;
	for(int j=6;j<15;j++)
		gameplay[i][j]=1;
	gameplay[2][10]=0;
	gameplay[2][11]=0;
	for(int i=3;i<8;i++)
		for(int j=10;j<12;j++)
			gameplay[i][j]=0;
	gameplay[7][12]=0;
	gameplay[7][13]=0;
	gameplay[7][14]=0;
	gameplay[3][13]=5;
	gameplay[4][2]=3;
	//l2tog=0;
	//l2f=0;
	gameplay[3][8]=4;
//	l2r=0;
	//l2togl=0;

}
void level3(){
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++)
			gameplay[i][j]=1;
	}
	for(int i=0;i<4;i++)
		for(int j=0;j<15;j++)
			gameplay[i][j]=0;
	for(int i=8;i<10;i++)
		for(int j=0;j<15;j++)
			gameplay[i][j]=0;
		for(int i=6;i<8;i++)
		for(int j=4;j<11;j++)
			gameplay[i][j]=0;
		gameplay[7][11]=0;
		int i=3;
		for(int j=6;j<15;j++)
			gameplay[i][j]=1;
		gameplay[4][4]=2;
		gameplay[4][5]=2;
    gameplay[4][6]=2;
		gameplay[4][9]=0;
		gameplay[4][10]=0;
		gameplay[5][9]=0;
		gameplay[5][10]=0;
		gameplay[3][13]=0;
		gameplay[3][14]=0;
		gameplay[4][13]=0;
		gameplay[4][14]=0;
		gameplay[6][13]=5;


}
void level4(){
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++)
			gameplay[i][j]=1;
	}
	int i=0;
	for(int j=0;j<15;j++)
		gameplay[i][j]=0;
	for(int i=1;i<3;i++){
		for(int j=0;j<3;j++)
			gameplay[i][j]=0;
		for(int j=13;j<15;j++)
			gameplay[i][j]=0;
	}
	for(int i=3;i<6;i++)
		for(int j=4;j<9;j++)
			gameplay[i][j]=0;
		gameplay[4][3]=0;
		gameplay[4][9]=0;
		gameplay[5][3]=0;
		gameplay[5][9]=0;
		gameplay[6][3]=0;
		gameplay[6][4]=0;
		gameplay[7][3]=0;
		gameplay[7][4]=0;

		for(int i=8;i<10;i++)
		for(int j=0;j<5;j++)
			gameplay[i][j]=0;
		for(int i=8;i<10;i++)
		for(int j=8;j<10;j++)
			gameplay[i][j]=0;

		gameplay[8][6]=4;
		gameplay[8][13]=5;
		gameplay[6][8]=6;
		gameplay[6][9]=6;
		gameplay[7][8]=6;
		gameplay[7][9]=6;

}
void level6(){
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++)
			gameplay[i][j]=1;
	}
	int i;
	//int i=0;
	//for(int j=0;j<15;j++)
	//	gameplay[i][j]=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<5;j++)
			gameplay[i][j]=0;
	}
	gameplay[1][6]=0;
	gameplay[1][7]=0;
	gameplay[2][6]=0;
	gameplay[2][7]=0;
	gameplay[3][6]=0;
	for(int i=3;i<6;i++){
		for(int j=7;j<11;j++)
			gameplay[i][j]=0;
	}
	gameplay[6][8]=0;
	gameplay[6][7]=0;
	gameplay[5][11]=0;
	for(i=6;i<9;i++)
	for(int j=11;j<15;j++)
		gameplay[i][j]=0;
	for(i=0;i<2;i++)
	for(int j=11;j<15;j++)
		gameplay[i][j]=0;
	gameplay[2][13]=0,gameplay[2][14]=0;
	for(i=4;i<9;i++)
	for(int j=0;j<4;j++)
		gameplay[i][j]=0;
	for(i=6;i<9;i++)
	for(int j=4;j<6;j++)
		gameplay[i][j]=0;
	gameplay[9][6]=0;
	gameplay[9][10]=0;
	gameplay[4][13]=4;
	for(int j=0;j<6;j++)
		gameplay[9][j]=0;
	for(int j=10;j<15;j++)
		gameplay[9][j]=0;
}
void level7(){
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++)
			gameplay[i][j]=1;
	}
	int i=0;
	for(int j=0;j<15;j++)
		gameplay[i][j]=0;
	i=9;
	for(int j=0;j<15;j++)
		gameplay[i][j]=0;
	for(int i=1;i<3;i++)
		for(int j=0;j<8;j++)
		gameplay[i][j]=0;
	for(int i=1;i<3;i++)
		for(int j=12;j<15;j++)
		gameplay[i][j]=0;
	i=3;
		for(int j=3;j<8;j++)
		gameplay[i][j]=0;
	gameplay[3][9]=0;
	gameplay[3][10]=0;
	gameplay[4][9]=0;
	for(int i=4;i<7;i++)
		for(int j=10;j<12;j++)
		gameplay[i][j]=0;
	for(int i=5;i<8;i++)
		for(int j=3;j<7;j++)
		gameplay[i][j]=0;
	for(int i=7;i<9;i++)
		for(int j=9;j<15;j++)
		gameplay[i][j]=0;
	gameplay[4][13]=4;
	gameplay[5][9]=2;

}
void level8(){
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++)
			gameplay[i][j]=0;
	}
	for(int i=4;i<7;i++){
		for(int j=0;j<6;j++)
			gameplay[i][j]=1;
	}
	for(int i=1;i<10;i++){
		for(int j=9;j<12;j++)
			gameplay[i][j]=1;
	}
	for(int i=4;i<7;i++){
		for(int j=12;j<15;j++)
			gameplay[i][j]=1;
	}
	gameplay[5][13]=4;
	gameplay[5][4]=7;
//l8f=0;
}
void level9(){
	for(int i=0;i<10;i++){
		for(int j=0;j<15;j++)
			gameplay[i][j]=0;
	}
	for(int i=3;i<6;i++){
		for(int j=0;j<4;j++)
			gameplay[i][j]=1;
	}
	for(int i=3;i<6;i++){
		for(int j=11;j<15;j++)
			gameplay[i][j]=1;
	}
	for(int i=5;i<6;i++){
		for(int j=4;j<15;j++)
			gameplay[i][j]=1;
	}
	gameplay[3][7]=1;
	gameplay[4][7]=1;
	gameplay[6][6]=1,gameplay[7][6]=1,gameplay[6][8]=1,gameplay[7][8]=1,gameplay[6][7]=4;
	gameplay[7][7]=1;
	gameplay[4][13]=7;

}


/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void quit(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
//    exit(EXIT_SUCCESS);
}
void init1();
int ltog=0;
int flag1=1;
void init();
void createtile(int a,int b,int c);
int checkcoll()
{
  int flag=0;
  int x1=2*xcm;
  int  z1=2*zcm;
  if(block.orientation==0)
  {
    //  printf("%d %d\n",x1,z1);

    if(gameplay[x1][z1]==0||x1>10||z1>10||x1<0||z1<0)
    {
      flag=1;
    }
    if(gameplay[x1][z1]==5)
    {
      flag=1;
      if(flag1<5)
      {
        flag1++;
      }
      printf("won the match");
    }
    if(gameplay[x1][z1]==3)
    {
      printf("hefa1\n");
      printf("%d %f %f  \n",tog,xprev,zprev);
      if(tog==1&&(xprev!=xcm||zprev!=zcm))
      {
        tog=0;
        gameplay[5][6]=0;
        gameplay[5][7]=0;
        printf("hii1\n");

        init();
      }
    else  if((tog!=1&&(xprev!=xcm||zprev!=zcm)))
      {
          printf("hwll\n" );
        tog=1;
        gameplay[5][6]=1;
        gameplay[5][7]=1;
        //xprev=xcm;
        //zprev=zcm;
        createtile(5,6,0);
      createtile(5,7,0);
      // init();
      //  tiles[]
      }
}
      if(gameplay[x1][z1]==4)
      {
        printf("hefa1\n");
        printf("%d %f %f  \n",tog,xprev,zprev);
        if(ltog==1&&(xprev!=xcm||zprev!=zcm))
        {
          ltog=0;
          gameplay[4][6]=0;
          gameplay[4][7]=0;
          printf("hii1\n");

          init();
        }
       else if((ltog!=1&&(xprev!=xcm||zprev!=zcm)))
            {
          ltog=1;
          gameplay[4][6]=1;
          gameplay[4][7]=1;
          //xprev=xcm;
          //zprev=zcm;
          createtile(4,6,0);
          createtile(4,7,0);
        //init();
        //  tiles[]
        }

    }
    xprev=xcm;
    zprev=zcm;
  }
  int x2=(xcm+0.25)*2;
  int z2=zcm*2;
  int x3=(xcm-0.25)*2;
  int z3=zcm*2;
  if(block.orientation==1)
  {
    if(gameplay[x2][z2]==0||gameplay[x3][z3]==0||x2>10||x2<0||z2>10||z2<0||x3>10||x3<0||z3>10||z3<0)
    {
      flag=1;
    }
    if(gameplay[x2][z2]==3||gameplay[x3][z3]==3)
    {
      if(tog==1&&(xprev!=xcm||zprev!=zcm))
      {
        tog=0;
        gameplay[5][6]=0;
        gameplay[5][7]=0;
        init();
      }
      else if(tog==0&&(xprev!=xcm||zprev!=zcm))
      {
        tog=1;
        gameplay[5][6]=1;
        gameplay[5][7]=1;
        init();
      }
    }
    xprev=xcm;
    zprev=zcm;
  }
  x2=(xcm)*2;
  z2=(zcm-0.25)*2;
  x3=(xcm)*2;
  z3=(zcm+0.25)*2;
  if(block.orientation==2)
  {
    //printf("%d %d %d %d %f %f\n",x2,z2,x3,z3,block.x,block.z);
    if(gameplay[x2][z2]==0||gameplay[x3][z3]==0||x2>10||x2<0||z2>10||z2<0||x3>10||x3<0||z3>10||z3<0)
    {
      flag=1;
    }
    if(gameplay[x2][z2]==3||gameplay[x3][z3]==3)
    {
      if(tog==1&&(xprev!=xcm||zprev!=zcm))
      {
        tog=0;
        gameplay[5][6]=0;
        gameplay[5][7]=0;
        init();
      }
      else if(tog==0&&(xprev!=xcm||zprev!=zcm))
      {
        tog=1;
        gameplay[5][6]=1;
        gameplay[5][7]=1;
        init();
      }
    }
    xprev=xcm;
    zprev=zcm;
  }

  return flag;
}

/* Generate VAO, VBOs and return VAO handle */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode=GL_FILL)
{
    struct VAO* vao = new struct VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers (1, &(vao->VertexBuffer)); // VBO - vertices
    glGenBuffers (1, &(vao->ColorBuffer));  // VBO - colors

    glBindVertexArray (vao->VertexArrayID); // Bind the VAO
    glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
                          0,                  // attribute 0. Vertices
                          3,                  // size (x,y,z)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    glBindBuffer (GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);  // Copy the vertex colors
    glVertexAttribPointer(
                          1,                  // attribute 1. Color
                          3,                  // size (r,g,b)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    return vao;
}

struct obj circle;
void createCircle(int a,int b)
{
	GLfloat vertex_buffer_data [360*9]={0};
	for(int i=0;i<360;i++)
	{
		vertex_buffer_data[9*i]=0;
		vertex_buffer_data[9*i+1]=0;
		vertex_buffer_data[9*i+2]=0;
		vertex_buffer_data[9*i+3]=0.2*cos(i*M_PI/180);
		vertex_buffer_data[9*i+4]=0;
		vertex_buffer_data[9*i+5]=0.2*sin(i*M_PI/180);;
		vertex_buffer_data[9*i+6]=0.2*cos((i+1)*M_PI/180);
		vertex_buffer_data[9*i+7]=0;
		vertex_buffer_data[9*i+8]=0.2*sin((i+1)*M_PI/180);
	}
	GLfloat color_buffer_data [360*9];
	GLfloat color_buffer_data1 [360*9];

	for (int i = 0; i<360*9 ; i+=3)
	{
		color_buffer_data[i]=0.7529;
		color_buffer_data[i+1]=0.7529;
		color_buffer_data[i+2]=0.7529;
	}
	for (int i = 0; i<360*9 ; i+=3)
	{
		color_buffer_data1[i]=0;
		color_buffer_data1[i+1]=1;
		color_buffer_data1[i+2]=0;
	}
	circle.block = create3DObject(GL_TRIANGLES,360*3,vertex_buffer_data,color_buffer_data,GL_FILL);
	//circle1 = create3DObject(GL_TRIANGLES,360*3,vertex_buffer_data,color_buffer_data1,GL_FILL);
circle.flag=1;
circle.x=(float)a;
circle.z=(float)a;

}

void createcube(float l,float b,float h)
{
  l=l/2;
  h=h/2;
  b=b/2;
  GLfloat a[]={

  		/* Rectangle 1 */

  		-l, -b, -h,
  		-l, -b, h,
  		l, -b, h,
  		l, -b, h,
  		l, -b, -h,
  		-l, -b, -h,

  		/* Rectangle 2 */

  		l, b, -h,
  		l, b, h,
  		l, -b, h,
  		l, -b, h,
  		l, -b, -h,
  		l, b, -h,

  		/* Rectangle 3 */

  		-l, b, -h,
  		-l, b, h,
  		l, b, h,
  		l, b, h,
  		l, b, -h,
  		-l, b, -h,

  		/* Rectangle 4 */

  		-l, b, -h,
  		-l, b, h,
  		-l, -b, h,
  		-l, -b, h,
  		-l, -b, -h,
  		-l, b, -h,

  		/* Rectangle 5 */

  		-l, -b, -h,
  		-l, b, -h,
  		l, b, -h,
  		l, b, -h,
  		l, -b, -h,
  		-l, -b, -h,

  		/* Rectangle 6 */
  		-l, -b, h,
  		-l, b, h,
  		l, b, h,
  		l, b, h,
  		l, -b, h,
  		-l, -b, h,

  };
  /*static const GLfloat color_buffer_data [] = {
  		1,0,0, // color 1
  		1,0,0, // color 2
      1,0,0, // color 3
      1,0,0,
      1,0,0,
      1,0,0,

      1,0,0, // color 1
  		1,0,0, // color 2
      1,0,0, // color 3
      1,0,0,
      1,0,0,
      1,0,0,

      1,0,0, // color 1
  		1,0,0, // color 2
      1,0,0, // color 3
      1,0,0,
      1,0,0,
      1,0,0,

      1,0,0, // color 1
  		1,0,0, // color 2
      1,0,0, // color 3
      1,0,0,
      1,0,0,
      1,0,0,

      1,0,0, // color 1
  		1,0,0, // color 2
      1,0,0, // color 3
      1,0,0,
      1,0,0,
      1,0,0,

      1,0,0, // color 1
  		1,0,0, // color 2
      1,0,0, // color 3
      1,0,0,
      1,0,0,
      1,0,0


};*/
GLfloat color_buffer_data[12*3*3];
for(int i=0;i<36;i++)
{
  color_buffer_data[3*i+0]=0.282;
  color_buffer_data[3*i+1]=0.23;
  color_buffer_data[3*i+2]=0.545;
}

block.block=create3DObject(GL_TRIANGLES,  6*6,  a,  color_buffer_data, GL_FILL );
block.x=0;
block.xangle=0;
block.zangle=0;
block.y=0;
block.z=0;
block.orientation=0;

}
float xtr=0;
float ztr=0;
/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode=GL_FILL)
{
    GLfloat* color_buffer_data = new GLfloat [3*numVertices];
    for (int i=0; i<numVertices; i++) {
        color_buffer_data [3*i] = red;
        color_buffer_data [3*i + 1] = green;
        color_buffer_data [3*i + 2] = blue;
    }

    return create3DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}

/* Render the VBOs handled by VAO */
void draw3DObject (struct VAO* vao)
{
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray (vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

/**************************
 * Customizable functions *
 **************************/

float triangle_rot_dir = 1;
float rectangle_rot_dir = 1;
bool triangle_rot_status = true;
bool rectangle_rot_status = true;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_C:
                rectangle_rot_status = !rectangle_rot_status;
                break;
            case GLFW_KEY_P:
                triangle_rot_status = !triangle_rot_status;
                break;
            case GLFW_KEY_X:
                // do something ..
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            case GLFW_KEY_RIGHT:
                  if(block.orientation==0)
                  {
                  //xtr+=0.5;
                  xcm+=0.75;
                  block.x+=0.5;
                  block.zangle-=90;
                  block.orientation=1;
                  }
                  else if(block.orientation==1)
                  {
                    //xtr+=1;
                    block.x+=1;
                    xcm+=0.75;
                    block.zangle=0;
                    block.orientation=0;
                  }
                  else if(block.orientation==2)
                  {
                  block.x+=0.5;
                  xcm+=0.5;
                  }
                  break;
              case GLFW_KEY_LEFT:
                        if(block.orientation==0)
                        {
                        block.x-=1;
                        xcm-=0.75;
                        block.zangle-=90;
                        block.orientation=1;
                        }
                        else if(block.orientation==1)
                        {
                          xcm-=0.75;
                          block.x-=0.5;
                          block.zangle=0;
                          block.orientation=0;
                        }
                        else if(block.orientation==2)
                        {
                          xcm-=0.5;
                          block.x-=0.5;
                        }
                        break;
                  case GLFW_KEY_UP:
                              if(block.orientation==0)
                              {
                              //xtr+=0.5;
                              block.z-=0.5;
                              zcm-=0.75;
                              block.xangle-=90;
                              block.orientation=2;
                              }
                              else if(block.orientation==1)
                              {
                                //xtr+=1;
                                block.z-=0.5;
                                zcm-=0.5;
                                //block.zangle=0;
                                //block.orientation=0;
                              }
                              else if(block.orientation==2)
                              {
                              //block.x+=0.5;
                              block.xangle=0;
                              zcm-=0.75;
                              block.z-=1;
                              block.orientation=0;


                              }
                              break;
                      case GLFW_KEY_DOWN:
                                  if(block.orientation==0)
                                    {
                                      //xtr+=0.5;
                                      block.z+=1;
                                      block.xangle-=90;
                                      block.orientation=2;
                                      zcm+=0.75;
                                      }
                                    else if(block.orientation==1)
                                        {
                                        //xtr+=1;
                                        block.z+=0.5;
                                        zcm+=0.5;
                                        //block.zangle=0;
                                        //block.orientation=0;
                                        }
                                      else if(block.orientation==2)
                                        {
                                      //block.x+=0.5;
                                        block.xangle=0;
                                        block.z+=0.5;
                                        block.orientation=0;
                                        zcm+=0.75;
                                        }
                                      break;

            default:
                break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
	switch (key) {
		case 'Q':
		case 'q':
            quit(window);
            break;
		default:
			break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_RELEASE)
                triangle_rot_dir *= -1;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_RELEASE) {
                rectangle_rot_dir *= -1;
            }
            break;
        default:
            break;
    }
}


/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
    int fbwidth=width, fbheight=height;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
     is different from WindowSize */
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

	GLfloat fov = 90.0f;

	// sets the viewport of openGL renderer
	glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

	// set the projection matrix as perspective
	/* glMatrixMode (GL_PROJECTION);
	   glLoadIdentity ();
	   gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
	// Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    // Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

    // Ortho projection for 2D views
    Matrices.projection = glm::ortho(-6.0f, 6.0f, -4.0f, 4.0f, 0.1f, 500.0f);
  //  Matrices.projection = glm::perspective(fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);
}

VAO *triangle, *rectangle;

// Creates the triangle object used in this sample code
void createTriangle ()
{
  /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

  /* Define vertex array as used in glBegin (GL_TRIANGLES) */
  static const GLfloat vertex_buffer_data [] = {
    0, 1,0, // vertex 0
    -1,-1,0, // vertex 1
    1,-1,0, // vertex 2
  };

  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 0
    0,1,0, // color 1
    0,0,1, // color 2
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  triangle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}

// Creates the rectangle object used in this sample code
void createRectangle ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
    -1.2,-1,0, // vertex 1
    1.2,-1,0, // vertex 2
    1.2, 1,0, // vertex 3

    1.2, 1,0, // vertex 3
    -1.2, 1,0, // vertex 4
    -1.2,-1,0  // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
    0.3,0.3,0.3, // color 4
    1,0,0  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}

float camera_rotation_angle = 120;
float rectangle_rotation = 0;
float triangle_rotation = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void createtile(int i1,int j1,int k)
{
  int index;
  for(int i=0;i<100;i++)
  {
      if(tiles[i].flag==0)
      {
        index=i;
        break;
     }
  }
/*  static const GLfloat vertex_buffer_data [] = {
    -0.25,-0.5,0.25, // vertex 1
    0.25,-0.5,0.25, // vertex 2
    0.25, -0.5,-0.25, // vertex 3

    0.25, -0.5,-0.25, // vertex 3
    -0.25, -0.5,-0.25, // vertex 4
    -0.25,-0.5,0.25  // vertex 1
  };*/
  float l=0.5;
  float h=0.5;
  float b=0.10;
  l=l/2;
  h=h/2;
  b=b/2;
  GLfloat a[]={

  		/* Rectangle 1 */

  		-l, -b, -h,
  		-l, -b, h,
  		l, -b, h,
  		l, -b, h,
  		l, -b, -h,
  		-l, -b, -h,

  		/* Rectangle 2 */

  		l, b, -h,
  		l, b, h,
  		l, -b, h,
  		l, -b, h,
  		l, -b, -h,
  		l, b, -h,

  		/* Rectangle 3 */

  		-l, b, -h,
  		-l, b, h,
  		l, b, h,
  		l, b, h,
  		l, b, -h,
  		-l, b, -h,

  		/* Rectangle 4 */

  		-l, b, -h,
  		-l, b, h,
  		-l, -b, h,
  		-l, -b, h,
  		-l, -b, -h,
  		-l, b, -h,

  		/* Rectangle 5 */

  		-l, -b, -h,
  		-l, b, -h,
  		l, b, -h,
  		l, b, -h,
  		l, -b, -h,
  		-l, -b, -h,

  		/* Rectangle 6 */
  		-l, -b, h,
  		-l, b, h,
  		l, b, h,
  		l, b, h,
  		l, -b, h,
  		-l, -b, h,

  };

  GLfloat color_buffer_data1[12*3*3];
  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    /*0,1,0, // color 3
    0.3,0.3,0.3, // color 4
    1,0,0  // color 1*/
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0,

    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0,

    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0,

    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0,

    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0,

  };
  static const GLfloat color_buffer_data2 [] = {
    0,1,0, // color 1
    0,1,0, // color 2
    0,1,0, // color 3

    /*0,1,0, // color 3
    0.3,0.3,0.3, // color 4
    1,0,0  // color 1*/
    0,1,0, // color 1
    0,1,0, // color 2
    0,1,0,

    0,1,0, // color 1
    0,1,0, // color 2
    0,1,0,

    0,1,0, // color 1
    0,1,0, // color 2
    0,1,0,

    0,1,0, // color 1
    0,1,0, // color 2
    0,1,0,

    0,1,0, // color 1
    0,1,0, // color 2
    0,1,0,

  };
  GLfloat color_buffer_data11[12*3*3];
  GLfloat color_buffer_data21[12*3*3];



  for (int v = 0; v < 12*3 ; v++){
    color_buffer_data11[3*v+0] = 0.8;
    color_buffer_data11[3*v+1] = 0.8;
    color_buffer_data11[3*v+2] = 0.6;
  }
  for (int v = 0; v < 12*3 ; v++){
    color_buffer_data21[3*v+0] = 1;
    color_buffer_data21[3*v+1] = 1;
    color_buffer_data21[3*v+2] = 1;
  }
  for (int v = 0; v < 12*3 ; v++){
    color_buffer_data1[3*v+0] = 0.85;
    color_buffer_data1[3*v+1] = 0.647;
    color_buffer_data1[3*v+2] = 0.125;
  }
  if(k==0||k==2)
  {

    if((i1+j1)%2==0)
    {
        tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data11, GL_FILL);
    }
    else
    {
        tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data21, GL_FILL);
    }
    tiles[index].frag=0;
  }
else if(k==1)
{
  tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data1, GL_FILL);
  tiles[index].frag=1;
}
/*else if(k==2)k
{
  tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data2, GL_FILL);
}*/

tiles[index].x=(float)i1;
tiles[index].y=-0.51;
tiles[index].z=(float)j1;
tiles[index].flag=1;

}
float y=0;
float y12=0;
int fl2=0;
struct obj tex[2];
void createx(int  x,int y)
{
  static const GLfloat vertex_buffer_data [] = {
      -0.25,-0.5,0.25, // vertex 1
      -0.25,-0.5,0.25, // vertex 2
      0.25, -0.5,-0.25, // vertex 3
};
static const GLfloat color_buffer_data [] = {
  0,0,0, // color 1
  0,0,0, // color 2
  0,0,0, // color 3
};
static const GLfloat vertex_buffer_data1 [] = {
    0.25,-0.5,0.25, // vertex 1
    0.25,-0.5,0.25, // vertex 2
    -0.25, -0.5,-0.25, // vertex 3
};
tex[0].block=create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
tex[1].block=create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, color_buffer_data, GL_LINE);
tex[0].x=(float)x;
tex[0].z=(float)y;
tex[1].x=(float)x;
tex[1].z=(float)y;
tex[0].flag=1;
tex[1].flag=1
;
}
double utime;
void draw ()
{
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f)+2.5, 4 , 5*sin(camera_rotation_angle*M_PI/180.0f)+2.5 );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (2.5, 0, 2.5);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
   Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //  Don't change unless you are sure!!
 //Matrices.view = glm::lookAt(glm::vec3(-20,20,-15), glm::vec3(0,0,0), glm::vec3(1,1,8/3)); // Fixed camera for 2D (ortho) in XY plane
 //Matrices.view = glm::lookAt(glm::vec3(3,2,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
  // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  //  Don't change unless you are sure!!
//Matrices.view = glm::lookAt(glm::vec3(3,2,), glm::vec3(0,0,1), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
  glm::mat4 VP = Matrices.projection * Matrices.view;

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  //  Don't change unless you are sure!!
  glm::mat4 MVP;	// MVP = Projection * View * Model

  // if identity to model matrix


  // Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
  // glPopMatrix ();
  int fl=0;

  fl=checkcoll();
  double ctime=glfwGetTime();
  if(ctime-utime>0.05&&fl==1)
  {
  y-=0.5;
  utime=glfwGetTime();
}
if(y<-20)
{
  if(flag1==1)
  {
    //level1();
    init1();
    init();
  }
  if(flag1==2)
  {
    //level2();
    init1();
    init();
  }
  if(flag1==3)
  {
    //level3();
    init1();
    init();
  }
}
ctime=glfwGetTime();
if(ctime-utime>0.05&&fl2==1)
{
y12-=0.5;
utime=glfwGetTime();
}
if(y12<-20)
{
if(flag1==1)
{
  //level1();
  init1();
  init();
}
if(flag1==2)
{
  //level2();
  init1();
  init();
}
if(flag1==3)
{
  //level3();
  init1();
  init();
}
}
    if(fl==1)
  {

    Matrices.model = glm::mat4(1.0f);
  glm::mat4 translateRectangle = glm::translate (glm::vec3(block.x, y-0.25, block.z));        // glTranslatef
    glm::mat4 tra = glm::translate (glm::vec3(0, 0.25, 0));
  glm::mat4 rotateRectangle = glm::rotate((float)(block.zangle*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  glm::mat4 rotateRectangle2 = glm::rotate((float)(block.xangle*M_PI/180.0f), glm::vec3(1,0,0)); // rotate about vector (-1,1,1)
  Matrices.model *= (translateRectangle*rotateRectangle2*rotateRectangle*tra);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(block.block);
}


  else if(fl!=1&&fl2!=1)
  {

    y=0;
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateRectangle = glm::translate (glm::vec3(block.x,-0.25, block.z));        // glTranslatef
      glm::mat4 tra = glm::translate (glm::vec3(0, 0.25, 0));
    glm::mat4 rotateRectangle = glm::rotate((float)(block.zangle*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    glm::mat4 rotateRectangle2 = glm::rotate((float)(block.xangle*M_PI/180.0f), glm::vec3(1,0,0)); // rotate about vector (-1,1,1)
    Matrices.model *= (translateRectangle*rotateRectangle2*rotateRectangle*tra);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(block.block);
  }
  else if(fl!=1&&fl2==1)
  {

      Matrices.model = glm::mat4(1.0f);
        glm::mat4 translateRectangle = glm::translate (glm::vec3(block.x,y12-0.25, block.z));        // glTranslatef
      glm::mat4 tra = glm::translate (glm::vec3(0, 0.25, 0));
    glm::mat4 rotateRectangle = glm::rotate((float)(block.zangle*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    glm::mat4 rotateRectangle2 = glm::rotate((float)(block.xangle*M_PI/180.0f), glm::vec3(1,0,0)); // rotate about vector (-1,1,1)
    Matrices.model *= (translateRectangle*rotateRectangle2*rotateRectangle*tra);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(block.block);
  }

  // draw3DObject draws the VAO given to it using current MVP matrix


  for(int i=0;i<100;i++)
  {
    if(tiles[i].flag==1)
    {
      if(tiles[i].frag==0)
      {
  Matrices.model = glm::mat4(1.0f);
  float m=tiles[i].x/2.0;
  float n=tiles[i].z/2.0;
  glm::mat4 translateRectangle1 = glm::translate (glm::vec3(m, -0.57,n));        // glTranslatef
  glm::mat4 rotateRectangle1 = glm::rotate((float)(90*M_PI/180.0f), glm::vec3(1,0,0 )); // rotate about vector (-1,1,1)
  Matrices.model *= (translateRectangle1);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(tiles[i].block);
}

else if(tiles[i].frag==1)
{
  int l1=xcm*2;
  int m1=zcm*2;
if(block.orientation==0&&tiles[i].x==l1&&tiles[i].z==m1)
{
//y12-=0.5;
printf("hello\n");
  fl2=1;
  Matrices.model = glm::mat4(1.0f);
  float m=tiles[i].x/2.0;
  float n=tiles[i].z/2.0;
  glm::mat4 translateRectangle1 = glm::translate (glm::vec3(m, y12-0.57,n));        // glTranslatef
  glm::mat4 rotateRectangle1 = glm::rotate((float)(90*M_PI/180.0f), glm::vec3(1,0,0 )); // rotate about vector (-1,1,1)
  Matrices.model *= (translateRectangle1);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(tiles[i].block);

}
else
{
//fl2=0;
//y12=0;
Matrices.model = glm::mat4(1.0f);
float m=tiles[i].x/2.0;
float n=tiles[i].z/2.0;
glm::mat4 translateRectangle1 = glm::translate (glm::vec3(m, -0.57,n));        // glTranslatef
glm::mat4 rotateRectangle1 = glm::rotate((float)(90*M_PI/180.0f), glm::vec3(1,0,0 )); // rotate about vector (-1,1,1)
Matrices.model *= (translateRectangle1);
MVP = VP * Matrices.model;
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

// draw3DObject draws the VAO given to it using current MVP matrix
draw3DObject(tiles[i].block);

}
}
}
}
// Increment angles
  float increments = 1;

  //camera_rotation_angle++; // Simulating camera rotation
  triangle_rotation = triangle_rotation + increments*triangle_rot_dir*triangle_rot_status;
  rectangle_rotation = rectangle_rotation + increments*rectangle_rot_dir*rectangle_rot_status;
  if(tex[0].flag==1)
  {
    for(int i=0;i<2;i++)
    {
      Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateRectangle3 = glm::translate (glm::vec3(0,0,3.5));        // glTranslatef
    Matrices.model *= (translateRectangle3);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(tex[i].block);

    }
  }
  if(circle.flag==1)
  {
    Matrices.model = glm::mat4(1.0f);

  glm::mat4 translateRectangle31 = glm::translate (glm::vec3(4,-0.5,0));        // glTranslatef
  Matrices.model *= (translateRectangle31);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(circle.block);
  }
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
//        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
//        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
	// Create the models
	//createTriangle (); // Generate the VAO, VBOs, vertices data & copy into the array buffer
	//createRectangle ();
  createcube(0.5,1,0.5);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor (0.529f, 0.807f, 0.92f, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
int main (int argc, char** argv)
{
	int width = 1500;
	int height = 800;

    GLFWwindow* window = initGLFW(width, height);
    for (int i = 0; i < 100; i++) {
      /* code */
      tiles[i].flag=0;
    }
    //level1();

	initGL (window, width, height);
  //init();

  for (int i = 0; i < 10; i++)
  {
    for(int j=0;j<10;j++)
    {
      if(gameplay[i][j]==1)
      {
          createtile(i,j,0);
      }
      else if(gameplay[i][j]==2)
      {
        createtile(i,j,1);
      }
      else if(gameplay[i][j]==3)
      {
        printf("%d %d",i,j);
        createtile(i,j,0);
        createx(i,j);
      }
      else if(gameplay[i][j]==4)
      {
        createtile(i,j,2);
        createCircle(i,j);
      }
    }
    /* code */
  }

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {

        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            last_update_time = current_time;
        }
    }

    glfwTerminate();
//    exit(EXIT_SUCCESS);0
}


void init()
{
  for (int i = 0; i < 100; i++) {
    /* code */
    tiles[i].flag=0;
  }
  for (int i = 0; i < 10; i++)
  {
    for(int j=0;j<10;j++)
    {
      if(gameplay[i][j]==1)
      {
          createtile(i,j,0);
      }
      else if(gameplay[i][j]==2)
      {
        createtile(i,j,1);
      }
      else if(gameplay[i][j]==3)
      {
        printf("%d %d",i,j);
        createtile(i,j,0);
        createx(i,j);
      }
      else if(gameplay[i][j]==4)
      {
        createtile(i,j,2);
      }
    }
    /* code */
  }

}

void init1()
{
    createcube(0.5,1,0.5);
    xcm=0;zcm=0;
    xprev=0;
    zprev=0;
    y12=0;
    y=0;
    //fl=0;
    fl2=0;

}
