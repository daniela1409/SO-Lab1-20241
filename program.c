#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void printErrorMessage(const char *message) {
    fprintf(stderr, "%s\n", message);
}

// Esta función invierte el orden de un arreglo de cadenas
void reverseLines(char **lines, int numLines) {
    int start = 0;
    int end = numLines - 1;
    char *temp;

    while (start < end) {
        temp = lines[start];
        lines[start] = lines[end];
        lines[end] = temp;
        start++;
        end--;
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;

    // Verificar el número de argumentos
    if (argc > 3) {
        printErrorMessage("usage: reverse <input> <output>");
        exit(1);
    }

    // Manejar los casos de argumentos
    if (argc == 1) {
        // No se especificaron argumentos, leer desde stdin
        inputFile = stdin;
        outputFile = stdout;
    } else if (argc == 2) {
        // Se especificó solo un argumento, leer desde el archivo de entrada y escribir en stdout
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            printErrorMessage("cannot open file");
            exit(1);
        }
        outputFile = stdout;
    } else {
        // Se especificaron dos argumentos, leer desde el archivo de entrada y escribir en el archivo de salida
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            printErrorMessage("cannot open input file");
            exit(1);
        }
        outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            printErrorMessage("cannot open output file");
            exit(1);
        }

        // Verificar si el archivo de entrada y salida son el mismo
        if (strcmp(argv[1], argv[2]) == 0) {
            printErrorMessage("input and output files must differ");
            exit(1);
        }
    }

    // Almacenar las líneas en un arreglo dinámico
    char **lines = NULL;
    int numLines = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Eliminar el salto de línea del final de la línea
        line[strcspn(line, "\n")] = '\0';

        // Añadir la línea al arreglo dinámico
        lines = realloc(lines, (numLines + 1) * sizeof(char *));
        if (lines == NULL) {
            printErrorMessage("malloc failed");
            exit(1);
        }
        lines[numLines] = strdup(line);
        if (lines[numLines] == NULL) {
            printErrorMessage("malloc failed");
            exit(1);
        }
        numLines++;
    }

    // Invertir el orden de las líneas
    reverseLines(lines, numLines);

    // Imprimir las líneas en orden inverso
    for (int i = 0; i < numLines; i++) {
        fprintf(outputFile, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    // Cerrar archivos si no son stdin/stdout
    if (inputFile != stdin) fclose(inputFile);
    if (outputFile != stdout) fclose(outputFile);

    return 0;
}
