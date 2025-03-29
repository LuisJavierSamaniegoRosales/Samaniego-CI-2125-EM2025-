#include <iostream>
#include <fstream>
#include <cstring>

struct Asignatura {
    char codigo_asignatura[7];
    char nombre_asignatura[20];
};

int main() {
    std::ofstream archivo("asignaturas.txt", std::ios::app); // Abrir archivo en modo añadir
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    int cantidad;
    std::cout << "Ingrese la cantidad de asignaturas que desea registrar: ";
    std::cin >> cantidad;

    std::cin.ignore(); // Limpiar el búfer para evitar problemas con getline
    for (int i = 0; i < cantidad; ++i) {
        Asignatura asignatura;

        std::cout << "Asignatura " << i + 1 << ":" << std::endl;
        
        std::cout << "Código (máximo 6 caracteres): ";
        std::cin.getline(asignatura.codigo_asignatura, 7); // Leer hasta 6 caracteres
        
        std::cout << "Nombre (máximo 19 caracteres): ";
        std::cin.getline(asignatura.nombre_asignatura, 20); // Leer hasta 19 caracteres

        archivo << "" << asignatura.codigo_asignatura 
                << "  " << asignatura.nombre_asignatura << std::endl;
    }

    std::cout << "Asignaturas registradas correctamente en 'asignaturas.txt'." << std::endl;
    archivo.close();

    return 0;
}