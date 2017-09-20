// eJylU11v2jAUlV_15FRnaA9Eo_0YJBs3VSm7KpEFJY4GFPlZsYcAlJajuQgPjvcwyECXkP0wyK7aNzrXPvPZemUYugCDKcxDCy7e9ZHLCEAAPo_1GeBequlHf_0sSJH2gAZbMvLb5rAwnt35YDR8_1UV9nFvubOMNi1Xmvf0cTp3uYDfqub6TD3eO_1uN_0vJvcW4vWsv6X57amP1tRfzK5f3T7zmMsZxbEe9Ktqa_0_1F7hXDGc9WryNB7v_0xvV0YzD1U88r9NRf5c8PE6eDJlmnfEcHhgEizD7qwB_07tk0oIzheAIEZEsyUYJYEa0uwjgT7LMG6EqwnwW5lmk_0JZDhmlgkA0NYoxFCj8xe6hASFGk4YvqFLjKKQlpc2vtmYGsrhOo0Q1Sgu94rgEEiXvrhoIWQQxEmMDBBAFiwByzj1K4qz9Z5rQHBNm5SFTRhFzZJ2UFAeoLQ0T_1M1SSIEY0WETAkMUAVRBoOVgL6VluLRdQAYydD5a4A5jhgqbSdyOwXyawOnCeHNay0Qe8koIk9hQ1U_03CmipSro5ylBlHIBwrIn9vGV_1zErwICIEdjXFL7wXGnIpdwdpXRVVRHMcu2rU7lsW6gRk8V1UtueMcxjCtuGaTolQeOs9t8dbttbSOKmkNA7brfHzdDVL5WMQ_01QA7z0R9Xg7CcCt_10NihmtECgkjiHhna7AsrCJpLDXYwvWoOygMNEl9mrGeEtPSwyH8kmRlVXluBio86F9PljqVUiVxCXKvOb8mdaFZqg8s9_1fzohz


#include "./stringify.h"
using namespace SPL::_Operator::sink::prepare;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator::sink::prepare
#define MY_BASE_OPERATOR stringify_Base
#define MY_OPERATOR stringify$OP




void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port) 
{
   IPort0Type const & iport$0 = static_cast<IPort0Type const&>(tuple);
   if (! ((iport$0.get_userId() != lit$0)) ) 
       return;
   { OPort0Type otuple(((((((((lit$6 + iport$0.get_userId()) + lit$5) + lit$4) + lit$3) + iport$0.get_rawEvents()) + lit$2) + iport$0.get_actionParams()) + lit$1)); submit (otuple, 0);
 }
   
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port) 
{
   forwardWindowPunctuation(punct);
}

static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("sink::prepare::stringify",&initer));
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
    initRTC(*this, lit$3, "lit$3");
    initRTC(*this, lit$4, "lit$4");
    initRTC(*this, lit$5, "lit$5");
    initRTC(*this, lit$6, "lit$6");
    initRTC(*this, lit$7, "lit$7");
    initRTC(*this, lit$8, "lit$8");
    initRTC(*this, lit$9, "lit$9");
    initRTC(*this, lit$10, "lit$10");
    addParameterValue ("filter");
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
    IPort0Type const & iport$0 = static_cast<IPort0Type const  &>(tuple);
    AutoPortMutex $apm($svMutex, *this);
    
{
    if ((iport$0.get_userId() == lit$7)) 
        {
            ::SPL::Functions::Utility::appTrc(SPL::BeJyrNI03TS0qyi8yKU8syjPJzEvLN01JTSpNNy0pSkxOBQC5eQu5::warn, lit$8, lit$9, lit$10);
        }
}

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



