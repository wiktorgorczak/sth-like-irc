//
// Created by wiktor on 03.01.2021.
//

#include "InternalError.h"

const char *InternalError::what() const noexcept {
    return "Could not perform a request due to internal server error.";
}
