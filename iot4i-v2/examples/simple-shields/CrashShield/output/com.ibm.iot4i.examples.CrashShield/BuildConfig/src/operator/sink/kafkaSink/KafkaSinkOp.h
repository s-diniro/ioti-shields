// eJzNVdtunDAQlf8ErfoALYEFNmliRZHSppE23VykTZ6RMZPgcDGyTTbbqv9eY8gqu_1VD8lC1AjH4MPY5Mx7GlNcBy_0pAKgGkls9BSe5LgvH33twInncUBIrQVF8xmgRBONxq3UL4BS5W4nI5ixe0fFp_1W3VXcv9aLFfxj_0lULcr9y9vV3SlZzudnKigm6Hh5s0gvrubnXUMV441MKa9TzZ4yrmasH9W8CYoTzRUlqGLqwxTpORgLLY81D8hgkQWLLVhiwWYWbN_0CHViwzxbs0IId2TRbA7FFEu2GgsIackZCeZ_1KggjIQ50tticLBlUuQ5O6vac4hGdStxXIULLebhy_0CiKLpRmEOVEENbyBCFGiaIFUp12Poenqn2MF_0FLlPqkqv3f75cAzhbbfLD_1jvALSOGbKrSAUNpBUhJYGOkEJmujZE4SU6ODlmSBaESmvSA1oJ_0jtxLgTai3IgLcgiOJCBluVeT3CEw_0dKr1C1ik4FwAD34Jlgog1SnYpXTPe1CHGd4rp5K8xfgB1q6MqmTpjAqheeu2_0ReDE85xPzrZn2G9E_0EieSJixRnvsaPw3onirwpyvmoqTXBfTx_19Fl0lWxTKbolb0_068YyHNW_1VFCEcLYAK97C8aaG2NNrh_19P2IA3V_0Mb7rtqgN5KatXPH25vi9407I83zE_18mDiwSS_0Y77OdOCjWtlWKSVSHb8Oxh_1S0rFGHcycEy1ae7jjDJuMR57Nz1zP06yuaygO_1hqFXtg0TO9tDJogid9CoFP5tSBNA9UQiOm2gzkczNGY0_0lox_0RG8W6l9CcVa7nYHB3vOKMQQ8IcdH3DUrxlFL2UWAnrzXsNUpIH2IynvwGnvmVk

#include <SPL/Toolkit/JavaOp.h>


#ifndef SPL_OPER_INSTANCE_SINK_KAFKASINK_KAFKASINKOP_H_
#define SPL_OPER_INSTANCE_SINK_KAFKASINK_KAFKASINKOP_H_

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

#include "../../../type/BeJwrMS42LckvyEwuNs5OrSw2z00tLk5MTwUAaSIIDt.h"
#include <SPL_JNIFunctions_com_ibm_iot4i_common.h>


#define MY_OPERATOR KafkaSinkOp$OP
#define MY_BASE_OPERATOR KafkaSinkOp_Base
#define MY_OPERATOR_SCOPE SPL::_Operator::sink::kafkaSink

namespace SPL {
namespace _Operator {
namespace sink {
namespace kafkaSink {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMS42LckvyEwuNs5OrSw2z00tLk5MTwUAaSIIDt IPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    virtual void javaopInternalAction(Punctuation const & punct, uint32_t port) = 0;
    
    
    
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
    SPL::rstring lit$10;
    SPL::rstring lit$11;
    SPL::rstring lit$12;
    
    
protected:
    Mutex $svMutex;
    SPL::rstring param$className$0;
    SPL::rstring param$classLibrary$0;
    SPL::rstring param$classLibrary$1;
    SPL::rstring param$classLibrary$2;
    SPL::rstring param$propertiesFile$0;
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
  // constructor
  MY_OPERATOR();

  // destructor
  virtual ~MY_OPERATOR(); 

  // notify port readiness
  void allPortsReady(); 

  // notify termination
  void prepareToShutdown(); 

  // processing for source and threaded operators   
  void process(uint32_t idx);
    
  // tuple processing for mutating ports 
  void process(Tuple & tuple, uint32_t port);
    
  // tuple processing for non-mutating ports
  void process(Tuple const & tuple, uint32_t port);

  // punctuation processing
  void process(Punctuation const & punct, uint32_t port);
private:
  void setupStateHandler();

  // members
  
  /** How we invoke actions on the Java Operator implementation */
  SPL::JNI::JNIBridgeInvoker* _bi;
  
  /* The instance of the JNIBridge used to wrap the Java Operator implementation */
  jobject _bridge;

  typedef void (*FP)(SPL::JNI::JNIBridgeInvoker&, jobject, NativeByteBuffer &, uint32_t);
  FP _fp;
  
  bool hasTupleLogic;
  
  std::tr1::shared_ptr<SPL::StateHandler> _stateHandler;

public:
  virtual void javaopInternalAction(Punctuation const & punct, uint32_t port)
  {
     _bi->action(_bridge, punct, port);
  }
    
  // handle byte buffers being send as is
  virtual void processRaw(NativeByteBuffer & buffer, uint32_t port)
  {
     (*_fp)(*_bi, _bridge, buffer, port);
  }
  
  //Java operators handle byte buffers directly
  virtual bool sendRawBufferData() { return !hasTupleLogic; }

  // Requests the blocking of a consistent region permit
  virtual void blockConsistentRegionPermit() {
      _bi->blockConsistentRegionPermit(_bridge);
  }
}; 

} // namespace sink
} // namespace kafkaSink
} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_SINK_KAFKASINK_KAFKASINKOP_H_

