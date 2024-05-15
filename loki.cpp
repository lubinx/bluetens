#include <cstring>
#include <cstdlib>
#include <cctype>

#include <sys/errno.h>
#include <ultracore/assert.h>

#include "loki.hpp"

using namespace Loki;
#define MINI_IMPULSE                    (20)

/***************************************************************************/
/* picture of a block of output

out1/4
            +---+                                   +---+
            |   |                                   |   |
            |   |                                   |   |
            |   |                                   |   |
    --------+   +-------+-----------+---------------+   +-----------------...
           MR0 MR1      |           |               |
            |   |.......|           |               |
            |impulse    |           |               |
            +-----------+           |               |
            |           |           |               |
            |           |           |               |
            | half frequency        |               |
out2/3      |           |           |               |
            |           +---+       |               |               +---+
            |           |   |       |               |               |   |
            |           |   |       |               |               |   |
            |           |   |       |               |               |   |
    --------+-----------+   +-------+---------------+---------------+   +-...
            |          MR2 MR3      |               |
            |           |   |.......|               |
            |           | impulse   |               |
            |           +-----------+               |
            |                       |               |
            |-->    frequency    <--+-> interval <--|
            .                       .               .
            .                       .               .
out overlapped                      .               .
            .                       .               .
            +---+                   .               .
            |   |\                  .               .
            |   | |                 .               .
            |   |  \ intensity      .               .
            |   |  /                .               .
            |   | |                 .               .
            |   |/                  .               .
    --------+   +-------+   +-------+---------------+...
            .           |   |       .               .
            .           |   |       .               .
            .           |   |       .               .
            .           |   |       .               .
            .           |   |       .               .
            .           |   |       .               .
            .           +---+       .               .
            .                       .               .
            .-->    frequency    <--+-> interval <--.

cluster is continues output (of frequency) without interval
            +---+                   +---+
            |   |                   |   |
            |   |                   |   |
            |   |                   |   |
            |   |                   |   |
            |   |                   |   |
            |   |                   |   |
    --------+   +-------+   +-------+   +-------+   +-------+---------------+...
            .           |   |       .           |   |       .               .
            .           |   |       .           |   |       .               .
            .           |   |       .           |   |       .               .
            .           |   |       .           |   |       .               .
            .           |   |       .           |   |       .               .
            .           |   |       .           |   |       .               .
            .           +---+       .           +---+       .               .
            .                       .                       .               .
            .-->    frequency    <--+-->    frequency    <--+-> interval <--.

            cluster1                 cluster2...


describe as
    block = [T(impulse, frequency) * C(n) + I(interval)] * repeat
    section = {block...block + I(interval)} * repeat

script
    'V'     version of the file
    'D'     digit base of decimal or hex, we only support 10 base digit and 16 base digit
    'F'     frequency
    'T'     ten persent of frequency. example T105 = 10.5hz
    'P'     impulse
    'C'     cluster of block, loop block without interval
    'I'     interval
    'R'     repeat count
    '['     block start
    ']'     block ending
    '{'     section start
    '}'     section ending

example of section
    {Rnnnn  Innnn [Fnnnn Pnnnn Innnn Rnnnn Cnnnn] [Fnnnn Pnnnn Innnn Rnnnn Cnnnn]...}
     ^^^^^^^^^^^^                               -> section params/block params
                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^-> block use '[]'

    or the smaller file

    {Rnnnn  Innnn |Fnnnn Pnnnn Innnn Rnnnn Cnnnn |Fnnnn Pnnnn Innnn Rnnnn Cnnnn...}
                  ^ block use single '|'
                                                 ^ next block start

example of real file
    V1D16{R1|R3e8P64F32|F2}
    ^^^^^                                       -> file version 1, 16 base digit
         ^^^^^^^^^^^^^^^^^^                     -> section 1
            ^^^^^^^^^^^                         -> the block repeat 1000 times with 54hz of impulse 100us
                        ^^                      -> the next block reeat 1000 times with 2hz of impulse 100us
                                                    *WHY NO 'R' AND 'P'?*
                                                        the next block of section only need to change the
                                                        paratemters difference to previous block
                                                        this greatly reduced the file size
*Important* hex word of 'abcdef' must be lowercase

futher more complex need of loki file?

complex script: presistent at end of file, any section after script is ignored
    '<'     script start
    '>'     script end
    'S'     jump section No.

example of script:
    <S2S1S2S3S2S1>
    let say a file has 3 section,
    after forward execute the loki file: SECTION1 -> SECTION2 -> SECTION3
    this script plus do more loop: SECTION2->SECTION1->SECTION3->SECTION2->SECTION1

****************************************************************************/



/*****************************************************************************
 *  @TTaken
 *****************************************************************************/
 TTaken::TTaken() :
    FType(takenError), FIncompletedType(takenError),
    FVersion(LOKI_SUPPORT_VERSION), FDigitBase(10), FMode(MODE_EMS),
    FSectionDepth(0), FBlockDepth(0),
    FCachedBytes(0)
{
}

TTaken::Type TTaken::Push(char *&Script)
{
    if (takenIncomplete == FType)
    {
        Script = CacheValue(Script);
        return FType;
    }
    FType = (TTaken::Type)*Script;

    switch (FType)
    {
    case TTaken::takenVersion:
        if (0 == FSectionDepth)
        {
            Script = CacheValue(Script);
            FVersion = (uint8_t)Value(10);      // always 10base
            if (FVersion > LOKI_SUPPORT_VERSION)
                FType = takenError;
        }
        else
            FType = takenError;
        break;

    case TTaken::takenDigitBase:
        if (0 == FSectionDepth)
        {
            Script = CacheValue(Script);
            FDigitBase = (uint8_t)Value(10);    // always 10base

            if (! (10 == FDigitBase || 16 == FDigitBase))
                FType = takenError;
        }
        else
            FType = takenError;
        break;

#if LOKI_SUPPORT_VERSION > 1
    case TTaken::takenMode:
        if (0 == FSectionDepth)
        {
            Script = CacheValue(Script);
            FMode = (mode_t)Value(10);          // always 10base

            if (FMode > MODE_MAX_VALUE)
                FType = takenError;
        }
        else
            FType = takenError;
        break;
#endif

    case TTaken::takenFrequencyT:
    case TTaken::takenImpulse:
    case TTaken::takenFrequency:
    case TTaken::takenCluster:
#if LOKI_SUPPORT_VERSION > 1
    case TTaken::takenSync:
#endif
        if (FBlockDepth != 1)
        {
            FType = takenError;
            break;
        }
        goto fall_through_dummy1;
fall_through_dummy1:
    case TTaken::takenInterval:
    case TTaken::takenRepeat:
    case TTaken::takenSection:
        Script = CacheValue(Script);
        break;

    case TTaken::takenBlockSingle:
        if (FBlockDepth > 0)
            FBlockDepth --;
        goto fall_through_dummy2;
fall_through_dummy2:
    case TTaken::takenBlockStart:
        FBlockDepth ++;
        if (1 != FBlockDepth)
            FType = takenError;
        else
            Script ++;
        break;

    case TTaken::takenBlockEnd:
        FBlockDepth --;
        if (0 != FBlockDepth)
            FType = takenError;
        else
            Script ++;
        break;

    case TTaken::takenSectionStart:
        FSectionDepth ++;
        if (1 != FSectionDepth)
            FType = takenError;
        else
            Script ++;
        break;

    case takenSectionEnd:
        FSectionDepth --;
        FBlockDepth = 0;

        if (0 != FSectionDepth)
            FType = takenError;
        else
            Script ++;
        break;

    case takenVolumeStart:
    case takenVolumeEnd:
        Script ++;
        break;

    default:
        FType = takenError;
    }

    return FType;
}

uint16_t TTaken::Value(uint16_t DigitBase)
{
    if (FCachedBytes > 0)
    {
        FCache[FCachedBytes] = '\0';

        FCachedBytes = 0;   // clear when take the value
        FIncompletedType = takenError;

        return (uint16_t)std::strtol(FCache, NULL, DigitBase);
    }
    else
        return std::numeric_limits<uint16_t>::max();
}

uint16_t TTaken::Value(void)
{
    return Value(FDigitBase);
}

void TTaken::Reset(void)
{
    FCachedBytes = 0;
    FIncompletedType = takenError;

    FSectionDepth = 0;
    FBlockDepth = 0;
    FType = takenError;
}

char *TTaken::CacheValue(char *p)
{
    if (takenIncomplete != FType)
        p ++;

    uint8_t idx = FCachedBytes;
    while (idx < sizeof(FCache) - 1)
    {
        if (*p)
        {
            if (std::isdigit(*p) || (*p >= 'a' && *p <= 'f'))
            {
                if (*p > 0x20)
                {
                    FCache[idx] = *p;
                    idx ++;
                }
                p ++;
            }
            else
            {
                if (takenIncomplete == FType)
                    FType = FIncompletedType;

                FCachedBytes = idx;
                return p;
            }
        }
        else
        {
            if (takenIncomplete != FType)
            {
                FIncompletedType = FType;
                FType = takenIncomplete;
            }

            FCachedBytes = idx;
            return p;
        }
    }

    // cache overflow: should never falling here
    FType = takenError;
    return NULL;
}

/*****************************************************************************
 *  @TBlock
 *****************************************************************************/
TBlock::TBlock(uint16_t const repeat) :
    FRepeat(repeat), FCluster(1),
    FFrequencyT(500), FImpulseUS(100), FIntervalMS(0),
    FNotify(0)
{
}

TBlock::TBlock(TBlock const *prev) :
    FRepeat(prev->FRepeat), FCluster(prev->FCluster),
    FFrequencyT(prev->FFrequencyT), FImpulseUS(prev->FImpulseUS), FIntervalMS(prev->FIntervalMS),
    FNotify(0)
{
}

bool TBlock::PushTaken(TTaken &Taken)
{
    switch(Taken)
    {
    case TTaken::takenInterval:
        FIntervalMS = Taken.Value();
        return true;

    case TTaken::takenRepeat:
        FRepeat = Taken.Value();
        return true;

    case TTaken::takenFrequencyT:
        FFrequencyT = Taken.Value();
        return true;

    case TTaken::takenFrequency:
        FFrequencyT = Taken.Value() * 10;
        return true;

    case TTaken::takenImpulse:
        FImpulseUS = Taken.Value();
        if (FImpulseUS <= MINI_IMPULSE)
            FImpulseUS = MINI_IMPULSE;
        return true;

    case TTaken::takenCluster:
        FCluster = Taken.Value();
        return true;

#if LOKI_SUPPORT_VERSION > 1
    case TTaken::takenSync:
        FNotify = Taken.Value();
        return true;
#endif

    default:
        return false;
    }
}

/*****************************************************************************
 *  @TBlockParams
 *****************************************************************************/
TBlockParams::TBlockParams() :
    TBlock(1),
    FCurrRepeating(0)
{
}

TBlockParams::TBlockParams(TBlock const *block) :
    TBlock(block),
    FCurrRepeating(0)
{
}

/*****************************************************************************
 *  @TSection
 *****************************************************************************/
TSection::TSection() :
    FRepeat(1), FIntervalMS(0),
    FReadingBlock(NULL)
{
}

TSection::~TSection()
{
    if (FReadingBlock)
        TBlockList::Release(FReadingBlock);
}

bool TSection::PushTaken(TTaken &Taken)
{
    if (0 == Taken.BlockDepth())
    {
        switch (Taken)
        {
        case TTaken::takenBlockEnd:
            if (! FReadingBlock)
                return false;
        case TTaken::takenSectionEnd:
            goto block_end;

        case TTaken::takenRepeat:
            FRepeat = Taken.Value();
            return true;

        case TTaken::takenInterval:
            FIntervalMS = Taken.Value();
            return true;

        default:
            return false;
        };
    }
    else if (1 == Taken.BlockDepth())
    {
        TBlock *Block;

        switch (Taken)
        {
        case TTaken::takenBlockSingle:
        case TTaken::takenBlockStart:
block_end:
            Block = FReadingBlock;
            if (Block)
            {
                if (Block->Validate())
                    PushBlock(Block);
                else
                    return false;
            }

            if (Taken != TTaken::takenSectionEnd)
            {
                FReadingBlock = TBlockList::Allocate();
                if (Block)
                    *FReadingBlock = *Block;
            }
            else
                FReadingBlock = NULL;

            return true;

        default:
            return FReadingBlock->PushTaken(Taken);
        };
    }
    else
        return false;
}

/*****************************************************************************
 *  @TParser
 *****************************************************************************/
int TParser::Open(char const *FileName)
{
    if (FFile)
        delete FFile;
    FFile = new TFileStream(FileName, 0);

    if (-1 == FFile->Fd() || ! ReadNext())
    {
        delete FFile;
        FFile = NULL;

        return -1;
    }

    TRACE(LOG, "Loki File Version %d, DigitBase %d", Version(), DigitBase());
    return FFile->Fd();
}

TBlock *TParser::NextBlock()
{
    while (FCurrSection.IsEmpty())
    {
        if (FEndOfCurrSection)
        {
            FCurrSection.Reset();
            FEndOfCurrSection = false;

            if (FEndOfAllSections)
            {
                if (FScriptRPos >= FScriptWPos)
                    return NULL;

                // seek to volume script section offset
                uint16_t SectionNo = FScript[FScriptRPos];
                FScriptRPos ++;

                if (SectionNo > FSectionCount)
                    return NULL;
                FFile->Seek(FSectionOffsets[SectionNo], SEEK_SET);

                TRACE(LOG, "Script... No:%d @Offset:%d of %d msec",
                    SectionNo + 1, FSectionOffsets[SectionNo], FTimeEstimateMS);
            }
            else
            {
                TRACE(LOG, "Reading...No:%d @Offset:%d of %d msec",
                    FSectionCount, FCurrSectionOffset, FTimeEstimateMS);
            }
        }

        if (! ReadNext())
            return NULL;
    }

    TBlock *Block = FCurrSection.NextBlock();
    if (Block)
    {
        FTimeEstimateMS += Block->TimeEstimateMS();

        FCurrBlock = Block;
        TBlockList::Release(Block);

        return &FCurrBlock;
    }
    else
        return NULL;
}

bool TParser::ReadNext(void)
{
    if (! FFile)
        return false;

    char *CachePtr = FCache;
    int Len = FFile->Read(CachePtr, sizeof(FCache) - 1);

    if (0 == Len)
        return false;
    else
        CachePtr[Len] = '\0';

    while (*CachePtr)
    {
        while (*CachePtr && *CachePtr <= 0x20)
            CachePtr ++;
        if (! *CachePtr)
            return true;

        FTaken.Push(CachePtr);

        if (TTaken::takenError == FTaken)
        {
            TRACE(LOG, "parser error\r\n", 14);
            return false;
        }
        if (TTaken::takenIncomplete == FTaken)
            return true;

        if (1 == FTaken.SectionDepth())
        {
            switch (FTaken)
            {
            case TTaken::takenSectionStart:
                FCurrSectionOffset = FFile->Position() - Len + (CachePtr - FCache) - 1;

                if (FSectionCount > 0 &&
                    FSectionOffsets[FSectionCount - 1] == FCurrSectionOffset)
                {
                    // section repeat loop back
                    // nothing to do if this section is recorded
                    continue;
                }
                else
                {
                    if (! FEndOfAllSections)
                    {
                        // recoding section offset for final script
                        FSectionOffsets[FSectionCount] = FCurrSectionOffset;
                        FSectionCount ++;
                    }
                    continue;
                }

            default:
                if (! FCurrSection.PushTaken(FTaken))
                    return false;
            }
        }
        else if (0 == FTaken.SectionDepth())
        {
            switch (FTaken)
            {
            case TTaken::takenVersion:
            case TTaken::takenDigitBase:
                continue;

            case TTaken::takenSectionEnd:
                if (! FCurrSection.PushTaken(FTaken))
                    return false;

                // add a interval only block
                if (FCurrSection.IntervalMS() > 0)
                {
                    TBlock *Block = TBlockList::Allocate();
                    Block->IntervalOnly(FCurrSection.IntervalMS());
                    FCurrSection.PushBlock(Block);
                }

                if (! FCurrSection.LoopNext())
                {
                    FEndOfCurrSection = true;

                    if (! FEndOfAllSections)
                    {
                        // seek to next section start
                        uint32_t SectionOffset = Len - (CachePtr - FCache);
                        FFile->Seek(-SectionOffset, SEEK_CUR);
                    }
                }
                else
                    FFile->Seek(FCurrSectionOffset, SEEK_SET);

                return true;

            case TTaken::takenVolumeStart:
                if (FEndOfAllSections)
                    return true;
                FEndOfAllSections = true;
                continue;

            case TTaken::takenVolumeEnd:
                FEndOfCurrSection = true;
                return true;

            case TTaken::takenSection:
                if (! FEndOfAllSections)
                    return false;

                FScript[FScriptWPos] = (uint8_t)FTaken.Value(10) - 1;   // always 10base
                FScriptWPos ++;
                continue;

            default:
                return false;
            }
        }
        else
            return false;
    }
    return true;
}
