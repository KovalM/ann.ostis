/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-memory/cpp/sc_stream.hpp>
#include <sc-kpm/sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/AgentUtils.hpp>

#include "SubdividingSearchAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace exampleModule
{

SC_AGENT_IMPLEMENTATION(SubdividingSearchAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr param1 =  IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode,Keynodes::rrel_1);
 ScAddr param2 =  IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode,Keynodes::rrel_2);
  if (!param.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, param);
 
  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
