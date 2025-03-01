#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un polinomio
typedef struct {
    int grado;
    int *coeficientes;
} Polinomio;

// Función para crear un polinomio
Polinomio crearPolinomio(int grado) {
    Polinomio p;
    p.grado = grado;
    p.coeficientes = (int *)malloc((grado + 1) * sizeof(int));
    for (int i = 0; i <= grado; i++) {
        p.coeficientes[i] = 0;
    }
    return p;
}

// Función para leer un polinomio (coeficientes desde mayor a menor grado)
void leerPolinomio(Polinomio *p) {
    printf("Ingrese los coeficientes del polinomio de grado %d (desde mayor a menor grado):\n", p->grado);
    for (int i = 0; i <= p->grado; i++) {
        int gradoActual = p->grado - i;
        printf("Coeficiente de x^%d: ", gradoActual);
        scanf("%d", &p->coeficientes[i]);
    }
}

// Función para imprimir un polinomio
void imprimirPolinomio(Polinomio p) {
    int firstTerm = 1;
    for (int i = 0; i <= p.grado; i++) {
        int coef = p.coeficientes[i];
        int gradoActual = p.grado - i;
        if (coef != 0) {
            if (!firstTerm) {
                printf(coef > 0 ? "+ " : "- ");
            } else if (coef < 0) {
                printf("- ");
            }
            if (gradoActual == 0 || abs(coef) != 1) {
                printf("%d", abs(coef));
            } else if (abs(coef) == 1 && gradoActual == 0) {
                printf("1");
            }
            if (gradoActual > 0) {
                printf("x");
                if (gradoActual > 1) {
                    printf("^%d", gradoActual);
                }
                printf(" ");
            }
            firstTerm = 0;
        }
    }
    if (firstTerm) {
        printf("0");
    }
    printf("\n");
}

// Función principal
int main() {
    int n;
    printf("Ingrese el número de polinomios a sumar: ");
    scanf("%d", &n);

    Polinomio *polinomios = (Polinomio *)malloc(n * sizeof(Polinomio));

    // Encontrar el grado máximo entre todos los polinomios
    int maxGrado = 0;
    for (int i = 0; i < n; i++) {
        int grado;
        printf("\nIngrese el grado del polinomio %d: ", i + 1);
        scanf("%d", &grado);
        if (grado > maxGrado) {
            maxGrado = grado;
        }
        polinomios[i] = crearPolinomio(grado);
        leerPolinomio(&polinomios[i]);
    }

    // Crear una matriz de coeficientes ordenada desde mayor a menor grado
    int **matrizCoeficientes = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrizCoeficientes[i] = (int *)malloc((maxGrado + 1) * sizeof(int));
        int offset = maxGrado - polinomios[i].grado;
        // Inicializar con ceros
        for (int j = 0; j <= maxGrado; j++) {
            matrizCoeficientes[i][j] = 0;
        }
        // Copiar coeficientes alineados correctamente
        for (int j = 0; j <= polinomios[i].grado; j++) {
            matrizCoeficientes[i][j + offset] = polinomios[i].coeficientes[j];
        }
    }

    // Imprimir la matriz de coeficientes
    printf("\nMatriz de coeficientes (ordenada de mayor a menor grado):\n");
    for (int i = 0; i < n; i++) {
        printf("Polinomio %d: ", i + 1);
        for (int j = 0; j <= maxGrado; j++) {
            printf("%d ", matrizCoeficientes[i][j]);
        }
        printf("\n");
    }

    // Sumar los polinomios utilizando la matriz de coeficientes
    Polinomio suma = crearPolinomio(maxGrado);
    for (int i = 0; i <= maxGrado; i++) {
        suma.coeficientes[i] = 0;
        for (int j = 0; j < n; j++) {
            suma.coeficientes[i] += matrizCoeficientes[j][i];
        }
    }

    printf("\nEl mayor grado aceptado para los polinomios es: %d\n", maxGrado);
    printf("La suma de los polinomios es: ");
    imprimirPolinomio(suma);

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(polinomios[i].coeficientes);
        free(matrizCoeficientes[i]);
    }
    free(polinomios);
    free(matrizCoeficientes);
    free(suma.coeficientes);

    return 0;
}
