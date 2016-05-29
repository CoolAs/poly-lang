#pragma once
#include <string>
#include <memory>

#define EN_FOLDER "en/"
#define EN_EN_FOLDER "en/"
#define DE_FOLDER "de/"
#define EO_FOLDER "eo/"

#include "Language.h"
std::shared_ptr<Language> getLanguageFromStringID(std::string ID);
#define DICTIONARY "/home/coolas/compoglot/lang/"
