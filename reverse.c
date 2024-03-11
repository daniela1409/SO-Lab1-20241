#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFile (char*);
void writeFile (char*, char*);

int main(int argc, char *argv[]) {
    char *fileName = argv[1];
    char *fileNametoWrite = argv[2];
    int save = strcmp(fileName, fileNametoWrite);

    if(save == 0){
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
        return 1;
    }
    if(argc > 3){
        fprintf(stderr, "reverse <input> <output>\n");
        return 1;
    }
    if (argc == 2 || argc == 3) {
        char * fileReadyToWrite = readFile(fileName);

        if(strcmp(fileReadyToWrite, "1") == 0){
            fprintf(stderr, "malloc failed");
            return 1;
        }
        if (argc == 3)
        {
            writeFile(fileNametoWrite, fileReadyToWrite);
        }
        printf("%s", fileReadyToWrite);
        return 0;
    }
    else{
        return 1;
    } 
}

char *readFile(char *fileName){

    FILE *file;
    char *resultado = malloc(1);

    if (resultado == NULL) {
        return "1";
    }

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

void writeFile (char* fileName, char* textReadyToWrite){
    FILE *outFile = fopen(fileName, "w");
    if (outFile == NULL) {
        perror("Error al abrir el archivo de salida");
    }

    // Escribir el contenido en el archivo de salida
    fprintf(outFile, "%s", textReadyToWrite);

    // Cerrar el archivo de salida
    fclose(outFile);

    // Liberar la memoria utilizada por el resultado
    free(textReadyToWrite);
}