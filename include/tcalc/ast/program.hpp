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
class TCALC_PUBLIC ProgramNode : public Node
{
private:
  std::vector<NodePtr<>> _statements;

public:
  /**
   * @brief Construct a new Program Node object without statements.
   *
   */
  ProgramNode();

  /**
   * @brief Construct a new Program Node object with statements.
   *
   * @param statements Statements.
   */
  ProgramNode(std::vector<NodePtr<>> statements);

  ~ProgramNode() override = default;

  /**
   * @brief Get statements.
   *
   * @return const std::vector<NodePtr<>>& Statements.
   */
  [[nodiscard]] constexpr auto& statements() const noexcept
  {
    return _statements;
  }

  /**
   * @brief Get statements.
   *
   * @return std::vector<NodePtr<>>& Statements.
   */
  [[nodiscard]] constexpr auto& statements() noexcept { return _statements; }

  /**
   * @brief Push a statement.
   *
   * @param statement Statement.
   */
  constexpr void push_statement(NodePtr<> statement)
  {
    _statements.push_back(std::move(statement));
  }
};

/**
 * @brief Program import node.
 *
 */
class TCALC_PUBLIC ProgramImportNode : public Node
{
private:
  std::string _path;

public:
  /**
   * @brief Construct a new Program Import Node object.
   *
   * @param path Path.
   */
  ProgramImportNode(std::string path);

  ~ProgramImportNode() override = default;

  /**
   * @brief Get path.
   *
   * @return const std::string& Path.
   */
  [[nodiscard]] constexpr auto& path() const noexcept { return _path; }

  /**
   * @brief Get path.
   *
   * @return std::string& Path.
   */
  [[nodiscard]] constexpr auto& path() noexcept { return _path; }

  /**
   * @brief Set path.
   *
   * @param path Path.
   */
  constexpr void path(std::string path) noexcept { _path = std::move(path); }
};

}
