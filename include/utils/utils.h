/*
 * File: utils.h
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only
*/
#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <linked_list/linked_list.h>

FILE* open_file(char *name_file);

List* read_lines(char *name_file);
#endif
