#include "Curves.h"

// ─────────────────────────────────────────────────────
//  перегрузка для Point3D и Vector3D
// ─────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, const Point3D& p) {
    return os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

// ─────────────────────────────────────────────────────
//  перегрузка для CurveType
// ─────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, CurveType type) {
    switch (type) {
        case CurveType::CIRCLE:  return os << "Circle";
        case CurveType::ELLIPSE: return os << "Ellipse";
        case CurveType::HELIX:   return os << "Helix";
    }
    return os;
}

// ─────────────────────────────────────────────────────
//  Ellipse
// ─────────────────────────────────────────────────────

Ellipse::Ellipse(double Radius_x, double Radius_y) {
    if (Radius_x <= 0) throw std::invalid_argument("Ellipse: Radius_x must be positive");
    if (Radius_y <= 0) throw std::invalid_argument("Ellipse: Radius_y must be positive");
    R_x = Radius_x;
    R_y = Radius_y;
}

CurveType Ellipse::getType()    const { return CurveType::ELLIPSE; }
double    Ellipse::getRadiusX() const { return R_x; }

// C(t)  = (Rx*cos(t), Ry*sin(t), 0)
Point3D Ellipse::getPoint3D(double t) const {
    Point3D p;
    p.x = R_x * cos(t);
    p.y = R_y * sin(t);
    p.z = 0;
    return p;
}

// C'(t) = (-Rx*sin(t), Ry*cos(t), 0)
Vector3D Ellipse::getDerivative(double t) const {
    Vector3D v;
    v.x = -R_x * sin(t);
    v.y =  R_y * cos(t);
    v.z = 0;
    return v;
}

// ─────────────────────────────────────────────────────
//  Circle — частный случай Ellipse (Rx == Ry)
// ─────────────────────────────────────────────────────

// Передаём одинаковый радиус по обеим осям — получаем окружность
Circle::Circle(double Radius) : Ellipse(Radius, Radius) {}

// Переопределяем только тип — математика наследуется от Ellipse
CurveType Circle::getType() const { return CurveType::CIRCLE; }

// ─────────────────────────────────────────────────────
//  Helix
// ─────────────────────────────────────────────────────

Helix::Helix(double Radius, double Step) {
    if (Radius <= 0) throw std::invalid_argument("Helix: Radius must be positive");
    if (Step   <= 0) throw std::invalid_argument("Helix: Step must be positive");
    R = Radius;
    step = Step;
}

CurveType Helix::getType()    const { return CurveType::HELIX; }
double    Helix::getRadiusX() const { return R; }
double    Helix::getStep()    const { return step; }

// C(t) = (R*cos(t), R*sin(t), step/(2*PI) * t)
// за один оборот (2*PI) поднимается на step
Point3D Helix::getPoint3D(double t) const {
    Point3D p;
    p.x = R * cos(t);
    p.y = R * sin(t);
    p.z = (step / (2 * PI)) * t;
    return p;
}

// C'(t) = (-R*sin(t), R*cos(t), step/(2*PI))
Vector3D Helix::getDerivative(double t) const {
    Vector3D v;
    v.x = -R * sin(t);
    v.y =  R * cos(t);
    v.z =  step / (2 * PI);
    return v;
}

// ─────────────────────────────────────────────────────
//  Генерация случайных параметров
// ─────────────────────────────────────────────────────

int Random_amount(int max) {
    int min = 1;
    if (max < min)
        throw std::invalid_argument("You should create more than 0 figures");
    return rand() % (max - min + 1) + min; // [1, max]
}

double Random_radius_or_step() {
    return 0.1 + (rand() % 1000) / 100.0; // [0.1, 10.1]
}

// ─────────────────────────────────────────────────────
//  Вспомогательные функции
// ─────────────────────────────────────────────────────

void EnsureAllTypes(std::vector<std::unique_ptr<Curve>>& curves) {
    bool hasCircle  = false;
    bool hasEllipse = false;
    bool hasHelix   = false;

    for (const auto& c : curves) {
        switch (c->getType()) {
            case CurveType::CIRCLE:  hasCircle  = true; break;
            case CurveType::ELLIPSE: hasEllipse = true; break;
            case CurveType::HELIX:   hasHelix   = true; break;
        }
    }

    if (!hasCircle)
        curves.push_back(std::make_unique<Circle>(Random_radius_or_step()));
    if (!hasEllipse)
        curves.push_back(std::make_unique<Ellipse>(Random_radius_or_step(), Random_radius_or_step()));
    if (!hasHelix)
        curves.push_back(std::make_unique<Helix>(Random_radius_or_step(), Random_radius_or_step()));
}

void StatisticForVector(const std::vector<std::unique_ptr<Curve>>& curves) {
    int circleCount = 0, ellipseCount = 0, helixCount = 0;

    for (const auto& c : curves) {
        switch (c->getType()) {
            case CurveType::CIRCLE:  circleCount++;  break;
            case CurveType::ELLIPSE: ellipseCount++; break;
            case CurveType::HELIX:   helixCount++;   break;
        }
    }

    std::cout << "Total curves: " << curves.size() << "\n"
              << "  Circles:  "   << circleCount   << "\n"
              << "  Ellipses: "   << ellipseCount  << "\n"
              << "  Helixes:  "   << helixCount    << "\n";
}

void StatisticForCircleVector(const std::vector<Circle*>& circles) {
    std::cout << "\n=== Circles in second container: " << circles.size() << " ===\n";
    for (size_t i = 0; i < circles.size(); i++) {
        std::cout << "  Circle " << i + 1 << ": radius = " << circles[i]->getRadiusX() << "\n";
    }
}
