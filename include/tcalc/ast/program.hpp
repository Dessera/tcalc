/**
 * @file program.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Program node.
 * @version 0.1.0
 * @date 2025-06-18
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <vector>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief Program node.
 *
 */
class ProgramNode : public Node
{
private:
  std::vector<NodePtr<>> _statements;

public:
  /**
   * @brief Construct a new Program Node object without statements.
   *
   */
  ProgramNode()
    : ProgramNode{ {} }
  {
  }

  /**
   * @brief Construct a new Program Node object with statements.
   *
   * @param statements Statements.
   */
  explicit ProgramNode(std::vector<NodePtr<>> statements)
    : Node{ NodeType::PROGRAM }
    , _statements{ std::move(statements) }
  {
  }

  ~ProgramNode() override = default;

  /**
   * @brief Get statements.
   *
   * @return const std::vector<NodePtr<>>& Statements.
   */
  [[nodiscard]] TCALC_INLINE auto& statements() const noexcept
  {
    return _statements;
  }

  /**
   * @brief Get statements.
   *
   * @return std::vector<NodePtr<>>& Statements.
   */
  TCALC_INLINE auto& statements() noexcept { return _statements; }

  /**
   * @brief Push a statement.
   *
   * @param statement Statement.
   */
  TCALC_INLINE void push_statement(NodePtr<> statement)
  {
    _statements.push_back(std::move(statement));
  }
};

/**
 * @brief Program import node.
 *
 */
class ProgramImportNode : public Node
{
private:
  std::string _path;

public:
  /**
   * @brief Construct a new Program Import Node object.
   *
   * @param path Path.
   */
  explicit ProgramImportNode(std::string path)
    : Node{ NodeType::IMPORT }
    , _path{ std::move(path) }
  {
  }

  ~ProgramImportNode() override = default;

  /**
   * @brief Get path.
   *
   * @return const std::string& Path.
   */
  [[nodiscard]] TCALC_INLINE auto& path() const noexcept { return _path; }

  /**
   * @brief Get path.
   *
   * @return std::string& Path.
   */
  TCALC_INLINE auto& path() noexcept { return _path; }

  /**
   * @brief Set path.
   *
   * @param path Path.
   */
  TCALC_INLINE void path(std::string path) noexcept { _path = std::move(path); }
};

}
