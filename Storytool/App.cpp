#include "App.hpp"
#ifdef _WIN32
#include <Windows.h>
#endif
#include "imgui_stdlib.h"
#include <iostream>

namespace st {



	App::App() : project { &font } {
		win.create(sf::VideoMode::getDesktopMode(), "Storytool | " + project.name, sf::Style::Default);
#ifdef _WIN32
		//Maximize Window
		ShowWindow(win.getSystemHandle(), SW_MAXIMIZE);
		//Set DoubleClickTime
		doubleClickTime = sf::milliseconds(GetDoubleClickTime());
#else
		//Set Doubleclicktime a custom value
		doubleClickTime = sf::milliseconds(500);

#endif // _WIN32
		win.setFramerateLimit(60);
		ImGui::SFML::Init(win);
		ImGui::StyleColorsLight();
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.f;
		font.loadFromFile("font.ttf");
		main();
	}
	App::~App() {

	}



	void App::main() {
		//Test stuff


		//End

		while (win.isOpen()) {
			processEvents();
			update();
			ImGui::ShowDemoWindow();



			win.clear({ 245, 245, 245 });
			win.draw(project);
			ImGui::SFML::Render(win);
			if (to_add != nullptr)
				win.draw(*to_add);
			if (connecting_nodes)
				win.draw(line);
			win.display();
		}
	}




	void App::processEvents() {
		sf::Event e;
		while (win.pollEvent(e)) {
			ImGui::SFML::ProcessEvent(e);
			switch (e.type) {
				case sf::Event::Closed:
					win.close();
					break;
				case sf::Event::MouseButtonReleased:
					switch (e.mouseButton.button) {
						case sf::Mouse::Button::Right:
							if (to_add != nullptr) {
								//Cancel adding of node
								to_add = nullptr;
								break;
							}
							if (connecting_nodes) {
								connecting_nodes = false;
							}
							//Context menu
							ImGui::SetWindowPos("right-click", sf::Mouse::getPosition());
							window_states["right-click-menu"] = false; //FIXME: complete right-click menu
							break;
						case sf::Mouse::Button::Left: {

								if (to_add != nullptr) {
									//Add node
									to_add->setPosition(win.mapPixelToCoords(sf::Mouse::getPosition(win)));
									project.addNode(to_add);
									to_add = nullptr;
									break;
								}

								//Disappear right-click menu if the click was not in a window
								window_states["right-click-menu"] = false;//FIXME: right-click menu disappearing
								node_moving = false;
								//Select node
								if (!ImGui::IsAnyItemActive() && !ImGui::IsAnyItemFocused()) {
									project.selectNode(win.mapPixelToCoords(sf::Mouse::getPosition(win)));
									if (!connecting_nodes) {
										if (last_click < doubleClickTime) {
											if (project.hasActiveNode()) {
												line[0].position = project.active->getPosition();
												connecting_nodes = true;
												start_node = project.active->id;

											}
										}
										last_click = sf::Time::Zero;
									} else if (project.hasActiveNode()) {
										project.addConnection(start_node, project.active->id);
										connecting_nodes = false;
									}

								}
								break;
							}
						default:
							break;
					}

					break;
				case sf::Event::MouseMoved:
					if (to_add != nullptr) {
						//Move node
						to_add->setPosition(win.mapPixelToCoords(sf::Mouse::getPosition(win)));
						break;
					}
					if (connecting_nodes) {
						line[1].position = win.mapPixelToCoords(sf::Mouse::getPosition(win));
						break;
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !ImGui::IsAnyItemActive()) {
						if (!project.hasActiveNode()) {
							project.selectNode(win.mapPixelToCoords({ e.mouseMove.x, e.mouseMove.y }));
							node_moving = false;
						}
						//We want to move a node or select a group of nodes
						if (project.hasActiveNode()) {
							if (!node_moving) {
								node_moving = true;
								move_offset = win.mapPixelToCoords(sf::Mouse::getPosition(win)) - project.active->getPosition();
								if (sf::length<float>(move_offset) > sf::length<float>(project.active->shape.getSize())) {
									project.deselectNode();
									goto skip;
								}
							}
							auto p = sf::Mouse::getPosition(win);
							project.moveNode(win.mapPixelToCoords(p) - move_offset);
						}

					} else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
						//Move the view
						auto& s = e.mouseMove;
						auto view = win.getView();
						view.move(static_cast<float>(last_mousePos.x - s.x)*zoomfactor, static_cast<float>(last_mousePos.y - s.y)*zoomfactor);

						win.setView(view);
					}
				skip:


					last_mousePos.x = e.mouseMove.x;
					last_mousePos.y = e.mouseMove.y;
					break;
				case sf::Event::MouseWheelScrolled: {
						if (ImGui::IsAnyItemActive()) {
							//TODO: Don't zoom if we are in a menu
							break;
						}
						auto& s = e.mouseWheelScroll;
						auto view = win.getView();
						//Set the center to the cursor, to zoom at the cursor (feels better/normal)
						//auto center = view.getCenter();
						//FIXME: Scrolling
						//view.setCenter(win.mapPixelToCoords({(s.x), (s.y)}));
						//view.setCenter(sf::Vector2f { static_cast<float>(s.x), static_cast<float>(s.y) });
						if (s.delta < 0 && zoomfactor < 2.0f) {
							zoomfactor += 0.3f;
							view.zoom(1.3f);
						} else if (s.delta > 0 && zoomfactor > 0.125f) {
							zoomfactor -= 0.3f;
							view.zoom(1 / 1.3f);
						}
						//Reset the center
						//view.setCenter(center);
						win.setView(view);
						break;

					}

				case sf::Event::KeyReleased:
					switch (e.key.code) {
						case sf::Keyboard::M:

						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		//Add to double click time
		last_click += clock.getElapsedTime();
	}


	void App::update() {
		project.update();
		win.setTitle("Storytool v" + VERSION + " | " + project.getTitle());
		ImGui::SFML::Update(win, clock.restart());
		mainMenuBar();
		draw();

	}

	void App::drawStorylineWindow() {
		static ImGuiTextFilter filter;
		static std::string id;
		static std::string text;
		if (ImGui::Begin("Storylines", &window_states["storyline"])) {
			ImGui::InputText("ID Template", &project.storyline_id_template);
			//TODO: Make helper
			ImGui::Text("Vars: C = Character\nI = Counter\nG = Graph\nN = Node\nDefault: C-I");
			ImGui::Separator();
			ImGui::Separator();
			//Add
			ImGui::InputText("ID", &id);
			ImGui::InputTextMultiline("Text", &text);
			if (ImGui::Button("Add")) {
				project.storyline[id] = text;
				id.clear();
				text.clear();
			}
			ImGui::Separator();
			ImGui::Separator();
			//TODO: Allow sort
			filter.Draw("Filter");
			ImGui::Separator();
			for (auto& s : project.storyline) {
				if (filter.PassFilter(s.first.data())) {
					ImGui::InputTextMultiline(s.first.data(), &s.second);
				}
			}

		}
		ImGui::End();
	}

	void App::drawCharacterWindow() {
		static std::string name;
		static ImVec4 color;
		static std::string description;
		static std::string* n;
		static std::string n_backup;
		static bool modal;
		if (ImGui::Begin("Characters", &window_states["character"])) {
			ImGui::TreePush("Characters##c");
			if (ImGui::TreeNode("New")) {
				ImGui::InputText("Name", &name);
				ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&color));
				ImGui::InputTextMultiline("Description", &description);

				if (ImGui::Button("Create")) {
					project.characters.push_back({ name, description, color });
					name.clear();
					color = sf::Color::Black;
					description.clear();
				}
				ImGui::TreePop();
			}

			for (auto& c : project.characters) {
				ImGui::PushID(c.name.data());
				if (ImGui::TreeNode(c.name.data())) {
					ImGui::InputText("Name", &c.name, ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
					if (ImGui::Button("Rename")) {
						n = &c.name;
						n_backup = c.name;
						modal = true;
						ImGui::OpenPopup("Rename Char");
					}
					ImGui::InputTextMultiline("Description", &c.description);
					ImVec4 c_t = c.color;
					if (ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&c_t))) {
						c.color = c_t;
					}
					ImGui::TreePop();
				}
				ImGui::PopID();
			}
			ImGui::TreePop();


		}
		if (modal) {
			ImGui::OpenPopup("Rename Char");
			if (ImGui::BeginPopupModal("Rename Char", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
				ImGui::InputText("Name", n);
				if (ImGui::Button("Rename")) {
					modal = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					*n = n_backup;
					modal = false;
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::EndPopup();
		}
		ImGui::End();
		//TODO: Write Rename model
	}

	void App::drawNodeCollection() {
		static std::string name;
		static std::string d_text;
		static std::string i_a;
		static std::string a_e;
		static ImVec4 bg_color;
		static ImVec4 t_color;
		static std::string character;
		if (ImGui::Begin("Node Collection", &window_states["nodecollection"])) {
			if (ImGui::CollapsingHeader("Add")) {
				ImGui::InputText("Name", &name);
				ImGui::InputText("Text", &d_text);
				ImGui::InputTextMultiline("STS is_activated", &i_a);
				ImGui::InputTextMultiline("STS after_execute", &a_e);
				ImGui::ColorEdit4("Fill Color", reinterpret_cast<float*>(&bg_color));
				ImGui::ColorEdit4("Text Color", reinterpret_cast<float*>(&t_color));
				if (ImGui::BeginCombo("Character", character.data())) {
					for (auto& c : project.characters) {
						if (ImGui::Selectable(c.name.data()))
							character = c.name;
					}
					ImGui::EndCombo();
				}

				if (ImGui::Button("Add##insert")) {
					project.def_nodes.insert_or_assign(name, Node { name, character, d_text, font, bg_color, t_color, i_a, a_e });

				}
			}

			if (ImGui::CollapsingHeader("Collection")) {
				for (auto& i : project.def_nodes) {
					Node& n = i.second;
					ImGui::PushStyleColor(ImGuiCol_Button, n.shape.getFillColor());
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, n.shape.getFillColor());
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, n.shape.getFillColor());
					ImGui::PushStyleColor(ImGuiCol_Text, n.rendered_name.getFillColor());
					if (ImGui::Button(n.id.data())) {
						//TODO: Add node to cursor
						to_add = &n;
						to_add->setPosition(win.mapPixelToCoords(sf::Mouse::getPosition(win)));

					}
					ImGui::PopStyleColor(4);
				}
			}
		}
		ImGui::End();
	}

	void App::drawPropertyEditor() {
		static std::string sid;
		static std::string text;
		static std::string buff;
		static sf::Color res_color;
		static std::string msg;
		static sf::Color res_color1;
		static std::string msg1;
		static std::string sub_graph;
		static sf::Vector2f sub_pos;
		Node& n = *project.active;
		if (ImGui::Begin("Property Editor", &window_states["property"])) {
			ImGui::InputFloat("Zoomlevel", &zoomfactor, .0f, .0f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			if (!project.hasActiveNode()) {
				ImGui::Text("No Node selected.");
				goto end;
			}
			std::string node_name = "Node (" + n.id + ")";
			if (ImGui::CollapsingHeader(node_name.data())) {
				buff = n.rendered_name.getString();
				if (ImGui::InputTextMultiline("Text", &buff)) {
					n.setDisplayString(buff);
				}
				float pos_temp[2] = { n.getPosition().x, n.getPosition().y };
				if (ImGui::InputFloat2("Positon (x,y)", pos_temp, "%.0f")) {
					n.setPosition({ pos_temp[0], pos_temp[1] });
				}
				ImVec4 bg_temp = n.shape.getFillColor();
				if (ImGui::ColorEdit4("Fill Color", (float*)&bg_temp)) {
					n.shape.setFillColor(bg_temp);
				}
				ImVec4 c_temp = n.rendered_name.getFillColor();
				if (ImGui::ColorEdit4("Text Color", (float*)&c_temp)) {
					n.rendered_name.setFillColor(c_temp);
				}
				ImGui::PushID("character");
				if (ImGui::BeginCombo("Character", n.character.data())) {
					for (auto& c : project.characters) {
						if (ImGui::Selectable(c.name.data())) {
							n.character = c.name;
						}
					}

					ImGui::EndCombo();
				}
				ImGui::PopID();

				ImGui::Separator();
				if (ImGui::InputTextMultiline("Check activation (STS)", &n.is_activated)) {
					msg.clear();
				}
				ImGui::TextColored(res_color, msg.data());
				if (ImGui::Button("Syntax check##i_a")) {
					try {
						GlobalVars g_copy = project.global_vars;
						bool ret = script::run(n.is_activated, g_copy);
						res_color = sf::Color::Green;
						msg = "Test passed (return: ";
						msg += std::to_string(ret) + ").";
					} catch (std::invalid_argument e) {
						res_color = sf::Color::Red;
						msg = e.what();
					}
				}
				ImGui::InputTextMultiline("After execution (STS)", &n.after_execute);
				ImGui::TextColored(res_color1, msg1.data());
				if (ImGui::Button("Syntax check##a_e")) {
					try {
						GlobalVars g_copy = project.global_vars;
						script::run(n.is_activated, g_copy);
						res_color1 = sf::Color::Green;
						msg1 = "Test passed.";
					} catch (std::invalid_argument e) {
						res_color1 = sf::Color::Red;
						msg1 = e.what();
					}
				}
				if (sid.empty()) {
					sid = project.proposeStorylineID();
				}
				ImGui::InputText("ID", &sid);
				ImGui::InputTextMultiline("Text##t", &text);
				if (ImGui::Button("Add")) {
					project.addStoryline(text, sid);
					n.storylines.insert(sid);
					sid.clear();
					text.clear();
				}
				ImGui::PushID("sline");
				for (auto& s : n.storylines) {
					ImGui::InputTextMultiline(s.data(), &project.storyline[s]);
				}
				ImGui::PopID();

			}
		}
	end:
		if (ImGui::CollapsingHeader("Graph")) {

			ImGui::Separator();
			ImGui::Separator();
			ImGui::Text("Subgraphs");
			ImGui::InputText("Graph ID", &sub_graph);
			ImVec2 vec = sub_pos;
			if (ImGui::InputFloat2("Position (x,y)", (float*)&vec, "%.0f")) {
				sub_pos = vec;
			}
			if (project.isValidSubgraph(sub_graph) && ImGui::Button("Add Subgraph")) {
				project.current_graph->sub_graphs.push_back({sub_graph, sub_pos });
				sub_graph.clear();
				sub_pos *= 0.f; //Cheating...
			}
			ImGui::Separator();
			for (auto i : project.current_graph->sub_graphs) {
				if (ImGui::Selectable(i.first.data())) {
					project.changeGraph(i.first);
				}
			}
		}
		ImGui::End();
	}

	void App::drawRightClickMenu() {
		ImGui::SetNextWindowBgAlpha(0.7f); // Transparent background
		if (ImGui::Begin("right-click", nullptr, ImGuiWindowFlags_NoMove | /*ImGuiWindowFlags_NoTitleBar |*/ ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav)) {
			ImGui::Text("Right-Click Menu");
			ImGui::Separator();
			if (ImGui::IsMousePosValid())
				ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
			else
				ImGui::Text("Mouse Position: <invalid>");

			if (ImGui::Button("Testy Button")) {
				std::cout << "T(a)esty Button was pressed!\n";
				window_states["globalvars"] = false;
			}
		}
		ImGui::End();
	}

	void App::drawGraphOverview() {
		static std::string id;
		static std::string headline;
		static std::string description;
		if (ImGui::Begin("Graph Overview", &window_states["graphoverview"])) {
			ImGui::InputText("ID", &id);
			ImGui::InputText("Headline", &headline);
			ImGui::InputTextMultiline("Description", &description);

			if (!id.empty() && !project.existGraph(id) && ImGui::Button("Add Graph")) {
				project.addGraph(id, headline, description);
				id.clear();
				//We leave the rest
			}
			ImGui::Separator();
			for (auto g : project.graphs) {
				if (ImGui::Selectable(g.first.data())) {
					project.changeGraph(g.first);
				}
			}
		}
		ImGui::End();
	}

	void App::draw() {
		if (window_states["globalvars"]) drawGlobalsWindow();
		if (window_states["property"]) drawPropertyEditor();
		if (window_states["right-click-menu"]) drawRightClickMenu();
		if (window_states["nodecollection"]) drawNodeCollection();
		if (window_states["character"]) drawCharacterWindow();
		if (window_states["storyline"]) drawStorylineWindow();
		if (window_states["graphoverview"]) drawGraphOverview();

	}

	void App::mainMenuBar() {
		if (ImGui::BeginMainMenuBar()) {

			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New")) {

				}
				if (ImGui::MenuItem("Open")) {

				}
				if (ImGui::MenuItem("Save")) {

				}
				if (ImGui::MenuItem("Save as")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Import")) {

				}
				if (ImGui::MenuItem("Export")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Print")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Settings")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Close")) {
					win.close();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Undo")) {

				}
				if (ImGui::MenuItem("Redo")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Copy")) {

				}
				if (ImGui::MenuItem("Cut")) {

				}

				if (ImGui::MenuItem("Paste")) {

				}

				if (ImGui::MenuItem("Dublicate")) {

				}

				if (ImGui::MenuItem("Delete")) {

				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View")) {
				if (ImGui::MenuItem("Node Collection")) {
					window_states["nodecollection"] = !window_states["nodecollection"];
				}
				if (ImGui::MenuItem("Property Editor")) {
					window_states["property"] = !window_states["property"];
				}

				ImGui::Separator();
				if (ImGui::MenuItem("Graph Overview")) {
					window_states["graphoverview"] = !window_states["graphoverview"];
				}
				if (ImGui::MenuItem("Global Variables")) {
					window_states["globalvars"] = !window_states["globalvars"];
				}
				if (ImGui::MenuItem("Storylines")) {
					window_states["storyline"] = !window_states["storyline"];
				}
				if (ImGui::MenuItem("ST Script")) {

				}
				if (ImGui::MenuItem("Characters")) {
					window_states["character"] = !window_states["character"];
				}
				ImGui::EndMenu();
			}



			if (ImGui::BeginMenu("Team")) {
				if (ImGui::MenuItem("Connect")) {

				}

				if (ImGui::MenuItem("Create")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Settings")) {

				}
				ImGui::Separator();
				if (ImGui::MenuItem("Close")) {

				}
				ImGui::EndMenu();
			}

		}
		ImGui::EndMainMenuBar();
	}

	void App::drawGlobalsWindow() {
		if (ImGui::Begin("Global variables"), &window_states["globalvars"]) {
			static std::string name;
			static double value = 0;
			ImGui::InputText("Name", &name, ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsNoBlank);

			ImGui::InputDouble("Value", &value, 0.1, 1);

			if (ImGui::Button("Add")) {
				if (name != "")
					project.global_vars.insert_or_assign(name, value);
				name.clear();
				value = 0;
			}
			ImGui::TreePush("vars");
			for (auto& i : project.global_vars) {
				ImGui::InputDouble(i.first.data(), &i.second);
				//if (ImGui::TreeNode(i.first.data())) {
					//FIXME: Seperate Init Value and Current value (if in sim)
					//TODO: Add Delete

					//ImGui::TreePop();
				//}
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}
}