#include <cassert>
#include <cstddef>
#include <memory>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/control_flow.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/program.hpp"
#include "tcalc/ast/unaryop.hpp"
#include "tcalc/ast/variable.hpp"
#include "tcalc/error.hpp"
#include "tcalc/parser.hpp"
#include "tcalc/priority.hpp"
#include "tcalc/token.hpp"
#include "tcalc/tokenizer.hpp"

namespace tcalc::ast {

error::Result<ParserContext>
ParserContext::create(std::string_view input)
{
  auto tokenizer = token::Tokenizer{ input };
  auto init_token = unwrap_err(tokenizer.next());

  return ParserContext{ tokenizer, init_token };
}

error::Result<void>
ParserContext::eat(token::TokenType type)
{
  if (_current.type != type) {
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected token %s at position %zu, expected %s",
                      token::TOKEN_TYPE_NAMES.at(_current.type).c_str(),
                      _tokenizer.spos() - 1,
                      token::TOKEN_TYPE_NAMES.at(type).c_str());
  }

  _current = unwrap_err(_tokenizer.next());

  return error::ok<void>();
}

error::Result<void>
ParserContext::eat()
{
  _current = unwrap_err(_tokenizer.next());

  return error::ok<void>();
}

ParserContext::ParserContext(token::Tokenizer tokenizer, token::Token current)
  : _tokenizer{ tokenizer }
  , _current{ std::move(current) }
{
}

error::Result<NodePtr<>>
Parser::parse(std::string_view input)
{
  auto ctx = unwrap_err(ParserContext::create(input));

  return error::ok<NodePtr<>>(unwrap_err(next_program(ctx)));
}

// program : (statement)*
error::Result<NodePtr<>>
Parser::next_program(ParserContext& ctx)
{
  auto node = std::make_shared<ProgramNode>();

  while (ctx.current().type != token::TokenType::EOI) {
    node->statements().push_back(unwrap_err(next_statement(ctx)));
  }

  return error::ok<NodePtr<>>(node);
}

// program : expr | fdef | assign
error::Result<NodePtr<>>
Parser::next_statement(ParserContext& ctx)
{
  if (ctx.current().type == token::TokenType::DEF) {
    return next_fdef(ctx);
  }

  if (ctx.current().type == token::TokenType::LET) {
    return next_assign(ctx);
  }

  if (ctx.current().type == token::TokenType::IMPORT) {
    return next_import(ctx);
  }

  return next_expr(ctx);
}

// expr : if | prio_term
error::Result<NodePtr<>>
Parser::next_expr(ParserContext& ctx)
{
  if (ctx.current().type == token::TokenType::IF) {
    return next_if(ctx);
  }

  return next_prio_term(ctx, 0);
}

error::Result<NodePtr<>>
Parser::next_prio_term(ParserContext& ctx, std::size_t prio)
{
  if (prio >= BINOP_PRIORITY.size()) {
    return next_factor(ctx);
  }

  auto node = unwrap_err(next_prio_term(ctx, prio + 1));

  while (BINOP_PRIORITY[prio].contains(ctx.current().type)) {
    auto type = ctx.current().type;
    ret_err(ctx.eat());

    node =
      std::make_shared<BinaryOpNode>(BINOP_PRIORITY[prio].at(type),
                                     node,
                                     unwrap_err(next_prio_term(ctx, prio + 1)));

    if (ctx.current().type == token::TokenType::SEMICOLON) {
      if (prio == 0) {
        ret_err(ctx.eat(token::TokenType::SEMICOLON));
      }
      return error::ok<NodePtr<>>(node);
    }
  }

  if (ctx.current().type == token::TokenType::SEMICOLON && prio == 0) {
    ret_err(ctx.eat(token::TokenType::SEMICOLON));
  }

  return error::ok<NodePtr<>>(node);
}

// if : IF expr THEN expr ELSE expr
error::Result<NodePtr<>>
Parser::next_if(ParserContext& ctx)
{
  ret_err(ctx.eat(token::TokenType::IF));

  auto node = std::make_shared<IfNode>();

  node->cond(unwrap_err(next_expr(ctx)));
  ret_err(ctx.eat(token::TokenType::THEN));

  node->then(unwrap_err(next_expr(ctx)));
  ret_err(ctx.eat(token::TokenType::ELSE));

  node->else_(unwrap_err(next_expr(ctx)));

  return error::ok<NodePtr<>>(node);
}

// assign : LET IDENTIFIER ASSIGN expr
error::Result<NodePtr<>>
Parser::next_assign(ParserContext& ctx)
{
  ret_err(ctx.eat(token::TokenType::LET));

  auto node = std::make_shared<VarAssignNode>(ctx.current().text);

  ret_err(ctx.eat(token::TokenType::IDENTIFIER));
  ret_err(ctx.eat(token::TokenType::ASSIGN));
  node->body(unwrap_err(next_expr(ctx)));

  return error::ok<NodePtr<>>(node);
}

// factor : NUMBER |
//          idref |
//          LPAREN expr RPAREN |
//          MINUS factor |
//          PLUS factor
error::Result<NodePtr<>>
Parser::next_factor(ParserContext& ctx) // NOLINT
{
  auto current = ctx.current();
  NodePtr<> node;

  if (current.type == token::TokenType::NUMBER) {
    // is number
    node = std::make_shared<NumberNode>(std::stod(current.text));
    ret_err(ctx.eat(token::TokenType::NUMBER));
  } else if (current.type == token::TokenType::IDENTIFIER) {
    // is idref
    node = unwrap_err(next_idref(ctx));
  } else if (current.type == token::TokenType::LPAREN) {
    // is parenthesized expr
    ret_err(ctx.eat(token::TokenType::LPAREN));
    node = unwrap_err(next_expr(ctx));
    ret_err(ctx.eat(token::TokenType::RPAREN));
  } else if (UNARYOP_PRIORITY[0].contains(current.type)) {
    auto type = current.type;
    ret_err(ctx.eat(type));
    node = std::make_shared<UnaryOpNode>(UNARYOP_PRIORITY[0].at(type),
                                         unwrap_err(next_factor(ctx)));
  } else {
    // syntax error
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected token %s at position %zu",
                      token::TOKEN_TYPE_NAMES.at(current.type).c_str(),
                      ctx.tokenizer().spos() - 1);
  }

  return error::ok<NodePtr<>>(node);
}

// idref : VARREF | FCALL
error::Result<NodePtr<>>
Parser::next_idref(ParserContext& ctx)
{
  auto id = ctx.current().text;

  ret_err(ctx.eat(token::TokenType::IDENTIFIER));

  if (ctx.current().type != token::TokenType::LPAREN) {
    return error::ok<NodePtr<>>(std::make_shared<VarRefNode>(id));
  }

  ret_err(ctx.eat(token::TokenType::LPAREN));

  auto fnode = std::make_shared<FcallNode>(id);
  while (ctx.current().type != token::TokenType::RPAREN) {
    fnode->push_arg(unwrap_err(next_expr(ctx)));
    if (ctx.current().type != token::TokenType::RPAREN) {
      ret_err(ctx.eat(token::TokenType::COMMA));
    }
  }

  ret_err(ctx.eat(token::TokenType::RPAREN));

  return error::ok<NodePtr<>>(fnode);
}

// fdef : DEF IDENTIFIER LPAREN (IDENTIFIER (COMMA IDENTIFIER)*)? RPAREN expr
error::Result<NodePtr<>>
Parser::next_fdef(ParserContext& ctx)
{
  ret_err(ctx.eat(token::TokenType::DEF));

  auto id = ctx.current().text;
  ret_err(ctx.eat(token::TokenType::IDENTIFIER));

  ret_err(ctx.eat(token::TokenType::LPAREN));

  auto fnode = std::make_shared<FdefNode>(id);
  while (ctx.current().type != token::TokenType::RPAREN) {
    fnode->push_arg(ctx.current().text);
    ret_err(ctx.eat(token::TokenType::IDENTIFIER));
    if (ctx.current().type != token::TokenType::RPAREN) {
      ret_err(ctx.eat(token::TokenType::COMMA));
    }
  }

  ret_err(ctx.eat(token::TokenType::RPAREN));

  fnode->body(unwrap_err(next_expr(ctx)));

  return error::ok<NodePtr<>>(fnode);
}

error::Result<NodePtr<>>
Parser::next_import(ParserContext& ctx)
{
  ret_err(ctx.eat(token::TokenType::IMPORT));

  auto node = std::make_shared<ProgramImportNode>(ctx.current().text);
  ret_err(ctx.eat(token::TokenType::IDENTIFIER));

  return error::ok<NodePtr<>>(node);
}

}
