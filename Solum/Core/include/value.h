#pragma once

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#include <vector>
#include <string>
#include "solum_obj.h"

namespace solum {
	class CORE_API Value : SolumObj {
	private:
		std::vector<int> data;

	public:
		Value() = default;
		virtual ~Value() = default;
		Value(const std::vector<int>& initData);
		Value(const std::string& bitstringData);
		
		std::vector<int> getData() const;
		std::string toBitstring() const;

		virtual std::string asStyledString() const override;
	};
}