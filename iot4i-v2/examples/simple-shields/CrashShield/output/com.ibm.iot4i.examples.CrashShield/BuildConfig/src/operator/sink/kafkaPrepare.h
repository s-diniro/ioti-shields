// eJyNkmFr2zAQhrl_1YsI_02My1HTftB1EKXdNBRrqtOP0cNPkaC8uW0cl1s7H_1Pkm0oZS0DAvbd3rvlfScaFCZQcWt1D1XjH0de2G1gTkU7ilhlmW5G3Y_1YP4Fv03mtlqUa9E_07m_0m8Tud_1TDVVP4uCrtuz2430_10Vr1arpc2a2bHSqazuW6ru7q6W65vrZe9lBZyCkvZTAdXPNWOGrJH9DkJufiRXvslB3mEteU4PW2q4wTqX2soTaiSqmnywkCePZY5PvBsUUk7Sfw_0Ca8OpqUKQ19xy6HWPcxDcigbs6KQX2I_1dH7ce8o5SsnXKlUq97G_0ETwIHDy_19pbVC3kehZGO4wEOKLBdtSF26w85c9QzAmhFf3kXgLQdtDhzeIQYSTGgNuJKw3RcQ3kEfcfifdkHnXE_1B6kGKV4Zv8M_0f_0be4_10gUx6F10eeIsTBFg9oKTvbitTCNQvSgNLfni_0iSMS_0Jn0vCNXRUibGN7JCxHVr_140h2w6qvUFCcJIlbI1ydBNwU8R2_0v68D3sxZbT25OHHI_1gFdAvK4



#ifndef SPL_OPER_INSTANCE_SINK_KAFKAPREPARE_H_
#define SPL_OPER_INSTANCE_SINK_KAFKAPREPARE_H_

#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/Operator/State/StateHandler.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../../type/BeJwrMS42LckvyEwuNs5OrSw2z00tLk5MTwUAaSIIDt.h"
#include "../../type/BeJwrMSw2SUksSQQADLECDn.h"

#include <bitset>

#define MY_OPERATOR kafkaPrepare$OP
#define MY_BASE_OPERATOR kafkaPrepare_Base
#define MY_OPERATOR_SCOPE SPL::_Operator::sink

namespace SPL {
namespace _Operator {
namespace sink {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSw2SUksSQQADLECDn IPort0Type;
    typedef SPL::BeJwrMS42LckvyEwuNs5OrSw2z00tLk5MTwUAaSIIDt OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    
    inline void submit(Tuple & tuple, uint32_t port)
    {
        Operator::submit(tuple, port);
    }
    inline void submit(Punctuation const & punct, uint32_t port)
    {
        Operator::submit(punct, port);
    }
    
    
    
    SPL::rstring lit$0;
    SPL::rstring lit$1;
    SPL::rstring lit$2;
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<2> OPortBitsetType;
    OPortBitsetType $oportBitset;
    Mutex $fpMutex;
    void checkpointStateVariables(NetworkByteBuffer & opstate) const;
    void restoreStateVariables(NetworkByteBuffer & opstate);
    void checkpointStateVariables(Checkpoint & ckpt);
    void resetStateVariables(Checkpoint & ckpt);
    void resetStateVariablesToInitialState();
    bool hasStateVariables() const;
    void resetToInitialStateRaw();
    void checkpointRaw(Checkpoint & ckpt);
    void resetRaw(Checkpoint & ckpt);
private:
    static bool globalInit_;
    static bool globalIniter();
    ParameterMapType paramValues_;
    Metric* metrics_[1];
    ParameterMapType& getParameters() { return paramValues_;}
    void addParameterValue(std::string const & param, ConstValueHandle const& value)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create(value));
    }
    void addParameterValue(std::string const & param)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create());
    }
};


class MY_OPERATOR : public MY_BASE_OPERATOR
{
public:
   MY_OPERATOR() {}
  
   void process(Tuple const & tuple, uint32_t port);
   void process(Punctuation const & punct, uint32_t port);
   
}; 

} // namespace sink
} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_SINK_KAFKAPREPARE_H_

