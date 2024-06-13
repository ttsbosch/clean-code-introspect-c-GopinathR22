#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void convertDataFromCSVtoXML(FILE* InputStream) {
    char line[1024];
    TradeRecord objects[1024];
    int lineCount = 0;
    int objectCount = 0;

    while (fgets(line, sizeof(line), InputStream)) {
        char* TradeInfoFields[3];
        int TotalTradeInfoFields = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            TradeInfoFields[TotalTradeInfoFields++] = token;
            token = strtok(NULL, ",");
        }

        if (TotalTradeInfoFields != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, TotalTradeInfoFields);
            continue;
        }

        if (strlen(TradeInfoFields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, TradeInfoFields[0]);
            continue;
        }

        int tradeamount;
        if (!tryToConvertasLongInt(TradeInfoFields[1], &tradeamount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, TradeInfoFields[1]);
        }

        double tradeprice;
        if (!tryToConvertasDouble(TradeInfoFields[2], &tradeprice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, TradeInfoFields[2]);
        }

        strncpy(objects[objectCount].SourceCurrency, TradeInfoFields[0], 3);
        strncpy(objects[objectCount].DestinationCurrency, TradeInfoFields[0] + 3, 3);
        objects[objectCount].Lots = tradeamount / LotSize;
        objects[objectCount].Price = tradeprice;
        objectCount++;
        lineCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int i = 0; i < objectCount; i++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", objects[i].SourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", objects[i].DestinationCurrency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", objects[i].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", objects[i].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades processed\n", objectCount);
}

