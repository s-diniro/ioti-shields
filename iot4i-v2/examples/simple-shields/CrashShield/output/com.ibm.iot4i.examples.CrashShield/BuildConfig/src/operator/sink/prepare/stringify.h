// eJylU11v2jAUlV_15FRnaA9Eo_0YJBs3VSm7KpEFJY4GFPlZsYcAlJajuQgPjvcwyECXkP0wyK7aNzrXPvPZemUYugCDKcxDCy7e9ZHLCEAAPo_1GeBequlHf_0sSJH2gAZbMvLb5rAwnt35YDR8_1UV9nFvubOMNi1Xmvf0cTp3uYDfqub6TD3eO_1uN_0vJvcW4vWsv6X57amP1tRfzK5f3T7zmMsZxbEe9Ktqa_0_1F7hXDGc9WryNB7v_0xvV0YzD1U88r9NRf5c8PE6eDJlmnfEcHhgEizD7qwB_07tk0oIzheAIEZEsyUYJYEa0uwjgT7LMG6EqwnwW5lmk_0JZDhmlgkA0NYoxFCj8xe6hASFGk4YvqFLjKKQlpc2vtmYGsrhOo0Q1Sgu94rgEEiXvrhoIWQQxEmMDBBAFiwByzj1K4qz9Z5rQHBNm5SFTRhFzZJ2UFAeoLQ0T_1M1SSIEY0WETAkMUAVRBoOVgL6VluLRdQAYydD5a4A5jhgqbSdyOwXyawOnCeHNay0Qe8koIk9hQ1U_03CmipSro5ylBlHIBwrIn9vGV_1zErwICIEdjXFL7wXGnIpdwdpXRVVRHMcu2rU7lsW6gRk8V1UtueMcxjCtuGaTolQeOs9t8dbttbSOKmkNA7brfHzdDVL5WMQ_01QA7z0R9Xg7CcCt_10NihmtECgkjiHhna7AsrCJpLDXYwvWoOygMNEl9mrGeEtPSwyH8kmRlVXluBio86F9PljqVUiVxCXKvOb8mdaFZqg8s9_1fzohz



#ifndef SPL_OPER_INSTANCE_SINK_PREPARE_STRINGIFY_H_
#define SPL_OPER_INSTANCE_SINK_PREPARE_STRINGIFY_H_

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

#include "../../../type/BeJwrMS42Ky1OLfJMKbYsSix3LUvNKykuNjRKTC7JzM8LSCxKzC0GAPzQA3g.h"
#include "../../../type/BeJwrMSw2SUksSQQADLECDn.h"
#include "../../../type/BeJyrNI03TS0qyi8yKU8syjPJzEvLN01JTSpNNy0pSkxOBQC5eQu5.h"

#include <bitset>

#define MY_OPERATOR stringify$OP
#define MY_BASE_OPERATOR stringify_Base
#define MY_OPERATOR_SCOPE SPL::_Operator::sink::prepare

namespace SPL {
namespace _Operator {
namespace sink {
namespace prepare {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMS42Ky1OLfJMKbYsSix3LUvNKykuNjRKTC7JzM8LSCxKzC0GAPzQA3g IPort0Type;
    typedef SPL::BeJwrMSw2SUksSQQADLECDn OPort0Type;
    
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
    SPL::rstring lit$3;
    SPL::rstring lit$4;
    SPL::rstring lit$5;
    SPL::rstring lit$6;
    SPL::rstring lit$7;
    SPL::rstring lit$8;
    SPL::rstring lit$9;
    SPL::uint32 lit$10;
    
    
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
} // namespace prepare
} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_SINK_PREPARE_STRINGIFY_H_

