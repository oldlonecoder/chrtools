/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/




#include "chrtools/accents.fr.h"
#include <map>





    std::vector<Accent::T> Accent::Data =
    {
        c_agrave ,
        c_acirc  ,
        c_cedile ,
        c_eacute ,
        c_egrave ,
        c_ecirc  ,
        c_etrema ,
        c_itrema ,
        c_ocirc  ,
        c_ugrave ,
        c_ucric  ,
        c_icirc  ,
        c_Agrave ,
        c_Acirc  ,
        c_Cedile ,
        c_Eacute ,
        c_Egrave ,
        c_Ecirc  ,
        c_Etrema ,
        c_Itrema ,
        c_Ocirc  ,
        c_Ugrave ,
        c_Ucric  ,
        c_Icirc
    };
    std::vector<std::string_view> Accent::Name =
    {
        "agrave",
        "acirc",
        "cedile",
        "eacute",
        "egrave",
        "ecirc",
        "etrema",
        "itrema",
        "ocirc",
        "ugrave",
        "ucirc",
        "icirc",
        "Agrave",
        "Acirc",
        "Cedile",
        "Eacute",
        "Egrave",
        "Ecirc",
        "Etrema",
        "Itrema",
        "Ocirc",
        "Ugrave",
        "Ucirc",
        "Icirc"
    };


    Accent::Type Accent::Code(std::string_view aTypeName)
    {
        std::map<std::string_view, Accent::Type> Map =
        {
            {"agrave", agrave},
            {"acirc",  acirc },
            {"cedile", cedile},
            {"eacute", eacute},
            {"egrave", egrave},
            {"ecirc",  ecirc },
            {"etrema", etrema},
            {"itrema", itrema},
            {"ocirc",  ocirc },
            {"ugrave", ugrave},
            {"ucirc",  ucirc },
            {"icirc",  icirc },
            {"Agrave", Agrave},
            {"Acirc",  Acirc },
            {"Cedile", Cedile},
            {"Eacute", Eacute},
            {"Egrave", Egrave},
            {"Ecirc",  Ecirc },
            {"Etrema", Etrema},
            {"Itrema", Itrema},
            {"Ocirc",  Ocirc },
            {"Ugrave", Ugrave},
            {"Ucirc",  Ucirc },
            {"Icirc",  Icirc}
        };
        for (auto const& [k, t] : Map)
        {
            if (k == aTypeName) return t;
        }

        return Type::Err;
    }


