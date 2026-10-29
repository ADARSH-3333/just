#include <stdio.h>

#define MAX 100

struct Term {
    int coeff;
    int exp;
};

void displayPolynomial(struct Term poly[], int terms) {
    if (terms == 0) {
        printf("0\n");
        return;
    }
    
    for (int i = 0; i < terms; i++) {
        if (poly[i].coeff == 0) continue;

        if (i > 0 && poly[i].coeff > 0) {
            printf(" + ");
        } else if (poly[i].coeff < 0) {
            printf(" - ");
        }

        int absolute_coeff = poly[i].coeff > 0 ? poly[i].coeff : -poly[i].coeff;
        
        if (poly[i].exp == 0) {
            printf("%d", absolute_coeff);
        } else if (poly[i].exp == 1) {
            printf("%dx", absolute_coeff);
        } else {
            printf("%dx^%d", absolute_coeff, poly[i].exp);
        }
    }
    printf("\n");
}

void sortPolynomial(struct Term poly[], int terms) {
    struct Term temp;
    for (int i = 0; i < terms - 1; i++) {
        for (int j = 0; j < terms - i - 1; j++) {
            if (poly[j].exp < poly[j + 1].exp) {
                temp = poly[j];
                poly[j] = poly[j + 1];
                poly[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct Term polyA[MAX], polyB[MAX], polyResult[MAX];
    int termsA, termsB, termsResult = 0;

    printf("Enter number of terms for Polynomial A: ");
    scanf("%d", &termsA);
    printf("Enter coefficient and exponent for each term:\n");
    for (int i = 0; i < termsA; i++) {
        printf("Term %d (coeff exp): ", i + 1);
        scanf("%d %d", &polyA[i].coeff, &polyA[i].exp);
    }

    printf("\nEnter number of terms for Polynomial B: ");
    scanf("%d", &termsB);
    printf("Enter coefficient and exponent for each term:\n");
    for (int i = 0; i < termsB; i++) {
        printf("Term %d (coeff exp): ", i + 1);
        scanf("%d %d", &polyB[i].coeff, &polyB[i].exp);
    }

    for (int i = 0; i < termsA; i++) {
        polyResult[termsResult] = polyA[i];
        termsResult++;
    }

    for (int i = 0; i < termsB; i++) {
        int found = 0;
        for (int j = 0; j < termsResult; j++) {
            if (polyB[i].exp == polyResult[j].exp) {
                polyResult[j].coeff += polyB[i].coeff; // Combine them!
                found = 1;
                break;
            }
        }
        if (!found) {
            polyResult[termsResult] = polyB[i];
            termsResult++;
        }
    }

    sortPolynomial(polyResult, termsResult);

    printf("\nPolynomial A: ");
    sortPolynomial(polyA, termsA);
    displayPolynomial(polyA, termsA);

    printf("Polynomial B: ");
    sortPolynomial(polyB, termsB);
    displayPolynomial(polyB, termsB);

    printf("Resultant Polynomial: ");
    displayPolynomial(polyResult, termsResult);

    return 0;
}

