#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Codigo tomado de: http://bluefever.net/Downloads/BeginC/ch51.c
char *readFile (char*);

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Uso: %s <nombre_del_archivo.txt>\n", argv[0]);
    return 1;  // Salir del programa con código de error
    }
    
    char *fileName = argv[1];
    char * fileReadyToWrite = readFile(fileName);
    printf("%s", fileReadyToWrite);

    return 0;
}

char *readFile(char *fileName){

    FILE *file;

    char *resultado = malloc(1);

    printf("Uso: %s <nombre_del_archivo.txt>\n", fileName);

    file = fopen(fileName, "r"); //abrir archivo en modo lectura

    if (file== NULL) { // Verificar que el archivo se abra bien
        resultado = "No se pudo abrir el archivo. Verifica el nombre y la ruta.\n";
        return resultado;  
    }

      // Array dinámico para almacenar las líneas
    char **lines = NULL;
    size_t linesNumber = 0;

    // Leer cada línea del archivo y almacenarla en el array
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Añadir una nueva línea al array
        lines = realloc(lines, (linesNumber + 1) * sizeof(char *));
        lines[linesNumber] = strdup(line);
        // Incrementar el contador de líneas
        linesNumber++;
    }

    resultado[0] = '\0';

    for (size_t i = linesNumber; i > 0; i--) {
        resultado = realloc(resultado, strlen(resultado) + strlen(lines[i - 1]) + 2);
        const char *lineBreak = strchr(lines[i-1], '\n');

        if (lineBreak == NULL) {
            strcat(lines[i-1], "\n");
            strcat(resultado, lines[i - 1]);
        } else{
            strcat(resultado, lines[i - 1]);
        }
        
    }

    return resultado;
}