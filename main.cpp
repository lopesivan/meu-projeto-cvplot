// Se estiver usando como header-only, lembre de definir:
// #define CVPLOT_HEADER_ONLY
#include <CvPlot/cvplot.h>

#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    const int num_points = 100;
    std::vector<double> x(num_points), y(num_points);

    // Cria os eixos uma vez
    auto axes = CvPlot::makePlotAxes();
    axes.title("Demo de Onda Senoidal Animada (v1.2.2)");
    axes.xLabel("Tempo");
    axes.yLabel("Amplitude");

    // Cria a série associada a x e y (ela guarda referência aos vetores)
    auto &series = axes.create<CvPlot::Series>(x, y, "b-o");
    (void)series; // só pra evitar warning se não usar 'series' diretamente

    std::cout << "Pressione qualquer tecla na janela do gráfico para sair..." << std::endl;

    int offset = 0;
    cv::Mat img;

    while (true) {
        // 1. Atualiza os dados
        for (int i = 0; i < num_points; ++i) {
            x[i] = i;
            y[i] = std::sin((i + offset) * 0.1) * 10.0;
        }

        // 2. Renderiza o gráfico inteiro (eixos + séries) em um Mat
        axes.render(img, cv::Size(600, 400));

        // 3. Exibe usando OpenCV
        cv::imshow("Demo CvPlot", img);

        // 4. Controle de FPS e Saída
        if (cv::waitKey(30) >= 0) {
            break;
        }

        ++offset;
    }

    return 0;
}

