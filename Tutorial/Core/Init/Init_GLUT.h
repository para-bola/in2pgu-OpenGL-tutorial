#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "Init_GLEW.h"
#include "IListener.h"
#include "DebugOutput.h"

namespace Core {
	namespace Init{
		class Init_GLUT{
		
		private:
			static Core::IListener* listener;
			static Core::WindowInfo windowInformation;
			static void idleCallback(void);
			static void displayCallback(void);
			static void reshapeCallback(int width, int height);
			static void closeCallback();

		public:
			static void init(const Core::WindowInfo& window,
							const Core::ContextInfo& context,
							const Core::FrameBufferInfo& framebufferInfo);
			static void setListener(Core::IListener*& iListener);
			static void run();
			static void close();

			void enterFullscreen();
			void exitFullscreen();

			static void printOpenGLInfo(const Core::WindowInfo& windowInfo,
										const Core::ContextInfo& context);
		
		};
	}
}