#pragma once

#ifdef VOLUND_ENABLE_PROFILING

namespace Volund
{
    class Instrumentor;

    struct InstrumentorNode
    {
        std::string Name;
        std::chrono::time_point<std::chrono::steady_clock> Start;
        std::chrono::time_point<std::chrono::steady_clock> End;
        std::shared_ptr<InstrumentorNode> Parent;
        std::vector<std::shared_ptr<InstrumentorNode>> Children;
        std::string FormatTime();
        std::string FormatName();
        std::string Serialize(int Depth);
    };

    class VOLUND_API InstrumentorTimer
    {
    public:
        InstrumentorTimer(std::string const& Name);
        ~InstrumentorTimer();
    private:
        friend class Instrumentor;
        std::shared_ptr<InstrumentorNode> _Node;
    };

    class VOLUND_API Instrumentor
    {
    public:
    private:
        friend class InstrumentorTimer;
        Instrumentor();
        ~Instrumentor();
        static inline std::shared_ptr<InstrumentorNode> FirstNode;
        static inline std::shared_ptr<InstrumentorNode> CurrentNode;
    };
}

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define VOLUND_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define VOLUND_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define VOLUND_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define VOLUND_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define VOLUND_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define VOLUND_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define VOLUND_FUNC_SIG __func__
#else
#define VOLUND_FUNC_SIG "VOLUND_FUNC_SIG unknown!"
#endif

#define VOLUND_PROFILE_SCOPE(Name) auto Timer##__LINE__ = Volund::InstrumentorTimer(Name)
#define VOLUND_PROFILE_FUNCTION() VOLUND_PROFILE_SCOPE(VOLUND_FUNC_SIG)

#else

#define VOLUND_PROFILE_FUNCTION()
#define VOLUND_PROFILE_SCOPE(Name)

#endif
