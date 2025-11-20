// main.cpp (plot simples y = sin(x) + janela OpenCV)

#include <cmath>
#include <cvplot/cvplot.h>
#include <opencv2/opencv.hpp>

int main() {
  const int N = 200;
  std::vector<float> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    x[i] = i * 2 * M_PI / N;
    y[i] = std::sin(x[i]);
  }

  cvplot::plot("Sinus", cvplot::plot::line(x, y)); // desenha
  cvplot::plot::show("CVPlot Demo");               // abre janela
  cv::waitKey(0);                                  // aguarda ESC
  return 0;
}
