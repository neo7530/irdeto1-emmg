#ifndef PARSER_H
#define PARSER_H
#include "irdeto_core.h"

extern void parse(uint8_t *frame,char *tbuffer);
extern void setup(int runde,char *sendbuffer);
extern void genframe(char *sendbuffer);
extern void copyemm(char *out,uint8_t *in);


#endif // PARSER_H



