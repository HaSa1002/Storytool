#include "Project.hpp"

namespace st {
	Project::Project(const std::string & path, sf::Font* font) : font { font } {
		load(path);
	}


	const std::string Project::proposeStorylineID() {

		std::string res = storyline_id_template;
		size_t c = res.find_first_of('C');
		if (c != std::string::npos) {
			if (hasActiveNode()) {
				res.replace(c, 1, active->character);
			} else {
				res.replace(c, 1, "?c?");
			}
		}
		size_t i = res.find_first_of('I');
		if (i != std::string::npos) {
			res.replace(i, 1, std::to_string(storyline_counter));
		}
		size_t g = res.find_first_of('G');
		if (g != std::string::npos) {
			if (hasActiveNode()) {
				res.replace(g, 1, current_graph->id);
			} else {
				res.replace(g, 1, "?g?");
			}
		}
		size_t n = res.find_first_of('N');
		if (n != std::string::npos) {
			if (hasActiveNode()) {
				res.replace(n, 1, active->id);
			} else {
				res.replace(n, 1, "?n?");
			}
		}
		return res;
	}

	void Project::addStoryline(const std::string & text) {
		addStoryline(text, proposeStorylineID());
	}

	void Project::addStoryline(const std::string & text, const std::string & id) {
		storyline.insert_or_assign(id, text);
		++storyline_counter;
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

	void Project::addNode(const Node * node) {
		if (current_graph != nullptr) {
			current_graph->addNode(node);
		}
	}

	void Project::deleteNode(const std::string & id) {
		if (active->id == id) active = nullptr;
		current_graph->deleteNode(id);
	}

	void Project::deselectNode() {
		active = nullptr;
	}

	void Project::addConnection(const std::string & start, const std::string & end) {
		if (current_graph == nullptr) return;
		current_graph->addConnection(start, end);
	}

	void Project::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		for (auto& graph : graphs)
			graph.second.draw(target, states, graphs);
	}

	void Project::update() {
		if (current_graph != nullptr) {
			current_graph->update();
		}
	}

}
