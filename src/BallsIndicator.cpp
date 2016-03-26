#include "BallsIndicator.h"

BallsIndicator::BallsIndicator(float x, float y, AssetFactory* assetFactory)
{
	this->ballsRemaining = 0;
	posX = x;
	posY = y;
	width = Globals::ballWidth;
	height = Globals::ballHeight;

	this->assetFactory = assetFactory;
	this->texture = assetFactory->getAsset<SDL_Texture>("./png/Ball.png");

	EventManager::Instance()->registerHandler(this);
}

BallsIndicator::~BallsIndicator()
{
	EventManager::Instance()->deregisterHandler(this);
}

void BallsIndicator::handleMouseEvents(int mouseState, int x, int y)
{

}

void BallsIndicator::handleKeyboardEvents(const Uint8*)
{

}

void BallsIndicator::handleGameEvents(const Uint8* events)
{
	if(events[BALL_LOST])
	{
		this->ballsRemaining--;
	}

	if(events[BALL_ADDED])
	{
		this->ballsRemaining += events[BALL_ADDED];
	}
}

void BallsIndicator::update(int frameTime)
{
	if(ballsRemaining < 0){
		EventManager::Instance()->reportGameEvent(BALLS_DEPLETED);
	}
}

void BallsIndicator::render(SDL_Renderer* gRenderer)
{
	for(int i = 0; i < ballsRemaining; i++)
	{
		SDL_Rect drawRect = {posX + i*width + i*gapWidth, posY, width, height};
		SDL_RenderCopy( gRenderer, this->texture, NULL, &drawRect );
	}
}

char* BallsIndicator::type()
{
	return "BallsIndicator";
}

SDL_Point BallsIndicator::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point BallsIndicator::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point BallsIndicator::getSize()
{
	SDL_Point size = {width, height};
	return size;
}

bool BallsIndicator::isDeletable()
{
	return false;
}