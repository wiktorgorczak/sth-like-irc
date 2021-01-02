//
// Created by wiktor on 02.01.2021.
//

#include "ParsingError.h"

const char *ParsingError::what() const noexcept {
    return "Error occurred while parsing a file.";
}
