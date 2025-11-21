// main.cpp (plot simples y = sin(x) + janela OpenCV)

#include <CvPlot/cvplot.h>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
  const int N = 200;
  std::vector<double> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    x[i] = i * 2 * M_PI / N;
    y[i] = std::sin(x[i]);
  }

  // renderiza o gráfico para cv::Mat
  cv::Mat img = CvPlot::plot(x, y, "-").render();

  cv::imshow("CVPlot Demo", img); // janela OpenCV
  cv::waitKey(0);
  return 0;
}
