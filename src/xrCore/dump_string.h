#pragma once
#ifdef DEBUG
#include <string>

// fwd. decl.
template <class T> struct _vector3; typedef _vector3<float> Fvector;
struct Fmatrix;
struct Fbox3; using Fbox = Fbox3;

std::string get_string(bool v);
std::string get_string(const Fvector& v);
std::string get_string(const Fmatrix& dop);
std::string get_string(const Fbox& box);

std::string dump_string(const char* name, const Fvector& v);
std::string dump_string(const char* name, const Fmatrix& form);
void dump(const char* name, const Fmatrix& form);
void dump(const char* name, const Fvector& v);

#endif
