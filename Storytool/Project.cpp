#include "Project.hpp"

namespace st {
	xmlData st::Project::save() {
		xmlData result { "project",
			{{"name", name }}, "", {
				{ }
		}
		};
		return std::move(result);
	}

}
