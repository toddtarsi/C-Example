#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>

#define PI 3.1415
#define STEP_COUNT 32
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
      void assign_points() {
       	float priv_n1(-1.0 / n1);
        writeLine("m " + std::to_string(m) +" n1 " + std::to_string(n1) +" n2 " + std::to_string(n2) +" n3 " + std::to_string(n3));
       	for (int i = 0; i != size; i++) {
       	  points.push_back(point(m, priv_n1, n2, n3, i * STEP_SIZE));
       	}
      }
      void read_points() {
        for (int i = 0; i != size; i++) {
          writeLine("THETA : " + std::to_string(i * STEP_SIZE) + " VAL: " + std::to_string(points[i]));
        }
      }
  };
}


int main() {
  writeLine("The superformula is a generalization of the superellipse that takes four variables: m, n1, n2, n3");
  writeLine("By varying these inputs, we can generate many of the shapes seen in nature");
  writeLine("This program takes four inputs and returns a 36 point cloud representing the custom shape points");
  writeLine("More advanced implementations may go so far as to take these inputs and generate 3d meshes");
  writeLine("However, that's a bit much for doing during my vacation :P");
  int m = readInt("m");
  int n1 = readInt("n1");
  int n2 = readInt("n2");
  int n3 = readInt("n3");
  superformula::PointCloud input (m, n1, n2, n3);
  writeLine("Generating points:");
  input.assign_points();
  input.read_points();
  writeLine("Thank you. Press Enter to exit.");
  std::string fin;
  std::getline(std::cin, fin);
}
