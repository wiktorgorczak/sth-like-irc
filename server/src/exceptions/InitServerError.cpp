//
// Created by wiktor on 02.01.2021.
//

#include "InitServerError.h"

const char *InitServerError::what() const noexcept {
    return "Server initialization failed!";
}
