#pragma once
#include "xrCore/Utils/intrusive_ptr.hpp"

class CPhraseDialog;

using DIALOG_SHARED_PTR = intrusive_ptr<CPhraseDialog>;

#include "PhraseDialog.h"

using DIALOG_ID_VECTOR = std::vector<shared_str>;
