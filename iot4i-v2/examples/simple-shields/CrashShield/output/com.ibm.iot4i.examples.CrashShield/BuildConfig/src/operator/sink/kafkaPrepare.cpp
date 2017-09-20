// eJyNkmFr2zAQhrl_1YsI_02My1HTftB1EKXdNBRrqtOP0cNPkaC8uW0cl1s7H_1Pkm0oZS0DAvbd3rvlfScaFCZQcWt1D1XjH0de2G1gTkU7ilhlmW5G3Y_1YP4Fv03mtlqUa9E_07m_0m8Tud_1TDVVP4uCrtuz2430_10Vr1arpc2a2bHSqazuW6ru7q6W65vrZe9lBZyCkvZTAdXPNWOGrJH9DkJufiRXvslB3mEteU4PW2q4wTqX2soTaiSqmnywkCePZY5PvBsUUk7Sfw_0Ca8OpqUKQ19xy6HWPcxDcigbs6KQX2I_1dH7ce8o5SsnXKlUq97G_0ETwIHDy_19pbVC3kehZGO4wEOKLBdtSF26w85c9QzAmhFf3kXgLQdtDhzeIQYSTGgNuJKw3RcQ3kEfcfifdkHnXE_1B6kGKV4Zv8M_0f_0be4_10gUx6F10eeIsTBFg9oKTvbitTCNQvSgNLfni_0iSMS_0Jn0vCNXRUibGN7JCxHVr_140h2w6qvUFCcJIlbI1ydBNwU8R2_0v68D3sxZbT25OHHI_1gFdAvK4


#include "./kafkaPrepare.h"
using namespace SPL::_Operator::sink;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator::sink
#define MY_BASE_OPERATOR kafkaPrepare_Base
#define MY_OPERATOR kafkaPrepare$OP




void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port) 
{
   IPort0Type const & iport$0 = static_cast<IPort0Type const&>(tuple);
   if (! (1) ) 
       return;
   { OPort0Type otuple(lit$2, ((lit$1 + ::SPL::spl_cast<SPL::rstring, SPL::float64 >::cast(::SPL::Functions::Time::getTimestampInSecs())) + lit$0), iport$0.get_data()); submit (otuple, 0);
 }
   
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port) 
{
   forwardWindowPunctuation(punct);
}

static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("sink::kafkaPrepare",&initer));
    return true;
}

template<class T> static void initRTC (SPL::Operator& o, T& v, const char * n) {
    SPL::ValueHandle vh = v;
    o.getContext().getRuntimeConstantValue(vh, n);
}

MY_BASE_OPERATOR::MY_BASE_OPERATOR()
 : Operator() {
    uint32_t index = getIndex();
    initRTC(*this, lit$0, "lit$0");
    initRTC(*this, lit$1, "lit$1");
    initRTC(*this, lit$2, "lit$2");
    (void) getParameters(); // ensure thread safety by initializing here
    $oportBitset = OPortBitsetType(std::string("01"));
    OperatorMetrics& om = getContext().getMetrics();
    metrics_[0] = &(om.createCustomMetric("nExceptionsCaughtPort0", "Number of exceptions caught on port 0", Metric::Counter));
}
MY_BASE_OPERATOR::~MY_BASE_OPERATOR()
{
    for (ParameterMapType::const_iterator it = paramValues_.begin(); it != paramValues_.end(); it++) {
        const ParameterValueListType& pvl = it->second;
        for (ParameterValueListType::const_iterator it2 = pvl.begin(); it2 != pvl.end(); it2++) {
            delete *it2;
        }
    }
}

void MY_BASE_OPERATOR::tupleLogic(Tuple const & tuple, uint32_t port) {
}


void MY_BASE_OPERATOR::processRaw(Tuple const & tuple, uint32_t port) {
    try {
            tupleLogic (tuple, port);
            static_cast<MY_OPERATOR_SCOPE::MY_OPERATOR*>(this)->MY_OPERATOR::process(tuple, port);
    } catch (SPL::SPLRuntimeException const & e) {
        if (getContext().getPE().mustRethrowException()) {
            throw e;
        }
        SPLAPPTRC(L_ERROR, "Exception in operator " << getContext().getName()
            << " in port " << port, SPL_OPER_DBG);
        SPLAPPTRC(L_ERROR, "Processed tuple: " << tuple, SPL_OPER_DBG);
        SPLAPPTRC(L_ERROR, "Exception: " << e, SPL_OPER_DBG);
        metrics_[port]->incrementValue();
    }
    catch (std::exception const & e) {
        if (getContext().getPE().mustRethrowException()) {
            throw e;
        }
        SPLAPPTRC(L_ERROR, "Exception in operator " << getContext().getName()
            << " in port " << port, SPL_OPER_DBG);
        SPLAPPTRC(L_ERROR, "Processed tuple: " << tuple, SPL_OPER_DBG);
        SPLAPPTRC(L_ERROR, "Exception identifier: " << e.what(), SPL_OPER_DBG);
        std::stringstream backtrace;
        SPL::BacktraceDumper::dump(backtrace);
        SPLAPPTRC(L_ERROR, "Exception: " << backtrace.str(), SPL_OPER_DBG);
        metrics_[port]->incrementValue();
    }
    catch (...) {
        if (getContext().getPE().mustRethrowException()) {
            throw;
        }
        SPLAPPTRC(L_ERROR, "Exception in operator " << getContext().getName()
            << " in port " << port, SPL_OPER_DBG);
        SPLAPPTRC(L_ERROR, "Processed tuple: " << tuple, SPL_OPER_DBG);
        std::stringstream backtrace;
        SPL::BacktraceDumper::dump(backtrace);
        SPLAPPTRC(L_ERROR, "Exception: " << backtrace.str(), SPL_OPER_DBG);
        metrics_[port]->incrementValue();
    }
}


void MY_BASE_OPERATOR::punctLogic(Punctuation const & punct, uint32_t port) {
}

void MY_BASE_OPERATOR::punctPermitProcessRaw(Punctuation const & punct, uint32_t port) {
    {
        punctNoPermitProcessRaw(punct, port);
    }
}

void MY_BASE_OPERATOR::punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port) {
    switch(punct) {
    case Punctuation::WindowMarker:
        punctLogic(punct, port);
        process(punct, port);
        break;
    case Punctuation::FinalMarker:
        punctLogic(punct, port);
        
        if (punct == Punctuation::FinalMarker) {
            process(punct, port);
            bool forward = false;
            {
                AutoPortMutex $apm($fpMutex, *this);
                $oportBitset.reset(port);
                if ($oportBitset.none()) {
                    $oportBitset.set(1);
                    forward=true;
                }
            }
            if(forward)
                submit(punct, 0);
            return;
        }
        process(punct, port);
        break;
    case Punctuation::DrainMarker:
    case Punctuation::ResetMarker:
    case Punctuation::ResumeMarker:
        break;
    case Punctuation::SwitchMarker:
        break;
    default:
        break;
    }
}

void MY_BASE_OPERATOR::processRaw(Punctuation const & punct, uint32_t port) {
    switch(port) {
    case 0:
        punctNoPermitProcessRaw(punct, port);
        break;
    }
}



void MY_BASE_OPERATOR::checkpointStateVariables(NetworkByteBuffer & opstate) const {
}

void MY_BASE_OPERATOR::restoreStateVariables(NetworkByteBuffer & opstate) {
}

void MY_BASE_OPERATOR::checkpointStateVariables(Checkpoint & ckpt) {
}

void MY_BASE_OPERATOR::resetStateVariables(Checkpoint & ckpt) {
}

void MY_BASE_OPERATOR::resetStateVariablesToInitialState() {
}

bool MY_BASE_OPERATOR::hasStateVariables() const {
    return false;
}

void MY_BASE_OPERATOR::resetToInitialStateRaw() {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->resetToInitialState();
    }
    resetStateVariablesToInitialState();
}

void MY_BASE_OPERATOR::checkpointRaw(Checkpoint & ckpt) {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->checkpoint(ckpt);
    }
    checkpointStateVariables(ckpt);
}

void MY_BASE_OPERATOR::resetRaw(Checkpoint & ckpt) {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->reset(ckpt);
    }
    resetStateVariables(ckpt);
}



