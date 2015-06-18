
#include "Init_GLUT.h"

using namespace Core::Init;

Core::IListener* Init_GLUT::listener = NULL;
Core::WindowInfo Init_GLUT::windowInformation;


void Init_GLUT::init(const Core::WindowInfo& windowInfo,
					const Core::ContextInfo& contextInfo,
					const Core::FrameBufferInfo& framebufferInfo){

	// creating fake arguments
	int fakeargc = 1;
	char *fakeargv[] {"fake", NULL};
	glutInit(&fakeargc, fakeargv);

	// setting version
	if (contextInfo.core){
		glutInitContextVersion(contextInfo.major_version,
								contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else {
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	// init window
	windowInformation = windowInfo;
	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x, windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);
	
	glutInitContextFlags(GLUT_DEBUG);
	
	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT: initialized" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);

	DebugOutput * m_debugOutput = new DebugOutput();
	glDebugMessageCallback(m_debugOutput->myCallback, NULL);

	//glDebugMessageCallback(DebugOutput::myCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
		GL_DONT_CARE, 0, NULL, GL_TRUE);

	// register callbacks
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	Init::Init_GLEW::Init();

	// cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	printOpenGLInfo(windowInfo, contextInfo);
}




void Init_GLUT::run(){
	std::cout << "GLUT:\t Start Running" << std::endl;
	glutMainLoop();
}

void Init_GLUT::close(){
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallback(void){
	glutPostRedisplay();
}

void Init_GLUT::displayCallback(){	

	if (listener){
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();
		
		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height){
	if (windowInformation.isReshapeable == true){
		if (listener){
			listener->notifyReshape(width,
				height,
				windowInformation.width,
				windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void Init_GLUT::setListener(Core::IListener*& iListener){
	listener = iListener;
}

void Init_GLUT::closeCallback(){
	close();
}

void Init_GLUT::enterFullscreen(){
	glutFullScreen();
}

void Init_GLUT::exitFullscreen(){
	glutLeaveFullScreen();
}

void Init_GLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo){

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}