#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>


#define EPS 1e-6
#define MAX_ITER 1000

// Функція f(x) = cot(x) - 0.5x
double f(double x) {
    return 1 / tan(x) - 0.5 * x;
}

// Похідна функції f(x)
double f_prime(double x) {
    return -1 / (sin(x) * sin(x)) - 0.5;
}

// Метод бісекції
double bisection(double a, double b) {
    double c;
    int n = 0;
    while ((b - a) >= EPS && n < MAX_ITER) {
        c = (a + b) / 2;
        if (f(c) == 0.0) {
            break;
        }
        else if (f(c) * f(a) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        n++;
    }
    return c;
}

// Метод простої ітерації
double simple_iteration(double x0) {
    double x1;
    int n = 0;
    do {
        // g(x) = cot(x) / 0.5
        x1 = 1 / tan(x0) / 0.5;
        if (fabs(x1 - x0) < EPS) {
            break;
        }
        x0 = x1;
        n++;
    } while (n < MAX_ITER);
    return x1;
}

// Метод хорд
double chord(double a, double b) {
    double c;
    int n = 0;
    while (fabs(b - a) >= EPS && n < MAX_ITER) {
        c = b - f(b) * (b - a) / (f(b) - f(a));
        a = b;
        b = c;
        n++;
    }
    return c;
}

// Метод дотичних
double tangent(double x0) {
    double x1;
    int n = 0;
    do {
        x1 = x0 - f(x0) / f_prime(x0); // Виправлено на правильну похідну
        if (fabs(x1 - x0) < EPS) {
            break;
        }
        x0 = x1;
        n++;
    } while (n < MAX_ITER);
    return x1;
}

int main() {
    setlocale(LC_ALL, "RU");
    // Приклад використання методів
    double a = 1.0, b = 2.0, x0 = 1.5;

    printf("Метод бисекции: %lf\n", bisection(a, b));
    printf("Метод простой итерации: %lf\n", simple_iteration(x0));
    printf("Метод хорд: %lf\n", chord(a, b));
    printf("Метод касающихся: %lf\n", tangent(x0));

    return 0;
}
