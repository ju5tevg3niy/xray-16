#pragma once
#include <string>
#include "xrCore/Math/fbox.hpp"
#include "xrCore/Math/matrix.hpp"
#include "xrCore/Math/vector3.hpp"

#ifdef DEBUG

std::string get_string(bool v);
std::string get_string(const Fvector& v);
std::string get_string(const Fmatrix& dop);
std::string get_string(const Fbox& box);

std::string dump_string(const char* name, const Fvector& v);
std::string dump_string(const char* name, const Fmatrix& form);

void dump(const char* name, const Fmatrix& form);
void dump(const char* name, const Fvector& v);

#endif
