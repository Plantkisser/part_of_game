#include <assert.h>


enum
{
	DOWN = 0,
	UP = 1,
	LEFT = 2,
	RIGHT = 3
};


template <typename T>
struct Coordinate 
{
	T x, y;
};

class GameObject
{
	private:
		float x_, y_;
		float vx_, vy_;
		sf:: Texture object_texture_;
		float current_frame_;
		int frame_amount_;


		Coordinate <int> sprite_array_[4]; // point start
		int height_;
		int width_;

		int last_move_;
		sf:: Sprite object_sprite_;
		char* object_name_;
	protected:
		bool exist_;

	public:
		GameObject(char* picture_name, float x, float y, char* file_name, char* object_name);
		GameObject(){}
		virtual void update(float time, sf:: RenderWindow* window);
		void add_speed(float vx, float vy);
		//void set_start_GameObject(char* picture_name, float x, float y, char* file_name, char* object_name);
		Coordinate <float> getObjectCenterCoordinate();
		Coordinate <float> getObjectCoordinate();
		virtual void draw(float time, sf:: RenderWindow* window);
		bool does_exist();
};

GameObject:: GameObject(char* picture_name, float x, float y, char* file_name, char* object_name)
{
	assert(file_name);
	assert(picture_name);
	assert(object_name);



	object_texture_.loadFromFile(picture_name);

	x_ = x;
	y_ = y;
	vx_ = 0;
	vy_ = 0;
	current_frame_ = 0;

	object_name_ = object_name;

	last_move_ = DOWN;

	FILE* f_text = fopen(file_name, "r");
	assert(f_text);

	fscanf(f_text, "%d%d%d%d%d%d%d%d%d", &frame_amount_, &sprite_array_[DOWN].x, &sprite_array_[DOWN].y, &sprite_array_[UP].x, &sprite_array_[UP].y, &sprite_array_[LEFT].x, &sprite_array_[LEFT].y, &width_, &height_);


	fclose(f_text);

	object_sprite_.setTexture(object_texture_);
	object_sprite_.setTextureRect(sf:: IntRect(sprite_array_[DOWN].x, sprite_array_[DOWN].y, width_, height_));
	object_sprite_.setPosition(x, y);

}

void GameObject:: update(float time, sf:: RenderWindow* window)
{
	assert(window);


	current_frame_ += 0.01 * time;
	if (current_frame_ > frame_amount_)
		current_frame_ -= frame_amount_;


	x_ += vx_ * time;
	y_ += vy_ * time;
	object_sprite_.move(vx_ * time, vy_ * time);


}

void GameObject:: add_speed(float vx, float vy)
{
	vx_ += vx;
	vy_ += vy;
}


Coordinate <float> GameObject:: getObjectCenterCoordinate()
{
	Coordinate <float> crd;
	crd.x = this->x_ + this->width_ / 2;
	crd.y = this->y_ + this->height_ / 2;

	return crd;
}

Coordinate <float> GameObject:: getObjectCoordinate()
{
	Coordinate <float> crd;
	crd.x = this->x_;
	crd.y = this->y_;

	return crd;
}

void GameObject:: draw(float time, sf:: RenderWindow* window)
{
	if (vx_ > 0)
	{
		printf("*\n");
		object_sprite_.setTextureRect(sf::IntRect(sprite_array_[LEFT].x + width_ * int(current_frame_ + 1), sprite_array_[LEFT].y, -1 * width_, height_));

		last_move_ = RIGHT;
	}

	if (vx_ < 0)
	{
		printf("*\n");
		object_sprite_.setTextureRect(sf::IntRect(sprite_array_[LEFT].x + width_ * int(current_frame_), sprite_array_[LEFT].y, width_, height_));

		last_move_ = LEFT;
	}

	if (vy_ > 0)
	{
		printf("*\n");
		object_sprite_.setTextureRect(sf::IntRect(sprite_array_[DOWN].x + width_ * int(current_frame_), sprite_array_[DOWN].y, width_, height_));		

		last_move_ = DOWN;
	}

	if (vy_ < 0)
	{
		printf("*\n");
		object_sprite_.setTextureRect(sf::IntRect(sprite_array_[UP].x + width_ * int(current_frame_), sprite_array_[UP].y, width_, height_));

		last_move_ = UP;
	}

	if (vx_ == 0 && vy_ == 0)
	{
		if (last_move_ == RIGHT)
			object_sprite_.setTextureRect(sf::IntRect(sprite_array_[LEFT].x + width_, sprite_array_[LEFT].y, -1 * width_, height_));
		else
			object_sprite_.setTextureRect(sf::IntRect(sprite_array_[last_move_].x, sprite_array_[last_move_].y, width_, height_));
	
		current_frame_ = 0;		
	}

	window->draw(object_sprite_);

	vx_ = 0;
	vy_ = 0;
}

bool GameObject:: does_exist()
{
	return exist_;
}


