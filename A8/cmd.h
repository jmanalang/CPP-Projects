/*
 * *****************************************************************************
 * file name  : cmd.h
 * author     : Hung Ngo
 * description: codes to implement user's commands
 *              illustrates the user of function pointers for late binding
 *              this implementation is overkill for this particular example,
 *              I wanted to illustrate this idea so that you can reuse it in
 *              later assignments which might require more sophisticated
 *              commands
 * *****************************************************************************
 */


#ifndef CMD_H_
#define CMD_H_

#include <string>
#include "Lexer.h"

/**
 * cmd_handler_t is a function pointer type, pointing to a function which takes
 * two arguments of type std::string and returns nothing
 */
typedef void (*cmd_handler_t)(Lexer);

void loaddb(Lexer);
void slowin(Lexer);
void slowout(Lexer);
void fastin(Lexer);
void fastout(Lexer);
void slowun(Lexer);
void slowun1(Lexer);
void fastun(Lexer);
void fastun1(Lexer);
void bye(Lexer);

#endif
