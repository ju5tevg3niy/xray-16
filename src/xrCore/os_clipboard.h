#pragma once
#include <cstddef>
#include "Common/types.hpp"

////////////////////////////////////////////////////////////////////////////
// Module : os_clipboard.h
// Created : 21.02.2008
// Modified : 04.03.2008
// Author : Evgeniy Sokolov
// Description : os clipboard class
////////////////////////////////////////////////////////////////////////////

namespace os_clipboard {
void copy_to_clipboard(pcstr buf, bool alreadyUTF8 = false);
void paste_from_clipboard(pstr buf, size_t buf_size);
void update_clipboard(pcstr str);
}  // namespace os_clipboard
