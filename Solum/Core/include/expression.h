#pragma once

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#include <vector>
#include <string>
#include <memory>
#include "solum_obj.h"
#include "value.h"

namespace solum {
	enum class ExprType {
		CST, VAR, OPR_ASSIGN, OPR_FDEF, OPR_FCALL, OPR_JMP, OPR_CJMP, OPR_IDX
	};
	
	class CORE_API Expr : SolumObj {
	protected:
		const ExprType exprType;
	public:
		Expr(ExprType exprType);
		virtual ~Expr();
		ExprType getExprType() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API CstExpr : public Expr {
	private:
		const Value value;
	public:
		CstExpr(Value value);
		virtual ~CstExpr();
		Value getValue() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API VarExpr : public Expr {
	private:
		const Value id;
	public:
		VarExpr(Value id);
		virtual ~VarExpr();
		Value getId() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API AssignExpr : public Expr {
	private:
		const std::unique_ptr<Expr> lhs;
		const std::unique_ptr<Expr> rhs;
	public:
		AssignExpr(std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs);
		virtual ~AssignExpr();
		const Expr& getLhs() const;
		const Expr& getRhs() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API FDefExpr : public Expr {
	private:
		const std::vector<std::unique_ptr<VarExpr>> params;
		const std::vector<std::unique_ptr<Expr>> body;
	public:
		FDefExpr(std::vector<std::unique_ptr<VarExpr>> params, std::vector<std::unique_ptr<Expr>> body);
		virtual ~FDefExpr();
		std::vector<VarExpr*> getParams() const;
		std::vector<Expr*> getBody() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API FCallExpr : public Expr {
	private:
		const std::unique_ptr<Expr> func;
		const std::vector<std::unique_ptr<Expr>> args;
	public:
		FCallExpr(std::unique_ptr<Expr> func, std::vector<std::unique_ptr<Expr>> args);
		virtual ~FCallExpr();
		const Expr& getFunc() const;
		std::vector<Expr*> getArgs() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API JmpExpr : public Expr {
	private:
		const std::unique_ptr<Expr> target;
	public:
		JmpExpr(std::unique_ptr<Expr> target);
		virtual ~JmpExpr();
		const Expr& getTarget() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API CJmpExpr : public Expr {
	private:
		const std::unique_ptr<Expr> condition;
		const std::unique_ptr<Expr> target;
	public:
		CJmpExpr(std::unique_ptr<Expr> condition, std::unique_ptr<Expr> target);
		virtual ~CJmpExpr();
		const Expr& getCondition() const;
		const Expr& getTarget() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API IdxExpr : public Expr {
	private:
		const std::unique_ptr<Expr> base;
		const std::unique_ptr<Expr> index;
	public:
		IdxExpr(std::unique_ptr<Expr> base, std::unique_ptr<Expr> index);
		virtual ~IdxExpr();
		const Expr& getBase() const;
		const Expr& getIndex() const;
		virtual std::string asStyledString() const override;
	};
}