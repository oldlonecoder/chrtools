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

#include "chrtools/Icons.h"
#include <map>




Icon::DataArray Icon::Data =
{
    COk                ,
    CComment           ,
    CArrowRight        ,
    CArrowLeft         ,
    CArrowUp           ,
    CArrowDown         ,
    CArrowUpRight      ,
    CArrowUpLeft       ,
    CArrowDownRight    ,
    CArrowDownLeft     ,
    CArrowHeadRight    ,
    CArrowDheadRight   ,
    CPencilDr          ,
    CPencilUr          ,
    CErr1              ,
    CFlag              ,
    CBolt              ,
    CSuccess           ,
    CSmallDot          ,
    CBigDot            ,
    CBall1             ,
    CBall2             ,
    CDeadHead          ,
    CYinYang           ,
    CSadface           ,
    CHappy1            ,
    CHappy2            ,
    CCircleX           ,
    CFunction          ,
    CCut1              ,
    CCut2              ,
    CCut3              ,
    CCMarkX            ,
    CBaseline          ,
    CStar5             ,
    CCMarkCheck        ,
    CSwordCross        ,
    CHammerCross       ,
    CSmallDot2         ,
    CErr2              ,
    CErr3              ,
    CSQuote1           ,
    CDQuoteLeft        ,
    CDuoteRight        ,
    CDowntobottomleft  ,
    CUndo              ,
    CEnter             ,
    CKeyEnter          ,
    CLinux             ,
    CArch              ,
    CHome              ,
    CFile              ,
    CThumbDown         ,
    CGithubCircle      ,
    CGithubFolder      ,
    CWindows           ,
    CPi                ,
    CFolder            ,
    CBug               ,
    CInfo              ,
    CWarning           ,
    CBomb              ,
    CEditPencilBR      ,
    CEditPencilR       ,
    CEditPencilUR      ,
    CNegCrossCheck     ,
    CShadowedCheckBox  ,
    CSpinArrowSpin0    ,
    CSpinArrowSpin1    ,
    CSpinArrowSpin2    ,
    CSpinArrowSpin3    ,
    CSpinArrowSpin4    ,
    CSpinArrowSpin5    ,
    CSpinArrowSpin6    ,
    CSpinArrowSpin7    ,
    CThumbUp           ,
    CChronos           ,
    CSand              ,
    CCoffee            ,
    CUnAuth            ,
    CHandwrite         ,
    CWorld             ,
    CWorldGrid         ,
    CSchool            ,
    CHat               ,
    CAdmin             ,
    CFabric            ,
    CCat               ,
    CFish              ,
    CSearch            ,
    CPeople            ,
    CAlien             ,
    CLight             ,
    CPoop              ,
    CCash              ,
    CComputer          ,
    CNotePad           ,
    CBooks             ,
    CSend              ,
    CRecieve           ,
    CEmail             ,
    CEmail2            ,
    CNullPtr           ,
    CStop

};

std::map<Icon::Type, std::string> IcNamesMap =
{
    {Icon::Ok                 ,"Ok"},
    {Icon::Comment            ,"Comment"},
    {Icon::ArrowRight         ,"ArrowRight"},
    {Icon::ArrowLeft          ,"ArrowLeft"},
    {Icon::ArrowUp            ,"ArrowUp"},
    {Icon::ArrowDown          ,"ArrowDown"},
    {Icon::ArrowUpRight       ,"ArrowUpRight"},
    {Icon::ArrowUpLeft        ,"ArrowUpLeft"},
    {Icon::ArrowDownRight     ,"ArrowDownRight"},
    {Icon::ArrowDownLeft      ,"ArrowDownLeft"},
    {Icon::ArrowHeadRight     ,"ArrowHeadRight"},
    {Icon::ArrowDheadRight    ,"ArrowDheadRight"},
    {Icon::PencilDr           ,"PencilDr"},
    {Icon::PencilUr           ,"PencilUr"},
    {Icon::Err1               ,"Err1"},
    {Icon::Flag               ,"Flag"},
    {Icon::Bolt               ,"Bolt"},
    {Icon::Success            ,"Success "},
    {Icon::SmallDot           ,"SmallDot"},
    {Icon::BigDot             ,"BigDot"},
    {Icon::Ball1              ,"Ball1"},
    {Icon::Ball2              ,"Ball2"},
    {Icon::DeadHead           ,"DeadHead"},
    {Icon::YinYang            ,"YinYang"},
    {Icon::Sadface            ,"Sadface"},
    {Icon::Happy1             ,"Happy1"},
    {Icon::Happy2             ,"Happy2"},
    {Icon::CircleX            ,"CircleX"},
    {Icon::Function           ,"Function"},
    {Icon::Cut1               ,"Cut1"},
    {Icon::Cut2               ,"Cut2"},
    {Icon::Cut3               ,"Cut3"},
    {Icon::CMarkX             ,"CMarkX"},
    {Icon::Baseline           ,"Baseline"},
    {Icon::Star5              ,"Star5"},
    {Icon::CMarkCheck         ,"CMarkCheck"},
    {Icon::SwordCross         ,"SwordCross"},
    {Icon::HammerCross        ,"HammerCross"},
    {Icon::SmallDot2          ,"SmallDot2"},
    {Icon::Err2               ,"Err2"},
    {Icon::Err3               ,"Err3"},
    {Icon::SQuote1            ,"SQuote1"},
    {Icon::DQuoteLeft         ,"DQuoteLeft"},
    {Icon::DQuoteRight        ,"DuoteRight"},
    {Icon::Downtobottomleft   ,"Downtobottomleft"},
    {Icon::Undo               ,"Undo"},
    {Icon::Enter              ,"Enter"},
    {Icon::KeyEnter           ,"KeyEnter"},
    {Icon::Linux              ,"Linux"},
    {Icon::Arch               ,"Arch"},
    {Icon::Home               ,"Home"},
    {Icon::File               ,"File"},
    {Icon::ThumbDown          ,"ThumbDown "},
    {Icon::GithubCircle       ,"GithubCircle"},
    {Icon::GithubFolder       ,"GithubFolder"},
    {Icon::Windows            ,"Windows"},
    {Icon::Pi                 ,"Pi"},
    {Icon::Folder             ,"Folder"},
    {Icon::Bug                ,"Bug"},
    {Icon::Info               ,"Info"},
    {Icon::Warning            ,"Warning"},
    {Icon::Bomb               ,"Bomb"},
    {Icon::EditPencilBR       ,"EditPencilBR"},
    {Icon::EditPencilR        ,"EditPencilR"},
    {Icon::EditPencilUR       ,"EditPencilUR"},
    {Icon::NegCrossCheck      ,"NegCrossCheck"},
    {Icon::ShadowedCheckBox   ,"ShadowedCheckBox"},
    {Icon::SpinArrowSpin0     ,"SpinArrowSpin0"},
    {Icon::SpinArrowSpin1     ,"SpinArrowSpin1"},
    {Icon::SpinArrowSpin2     ,"SpinArrowSpin2"},
    {Icon::SpinArrowSpin3     ,"SpinArrowSpin3"},
    {Icon::SpinArrowSpin4     ,"SpinArrowSpin4"},
    {Icon::SpinArrowSpin5     ,"SpinArrowSpin5"},
    {Icon::SpinArrowSpin6     ,"SpinArrowSpin6"},
    {Icon::SpinArrowSpin7     ,"SpinArrowSpin7"},
    {Icon::ThumbUp            ,"ThumbUp"},
    {Icon::Chronos            ,"Chronos"},
    {Icon::Sand               ,"Sand"},
    {Icon::Coffee             ,"Coffee"},
    {Icon::UnAuth             ,"UnAuth"},
    {Icon::Handwrite          ,"Handwrite"},
    {Icon::World              ,"World"},
    {Icon::WorldGrid          ,"WorldGrid"},
    {Icon::School             ,"School"},
    {Icon::Hat                ,"Hat"},
    {Icon::Admin              ,"Admin"},
    {Icon::Fabric             ,"Fabric"},
    {Icon::Cat                ,"Cat"},
    {Icon::Fish               ,"Fish"},
    {Icon::Search             ,"Search"},
    {Icon::People             ,"People"},
    {Icon::Alien              ,"Alien"},
    {Icon::Light              ,"Light"},
    {Icon::Poop               ,"Poop"},
    {Icon::Cash               ,"Cash"},
    {Icon::Computer           ,"Computer"},
    {Icon::NotePad            ,"NotePad"},
    {Icon::Books              ,"Books"},
    {Icon::Send               ,"Send"},
    {Icon::Recieve            ,"Recieve"},
    {Icon::Email              ,"Email"},
    {Icon::Email2             ,"Email2"},
    {Icon::NullPtr            ,"NullPtr"},
    {Icon::Stop               ,"Stop"}
};

Icon::Type Icon::Scan(std::string IcName)
{

    for (auto& [N,Str] : IcNamesMap)
    {
        if(IcName == Str) return N;
    }
    return 0;
}

std::string Icon::Name(Type ic)
{
    return IcNamesMap[ic];
}


