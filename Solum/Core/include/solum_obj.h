#pragma once

#include <string>
namespace solum {
	class SolumObj {
	private:
		std::string_view name;
	public:
		SolumObj(const std::string& objName)
			: name(objName) {
		}
		std::string_view getName() const {
			return name;
		}
		virtual std::string asStyledString() const = 0;
	};
}