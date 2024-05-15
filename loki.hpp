 #ifndef __LOKI_FILE_HPP
#define __LOKI_FILE_HPP

#define _RWSTD_NO_WCHAR_T

#include <limits>
#include <ultracore/glist.h>
#include <uc++/stream.hpp>

#include "config.h"

#ifndef LOKI_SUPPORT_VERSION
    /**
     *  loki parser support version
     *     default to 1, max supported now is 2
     */
    #define LOKI_SUPPORT_VERSION        (1)
#endif

#ifndef LOKI_PARSER_CACHE
    #define LOKI_PARSER_CACHE           (120)
#endif

    #define LOKI_INF_REPEAT             (std::numeric_limits<uint16_t>::max())
    #define LOKI_MAX_SECTIONS           (64)
    #define LOKI_MAX_SCRIPTS            (512)

namespace Loki
{
    enum mode_t
    {
        MODE_EMS,
        MODE_EMS_ASYMMETRY,
        MODE_TENS,

        MODE_MAX_VALUE              = MODE_TENS
    };

    class TTaken
    {
    public: // types
        enum Type
        {
            takenError,
            takenIncomplete,

            takenVersion                = 'V',
            takenDigitBase              = 'D',  // digit 10 base / 16 base

            takenBlockStart             = '[',
            takenBlockEnd               = ']',
            takenBlockSingle            = '|',

            takenSectionStart           = '{',
            takenSectionEnd             = '}',

            takenVolumeStart            = '<',
            takenVolumeEnd              = '>',
            takenSection                = 'S',

            takenInterval               = 'I',
            takenRepeat                 = 'R',
            takenImpulse                = 'P',
            takenFrequency              = 'F',  // frequency in HZ
            takenFrequencyT             = 'T',  // One-tenth of HZ for more accuracy
            takenCluster                = 'C',

#if LOKI_SUPPORT_VERSION > 1
            takenMode                   = 'M',  // set a mode before starting
            takenSync                   = 'N',  // notify synchronization %d
#endif
        };

    public:
        TTaken();

        Type Push(char *&Script);

        uint16_t Value(uint16_t DigitBase);
        uint16_t Value(void);

        void Reset(void);

    public:
        operator TTaken::Type () const
            { return FType; }

        int SectionDepth() const
            { return FSectionDepth; }
        int BlockDepth() const
            { return FBlockDepth; }
        uint8_t Version() const
            { return FVersion; }
        uint8_t DigitBase() const
            { return FDigitBase; }
        mode_t Mode() const
            { return (mode_t)FMode; }

    private:
        char *CacheValue(char *p);

        Type FType, FIncompletedType;

        uint8_t FVersion, FDigitBase, FMode;
        int FSectionDepth, FBlockDepth;

        uint8_t FCachedBytes;
        char FCache[9];
    };

    class TBlock: public glist_hdr_t
    {
        friend class TSection;

    public:
        TBlock(uint16_t const repeat = 1);
        TBlock(TBlock const *prev);

        bool Validate(void) const
        {
            // return (FImpulseUS < 1000000 * 10 / 2 / FFrequencyT);

            /// @limit block to 3/4 duty
            ///     1200hz = 416 us cycle = max 312 us duty
            ///     1000hz = 500 us cycle = max 375 us duty
            ///      936hz = 536 us cycle = max 400 us duty
            return (FImpulseUS < 1000000 * 10 * 3 / 8 / FFrequencyT);
        }

        uint32_t TimeEstimateMS() const
        {
            if (FRepeat == LOKI_INF_REPEAT)
                return 0;
            else if (FFrequencyT > 0)
                return (1000000 * 10 / FFrequencyT * FCluster * FRepeat + 499) / 1000 + FIntervalMS * FRepeat;
            else
                return FIntervalMS * FRepeat;
        }

        uint32_t TimeEstimateMSNoRepeat() const
        {
            if (FFrequencyT > 0)
                return (1000000 * 10 / FFrequencyT * FCluster + 499) / 1000 + FIntervalMS;
            else
                return FIntervalMS;
        }

        void IntervalOnly(uint16_t const val)
        {
            FIntervalMS = val;
            FRepeat = 1;
            FCluster = FFrequencyT = FImpulseUS = 0;
        }

        uint16_t Repeat(void) const
            { return FRepeat; }
        void Repeat(uint16_t val)
            { FRepeat = val; }

        void InfRepeat(void)
            { FRepeat = LOKI_INF_REPEAT; }
        bool IsInfRepeat(void) const
            { return LOKI_INF_REPEAT == FRepeat; }

        uint16_t FrequencyT(void) const
            { return FFrequencyT; }
        void FrequencyT(uint16_t const val)
            { FFrequencyT = val; }

        uint16_t ImpulseUS() const
            { return FImpulseUS; }
        void ImpulseUS(uint16_t const val)
            { FImpulseUS = val; }

        uint16_t Cluster(void) const
            { return FCluster; }
        void Cluster(uint16_t const val)
            { FCluster = val; }

        uint16_t IntervalMS(void) const
            { return FIntervalMS; }
        void IntervalMS(uint16_t const val)
            { FIntervalMS = val; }

    protected:
        uint16_t FRepeat;
        uint16_t FCluster;
        uint16_t FFrequencyT;
        uint16_t FImpulseUS;
        uint16_t FIntervalMS;
        uint16_t FNotify;

    private:
        bool PushTaken(TTaken &Taken);
    };

    class TBlockParams :public TBlock
    {
        typedef TBlock inherited;

    public:
        TBlockParams();
        TBlockParams(TBlock const *block);

        bool LoopNext(void)
        {
            // all loop already done, but still calling this function
            if (FRepeat != LOKI_INF_REPEAT && FCurrRepeating >= FRepeat)
                return false;

            FCurrRepeating ++;
            if (FCurrRepeating >= FRepeat)
                return FRepeat == LOKI_INF_REPEAT;

            return true;
        }

        uint16_t CurrRepeating() const
            { return FCurrRepeating; }

        void Skip(void)
            { FCurrRepeating = inherited::FRepeat; }

    protected:
        uint16_t FCurrRepeating;
    };

    class TBlockList :public glist_t
    {
    public:
        static TBlock *Allocate()
            { return new TBlock(); }
        static void Release (TBlock *ptr)
            { delete ptr; }

        bool IsEmpty() const
            { return glist_is_empty(const_cast<TBlockList *>(this)); }
        void Clear()
            { TBlock *ptr; while (nullptr != (ptr = Pop())) delete ptr; }

        void PushBack(TBlock *ptr)
            { glist_push_back(this, ptr); }
        TBlock *Pop(void)
            { return static_cast<TBlock *>(glist_pop(this)); }
    };

    class TSection
    {
    public:
        TSection();
        ~TSection();

        void Reset(void)
        {
            FBlockList.Clear();

            FRepeat = 1;
            FIntervalMS = 0;
        }

        bool IsEmpty(void) const
            { return FBlockList.IsEmpty(); }

    public:
        uint16_t Repeat() const
            { return FRepeat; }
        uint16_t IntervalMS() const
            { return FIntervalMS; }

    protected:
        void PushBlock(TBlock *Block)
            { FBlockList.PushBack(Block); }

        TBlock *NextBlock(void)
            { return FBlockList.Pop(); }

        bool PushTaken(TTaken &Taken);

        uint16_t FRepeat;
        uint16_t FIntervalMS;

        TBlockList FBlockList;
        TBlock *FReadingBlock;
    };

    class TSectionParams :public TSection
    {
        typedef TSection inherited;
        friend class TParser;

    public:
        TSectionParams() :
            TSection(),
            FCurrRepeating(0)
            { }

        void Reset(void)
        {
            inherited::Reset();
            FCurrRepeating = 0;
        };

        bool LoopNext(void)
        {
            // all loop is done but still calling this function
            if (FRepeat != LOKI_INF_REPEAT && FCurrRepeating >= FRepeat)
                return false;

            FCurrRepeating ++;
            return FCurrRepeating < FRepeat;
        }

        uint16_t CurrRepeating() const
            { return FCurrRepeating; }

    protected:
        uint16_t FCurrRepeating;

    private:
        void CurrRepeating(uint16_t Value)
            { FCurrRepeating = Value; }
    };

    class TParser
    {
    public:
        TParser() :
            FFile(NULL), FTaken(),
            FSectionCount(0), FEndOfCurrSection(false), FEndOfAllSections(false),
            FScriptRPos(0), FScriptWPos(0), FTimeEstimateMS(0)
        {
        }

        ~TParser()
        {
            if (FFile)
                delete FFile;
        }

        int Open(char const *FileName);

    public:
        uint8_t Version() const
            { return FTaken.Version(); }
        uint8_t DigitBase() const
            { return FTaken.DigitBase(); }
        mode_t Mode() const
            { return FTaken.Mode(); }
        uint32_t TimeEstimateMS() const
            { return FTimeEstimateMS; }

        TBlock *NextBlock();

    private:
        bool ReadNext(void);

        TFileStream *FFile;
        TTaken FTaken;

        uint32_t FSectionOffsets[LOKI_MAX_SECTIONS];
        uint8_t FSectionCount;
        uint32_t FCurrSectionOffset;
        bool FEndOfCurrSection, FEndOfAllSections;

        uint8_t FScript[LOKI_MAX_SCRIPTS];
        uint16_t FScriptRPos, FScriptWPos;

        TSectionParams FCurrSection;
        TBlock FCurrBlock;

        uint32_t FTimeEstimateMS;

        char FCache[LOKI_PARSER_CACHE];
    };
}

typedef Loki::TParser TLokiParser;
typedef Loki::TBlock TLokiBlock;
typedef Loki::TBlockParams TLokiBlockParams;

#endif  // __LOKI_FILE_HPP
