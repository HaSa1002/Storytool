#include "App.hpp"
#include <Windows.h>
#include "imgui_stdlib.h"
#include <iostream>

namespace st {



	App::App() {
		win.create(sf::VideoMode::getDesktopMode(), "Storytool", sf::Style::Default);
		ShowWindow(win.getSystemHandle(), SW_MAXIMIZE);
		win.setFramerateLimit(60);
		ImGui::SFML::Init(win);
		ImGui::StyleColorsLight();
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.f;
		main();
	}
	App::~App() {

	}



	void App::main() {
		sf::Font f;
		f.loadFromFile("font.ttf");
		Node n { "test", "", "Test", f };
		n.rendered_name.setFillColor(sf::Color::Black);
		n.setPosition({ 400, 400 });

		while (win.isOpen()) {
			processEvents();
			update();
			ImGui::ShowDemoWindow();

			//Nodetest
			if (ImGui::Begin("Nodetest")) {

			}
			ImGui::End();

			win.clear({ 245, 245, 245 });
			win.draw(n);
			ImGui::SFML::Render(win);
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
							//Context menue
							break;
						case sf::Mouse::Button::Left:
							//Select node
							project.selectNode({ e.mouseButton.x, e.mouseButton.y });
							break;
						default:
							break;
					}

					break;
				case sf::Event::MouseMoved:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
						//We want to move a node or select a group of nodes
						if (project.hasActiveNode())
							project.moveNode({ e.mouseMove.x, e.mouseMove.y });
						//TODO: else //Determine if actions started
						//if then position select shape
						//else increase size to the x,y of the cursor

					} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
						//Move the view
						auto& s = e.mouseMove;
						auto view = win.getView();
						view.move(last_mousePos.x - s.x, last_mousePos.y - s.y);
						
						win.setView(view);
					}

					last_mousePos.x = e.mouseMove.x;
					last_mousePos.y = e.mouseMove.y;
					break;
				case sf::Event::MouseWheelScrolled: {
						auto& s = e.mouseWheelScroll;
						auto view = win.getView();
						if (s.delta < 0)
							view.zoom(-1.1f * s.delta);
						else
							view.zoom(0.9f * s.delta);
						win.setView(view);
						break;
					}
				default:
					break;
			}
		}
	}
	void App::update() {
		ImGui::SFML::Update(win, clock.restart());
		mainMenuBar();
		draw();

	}

	void App::draw() {
		if (window_states["globalvars"]) drawGlobalsWindow();
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

				}
				if (ImGui::MenuItem("Graph Overview")) {

				}

				ImGui::Separator();
				if (ImGui::MenuItem("Global Var Window")) {
					window_states["globalvars"] = !window_states["globalvars"];
				}
				if (ImGui::MenuItem("Storyline Window")) {

				}
				if (ImGui::MenuItem("Actions Window")) {

				}
				if (ImGui::MenuItem("Character Window")) {
					window_states["character"] = !window_states["character"];
				}
				if (ImGui::MenuItem("Property Window")) {

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
				if (ImGui::TreeNode(i.first.data())) {
					ImGui::InputDouble("Value", &i.second);
					//FIXME: Seperate Init Value and Current value (if in sim)
					//TODO: Add Delete

					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}
}