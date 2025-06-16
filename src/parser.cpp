#include <cassert>
#include <magic_enum/magic_enum.hpp>
#include <memory>

#include "tcalc/ast/binaryop.hpp"
#include "tcalc/ast/function.hpp"
#include "tcalc/ast/node.hpp"
#include "tcalc/ast/number.hpp"
#include "tcalc/ast/unaryop.hpp"
#include "tcalc/ast/variable.hpp"
#include "tcalc/error.hpp"
#include "tcalc/parser.hpp"
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
                      "Unexpected token {} at position {}",
                      magic_enum::enum_name(type),
                      _tokenizer.spos() - 1);
  }

  _current = unwrap_err(_tokenizer.next());

  return error::ok<void>();
}

ParserContext::ParserContext(token::Tokenizer tokenizer, token::Token current)
  : _tokenizer{ tokenizer }
  , _current{ std::move(current) }
{
}

NodeResult<Node>
Parser::parse(std::string_view input)
{
  auto ctx = unwrap_err(ParserContext::create(input));
  auto res = unwrap_err(next_expr(ctx));

  if (ctx.current().type != token::TokenType::EOI) {
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected token {} at position {}",
                      magic_enum::enum_name(ctx.current().type),
                      ctx.tokenizer().spos() - 1);
  }

  return error::ok<std::shared_ptr<Node>>(res);
}

// expr : term ((PLUS | MINUS) term)*
NodeResult<Node>
Parser::next_expr(ParserContext& ctx)
{
  auto node = unwrap_err(next_term(ctx));

  while (ctx.current().type == token::TokenType::PLUS ||
         ctx.current().type == token::TokenType::MINUS) {
    if (ctx.current().type == token::TokenType::PLUS) {
      ret_err(ctx.eat(token::TokenType::PLUS));
      node = std::make_shared<BinaryPlusNode>(node, unwrap_err(next_term(ctx)));
    } else if (ctx.current().type == token::TokenType::MINUS) {
      ret_err(ctx.eat(token::TokenType::MINUS));
      node =
        std::make_shared<BinaryMinusNode>(node, unwrap_err(next_term(ctx)));
    }
  }

  return error::ok<std::shared_ptr<Node>>(node);
}

// term : factor ((MUL | DIV) factor)*
NodeResult<Node>
Parser::next_term(ParserContext& ctx)
{
  auto node = unwrap_err(next_factor(ctx));

  while (ctx.current().type == token::TokenType::MULTIPLY ||
         ctx.current().type == token::TokenType::DIVIDE) {
    if (ctx.current().type == token::TokenType::MULTIPLY) {
      ret_err(ctx.eat(token::TokenType::MULTIPLY));
      node = std::make_shared<BinaryMultiplyNode>(node,
                                                  unwrap_err(next_factor(ctx)));
    } else if (ctx.current().type == token::TokenType::DIVIDE) {
      ret_err(ctx.eat(token::TokenType::DIVIDE));
      node =
        std::make_shared<BinaryDivideNode>(node, unwrap_err(next_factor(ctx)));
    }
  }

  return error::ok<std::shared_ptr<Node>>(node);
}

// factor : NUMBER |
//          idref |
//          LPAREN expr RPAREN |
//          MINUS factor |
//          PLUS factor
NodeResult<Node>
Parser::next_factor(ParserContext& ctx) // NOLINT
{
  auto current = ctx.current();
  std::shared_ptr<Node> node;

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
  } else if (current.type == token::TokenType::PLUS) {
    // is unary plus
    ret_err(ctx.eat(token::TokenType::PLUS));
    node = std::make_shared<UnaryPlusNode>(unwrap_err(next_factor(ctx)));
  } else if (current.type == token::TokenType::MINUS) {
    // is unary minus
    ret_err(ctx.eat(token::TokenType::MINUS));
    node = std::make_shared<UnaryMinusNode>(unwrap_err(next_factor(ctx)));
  } else {
    // syntax error
    return error::err(error::Code::SYNTAX_ERROR,
                      "Unexpected token {} at position {}",
                      magic_enum::enum_name(current.type),
                      ctx.tokenizer().spos() - 1);
  }

  return error::ok<std::shared_ptr<Node>>(node);
}

// idref : VARREF | FCALL
NodeResult<Node>
Parser::next_idref(ParserContext& ctx)
{
  auto id = ctx.current().text;

  ret_err(ctx.eat(token::TokenType::IDENTIFIER));

  if (ctx.current().type != token::TokenType::LPAREN) {
    return error::ok<std::shared_ptr<Node>>(std::make_shared<VarRefNode>(id));
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

  return error::ok<std::shared_ptr<Node>>(fnode);
}

}
