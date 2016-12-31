#pragma once

#include "bmp.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdarg.h>

bool encrypt(string path, string message);
string decrypt(const char* path, const unsigned char stop_symbol);