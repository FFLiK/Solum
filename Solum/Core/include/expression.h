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
		ExprType exprType;
	public:
		Expr(ExprType exprType);
		ExprType getExprType() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API CstExpr : public Expr {
	private:
		Value value;
	public:
		CstExpr(Value value);
		Value getValue() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API VarExpr : public Expr {
	private:
		Value id;
	public:
		VarExpr(Value id);
		Value getId() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API AssignExpr : public Expr {
	private:
		std::unique_ptr<Expr> lhs;
		std::unique_ptr<Expr> rhs;
	public:
		AssignExpr(std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs);
		virtual ~AssignExpr() = default;
		AssignExpr(AssignExpr&&) noexcept = default;
		AssignExpr& operator=(AssignExpr&&) noexcept = default;
		AssignExpr(const AssignExpr&) = delete;
		AssignExpr& operator=(const AssignExpr&) = delete;

		const Expr& getLhs() const;
		const Expr& getRhs() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API FDefExpr : public Expr {
	private:
		std::vector<std::unique_ptr<VarExpr>> params;
		std::vector<std::unique_ptr<Expr>> body;
	public:
		FDefExpr(std::vector<std::unique_ptr<VarExpr>> params, std::vector<std::unique_ptr<Expr>> body);
		virtual ~FDefExpr() = default;
		FDefExpr(FDefExpr&&) noexcept = default;
		FDefExpr& operator=(FDefExpr&&) noexcept = default;
		FDefExpr(const FDefExpr&) = delete;
		FDefExpr& operator=(const FDefExpr&) = delete;

		std::vector<VarExpr*> getParams() const;
		std::vector<Expr*> getBody() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API FCallExpr : public Expr {
	private:
		std::unique_ptr<Expr> func;
		std::vector<std::unique_ptr<Expr>> args;
	public:
		FCallExpr(std::unique_ptr<Expr> func, std::vector<std::unique_ptr<Expr>> args);
		virtual ~FCallExpr() = default;
		FCallExpr(FCallExpr&&) noexcept = default;
		FCallExpr& operator=(FCallExpr&&) noexcept = default;
		FCallExpr(const FCallExpr&) = delete;
		FCallExpr& operator=(const FCallExpr&) = delete;

		const Expr& getFunc() const;
		std::vector<Expr*> getArgs() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API JmpExpr : public Expr {
	private:
		std::unique_ptr<Expr> target;
	public:
		JmpExpr(std::unique_ptr<Expr> target);
		virtual ~JmpExpr() = default;
		JmpExpr(JmpExpr&&) noexcept = default;
		JmpExpr& operator=(JmpExpr&&) noexcept = default;
		JmpExpr(const JmpExpr&) = delete;
		JmpExpr& operator=(const JmpExpr&) = delete;

		const Expr& getTarget() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API CJmpExpr : public Expr {
	private:
		std::unique_ptr<Expr> condition;
		std::unique_ptr<Expr> target;
	public:
		CJmpExpr(std::unique_ptr<Expr> condition, std::unique_ptr<Expr> target);
		virtual ~CJmpExpr() = default;
		CJmpExpr(CJmpExpr&&) noexcept = default;
		CJmpExpr& operator=(CJmpExpr&&) noexcept = default;
		CJmpExpr(const CJmpExpr&) = delete;
		CJmpExpr& operator=(const CJmpExpr&) = delete;

		const Expr& getCondition() const;
		const Expr& getTarget() const;
		virtual std::string asStyledString() const override;
	};

	class CORE_API IdxExpr : public Expr {
	private:
		std::unique_ptr<Expr> base;
		std::unique_ptr<Expr> index;
	public:
		IdxExpr(std::unique_ptr<Expr> base, std::unique_ptr<Expr> index);
		virtual ~IdxExpr() = default;
		IdxExpr(IdxExpr&&) noexcept = default;
		IdxExpr& operator=(IdxExpr&&) noexcept = default;
		IdxExpr(const IdxExpr&) = delete;
		IdxExpr& operator=(const IdxExpr&) = delete;

		const Expr& getBase() const;
		const Expr& getIndex() const;
		virtual std::string asStyledString() const override;
	};
}