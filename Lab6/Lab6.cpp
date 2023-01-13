#include <iostream>
#include "Graph.h"

int main()
{
    srand(time(NULL));

    int n1, n2;

    std::cout << "Enter Matrix A size >> ";
    std::cin >> n1;
    std::cout << "Enter Matrix B size >> ";
    std::cin >> n2;

    Graph a(n1);
    Graph b(n2);

    std::cout << "[Matrix A]\n";
    a.Print();

    std::cout << "\n[Matrix B]\n";
    b.Print();

    std::cout << "\n[Matrix Union]\n";
    a.Union(b).Print();

    std::cout << "\n[Matrix Intersection]\n";
    a.Intersection(b).Print();

    std::cout << "\n[Matrix Decart's Multiplication]\n";
    a.DecartMul(b).Print();

    std::cout << "\n[Matrix Ring Adding]\n";
    a.RingAdd(b).Print();

    system("pause");
    return 0;
}