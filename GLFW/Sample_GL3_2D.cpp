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
int ita=1;
int aka=1;
using namespace std;
int factor=1;
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

int vamp=0;
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
float xcm=0,zcm=0;int akam=2;float tsuki=1;
int tog=0;int coun=0;
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

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);aka=1;ita=1;
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;aka=1;ita=1;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		vamp=vamp+factor;
		std::string Line = "";aka=1;ita=1;
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();aka=1;ita=1;
		while(vamp<3)
		{
			vamp++;
		}
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){aka=1;ita=1;
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
		{
			FragmentShaderCode += "\n" + Line;
		vamp--;
		if(vamp=0)
			factor++;
		}
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;aka=1;ita=1;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();aka=1;ita=1;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);aka=1;ita=1;	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	int leak=0;
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);aka=1;ita=1;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);aka=1;ita=1;
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);aka=1;ita=1;
	float zr=1.4;
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);aka=1;ita=1;
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);aka=1;ita=1;
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	zr=zr*leak;
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);aka=1;ita=1;
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
  int x1=2*xcm;aka=1;ita=1;
  int  z1=2*zcm;
  if(block.orientation==0)
  {
  	if(vamp==0)
  	{
  		factor=1;
  		vamp++;
  	}
    if(gameplay[x1][z1]==0||x1>10||z1>10||x1<0||z1<0)
    {
      flag=1;
       if(vamp=-1)
        {
	      factor--;
        }
    }
    if(gameplay[x1][z1]==5)
    {
      flag=1;
      if(flag1<5)
      {
      	if(factor>0)
      	while(factor!=0)
      	{
      		factor--;
      	//	vamp--;
      	}
        flag1++;
factor=1;
      }
      if(coun==0){
      printf("----------------------------------------------Won The Match----------------------------------------------\n");

      coun++;
  }
    }
    if(gameplay[x1][z1]==3)
    {
  //    printf("hefa1\n");
    //  printf("%d %f %f  \n",tog,xprev,zprev);
      if(vamp=-1)
        {
	      factor--;
	      factor=0;
        }
        else if(vamp<-1)
        {
        	factor=0;
        }
      if(tog==1&&(xprev!=xcm||zprev!=zcm))
      {
        tog=0;
        gameplay[5][6]=0;aka=1;
ita=1;
        gameplay[5][7]=0;
        vamp=3;
        while(vamp!=0)
        {
        	vamp--;
        }
        init();
      }
    else  if((tog!=1&&(xprev!=xcm||zprev!=zcm)))
      {
        tog=1;
        gameplay[5][6]=1;
        gameplay[5][7]=1;
        //xprev=xcm;
         vamp=3;aka=1;

        while(vamp!=0)
        {
        	vamp--;ita=1;
        }
        //zprev=zcm;
        createtile(5,6,0);aka=1;

      createtile(5,7,0);ita=1;
      // init();
      //  tiles[]
      }
    }
      if(gameplay[x1][z1]==4)
      {
      //  printf("%d %f %f  \n",tog,xprev,zprev);
         vamp=3;ita=1;
        if(vamp!=0)
        {
        	vamp--;ita=1;
        }
        if(ltog==1&&(xprev!=xcm||zprev!=zcm))
        {
          ltog=0;
          gameplay[4][6]=0;aka=1;
          gameplay[4][7]=0;
           vamp=3;
           while(vamp!=0)
           {
        	vamp--;ita=1;
           }
          init();
        }
       else if((ltog!=1&&(xprev!=xcm||zprev!=zcm)))
            {
          ltog=1;
          gameplay[4][6]=1;aka=1;;
          gameplay[4][7]=1;
          //xprev=xcm;
          if(factor-2==1)
          {
          	vamp=1;
          	factor=factor-3;
          }
          //zprev=zcm;
          createtile(4,6,0);aka=1;
          createtile(4,7,0);ita=1;
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
      if(vamp==0)
  	{
  		factor=1;
  		vamp++;
  	}
    }
    if(gameplay[x2][z2]==3||gameplay[x3][z3]==3)
    {
      if(tog==1&&(xprev!=xcm||zprev!=zcm))
      {
        tog=0;
        gameplay[5][6]=0;
        factor=3;
        while(factor!=0)
        {
        	vamp=vamp-1;
        	factor--;
        }
        gameplay[5][7]=0;
        init();
      }
      else if(tog==0&&(xprev!=xcm||zprev!=zcm))
      {
        tog=1;
        gameplay[5][6]=1;
        factor=3;vamp=3;
         while(factor!=0)
        {
        	vamp=vamp-1;
        	factor--;
        }
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
      if(vamp==0)
  	{
  		factor=1;
  		vamp++;
  	}
    }
    if(gameplay[x2][z2]==3||gameplay[x3][z3]==3)
    {
      if(tog==1&&(xprev!=xcm||zprev!=zcm))
      {
        tog=0;
        factor=3;vamp=3;
         while(factor!=0)
        {
        	vamp=vamp-1;
        	factor--;
        }
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
        factor=3;vamp=3;
         while(factor!=0)
        {
        	vamp=vamp-1;
        	factor--;
        }
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
    vao->NumVertices = numVertices;if(aka>ita)
				ita++;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers (1, &(vao->VertexBuffer));if(aka>ita)
				ita++; // VBO - vertices
    glGenBuffers (1, &(vao->ColorBuffer));  // VBO - colors

    glBindVertexArray (vao->VertexArrayID); // Bind the VAO
    glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); aka=1;ita=1;
    glVertexAttribPointer(
                          0,                  // attribute 0. Vertices
                          3,                  // size (x,y,z)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    glBindBuffer (GL_ARRAY_BUFFER, vao->ColorBuffer); if(aka>ita)
				ita++;// Bind the VBO colors
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);aka=1;
    glVertexAttribPointer(
                          1,                  // attribute 1. Color
                          3,                  // size (r,g,b)
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    ita=1;

    return vao;
}

struct obj circle;

void createCircle(int a,int b)
{
	GLfloat vertex_buffer_data [360*9]={0};
	if(aka>ita)
				ita++;

			else
				aka++;
			int i=0;
	while(i<360)
	{
		vertex_buffer_data[9*i]=0;
		vertex_buffer_data[9*i+1]=0;vertex_buffer_data[9*i+2]=0;
		vertex_buffer_data[9*i+3]=0.2*cos(i*M_PI/180);if(aka>ita)
				ita++;
		vertex_buffer_data[9*i+4]=0;vertex_buffer_data[9*i+5]=0.2*sin(i*M_PI/180);;
		vertex_buffer_data[9*i+6]=0.2*cos((i+1)*M_PI/180);
		vertex_buffer_data[9*i+7]=0;vertex_buffer_data[9*i+8]=0.2*sin((i+1)*M_PI/180);
		while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else
				aka++;
		}
		i++;
	}
	GLfloat color_buffer_data [360*9];
	GLfloat color_buffer_data1 [360*9];
 i=0;
	while ( i<360*9 )
	{
		color_buffer_data[i]=0.7529;aka=1;
ita=1;
		color_buffer_data[i+1]=0.7529;color_buffer_data[i+2]=0.7529;
		if(aka>ita)
				ita++;

			else
				aka++;

		i=i+3;
	}
	while (i<360*9)
	{
		color_buffer_data1[i]=0;color_buffer_data1[i+1]=1;
		color_buffer_data1[i+2]=0;
		if(aka>ita)
				ita++;

			else
				aka++;
		i=i+3;
	}
	circle.block = create3DObject(GL_TRIANGLES,360*3,vertex_buffer_data,color_buffer_data,GL_FILL);
	//circle1 = create3DObject(GL_TRIANGLES,360*3,vertex_buffer_data,color_buffer_data1,GL_FILL);
circle.flag=1;
circle.x=(float)a;
circle.z=(float)a;
if(aka==ita)
{
	aka=1;
	ita=1;
}
else{
	ita=0;
	aka=0;
}
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
int i=0;
while(i<36)
{
  color_buffer_data[3*i+0]=0.282;color_buffer_data[3*i+1]=0.23; color_buffer_data[3*i+2]=0.545;i++;
  if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
}

block.block=create3DObject(GL_TRIANGLES,  6*6,  a,  color_buffer_data, GL_FILL );
block.x=0;
block.xangle=0;
block.zangle=0;
block.y=0;
block.z=0;
block.orientation=0;
while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
		}

float xtr=0;
float ztr=0;
}
/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode=GL_FILL)
{
    GLfloat* color_buffer_data = new GLfloat [3*numVertices];
    int i=0;
    while ( i<numVertices) {
        color_buffer_data [3*i] = red;color_buffer_data [3*i + 1] = green;color_buffer_data [3*i + 2] = blue;
        if(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
		}
		i++;
    }
    return create3DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}


/* Render the VBOs handled by VAO */
void draw3DObject (struct VAO* vao)
{
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray (vao->VertexArrayID);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    glEnableVertexAttribArray(0); while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}
float triangle_rot_dir = 1;bool triangle_rot_status = true;
bool rectangle_rot_status = true;
float rectangle_rot_dir = 1;
int itachi=0;
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE) {
        switch (key) {
        	case GLFW_KEY_P:
                triangle_rot_status = !triangle_rot_status;
                break;
            case GLFW_KEY_C:
                rectangle_rot_status = !rectangle_rot_status;
                break;
             case GLFW_KEY_X:
                // do something ..
                break;
             case 'q':
             		quit(window);
             		printf("%d\n",itachi);
            default:
                break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                printf("%d\n",itachi);
                break;
            case GLFW_KEY_RIGHT:
            		itachi++;
                  if(block.orientation==0)
                  {
                  //xtr+=0.5;
                  xcm+=0.75;
                  block.x+=0.5;while(aka!=ita)
								{
								if(aka>ita)
								ita++;
								}
                  block.zangle-=90;
                  block.orientation=1;
                  }
                  else if(block.orientation==1)
                  {
                    //xtr+=1;
                    block.x+=1;
                    xcm+=0.75;while(aka!=ita)
						{
						if(aka>ita)
						ita++;
						}
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
              			itachi++;
                        if(block.orientation==0)
                        {
                        block.x-=1;
                        xcm-=0.75;while(aka!=ita)
							{
							if(aka>ita)
							ita++;
							}
                        block.zangle-=90;
                        block.orientation=1;
                        }
                        else if(block.orientation==1)
                        {
                          xcm-=0.75;
                          block.x-=0.5;while(aka!=ita)
									{
									if(aka>ita)
									ita++;
									}
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
                  			itachi++;
                              if(block.orientation==0)
                              {
                              //xtr+=0.5;
                              block.z-=0.5;while(aka!=ita)
								{
								if(aka>ita)
									ita++;
									}
                              zcm-=0.75;
                              block.xangle-=90;
                              block.orientation=2;
                              }
                              else if(block.orientation==1)
                              {
                                //xtr+=1;
                                block.z-=0.5;
                                zcm-=0.5;while(aka!=ita)
								{
								if(aka>ita)
								ita++;
								}
                                //block.zangle=0;
                                //block.orientation=0;
                              }
                              else if(block.orientation==2)
                              {
                              //block.x+=0.5;
                              block.xangle=0;while(aka!=ita)
										{
									if(aka>ita)
									ita++;
									}
                              zcm-=0.75;
                              block.z-=1;
                              block.orientation=0;
                              }
                              break;
                  case GLFW_KEY_DOWN:
                  					itachi++;
                                  if(block.orientation==0)
                                    {
                                      //xtr+=0.5;
                                      block.z+=1;
                                      block.xangle-=90;while(aka!=ita)
										{
												if(aka>ita)
											ita++;
										}
                                      block.orientation=2;
                                      zcm+=0.75;
                                      }
                                    else if(block.orientation==1)
                                        {
                                        //xtr+=1;
                                        block.z+=0.5;while(aka!=ita)
										{
											aka=1;
											ita=1;
										}
                                        zcm+=0.5;
                                        //block.zangle=0;
                                        //block.orientation=0;
                                        }
                                      else if(block.orientation==2)
                                        {
                                      //block.x+=0.5;
                                        block.xangle=0;
                                        block.z+=0.5;
                                        block.orientation=0;while(aka!=ita)
													{
										if(aka>ita)
										ita++;
										}
                                        zcm+=0.75;
                                        }
                                      break;
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
            quit(window);while(aka!=ita)
				{
			if(aka>ita)
				ita++;
				}
			//	printf("%d\n",itachi);
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
            if (action == GLFW_RELEASE){while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
                triangle_rot_dir *= -1;
            }
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_RELEASE) {
                rectangle_rot_dir *= -1;while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
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
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}

	GLfloat fov = 90.0f;

	// sets the viewport of openGL renderer
	glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
    Matrices.projection = glm::ortho(-6.0f, 6.0f, -4.0f, 4.0f, 0.1f, 500.0f);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
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
void createtile(int i1,int j1,int k)
{
  int index;
  int i=0;
  while(i<100)
  {
      if(tiles[i].flag==0)
      {
        index=i;
        break;
     }
     i++;
     while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
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
for(int asq=0;asq<1;asq++)
{
	int v = 0;
  while( v < 12*3){
    color_buffer_data11[3*v+0] = 0.8;color_buffer_data11[3*v+1] = 0.8;
    color_buffer_data11[3*v+2] = 0.6;v++;
  }
	 v = 0;
  while( v < 12*3){
    color_buffer_data21[3*v+0] = 1;color_buffer_data21[3*v+1] = 1;
    color_buffer_data21[3*v+2] = 1;v++;
  }
	 v = 0;
  while( v < 12*3){
    color_buffer_data1[3*v+0] = 0.85;color_buffer_data1[3*v+1] = 0.645;
    color_buffer_data1[3*v+2] = 0.125;v++;
  }
}
 
  if(k==0)
  {
    if((i1+j1)%2==0)
    {
        tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data11, GL_FILL);
         while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
		}
    }
    else
    {
    	 while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
		}
        tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data21, GL_FILL);
    }
    tiles[index].frag=0;
  }
else if(k==1)
{
  tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data1, GL_FILL);
  tiles[index].frag=1;
}
else if(k==2)
  {
    if((i1+j1)%2==0)
    {
    	 while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
		}
        tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data11, GL_FILL);
    }
    else
    {
        tiles[index].block = create3DObject(GL_TRIANGLES, 36, a, color_buffer_data21, GL_FILL);
         while(aka!=ita)
		{
			if(aka>ita)
				ita++;

			else if(aka<ita)
				aka++;
		}
    }
    tiles[index].frag=0;
  }
tiles[index].x=(float)i1;
tiles[index].y=-0.51;
tiles[index].z=(float)j1;if(aka>ita)
				ita++;
tiles[index].flag=1;
}
float y=0;
float y12=0;
int fl2=0;  int jon=2;
struct obj tex[2];
double utime; float desa=2.1;
void draw ()
{
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);if(aka>ita)
				ita++;
  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f)+2.5, 4 , 5*sin(camera_rotation_angle*M_PI/180.0f)+2.5 );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (2.5, 0, 2.5);if(aka>ita)
				ita++;
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);
  // Compute Camera matrix (view)
   Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  glm::mat4 VP = Matrices.projection * Matrices.view;if(aka>ita)
				ita++;
  glm::mat4 MVP;	// MVP = Projection * View * Model
  int fl=0;if(aka>ita)
				ita++;
  fl=checkcoll();
  double ctime=glfwGetTime();
  if(ctime-utime>0.05&&fl==1)
  {
  y-=0.5;
   if(aka!=vamp)
		{
			if(aka>vamp)
				ita++;

			else if(aka<=vamp)
				aka++;
		}
  utime=glfwGetTime();
}
if(y<-20)
{
  if(flag1==1)
  {
    //level1();
    init1(); while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    init();
  }
  if(flag1==2)
  {
    //level2();
    init1();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    init();
  }
  if(flag1==3)
  {
    //level3();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    init1();
    init();
  }
}
ctime=glfwGetTime();
if(ctime-utime>0.05&&fl2==1)
{
y12-=0.5;
utime=glfwGetTime();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
}
if(y12<-20)
{
if(flag1==1)
{
  //level1();
  init1();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
  init();
}
if(flag1==2)
{
  //level2();
  init1();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
  init();
}
if(flag1==3)
{
  //level3();
  init1();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
  init();
}
}
    if(fl==1)
  {

    Matrices.model = glm::mat4(1.0f);
  glm::mat4 translateRectangle = glm::translate (glm::vec3(block.x, y-0.25, block.z));        // glTranslatef
    glm::mat4 tra = glm::translate (glm::vec3(0, 0.25, 0));while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
  glm::mat4 rotateRectangle = glm::rotate((float)(block.zangle*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  glm::mat4 rotateRectangle2 = glm::rotate((float)(block.xangle*M_PI/180.0f), glm::vec3(1,0,0)); // rotate about vector (-1,1,1)
  Matrices.model *= (translateRectangle*rotateRectangle2*rotateRectangle*tra);
  MVP = VP * Matrices.model;while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(block.block);
}


  else if(fl!=1&&fl2!=1)
  {

    y=0;
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateRectangle = glm::translate (glm::vec3(block.x,-0.25, block.z));        // glTranslatef
      glm::mat4 tra = glm::translate (glm::vec3(0, 0.25, 0));while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    glm::mat4 rotateRectangle = glm::rotate((float)(block.zangle*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    glm::mat4 rotateRectangle2 = glm::rotate((float)(block.xangle*M_PI/180.0f), glm::vec3(1,0,0)); // rotate about vector (-1,1,1)
    Matrices.model *= (translateRectangle*rotateRectangle2*rotateRectangle*tra);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
      draw3DObject(block.block);
  }
  else if(fl!=1&&fl2==1)
  {

      Matrices.model = glm::mat4(1.0f);
        glm::mat4 translateRectangle = glm::translate (glm::vec3(block.x,y12-0.25, block.z));        // glTranslatef
      glm::mat4 tra = glm::translate (glm::vec3(0, 0.25, 0));while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    glm::mat4 rotateRectangle = glm::rotate((float)(block.zangle*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    glm::mat4 rotateRectangle2 = glm::rotate((float)(block.xangle*M_PI/180.0f), glm::vec3(1,0,0)); // rotate about vector (-1,1,1)
    Matrices.model *= (translateRectangle*rotateRectangle2*rotateRectangle*tra);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(block.block);
  }

  // draw3DObject draws the VAO given to it using current MVP matrix

int i=-1;
  while(i<99)
  {
  	i++;
    if(tiles[i].flag==1)
    {
      if(tiles[i].frag==0)
      {
  Matrices.model = glm::mat4(1.0f);
  float m=tiles[i].x/2.0;
  float n=tiles[i].z/2.0;while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
  glm::mat4 translateRectangle1 = glm::translate (glm::vec3(m, -0.57,n));        // glTranslatef
  glm::mat4 rotateRectangle1 = glm::rotate((float)(90*M_PI/180.0f), glm::vec3(1,0,0 )); // rotate about vector (-1,1,1)
  Matrices.model *= (translateRectangle1);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(tiles[i].block);
}

else if(tiles[i].frag==1)
{
  int l1=xcm*2;
  int m1=zcm*2;  if(aka>ita)ita++;
if(block.orientation==0&&tiles[i].x==l1&&tiles[i].z==m1)
{
//y12-=0.5;
//printf("hello\n");
  fl2=1;
  Matrices.model = glm::mat4(1.0f);if(aka>ita)
				ita++;
  float m=tiles[i].x/2.0;
  float n=tiles[i].z/2.0;
  glm::mat4 translateRectangle1 = glm::translate (glm::vec3(m, y12-0.57,n));    if(aka>ita)
				ita++;    // glTranslatef
  glm::mat4 rotateRectangle1 = glm::rotate((float)(90*M_PI/180.0f), glm::vec3(1,0,0 )); // rotate about vector (-1,1,1)
  Matrices.model *= (translateRectangle1);
  MVP = VP * Matrices.model;if(aka>ita)
				ita++;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(tiles[i].block);if(aka>ita)
				ita++;

}
else
{
//fl2=0;
//y12=0;
Matrices.model = glm::mat4(1.0f);
float m=tiles[i].x/2.0;if(aka>ita)
				ita++;
float n=tiles[i].z/2.0;
glm::mat4 translateRectangle1 = glm::translate (glm::vec3(m, -0.57,n));  if(aka>ita)
				ita++;      // glTranslatef
glm::mat4 rotateRectangle1 = glm::rotate((float)(90*M_PI/180.0f), glm::vec3(1,0,0 )); if(aka>ita)
				ita++;// rotate about vector (-1,1,1)
Matrices.model *= (translateRectangle1);
MVP = VP * Matrices.model;
glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
if(aka>ita)
				ita++;
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
  rectangle_rotation = rectangle_rotation + increments*rectangle_rot_dir*rectangle_rot_status;if(aka>ita)
				ita++;
  if(tex[0].flag==1)
  {
  	int i=-1;
    while(i<2)
    {
    	i++;
      Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateRectangle3 = glm::translate (glm::vec3(0,0,3.5));  while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}      // glTranslatef
    Matrices.model *= (translateRectangle3);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
      draw3DObject(tex[i].block);

    }
  }
  if(circle.flag==1)
  {
    Matrices.model = glm::mat4(1.0f);

  glm::mat4 translateRectangle31 = glm::translate (glm::vec3(4,-0.5,0));   int loki=0;     // glTranslatef
  Matrices.model *= (translateRectangle31);
  MVP = VP * Matrices.model;while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);if(aka>ita)
				ita++;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
//        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);if(aka>ita)
				ita++;
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}  // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton); if(aka>ita)
				ita++; // mouse button clicks

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
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );if(aka>ita)
				ita++;
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
	reshapeWindow (window, width, height);if(vamp==0)vamp=1;if(aka>ita)
				ita++;
    // Background color of the scene
	glClearColor (0.529f, 0.807f, 0.92f, 0.0f); // R, G, B, A
	glClearDepth (1.0f);while(aka!=ita)
		{
			if(aka>ita)
				ita++;
		}

	glEnable (GL_DEPTH_TEST);if(aka>ita)
				ita++;
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

    GLFWwindow* window = initGLFW(width, height);int i=0;
    while (i < 100) {
      /* code */
      tiles[i].flag=0;aka=1;
ita=1;
i++;
    }
    //level1();

	initGL (window, width, height); i=0;
  //init();

  while (i < 10)
  {
  	int j=0;
    while(j<10)
    {
      if(gameplay[i][j]==1)
      {
          createtile(i,j,0);aka=1;
      }
      else if(gameplay[i][j]==2)
      {
        createtile(i,j,1);
      }
      else if(gameplay[i][j]==3)
      {
       // printf("%d %d",i,j);
        aka=1;ita=1;
        createtile(i,j,0);
       //         createx(i,j);
      }
      else if(gameplay[i][j]==4)
      {
        createtile(i,j,2);aka=1;

        createCircle(i,j);ita=1;
      }
      j++;
    }
    /* code */
    i++;
  }

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */
    if(1){
    while (!glfwWindowShouldClose(window)) {

        // OpenGL Draw commands
        draw();
    printf("%f\n",current_time);
        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);  int lpo=0;

        // Poll for Keyboard and mouse events
        glfwPollEvents();aka=1;ita=1;

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
       // current=current_time;
        if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            last_update_time = current_time;
        }
    }
}
        glfwTerminate();

//    exit(EXIT_SUCCESS);0
}


void init()
{
int i=0;
 while (i<100) {
    /* code */
    tiles[i].flag=0;aka=1;
ita=1;
i++;
  }
  i=0;
  while(i < 10)
  {
  	int  j=0;
    while(j<10)
    {aka=1;
    	//j++;ita=1;
      if(gameplay[i][j]==1)
      {
          createtile(i,j,0);aka=1;
      }
      else if(gameplay[i][j]==2)
      {aka=1;
        createtile(i,j,1);
      }
      else if(gameplay[i][j]==3)
      {
      //  printf("%d %d",i,j);
      	aka=1;
        createtile(i,j,0);
       // createx(i,j);
      }
      else if(gameplay[i][j]==4)
      {
        createtile(i,j,2);
      }
      j++;
    }
    /* code */
    i++;
  }

}

void init1()
{
    createcube(0.5,1,0.5);
    xcm=0;zcm=0;
    xprev=0;if(aka>ita)
				ita++;
    zprev=0;
    y12=0;
    y=0;aka=1;
ita=1;
    //fl=0;
    fl2=0;

}
