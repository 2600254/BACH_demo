#!/bin/bash
lex --outfile token.cpp --header-file=token.h token.ll
`which bison` -d --output grammer.cpp grammer.y
