// Copyright (c) 2020 Shadax-stack <shadax32@gmail.com>
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.
#include "Window.h"
#include <iostream>
#include <vector>

namespace Gamma {

	WindowClass::WindowClass(void) : FullscreenState(FullscreenState::WINDOWED), WindowState(WindowState::OPEN) {}

	WindowEvent::WindowEvent(const SDL_Event event) : EventData(event) {}

	void Window::OpenWindow(WindowClass wndclass, const char* title, int32_t width, int32_t height, int32_t xpos, int32_t ypos) {
		WndClass = wndclass;
		pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, (uint32_t)WndClass.FullscreenState || (uint32_t)WndClass.WindowState);
	}

	void Window::CloseWindow(void) {
		SDL_DestroyWindow(pWindow);
	}

	WindowState Window::GetState(void) {
		return WndClass.WindowState;
	}

	void Window::PollEvents(void) {
		SDL_Event Event;
		std::vector<SDL_Event> IrrelevantEvents;
		IrrelevantEvents.reserve(2048);
		while (SDL_PollEvent(&Event)) {
			if (Event.window.windowID == SDL_GetWindowID(pWindow)) {
				switch (Event.window.event) {
					case SDL_WINDOWEVENT_CLOSE: {
						WndClass.WindowState = WindowState::CLOSED;
					} break; 
					default: {
						EventQueue.push(Event);
					} break;
				}
			} else {
				IrrelevantEvents.emplace_back(Event);
			}
		}
		for (SDL_Event& IrrelevantEvent : IrrelevantEvents) {
			SDL_PushEvent(&IrrelevantEvent);
		}
	}

	bool Window::ShouldClose(void) {
		return GetState() == WindowState::CLOSED;
	}

}