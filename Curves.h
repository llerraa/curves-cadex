#pragma once

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <algorithm>

// Число PI 
const double PI = acos(-1.0);

// Структура 3D точки
struct Point3D {
    double x;
    double y;
    double z;
};

// Структура 3D вектора
struct Vector3D {
    double x;
    double y;
    double z;
};

// Перегрузка оператора вывода
// Чтобы писать cout << point и cout << vector
std::ostream& operator<<(std::ostream& os, const Point3D& p);
std::ostream& operator<<(std::ostream& os, const Vector3D& v);

// Тип кривой
enum class CurveType {
    CIRCLE,
    ELLIPSE,
    HELIX
};

// Перегрузка оператора вывода
// Чтобы писать cout << curveType
std::ostream& operator<<(std::ostream& os, CurveType type);

// ─────────────────────────────────────────────────────
//  Абстрактный базовый класс для всех кривых
// ─────────────────────────────────────────────────────

class Curve {
public:

    virtual CurveType getType()               const = 0;
    virtual double    getRadiusX()            const = 0;
    virtual Point3D   getPoint3D(double t)    const = 0;
    virtual Vector3D  getDerivative(double t) const = 0;

    // Виртуальный деструктор
    // Чтобы при delete через Curve* вызвался деструктор подкласса
    virtual ~Curve() {}
};

// ─────────────────────────────────────────────────────
//  Ellipse
// ─────────────────────────────────────────────────────

class Ellipse : public Curve {
protected:
    double R_x;
    double R_y;

public:
    Ellipse(double Radius_x, double Radius_y);

    CurveType getType()               const override;
    double    getRadiusX()            const override;
    double    getRadiusY()            const;
    Point3D   getPoint3D(double t)    const override;
    Vector3D  getDerivative(double t) const override;
};

// ─────────────────────────────────────────────────────
//  Circle — частный случай Ellipse (Rx == Ry)
// ─────────────────────────────────────────────────────

class Circle : public Ellipse {
public:
    explicit Circle(double Radius);

    // Переопределяем тип, чтобы dynamic_cast и getType() работали корректно
    CurveType getType() const override;
};

// ─────────────────────────────────────────────────────
//  Helix
// ─────────────────────────────────────────────────────

class Helix : public Curve {
private:
    double R;
    double step;
    // шаг спирали — смещение по Z за один полный оборот (2*PI)

public:
    Helix(double Radius, double St);

    CurveType getType()               const override;
    double    getRadiusX()            const override;
    Point3D   getPoint3D(double t)    const override;
    Vector3D  getDerivative(double t) const override;

    double getStep() const;
};

//  Генерация случайных параметров
int    Random_amount(int max);
double Random_radius_or_step();

//  Вспомогательные функции
void EnsureAllTypes(std::vector<std::unique_ptr<Curve>>& curves);
void StatisticForVector(const std::vector<std::unique_ptr<Curve>>& curves); // статистика первого контейнера
void StatisticForCircleVector(const std::vector<Circle*>& circles); // статистика второго контейнера
