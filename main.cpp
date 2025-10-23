#include <iostream>
#include <string>
#include <stdexcept>

#include "array.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"

int main() {
    Array arr;
    std::string cmd;

    while (std::cin >> cmd) {
        try {
            if (cmd == "ADD") {
                std::string type;
                if (!(std::cin >> type)) {
                    std::cerr << "error: expected figure type\n";
                    continue;
                }

                if (type == "TRAPEZOID") {
                    Trapezoid t;
                    t.read(std::cin);
                    arr.push(new Trapezoid(t));
                    std::cout << "OK\n";
                } else if (type == "RHOMBUS") {
                    Rhombus r;
                    r.read(std::cin);
                    arr.push(new Rhombus(r));
                    std::cout << "OK\n";
                } else if (type == "PENTAGON") {
                    Pentagon p;
                    p.read(std::cin);
                    arr.push(new Pentagon(p));
                    std::cout << "OK\n";
                } else {
                    std::cerr << "error: unknown figure type\n";
                }
            } else if (cmd == "PRINT") {
                arr.printFigures(std::cout);
            } else if (cmd == "INFO") {
                arr.printCentersAndAreas(std::cout);
            } else if (cmd == "AREA") {
                double s = arr.totalArea();
                std::cout << s << "\n";
            } else if (cmd == "DELETE") {
                size_t index = 0;
                if (!(std::cin >> index)) {
                    std::cerr << "error: expected index\n";
                    continue;
                }
                arr.erase(index);
                std::cout << "OK\n";
            } else if (cmd == "EQUAL") {
                size_t i = 0, j = 0;
                if (!(std::cin >> i >> j)) {
                    std::cerr << "error: expected two indices\n";
                    continue;
                }
                const Figure* a = arr.at(i);
                const Figure* b = arr.at(j);
                bool eq = a->equals(*b);
                std::cout << (eq ? "TRUE\n" : "FALSE\n");
            } else if (cmd == "STOP") {
                break;
            } else {
                std::cerr << "error: unknown command\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "error: " << e.what() << "\n";
        } catch (...) {
            std::cerr << "error: unknown\n";
        }
    }

    return 0;
}
