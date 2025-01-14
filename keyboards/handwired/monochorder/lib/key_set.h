/* Copyright 2024 Kim Hollstein (WiggelMc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEY_SET_H
#define KEY_SET_H

#include <stdbool.h>
#include <stdint.h>
#include "quantum.h"

#define ARR(array) array, ARRAY_SIZE(array)

bool   keyset_add(uint16_t *set, size_t size, uint16_t value);
bool   keyset_remove(uint16_t *set, size_t size, uint16_t value);
bool   keyset_contains(uint16_t *set, size_t size, uint16_t value);
void   keyset_clear(uint16_t *set, size_t size);
size_t keyset_size(uint16_t *set, size_t size);

#endif
