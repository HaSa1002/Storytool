#include "Project.hpp"

namespace st {
	Project::Project(const std::string & path) { 
		load(path);
	}


	xmlData st::Project::save() {
		xmlData result { "project",
			{{"name", name }}, "", {
				{ }
		}
		};
		return std::move(result);
	}


	void Project::load(const std::string & path) { 
		
	}

	bool Project::hasActiveNode() {
		return active != nullptr;
	}

	void Project::moveNode(const sf::Vector2f & dest) { 
		if (hasActiveNode())
			active->setPosition(dest);
	}

	void Project::selectNode(const sf::Vector2f & pos) { 
	active = nullptr;
		for (auto& graph : graphs) {
			if (Node* n = graph.second.hitNode(pos)) {
				active = n;
				return;
			}
		}
	}

	void Project::deselectNode() {
		active = nullptr;
	}

	void Project::draw(sf::RenderTarget & target, sf::RenderStates states) const { 
		for (auto& graph : graphs)
			target.draw(graph.second);
	}

}
