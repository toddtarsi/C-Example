#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#define PI 3.1415
#define HALF_PI PI/2.0
#define STEP_COUNT 1024.0
#define STEP_SIZE PI/STEP_COUNT

void writeLine(std::string lit_str) {
  std::cout << lit_str << std::endl;
}

int readInt(std::string variable) {
  writeLine("Enter positive nonzero integer value for " + variable + ".");
  std::string input;
  std::getline(std::cin, input);
  int j;
  std::stringstream(input) >> j;
  if (!(j > 0)) {
    writeLine("Invalid input detected. Setting to 1.");
    writeLine(std::to_string(j));
    j = 1;
  }
  return j;
}

namespace superformula {
  const float a = 1.0;
  const float b = 1.0;
  class PointCloud{
    private:
      float m;
      float n1;
      float n2;
      float n3;
      int size;
      std::vector<float> points;
      float point(float m, float n1, float n2, float n3, float theta) {
       	float a_val(fabs(cos(m * theta / 4.0) / a));
       	float b_val(fabs(sin(m * theta / 4.0) / b));
       	float ab_val(pow(a_val, n2) + pow(b_val, n3));
       	float f_val(pow(ab_val, n1));
       	return f_val;
      }
    public:
      PointCloud(int m_, int n1_, int n2_, int n3_){
        m = float(m_);
        n1 = float(n1_);
        n2 = float(n2_);
        n3 = float(n3_);
        size = int(m * STEP_COUNT);
      }
      void assign() {
       	float priv_n1(-1.0 / n1);
        float max_point = 0;
        writeLine("m " + std::to_string(m) +" n1 " + std::to_string(n1) +" n2 " + std::to_string(n2) +" n3 " + std::to_string(n3));
       	for (int i = 0; i != size; i++) {
       	  float r = point(m, priv_n1, n2, n3, i * STEP_SIZE - HALF_PI);
          max_point = std::max(max_point, r);
          points.push_back(r);
       	}
       	for (int i = 0; i != size; i++) {
       	  points[i] /= max_point;
       	}
      }
      void read() {
        for (int i = 0; i != size; i++) {
          writeLine("THETA : " + std::to_string(i * STEP_SIZE) + " VAL: " + std::to_string(points[i]));
        }
      }
      void draw() {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i != size; i++) {
          float point = points[i];
          float theta = i * STEP_SIZE - HALF_PI;
          float x = cos(theta) * point;
          float y = sin(theta) * point;
          glVertex3f(x, y, 0.0f);  // V0
        }
        glEnd();
      }
  };
}
superformula::PointCloud default_point_cloud(1,1,1,1);
superformula::PointCloud &point_cloud = default_point_cloud;

void Setup() { 
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.7f, 0.6f, 0.0f);
  point_cloud.draw();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  writeLine("The superformula is a generalization of the superellipse that takes four variables: m, n1, n2, n3");
  writeLine("By varying these inputs, we can generate many of the shapes seen in nature");
  writeLine("This pro'gram takes four inputs and returns a 36 point cloud representing the custom shape points");
  writeLine("More advanced implementations may go so far as to take these inputs and generate 3d meshes");
  writeLine("However, that's a bit much for doing during my vacation :P");
  int m = readInt("m");
  int n1 = readInt("n1");
  int n2 = readInt("n2");
  int n3 = readInt("n3");
  writeLine("Generating points:");
  superformula::PointCloud input (m, n1, n2, n3);
  input.assign();
  point_cloud = input;
  writeLine("Loading your superformula shape!");
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800,600);
  glutCreateWindow("2D SuperFormula Implementation");
  glutDisplayFunc(Display);
  glutMainLoop();

  return 0;
}
