#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 30

struct WordCount {
    char *word;
    int count;
};

int isLetter(char c) {
    return isalpha(c);
}

int main() {
    FILE *file;
    char filename[] = "test2.txt";

    // Відкриття файлу для читання
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    // Масив для зберігання слів і їх кількостей
    struct WordCount *words = NULL;
    int wordCount = 0;
    //int maxWordCount = 1000; // Максимальна кількість різних слів

    char c;
    char wordBuffer[MAX_WORD_LENGTH + 1];
    int wordIndex = 0;

    while ((c = fgetc(file)) != EOF) {
        if (isLetter(c)) {
            if (wordIndex < MAX_WORD_LENGTH) {
                wordBuffer[wordIndex] = c;
                wordIndex++;
            }
        } else if (wordIndex > 0) {
            wordBuffer[wordIndex] = '\0'; // Додаємо завершальний нуль-символ
            int found = 0;

            for (int i = 0; i < wordCount; i++) {
                if (strcmp(words[i].word, wordBuffer) == 0) {
                    words[i].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                 struct WordCount *temp = realloc(words, (wordCount + 1) * sizeof(struct WordCount));
                    if (temp == NULL) {
                        printf("Error allocating memory for structure.\n");
                        return 1;
                    }
                    words = temp;

                    words[wordCount].word = strdup(wordBuffer);
                    if (words[wordCount].word == NULL) {
                        printf("Error allocating memory for word.\n");
                        return 1;
                    }

                    words[wordCount].count = 1;
                    wordCount++;

            }

            wordIndex = 0;
        }
    }

    fclose(file);

    int maxCount = 0;
    char mostFrequentWord[MAX_WORD_LENGTH + 1];

    for (int i = 0; i < wordCount; i++) {
        if (words[i].count > maxCount) {
            maxCount = words[i].count;
            strcpy(mostFrequentWord, words[i].word);
        }
    }

    printf("The most frequent word: %s (%d times)\n", mostFrequentWord, maxCount);

    // Звільнення виділеної пам'яті
    for (int i = 0; i < wordCount; i++) {
        free(words[i].word);
    }
    free(words);

    return 0;
}
