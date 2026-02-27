#include "Curves.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main() {
    try {
        std::cout << std::fixed; // выводить числа в формате с фиксированной точкой (не научная нотация 1.5e+10)
        std::cout.precision(2); // количество знаков после запятой = 2
        srand(static_cast<unsigned int>(time(nullptr))); // инициализируем генератор случайных чисел текущим временем

        // Populate a container (e.g. vector or list) of objects of these types created in random manner with random parameters. 

        std::vector<std::unique_ptr<Curve>> curves;
        int figures_amount = Random_amount(100); // поставлю 100, но можно больше

        for (int i = 0; i < figures_amount; i++) {
            int type = rand() % 3; // случайный тип: 0 = Circle, 1 = Ellipse, 2 = Helix
            switch (type) {
                case 0:
                curves.push_back(std::make_unique<Circle>(Random_radius_or_step()));
                break;
                case 1:
                curves.push_back(std::make_unique<Ellipse>(Random_radius_or_step(), Random_radius_or_step()));
                break;
                case 2:
                curves.push_back(std::make_unique<Helix>(Random_radius_or_step(), Random_radius_or_step()));
                break;
            }
        }

        // Ensure that the container will contain objects of all supported types.
        EnsureAllTypes(curves);
        StatisticForVector(curves);

        // Print coordinates of points and derivatives of all curves in the container at t=PI/4.

        std::cout << "\n=== Points and derivatives at t = PI/4 ===\n";
        for (size_t i = 0; i < curves.size(); i++) {
            Point3D  p = curves[i]->getPoint3D(PI / 4.0);
            Vector3D v = curves[i]->getDerivative(PI / 4.0);
            std::cout << "\nCurve " << i + 1 << ": " << curves[i]->getType() << "\n";
            std::cout << "3D point: " << p << "\n";
            std::cout << "3D derivative: " << v << "\n";
        }

        // Populate a second container that would contain only circles from the first container. 
        // Make sure the second container shares (i.e. not clones) circles of the first one, e.g. via pointers.

        std::vector<Circle*> circles;
        for (const auto& c : curves) {
            // dynamic_cast вернёт nullptr если c не является Circle
            Circle* circle = dynamic_cast<Circle*>(c.get());
            if (circle != nullptr) {
                circles.push_back(circle);
            }
        }

        StatisticForCircleVector(circles);

        // Sort the second container in the ascending order of circles’ radii. 
        // That is, the first element has the smallest radius, the last - the greatest.

        std::sort(circles.begin(), circles.end(),
                  [](const Circle* a, const Circle* b) {
                      return a->getRadiusX() < b->getRadiusX();
                  });

        std::cout << "\n=== Circles sorted by radius (ascending) ===\n";
        for (size_t i = 0; i < circles.size(); i++) {
            std::cout << "  Circle " << i + 1 << ": radius = " << circles[i]->getRadiusX() << "\n";
        }

        // Compute the total sum of radii of all curves in the second container.

        double totalSum = 0.0;
        for (const auto& circle : circles) {
            totalSum += circle->getRadiusX();
        }
        std::cout << "\nTotal sum of circles' radii: " << totalSum << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
