#include <CvPlot/cvplot.h>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    const int num_points = 100;
    std::vector<double> x(num_points), y(num_points);

    auto axes = CvPlot::makePlotAxes();
    axes.title("Teste CvPlot Animado");
    axes.xLabel("Tempo");
    axes.yLabel("Amplitude");

    std::cout << "Pressione qualquer tecla na janela do gráfico para sair..."
              << std::endl;

// ...
    int offset = 0;
    while (true) {
        // 1. Atualiza os dados
        for (int i = 0; i < num_points; ++i) {
            x[i] = i;
            y[i] = std::sin((i + offset) * 0.1) * 10.0;
        }

        // 2. Renderiza a SÉRIE DE DADOS em uma linha (assume que o render retorna a Mat)
        // Usa a função mais simples de renderização da série de dados.
        cv::Mat img = CvPlot::plot(x, y, "b-o").render(600, 400);

        // 3. Exibe usando OpenCV padrão
        cv::imshow("Demo CvPlot", img);

        // 4. Controle de FPS e Saída
        if (cv::waitKey(30) >= 0) {
            break;
        }

        offset++;
    }

    return 0;
}

