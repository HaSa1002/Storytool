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
		while (win.isOpen()) {
			processEvents();
			update();
			ImGui::ShowDemoWindow();

			
			if (ImGui::Begin("Test")) {
				ImGui::InputTextMultiline("ST Script Test", &buff);
				if (ImGui::Button("Compile")) {
					std::cout << "Ergebnis: " << st::script::run(buff, global_vars) << "\n";
				}
			}
			ImGui::End();


			win.clear({ 250, 250, 250 });
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
			
		}
		ImGui::End();
	}
}