//
//  BasicDemo.cpp
//  test1
//
//  Created by t28a on 12/27/14.
//  Copyright (c) 2014 t28a. All rights reserved.
//

#include "BasicDemo.h"

//using namespace std;
using namespace SPK;
using namespace SPK::GL;

float angleY = 0.0f;
float angleX = 45.0f;
float camPosZ = 5.0f;

int deltaTime = 0;

FTGLTextureFont* fontPtr;

Group* particleGroup = NULL;
System* particleSystem = NULL;

const float PI = 3.14159265358979323846f;

const std::string STR_NB_PARTICLES = "NB PARTICLES : ";
const std::string STR_FPS = "FPS : ";

std::string strNbParticles = STR_NB_PARTICLES;
std::string strFps = STR_FPS;

int screenWidth;
int screenHeight;
float screenRatio;

int drawText = 2;

GLRenderer* particleRenderer = NULL;

#include <mach-o/dyld.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

SDL_Window* _window = NULL;

void* GLExtHandler::SPK_NSGLGetProcAddress(const char* name)
{
	NSSymbol symbol;
	char *symbolName;
    
	symbolName = (char*)malloc (strlen (name) + 2);
	strcpy(symbolName + 1, name);
	symbolName[0] = '_';
	symbol = NULL;
    
    void* result = dlsym(RTLD_DEFAULT, name);
    
    return result;
}

// Converts an int into a string
std::string int2Str(int a)
{
    std::ostringstream stm;
    stm << a;
    return stm.str();
}

// Loads a texture
bool loadTexture(GLuint& index,char* path,GLuint type,GLuint clamp,bool mipmap)
{
	SDL_Surface *particleImg;
	particleImg = SDL_LoadBMP(path);
	if (particleImg == NULL)
	{
        std::cout << "Unable to load bitmap :" << SDL_GetError() << std::endl;
		return false;
	}
    
	// converts from BGR to RGB
	if ((type == GL_RGB)||(type == GL_RGBA))
	{
		const int offset = (type == GL_RGB ? 3 : 4);
		unsigned char* iterator = static_cast<unsigned char*>(particleImg->pixels);
		unsigned char *tmp0,*tmp1;
		for (int i = 0; i < particleImg->w * particleImg->h; ++i)
		{
			tmp0 = iterator;
			tmp1 = iterator + 2;
            std::swap(*tmp0,*tmp1);
			iterator += offset;
		}
	}
    
	glGenTextures(1,&index);
	glBindTexture(GL_TEXTURE_2D,index);
    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,clamp);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,clamp);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
	if (mipmap)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, type, particleImg->w,particleImg->h, 0, type, GL_UNSIGNED_BYTE, particleImg->pixels);
		/*
         gluBuild2DMipmaps(GL_TEXTURE_2D,
         type,
         particleImg->w,
         particleImg->h,
         type,
         GL_UNSIGNED_BYTE,
         particleImg->pixels);
         i*/
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        
		glTexImage2D(GL_TEXTURE_2D,
                     0,
                     type,
                     particleImg->w,
                     particleImg->h,
                     0,
                     type,
                     GL_UNSIGNED_BYTE,
                     particleImg->pixels);
	}
    
	SDL_FreeSurface(particleImg);
    
	return true;
}

void renderFirstFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	SDL_GL_SwapWindow(_window);
}

void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
     GLfloat m[4][4] = {0.f};
 GLfloat sine, cotangent, deltaZ;
 GLfloat radians = fovy / 2 * 3.14 / 180;
 
 deltaZ = zFar - zNear;
 sine = sin(radians);
 if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
   return;
 cotangent = cos(radians) / sine;
 
 //__gluMakeIdentityf(&m[0][0]);
 m[0][0] = cotangent / aspect;
 m[1][1] = cotangent;
 m[2][2] = -(zFar + zNear) / deltaZ;
 m[2][3] = -1;
 m[3][2] = -2 * zNear * zFar / deltaZ;
 m[3][3] = 0;
 glMultMatrixf(&m[0][0]);
 }

class Graphics {
private:
    SDL_Window* window_;
public:
    Graphics(SDL_Window* window) { this->window_ = window; }
    void update() {
       
        struct Vertex {
            float Position[3];
            float Color[4];
        };
        
        const Vertex Vertices[] = {
            {{-0.5, -1., 0.f}, {1, 0, 0.0f, 0}},
            {{0.5, -1.,  0.f},  {1, 0, 0.0f, 0}},
            {{0, 1.,     0.f},         {1, 0, 0.0f, 0}},
            {{-0.5, -1., 0.f}, {0.5f, 0.5f, 0.5f}},
            {{0.5, -1.,  0.f},  {0.5f, 0.5f, 0.5f}},
            {{0, -0.f,   0.f},     {0.5f, 0.5f, 0.5f}},
        };

        glClearColor(0.7, 0.7, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        const float maxX = 2;
        const float maxY = 3;
        glOrthof(-maxX, +maxX, -maxY, +maxY, -1, 10);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &Vertices[0].Position[0]);
        glColorPointer(4, GL_FLOAT, sizeof(Vertex), &Vertices[0].Color[0]);
        
        GLsizei vertexCount = sizeof(Vertices) / sizeof(Vertex);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glPopMatrix();
        
        glPushMatrix();
        
    	particleSystem->render();
        glDisable(GL_BLEND);
        
        glPopMatrix();
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrthof(0, screenWidth, 0, screenHeight, -1, 100);
        
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        FTGLTextureFont* tfontPtr = (FTGLTextureFont*)fontPtr;
        
		if (drawText == 2)
			fontPtr->Render(strNbParticles.c_str(),-1,FTPoint(4.0f,40.0f));
		fontPtr->Render(strFps.c_str(),-1,FTPoint(4.0f,8.0f));
        
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR) {
            printf("OpenGL error #1: %d\n", err);
        }
        SDL_GL_SwapWindow(this->window_);
        while((err = glGetError()) != GL_NO_ERROR) {
            printf("OpenGL error #2: %d\n", err);
        }
        SPK::GL::GLRenderer* glr = (SPK::GL::GLRenderer*)particleRenderer;
        glr->validateBlitSanity();
    }
};

void UpdateWindow(void* arg) {
    Graphics* graphics = (Graphics*)arg;
    graphics->update();
}

// Main function
int demo_main()
{
#if defined(DEBUG) | defined(_DEBUG)
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	// random seed
	randomSeed = static_cast<unsigned int>(time(NULL));
	
	// Sets the update step
	System::setClampStep(true,0.1f);			// clamp the step to 100 ms
	System::useAdaptiveStep(0.001f,0.01f);		// use an adaptive step from 1ms to 10ms (1000fps to 100fps)
    
	SDL_Event event;
    
	// inits SDL
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_WM_SetCaption("SPARK Basic Demo",NULL);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);	// double buffering

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,1);
    //SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING,  1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
	SDL_ShowCursor(0);
    
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);
    screenWidth = displayMode.w;
    screenHeight = displayMode.h;
	_window = SDL_CreateWindow(NULL, 0, 0, screenWidth, screenHeight,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
    if(0 == _window)
        exit(42);
    auto gl = SDL_GL_CreateContext(_window);
    if(0 == gl)
        exit(42);
    Graphics* graphics = new Graphics(_window);
    SDL_iPhoneSetAnimationCallback(_window, 1, UpdateWindow, graphics);

	bool exit = false;
	bool paused = false;
    
	// renderValue :
	// 0 : normal
	// 1 : basic render
	// 2 : no render
	unsigned int renderValue = 0;
    
	float step = 0.0f;
    
	// inits openGL
    
	screenRatio = (float)screenWidth / (float)screenHeight;
	glViewport(0,0,screenWidth,screenHeight);

	// Loads texture font
	FTGLTextureFont font = FTGLTextureFont("font.ttf");
	if(font.Error())
		return 1;
	font.FaceSize(24);
	fontPtr = &font;
    
	// Loads particle texture
	GLuint textureParticle;
	if (!loadTexture(textureParticle,"point.bmp",GL_ALPHA,GL_CLAMP_TO_EDGE,false))
		return 1;
    
	// Inits Particle Engine
	Vector3D gravity(0.0f,-0.8f,0.0f);
    
	// Renderers
	GLPointRenderer* basicRenderer = GLPointRenderer::create();
    
	// We use pointSprites only if it is available and if the GL extension point parameter is available

	//if ((GLPointRenderer::loadGLExtPointSprite())&&(GLPointRenderer::loadGLExtPointParameter()))
    if(false)
	{
		GLPointRenderer* pointRenderer = GLPointRenderer::create();
		pointRenderer->setType(POINT_SPRITE);
		pointRenderer->setTexture(textureParticle);
		pointRenderer->setTextureBlending(GL_MODULATE);
		pointRenderer->enableWorldSize(true);
		GLPointRenderer::setPixelPerUnit(45.0f * PI / 180.f,screenHeight);
		pointRenderer->setSize(0.05f);
		particleRenderer = pointRenderer;
	}
	else // we use quads
	{
		GLQuadRenderer* quadRenderer = GLQuadRenderer::create();
		quadRenderer->setTexturingMode(TEXTURE_2D);
		quadRenderer->setTexture(textureParticle);
		quadRenderer->setTextureBlending(GL_MODULATE);
		quadRenderer->setScale(0.05f,0.05f);
		particleRenderer = quadRenderer;
	}
    
	particleRenderer->setBlending(BLENDING_ADD);
	particleRenderer->enableRenderingHint(DEPTH_WRITE,false);
    
	// Model
	Model* particleModel = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA);
	particleModel->setParam(PARAM_ALPHA,0.8f); // constant alpha
	particleModel->setLifeTime(8.0f,8.0f);
    
	// Emitter
	SphericEmitter* particleEmitter = SphericEmitter::create(Vector3D(0.0f,1.0f,0.0f),0.f * PI, 2.f * PI);
	particleEmitter->setZone(Point::create(Vector3D(0.0f,0.5f,0.0f)));
	particleEmitter->setFlow(250);
	particleEmitter->setForce(1.5f,1.5f);
    
	// Obstacle
	Plane* groundPlane = Plane::create();
	Obstacle* obstacle = Obstacle::create(groundPlane,INTERSECT_ZONE,0.6f,1.0f);
    
	// Group
	particleGroup = Group::create(particleModel,2100);
	particleGroup->addEmitter(particleEmitter);
    particleGroup->addModifier(obstacle);
	particleGroup->setRenderer(particleRenderer);
	particleGroup->setGravity(gravity);
    particleGroup->enableAABBComputing(true);
	
	particleSystem = System::create();
	particleSystem->addGroup(particleGroup);
    particleSystem->computeAABB();
    
    std::cout << "\nSPARK FACTORY AFTER INIT :" << std::endl;
	SPKFactory::getInstance().traceAll();
    
	SDL_Delay(3000);
	while (SDL_PollEvent(&event)){}
	
	std::deque<unsigned int> frameFPS;
	frameFPS.push_back(SDL_GetTicks());
    
	while(!exit)
	{
        SDL_PumpEvents();

		while (SDL_PollEvent(&event))
		{

			// if esc is pressed, exit
			if ((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_ESCAPE))
				exit = true;
            
			// if del is pressed, reinit the system
			if ((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_DELETE))
				particleSystem->empty();
            
			// if F1 is pressed, we display or not the text
			if ((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_F1))
			{
				--drawText;
				if (drawText < 0)
					drawText = 2;
			}
            
			// if F2 is pressed, we display or not the bounding boxes
			if ((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_F2))
			{
				particleGroup->enableAABBComputing(!particleGroup->isAABBComputingEnabled());
                
				if (paused)
					particleSystem->computeAABB();
			}
            
			// if F4 is pressed, the renderers are changed
			if ((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_F4))
			{
				renderValue = (renderValue + 1) % 3;
				switch (renderValue)
				{
                    case 0 :
                        particleGroup->setRenderer(particleRenderer);
                        break;
                        
                    case 1 :
                        particleGroup->setRenderer(basicRenderer);
                        break;
                        
                    case 2 :
                        particleGroup->setRenderer(NULL);
                        break;
				}
			}
            
			// if pause is pressed, the system is paused
			if ((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_PAUSE))
				paused = !paused;
            
			// Moves the camera with the mouse
			if (event.type == SDL_MOUSEMOTION)
			{
				angleY += event.motion.xrel * 0.05f;
				angleX += event.motion.yrel * 0.05f;
				angleX = std::min(179.0f,std::max(1.0f,angleX)); // we cannot look under the ground
			}
            
			// Zoom in and out
			if (event.type == SDL_MOUSEBUTTONUP) {
                if(event.button.button == SDL_BUTTON_LEFT)
					camPosZ = std::min(10.0f,camPosZ + 0.5f);
			    //if (event.button.button == SDL_BUTTON_RIGHT)
				//	camPosZ = std::max(0.5f,camPosZ - 0.5f);
            }

		}
        //particleSystem->computeAABB();
        //printf("Particles %d\n", particleGroup->getParticles().size());
        //printf("Particles %d\n", particleSystem->getNbParticles());
        //printf("Z=%f\n", camPosZ);

		if (!paused)
		{
			// Changes the color of the model over time
			step += deltaTime * 0.0005f;
			particleModel->setParam(PARAM_RED,0.6f + 0.4f * sin(step));
			particleModel->setParam(PARAM_GREEN,0.6f + 0.4f * sin(step + PI * 2.0f / 3.0f));
			particleModel->setParam(PARAM_BLUE,0.6f + 0.4f * sin(step + PI * 4.0f / 3.0f));
            
			// Updates particle system
			particleSystem->update(deltaTime * 0.001f);	// 1 defined as a second
            //printf("Delta: %f\n", deltaTime * 0.001f);
		}
        
		// Renders scene
		//render();

		// Computes delta time
		int time = SDL_GetTicks();
		deltaTime = time - frameFPS.back();
        
		frameFPS.push_back(time);
        
		while((frameFPS.back() - frameFPS.front() > 1000)&&(frameFPS.size() > 2))
			frameFPS.pop_front();
        
		// Updates info strings
		strNbParticles = STR_NB_PARTICLES + int2Str(particleSystem->getNbParticles());
		int fps = static_cast<int>(((frameFPS.size() - 1) * 1000.0f) / (frameFPS.back() - frameFPS.front()));
		if (drawText == 2)
			strFps = STR_FPS + int2Str(fps);
		else
			strFps = int2Str(fps);
	}
    
    std::cout << "\nSPARK FACTORY BEFORE DESTRUCTION :" << std::endl;
	SPKFactory::getInstance().traceAll();
	SPKFactory::getInstance().destroyAll();
    std::cout << "\nSPARK FACTORY AFTER DESTRUCTION :" << std::endl;
	SPKFactory::getInstance().traceAll();
	SPKFactory::destroyInstance();
	SDL_Quit();
    
    std::cout << std::endl;
	system("pause"); // Waits for the user to close the console
    
	return 0;
}

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

int
randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int
main(int argc, char *argv[])
{
    
    demo_main();
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    int done;
    SDL_Event event;
    
    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL\n");
        return 1;
    }
    
    /* seed random number generator */
    srand(time(NULL));
    
    /* create window and renderer */
    window =
    SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                     SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Could not initialize Window\n");
        return 1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer\n");
        return 1;
    }
    
    /* Enter render loop, waiting for user to quit */
    done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = 1;
            }
        }
        //render(renderer);
        SDL_Delay(1);
    }
    
    /* shutdown SDL */
    SDL_Quit();
    
    return 0;
}
