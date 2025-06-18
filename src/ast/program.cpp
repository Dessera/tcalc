#include "tcalc/ast/program.hpp"
#include "tcalc/ast/node.hpp"

namespace tcalc::ast {

ProgramNode::ProgramNode()
  : ProgramNode{ {} }
{
}

ProgramNode::ProgramNode(std::vector<NodePtr<>> statements)
  : Node{ NodeType::PROGRAM }
  , _statements{ std::move(statements) }
{
}

ProgramImportNode::ProgramImportNode(std::string path)
  : Node{ NodeType::IMPORT }
  , _path{ std::move(path) }
{
}

}
