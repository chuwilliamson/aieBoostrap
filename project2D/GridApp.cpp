#include "GridApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

GridApplication::GridApplication() {

}

GridApplication::~GridApplication() {

}

bool GridApplication::startup() {
	
 
	Triangle * t = new Triangle();
	m_gameObjects.push_back(t);
	
	float yinc = 0;
	float xinc = 0;
	float width = getWindowWidth();
	float height = getWindowHeight();
	
	for (int i = 1; i <= UNITS; i++)
	{
		yinc += height / UNITS;
		xinc += width / UNITS;
		Point left = Point(0, yinc);
		Point right = Point(width, yinc);
		Point bot = { xinc, 0 };
		Point top = { xinc, height };
		
		Line *h = new Line(left, right);
		Line *v = new Line(top, bot);		
		
		m_gameObjects.push_back(h);
		m_gameObjects.push_back(v);
	}

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void GridApplication::shutdown() {

	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
	for (auto &go : m_gameObjects)
		delete go;
 
}


void GridApplication::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)) { quit(); }
 

	
}
 
void GridApplication::draw() {

	// wipe the screen to the background colour
	this->clearScreen();
	this->setBackgroundColour(1, 1, 1);

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw a thin line

	// draw a grid of lines
	for(Line l : m_grid)
		l.Draw(m_2dRenderer);

	for(auto go : m_gameObjects)
		go->Draw(m_2dRenderer);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, getWindowHeight() - 24);


	// done drawing sprites
	m_2dRenderer->end();
}

void GridApplication::aiedraw() {
	clearScreen();
	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate animation
	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	// draw a thin line
	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press Space for sound!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

 