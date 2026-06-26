#include "xr_trims.hpp"
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>
#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "string_funcs_inline.hpp"
#include "xrCore/xrMemory.h"
#include "xrCore/xrstring.h"
#include "xr_token.hpp"

pstr _TrimLeft(pstr str, char whatToTrim /*= ' '*/) {
  pstr p = str;
  while (*p && (u8(*p) <= u8(whatToTrim)))
    p++;
  if (p != str) {
    pstr t = str;
    for (; *p; t++, p++)
      *t = *p;
    *t = 0;
  }
  return str;
}

pstr _TrimRight(pstr str, char whatToTrim /*= ' '*/) {
  pstr p = str + strlen(str);
  while ((p != str) && (u8(*p) <= u8(whatToTrim)))
    p--;
  *(++p) = 0;
  return str;
}

pstr _Trim(pstr str, char whatToTrim /*= ' '*/) {
  _TrimLeft(str, whatToTrim);
  _TrimRight(str, whatToTrim);
  return str;
}

pcstr _SetPos(pcstr src, u32 pos, char separator) {
  pcstr res = src;
  u32 p = 0;
  while ((p < pos) && (0 != (res = strchr(res, separator)))) {
    res++;
    p++;
  }
  return res;
}

pcstr _CopyVal(pcstr src, pstr dst, char separator) {
  pcstr p;
  size_t n;
  p = strchr(src, separator);
  n = (p != nullptr) ? (p - src) : strlen(src);
  strncpy(dst, src, n);
  dst[n] = 0;
  return dst;
}

int _GetItemCount(pcstr src, char separator) {
  u32 cnt = 0;
  if (src && src[0]) {
    pcstr res = src;
    pcstr last_res = res;
    while (0 != (res = strchr(res, separator))) {
      res++;
      last_res = res;
      cnt++;
      if (res[0] == separator)
        break;
    }
    if (strlen(last_res))
      cnt++;
  }
  return cnt;
}

pstr _GetItem(pcstr src,
              int index,
              pstr dst,
              u32 const dst_size,
              char separator,
              pcstr def,
              bool trim) {
  pcstr ptr;
  ptr = _SetPos(src, index, separator);
  if (ptr)
    _CopyVal(ptr, dst, separator);
  else
    xr_strcpy(dst, dst_size, def);
  if (trim)
    _Trim(dst);
  return dst;
}

pstr _GetItems(pcstr src,
               int idx_start,
               int idx_end,
               pstr dst,
               char separator) {
  pstr n = dst;
  int level = 0;
  for (pcstr p = src; *p != 0; p++) {
    if ((level >= idx_start) && (level < idx_end))
      *n++ = *p;
    if (*p == separator)
      level++;
    if (level >= idx_end)
      break;
  }
  *n = '\0';
  return dst;
}

pcstr _GetItems(pcstr src,
                int idx_start,
                int idx_end,
                std::string& dst,
                char separator) {
  int level = 0;
  for (pcstr p = src; *p != 0; p++) {
    if ((level >= idx_start) && (level < idx_end))
      dst += *p;
    if (*p == separator)
      level++;
    if (level >= idx_end)
      break;
  }
  return dst.c_str();
}

u32 _ParseItem(pcstr src, xr_token* token_list) {
  for (int i = 0; token_list[i].name; i++)
    if (!xr_stricmp(src, token_list[i].name))
      return token_list[i].id;
  return u32(-1);
}

u32 _ParseItem(pstr src, int ind, xr_token* token_list) {
  char dst[128];
  _GetItem(src, ind, dst);
  return _ParseItem(dst, token_list);
}

pstr _ReplaceItems(pcstr src,
                   int idx_start,
                   int idx_end,
                   pcstr new_items,
                   pstr dst,
                   char separator) {
  pstr n = dst;
  int level = 0;
  bool bCopy = true;
  for (pcstr p = src; *p != 0; p++) {
    if ((level >= idx_start) && (level < idx_end)) {
      if (bCopy) {
        for (pcstr itm = new_items; *itm != 0;)
          *n++ = *itm++;
        bCopy = false;
      }
      if (*p == separator)
        *n++ = separator;
    } else {
      *n++ = *p;
    }
    if (*p == separator)
      level++;
  }
  *n = '\0';
  return dst;
}

std::string& _ReplaceItems(pcstr src,
                           int idx_start,
                           int idx_end,
                           pcstr new_items,
                           std::string& dst,
                           char separator) {
  dst.clear();
  int level = 0;
  bool bCopy = true;
  for (pcstr p = src; *p != 0; p++) {
    if ((level >= idx_start) && (level < idx_end)) {
      if (bCopy) {
        for (pcstr itm = new_items; *itm != 0;)
          dst += *itm++;
        bCopy = false;
      }
      if (*p == separator)
        dst += separator;
    } else {
      dst += *p;
    }
    if (*p == separator)
      level++;
  }
  return dst;
}

pstr _ReplaceItem(pcstr src,
                  int index,
                  pcstr new_item,
                  pstr dst,
                  char separator) {
  pstr n = dst;
  int level = 0;
  bool bCopy = true;
  for (pcstr p = src; *p != 0; p++) {
    if (level == index) {
      if (bCopy) {
        for (pcstr itm = new_item; *itm != 0;)
          *n++ = *itm++;
        bCopy = false;
      }
      if (*p == separator)
        *n++ = separator;
    } else {
      *n++ = *p;
    }
    if (*p == separator)
      level++;
  }
  *n = '\0';
  return dst;
}

std::string& _ReplaceItem(pcstr src,
                          int index,
                          pcstr new_item,
                          std::string& dst,
                          char separator) {
  dst.clear();
  int level = 0;
  bool bCopy = true;
  for (pcstr p = src; *p != 0; p++) {
    if (level == index) {
      if (bCopy) {
        for (pcstr itm = new_item; *itm != 0;)
          dst += *itm++;
        bCopy = false;
      }
      if (*p == separator)
        dst += separator;
    } else {
      dst += *p;
    }
    if (*p == separator)
      level++;
  }
  return dst;
}

pstr _ChangeSymbol(pstr name, char src, char dest) {
  char* sTmpName = name;
  while (sTmpName[0]) {
    if (sTmpName[0] == src)
      sTmpName[0] = dest;
    sTmpName++;
  }
  return name;
}

std::string& _ChangeSymbol(std::string& name, char src, char dest) {
  for (std::string::iterator it = name.begin(); it != name.end(); ++it)
    if (*it == src)
      *it = std::string::value_type(dest);
  return name;
}

void _SequenceToList(std::vector<pstr>& lst, pcstr in, char separator) {
  int t_cnt = _GetItemCount(in, separator);
  string1024 T;
  for (int i = 0; i < t_cnt; i++) {
    _GetItem(in, i, T, separator, 0);
    _Trim(T);
    if (strlen(T) != 0)
      lst.push_back(xr_strdup(T));
  }
}

void _SequenceToList(std::vector<shared_str>& lst, pcstr in, char separator) {
  lst.clear();
  int t_cnt = _GetItemCount(in, separator);
  std::string T;
  for (int i = 0; i < t_cnt; i++) {
    _GetItem(in, i, T, separator, 0);
    _Trim(T);
    if (T.size())
      lst.push_back(T.c_str());
  }
}

void _SequenceToList(std::vector<std::string>& lst, pcstr in, char separator) {
  lst.clear();
  const int t_cnt = _GetItemCount(in, separator);
  std::string T;
  for (int i = 0; i < t_cnt; i++) {
    _GetItem(in, i, T, separator, 0);
    _Trim(T);
    if (T.size())
      lst.push_back(T);
  }
}

std::string _ListToSequence(const std::vector<std::string>& lst) {
  static std::string out;  // XXX: can cause crashes on exit
  out.clear();
  if (!lst.empty()) {
    out = lst.front();
    for (auto s_it = lst.cbegin() + 1; s_it != lst.cend(); ++s_it)
      out += std::string(",") + (*s_it);
  }
  return out;
}

std::string& _TrimLeft(std::string& str) {
  pcstr b = str.c_str();
  pcstr p = str.c_str();
  while (*p && (u8(*p) <= u8(' ')))
    p++;
  if (p != b)
    str.erase(0, p - b);
  return str;
}

std::string& _TrimRight(std::string& str) {
  pcstr b = str.c_str();
  size_t l = str.length();
  if (l) {
    pcstr p = str.c_str() + l - 1;
    while ((p != b) && (u8(*p) <= u8(' ')))
      p--;
    if (p != (str + b))
      str.erase(p - b + 1, l - (p - b));
  }
  return str;
}

std::string& _Trim(std::string& str) {
  _TrimLeft(str);
  _TrimRight(str);
  return str;
}

pcstr _CopyVal(pcstr src, std::string& dst, char separator) {
  pcstr p;
  std::ptrdiff_t n;
  p = strchr(src, separator);
  n = (p != nullptr) ? (p - src) : strlen(src);
  dst = src;
  dst = dst.erase(n, dst.length());
  return dst.c_str();
}

pcstr _GetItem(pcstr src,
               int index,
               std::string& dst,
               char separator,
               pcstr def,
               bool trim) {
  pcstr ptr;
  ptr = _SetPos(src, index, separator);
  if (ptr)
    _CopyVal(ptr, dst, separator);
  else
    dst = def;
  if (trim)
    _Trim(dst);
  return dst.c_str();
}

shared_str _ListToSequence(const std::vector<shared_str>& lst) {
  std::string out;
  if (lst.size()) {
    out = lst.front().c_str();
    for (auto s_it = lst.cbegin() + 1; s_it != lst.cend(); ++s_it) {
      out += ",";
      out += s_it->c_str();
    }
  }
  return shared_str(out.c_str());
}
