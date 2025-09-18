#include <stdio.h>

int main() {
    int n, k;
    double pi = 0.0;

    printf("Ingrese el numero de iteraciones: ");
    scanf("%d", &n);

    for (k = 0; k < n; k++) {
        if (k % 2 == 0) {
            pi += 4.0 / (2 * k + 1);   // términos positivos
        } else {
            pi -= 4.0 / (2 * k + 1);   // términos negativos
        }
    }

    printf("Aproximacion de pi con %d iteraciones: %.15f\n", n, pi);

    return 0;
}
