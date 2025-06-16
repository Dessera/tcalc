/**
 * @file binaryop.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Binary operation node.
 * @version 0.1.0
 * @date 2025-06-15
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <memory>
#include <utility>

#include "tcalc/ast/node.hpp"
#include "tcalc/common.hpp"

namespace tcalc::ast {

/**
 * @brief Binary operation base class.
 *
 */
class TCALC_PUBLIC BinaryOpNode : public Node
{
private:
  std::shared_ptr<Node> _left;
  std::shared_ptr<Node> _right;

public:
  /**
   * @brief Construct a new Binary Op Node object with no subnodes.
   *
   * @param type Node type.
   */
  BinaryOpNode(NodeType type);

  /**
   * @brief Construct a new Binary Op Node object with subnodes.
   *
   * @param type Node type.
   * @param left Left subnode.
   * @param right Right subnode.
   */
  BinaryOpNode(NodeType type,
               std::shared_ptr<Node> left,
               std::shared_ptr<Node> right);

  ~BinaryOpNode() override = default;

  /**
   * @brief Get the left subnode.
   *
   * @return std::shared_ptr<Node> Left subnode.
   */
  [[nodiscard]] constexpr auto& left() const noexcept { return _left; }
  [[nodiscard]] constexpr auto& left() noexcept { return _left; }

  /**
   * @brief Set the left subnode.
   *
   * @param left Left subnode.
   */
  constexpr void left(std::shared_ptr<Node> left) noexcept
  {
    _left = std::move(left);
  }

  /**
   * @brief Get the right subnode.
   *
   * @return std::shared_ptr<Node> Right subnode.
   */
  [[nodiscard]] constexpr auto& right() const noexcept { return _right; }
  [[nodiscard]] constexpr auto& right() noexcept { return _right; }

  /**
   * @brief Set the right subnode.
   *
   * @param right Right subnode.
   */
  constexpr void right(std::shared_ptr<Node> right) noexcept
  {
    _right = std::move(right);
  }
};

/**
 * @brief Binary plus node.
 *
 */
class TCALC_PUBLIC BinaryPlusNode : public BinaryOpNode
{
public:
  /**
   * @brief Construct a new Binary Plus Node object with no subnodes.
   *
   */
  BinaryPlusNode();

  /**
   * @brief Construct a new Binary Plus Node object with subnodes.
   *
   * @param left Left subnode.
   * @param right Right subnode.
   */
  BinaryPlusNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

  ~BinaryPlusNode() override = default;
};

/**
 * @brief Binary minus node.
 *
 */
class TCALC_PUBLIC BinaryMinusNode : public BinaryOpNode
{
public:
  /**
   * @brief Construct a new Binary Minus Node object with no subnodes.
   *
   */
  BinaryMinusNode();

  /**
   * @brief Construct a new Binary Minus Node object with subnodes.
   *
   * @param left Left subnode.
   * @param right Right subnode.
   */
  BinaryMinusNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

  ~BinaryMinusNode() override = default;
};

/**
 * @brief Binary multiply node.
 *
 */
class TCALC_PUBLIC BinaryMultiplyNode : public BinaryOpNode
{
public:
  /**
   * @brief Construct a new Binary Multiply Node object with no subnodes.
   *
   */
  BinaryMultiplyNode();

  /**
   * @brief Construct a new Binary Multiply Node object with subnodes.
   *
   * @param left Left subnode.
   * @param right Right subnode.
   */
  BinaryMultiplyNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

  ~BinaryMultiplyNode() override = default;
};

/**
 * @brief Binary divide node.
 *
 */
class TCALC_PUBLIC BinaryDivideNode : public BinaryOpNode
{
public:
  /**
   * @brief Construct a new Binary Divide Node object with no subnodes.
   *
   */
  BinaryDivideNode();

  /**
   * @brief Construct a new Binary Divide Node object with subnodes.
   *
   * @param left Left subnode.
   * @param right Right subnode.
   */
  BinaryDivideNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

  ~BinaryDivideNode() override = default;
};

}
