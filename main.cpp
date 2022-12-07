//
// Created by MalteGravert on 07.12.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef enum {Papier, Plastik, Glas, Restmuell} muelltyp;

typedef struct {
    float papier;
    float plastik;
    float glas;
    float restmuell;
} muellsack;

muellsack generiereMuellsack(float masse);
void muell_statistik(muellsack vorher, muellsack nachher);
void recycling_status(float papier_recycle, float plastik_recycle, float glas_recycle, float restmuell_verbrennen);
muellsack filtern(muellsack sack);
float trennung_auswertung(muellsack vorher, muellsack nachher, muelltyp typ);

int main() {
    srand(time(NULL));
    float papier_recycle = 0;
    float plastik_recycle = 0;
    float glas_recycle = 0;
    float restmuell_verbrennen = 0;
    int anzahl_muellsaecke;
    printf("Wie viele Müllsäcke sollen verarbeitet werden?\n");
    scanf("%d", &anzahl_muellsaecke);
    muellsack aktueller_muellsack;
    for (int i = 0; i < anzahl_muellsaecke; ++i) {
        aktueller_muellsack = generiereMuellsack(rand() % 100 + 1);
        muellsack gefiltert_muellsack;
        char eingabe;
        do {
            gefiltert_muellsack = filtern(aktueller_muellsack);
            muell_statistik(aktueller_muellsack, gefiltert_muellsack);
            printf("Möchten Sie nochmal filtern? (y/n)\n");
            scanf(" %c", &eingabe);
        } while (eingabe == 'y');
        aktueller_muellsack = gefiltert_muellsack;
        for (int j = 0; j < 3; ++j) {
            switch (j) {
                case Papier:
                    papier_recycle += trennung_auswertung(aktueller_muellsack, gefiltert_muellsack, j);
                    break;
                case Plastik:
                    plastik_recycle += trennung_auswertung(aktueller_muellsack, gefiltert_muellsack, j);
                    break;
                case Glas:
                    glas_recycle += trennung_auswertung(aktueller_muellsack, gefiltert_muellsack, j);
                    break;
            }
        }
        restmuell_verbrennen += aktueller_muellsack.restmuell;
    }
    recycling_status(papier_recycle, plastik_recycle, glas_recycle, restmuell_verbrennen);
    return 0;
}

muellsack generiereMuellsack(float masse) {
    muellsack sack;
    sack.papier = rand() % 100 / 100.0 * masse;
    sack.plastik = rand() % 100 / 100.0 * masse;
    sack.glas = rand() % 100 / 100.0 * masse;
    sack.restmuell = masse - sack.papier - sack.plastik - sack.glas;
    return sack;
}

void muell_statistik(muellsack vorher, muellsack nachher) {
    printf("Papier: %.2f kg\n", nachher.papier - vorher.papier);
    printf("Plastik: %.2f kg\n", nachher.plastik - vorher.plastik);
    printf("Glas: %.2f kg\n", nachher.glas - vorher.glas);
    printf("Restmüll: %.2f kg\n", nachher.restmuell - vorher.restmuell);
    printf("Papieranteil: %.2f %%\n", nachher.papier / (nachher.papier + nachher.plastik + nachher.glas + nachher.restmuell) * 100);
    printf("Plastikanteil: %.2f %%\n", nachher.plastik / (nachher.papier + nachher.plastik + nachher.glas + nachher.restmuell) * 100);
    printf("Glasanteil: %.2f %%\n", nachher.glas / (nachher.papier + nachher.plastik + nachher.glas + nachher.restmuell) * 100);
    printf("Restmüllanteil: %.2f %%\n", nachher.restmuell / (nachher.papier + nachher.plastik + nachher.glas + nachher.restmuell) * 100);
    printf("Gesamtgewicht: %.2f kg\n", nachher.papier + nachher.plastik + nachher.glas + nachher.restmuell);
}

void recycling_status(float papier_recycle, float plastik_recycle, float glas_recycle, float restmuell_verbrennen) {
    printf("Papier: %.2f kg\n", papier_recycle);
    printf("Plastik: %.2f kg\n", plastik_recycle);
    printf("Glas: %.2f kg\n", glas_recycle);
    printf("Restmüll: %.2f kg\n", restmuell_verbrennen);
}

muellsack filtern(muellsack sack) {
    if (sack.papier / (sack.papier + sack.plastik + sack.glas + sack.restmuell) * 100 > 5) {
        sack.papier -= sack.papier / 3;
    } else {
        if (sack.plastik > 200) {
            sack.plastik -= 200;
        }
        if (sack.glas > 1) {
            sack.glas -= 1;
        } else {
            sack.glas = 0;
        }
    }
    return sack;
}

float trennung_auswertung(muellsack vorher, muellsack nachher, muelltyp typ) {
    if (typ == Papier) {
        return nachher.papier - vorher.papier;
    } else if (typ == Plastik) {
        return nachher.plastik - vorher.plastik;
    } else if (typ == Glas) {
        return nachher.glas - vorher.glas;
    } else {
        return nachher.restmuell - vorher.restmuell;
    }
}