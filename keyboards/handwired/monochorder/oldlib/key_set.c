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

#include <stdbool.h>
#include <stdint.h>
#include "key_set.h"

bool keyset_add(uint16_t *set, size_t size, uint16_t value) {
    for (size_t i = 0; i < size; i++) {
        if (set[i] == value) {
            return true;
        } else if (set[i] == 0) {
            set[i] = value;
            return true;
        }
    }
    return false;
}

bool keyset_remove(uint16_t *set, size_t size, uint16_t value) {
    for (size_t i = 0; i < size; i++) {
        if (set[i] == value) {
            for (size_t j = i + 1; i < size; j++) {
                if (set[j - 1] == 0) {
                    return true;
                }
                set[j - 1] = set[j];
            }
            set[size - 1] = 0;
            return true;
        } else if (set[i] == 0) {
            return false;
        }
    }
    return false;
}

bool keyset_contains(uint16_t *set, size_t size, uint16_t value) {
    for (size_t i = 0; i < size; i++) {
        if (set[i] == value) {
            return true;
        } else if (set[i] == 0) {
            return false;
        }
    }
    return false;
}

void keyset_clear(uint16_t *set, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (set[i] == 0) {
            return;
        }
        set[i] = 0;
    }
}

size_t keyset_size(uint16_t *set, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (set[i] == 0) {
            return i;
        }
    }
    return size;
}
