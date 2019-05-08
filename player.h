#define AMOUNT_OF_PARAMETRS 9 // before description collision!!!!
struct Rectangle_collision
{
	Coordinate <float> start_;
	sf:: RectangleShape rectangle_;
	int width, height;
};

class Player : public GameObject

{
	private:
		bool life;
		bool computer;
		int life_amount;
		Rectangle_collision wallCollision_;
	public:
		Player(char* picture_name, float x, float y, char* file_name, char* object_name);
		Player()
		{}
		virtual void update(float time, sf:: RenderWindow* window);
};

void Player:: update(float time, sf:: RenderWindow* window)
{
	assert(window);

	GameObject:: update(time, window);

	//std:: cout << getObjectCoordinate().x << '\n';

	wallCollision_.rectangle_.setPosition(getObjectCoordinate().x + wallCollision_.start_.x, getObjectCoordinate().y + wallCollision_.start_.y);

	window->draw(wallCollision_.rectangle_);

	draw(time, window);
}

Player:: Player (char* picture_name, float x, float y, char* file_name, char* object_name):
	GameObject(picture_name, x, y, file_name, object_name)
{
	assert(object_name);
	assert(picture_name);

	//set_start_GameObject(picture_name, x, y, file_name, object_name);

	FILE* f_text = fopen(file_name, "r");
	assert(f_text);

	int a = 0;

	for (int i = 0; i < AMOUNT_OF_PARAMETRS; i++)
	{
		fscanf(f_text, "%d", &a);
		//printf("%d\n", a);
	}


	fscanf(f_text, "%d%d%f%f", &wallCollision_.width, &wallCollision_.height, &wallCollision_.start_.x, &wallCollision_.start_.y);


	wallCollision_.rectangle_ = sf:: RectangleShape(sf:: Vector2f(wallCollision_.width, wallCollision_.height));

	wallCollision_.rectangle_.setFillColor(sf::Color(0, 0, 255));
	wallCollision_.rectangle_.setPosition(getObjectCoordinate().x + wallCollision_.start_.x, getObjectCoordinate().y + wallCollision_.start_.y);

	fclose(f_text);
}