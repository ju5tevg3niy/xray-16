#pragma once

#define MACRO_TO_STRING_HELPER(a) #a
#define MACRO_TO_STRING(a) MACRO_TO_STRING_HELPER(a)

#define CONCATENIZE_HELPER(a, b) a##b
#define CONCATENIZE(a, b) CONCATENIZE_HELPER(a, b)
