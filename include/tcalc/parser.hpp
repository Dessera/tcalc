#pragma once

#include <memory>
#include <string_view>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"
#include "tcalc/error.hpp"
#include "tcalc/token.hpp"
#include "tcalc/tokenizer.hpp"

namespace tcalc::ast {

/**
 * @brief Result wrapper for AST nodes.
 *
 * @tparam T Node type.
 */
template<typename T>
  requires std::derived_from<T, Node>
using NodeResult = error::Result<std::shared_ptr<T>>;

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
   * @return NodeResult<Node> The root node of the AST.
   */
  NodeResult<Node> parse(std::string_view input);

  /**
   * @brief Get the next expression node.
   *
   * @param ctx The parser context.
   * @return NodeResult<Node> The expression node result.
   */
  NodeResult<Node> next_expr(ParserContext& ctx);

  /**
   * @brief Get the next term node.
   *
   * @param ctx The parser context.
   * @return NodeResult<Node> The term node result.
   */
  NodeResult<Node> next_term(ParserContext& ctx);

  /**
   * @brief Get the next factor node.
   *
   * @param ctx The parser context.
   * @return NodeResult<Node> The factor node result.
   */
  NodeResult<Node> next_factor(ParserContext& ctx);

  /**
   * @brief Get the next identifier reference node (function or variable).
   *
   * @param ctx The parser context.
   * @return NodeResult<Node> The identifier reference node result.
   */
  NodeResult<Node> next_idref(ParserContext& ctx);
};

}
