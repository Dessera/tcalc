/**
 * @file parser.hpp
 * @author Dessera (dessera@qq.com)
 * @brief AST parser.
 * @version 0.1.0
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <cstddef>
#include <string_view>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"
#include "tcalc/error.hpp"
#include "tcalc/token.hpp"
#include "tcalc/tokenizer.hpp"

namespace tcalc::ast {

/**
 * @brief Wrapper around the tokenizer to provide a context for parsing.
 *
 */
class TCALC_PUBLIC ParserContext
{
private:
  token::Tokenizer _tokenizer;
  token::Token _current;

public:
  /**
   * @brief Create a new parser context.
   *
   * @param input The input string to parse.
   * @return error::Result<ParserContext> The parser context result.
   */
  static error::Result<ParserContext> create(std::string_view input);

  ~ParserContext() = default;

  /**
   * @brief Get tokenizer.
   *
   * @return const token::Tokenizer& The tokenizer.
   */
  [[nodiscard]] constexpr auto& tokenizer() const noexcept
  {
    return _tokenizer;
  }

  /**
   * @brief Get current token.
   *
   * @return const token::Token& The current token.
   */
  [[nodiscard]] constexpr auto& current() const noexcept { return _current; }

  /**
   * @brief Eat the current token and get the next one.
   *
   * @param type The type of token to eat.
   * @return error::Result<void> The result of the operation.
   */
  error::Result<void> eat(token::TokenType type);

  /**
   * @brief Eat the current token and get the next one.
   *
   * @return error::Result<void> The result of the operation.
   */
  error::Result<void> eat();

private:
  /**
   * @brief Construct a new Parser Context object.
   *
   * @param tokenizer The tokenizer to use.
   * @param current First token.
   */
  ParserContext(token::Tokenizer tokenizer, token::Token current);
};

/**
 * @brief AST parser.
 *
 */
class TCALC_PUBLIC Parser
{
public:
  Parser() = default;
  ~Parser() = default;

  /**
   * @brief Parse the input string.
   *
   * @param input The input string to parse.
   * @return error::Result<NodePtr<>> The root node of the AST.
   */
  error::Result<NodePtr<>> parse(std::string_view input);

  /**
   * @brief Get the next program node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The program node result.
   */
  error::Result<NodePtr<>> next_program(ParserContext& ctx);

  /**
   * @brief Get the next statement node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The statement node result.
   */
  error::Result<NodePtr<>> next_statement(ParserContext& ctx);

  /**
   * @brief Get the next expression node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The expression node result.
   */
  error::Result<NodePtr<>> next_expr(ParserContext& ctx);

  /**
   * @brief Get the next term node with the given priority.
   *
   * @param ctx The parser context.
   * @param prio The priority of the term.
   * @return error::Result<NodePtr<>> The term node result.
   */
  error::Result<NodePtr<>> next_prio_term(ParserContext& ctx, std::size_t prio);

  /**
   * @brief Get the next if node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The if node result.
   */
  error::Result<NodePtr<>> next_if(ParserContext& ctx);

  /**
   * @brief Get the next assignment node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The assignment node result.
   */
  error::Result<NodePtr<>> next_assign(ParserContext& ctx);

  /**
   * @brief Get the next factor node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The factor node result.
   */
  error::Result<NodePtr<>> next_factor(ParserContext& ctx);

  /**
   * @brief Get the next identifier reference node (function or variable).
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The identifier reference node result.
   */
  error::Result<NodePtr<>> next_idref(ParserContext& ctx);

  /**
   * @brief Get the next function definition node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The function definition node result.
   */
  error::Result<NodePtr<>> next_fdef(ParserContext& ctx);

  /**
   * @brief Get the next import node.
   *
   * @param ctx The parser context.
   * @return error::Result<NodePtr<>> The import node result.
   */
  error::Result<NodePtr<>> next_import(ParserContext& ctx);
};

}
