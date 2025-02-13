#pragma once

#include <string>
#include <unordered_map>
#include "BACH/utils/types.h"

namespace BACH {
class Variable;

class Ast;
struct AstNode;

struct Variable {
  /// @brief indicates the type of the variable
  enum class Type {
    /// @brief a regular variable with a value determined while executing the
    /// query
    Regular,
    /// @brief a variable with a constant value
    Const
  };

  /// @brief create the variable
  Variable(std::string name, VariableId id, bool isDataFromCollection);

  /// @brief destroy the variable
  ~Variable();

  Variable* clone() const;

  /// @brief registers a constant value for the variable
  /// this constant value is used for constant propagation while creating the
  /// AST
  void setConstAstNode(AstNode* node) { _constAstNode = node; }

  /// @brief returns a constant value registered for this variable
  AstNode* getConstAstNode() const { return _constAstNode; }

  /// @brief whether or not the variable is user-defined
  bool isUserDefined() const;

  /// @brief whether or not the variable needs a register assigned
  bool needsRegister() const;


  /// @brief replace a variable by another
  static Variable const* replace(
      Variable const*, std::unordered_map<VariableId, Variable const*> const&);


  bool isEqualTo(Variable const& other) const;

  /// @brief returns the type of the variable. The type is determined based
  // on the constantValue. If constantValue.isNone, the type is Type::Regular,
  // otherwise it is Type::Const
  Type type() const noexcept;

  /// @brief variable id
  VariableId const id;

  /// @brief variable name
  /// note: this cannot be const as variables can be renamed by the optimizer
  std::string name;

  /// @brief whether or not the source data for this variable is from a
  /// collection (i.e. is a document). this is only used for optimizations
  bool isDataFromCollection;

  /// @brief name of $OLD variable
  static char const* const NAME_OLD;

  /// @brief name of $NEW variable
  static char const* const NAME_NEW;

  /// @brief name of $CURRENT variable
  static char const* const NAME_CURRENT;

 private:
  /// @brief constant variable value (points to another AstNode)
  /// Used for constant propagation while creating the AST.
  AstNode* _constAstNode{nullptr};

};
}
