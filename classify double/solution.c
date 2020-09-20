#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

const uint64_t PLUS_ZERO = 0x0000000000000000;
const uint64_t MINUS_ZERO = 0x8000000000000000;
const uint64_t MAX_EXPONENT = 0x7FF0000000000000;
const uint64_t MAX_FRACTION = 0x000FFFFFFFFFFFFF;

/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    return (number >> index) & 1u;
}

bool checkForPositive(const uint64_t number) {
    return !getBit(number, 63);
}

bool checkForSingleValueExponent(const uint64_t number, const bool value) {
    return (number & MAX_EXPONENT) == (value ? MAX_EXPONENT : PLUS_ZERO);
}

bool checkForSingleValueFraction(const uint64_t number, const bool value) {
    return (number & MAX_FRACTION) == (value ? MAX_FRACTION : PLUS_ZERO);
}

/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == PLUS_ZERO;
}

bool checkForMinusZero (uint64_t number) {
    return number == MINUS_ZERO;
}

bool checkForPlusInf (uint64_t number) {
    return checkForPositive(number) &&
           checkForSingleValueExponent(number, 1) &&
           checkForSingleValueFraction(number, 0);
}

bool checkForMinusInf (uint64_t number) {
    return !checkForPositive(number) &&
           checkForSingleValueExponent(number, 1) &&
           checkForSingleValueFraction(number, 0);
}

bool checkForPlusNormal (uint64_t number) {
    return checkForPositive(number) &&
           !checkForSingleValueExponent(number, 1) &&
           !checkForSingleValueExponent(number, 0);
}

bool checkForMinusNormal (uint64_t number) {
    return !checkForPositive(number) &&
           !checkForSingleValueExponent(number, 1) &&
           !checkForSingleValueExponent(number, 0);
}

bool checkForPlusDenormal (uint64_t number) {
    return checkForPositive(number) &&
           checkForSingleValueExponent(number, 0) &&
           !checkForSingleValueFraction(number, 0);
}

bool checkForMinusDenormal (uint64_t number) {
    return !checkForPositive(number) &&
           checkForSingleValueExponent(number, 0) &&
           !checkForSingleValueFraction(number, 0);
}

bool checkForSignalingNan (uint64_t number) {
    return checkForSingleValueExponent(number, 1) &&
           !checkForSingleValueFraction(number, 0) &&
           !getBit(number, 51);
}

bool checkForQuietNan (uint64_t number) {
    return checkForSingleValueExponent(number, 1) &&
           getBit(number, 51);
}

void classify (double number) {
    const uint64_t a = convertToUint64(number);
    for (int i = 63; i >= 0; --i)
        printf("%d", getBit(a, i));
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
