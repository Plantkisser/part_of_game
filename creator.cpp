#include <iostream>
#include <time.h>

enum
{
	ERROR = 134,

	WALL = 5,

	NO_WALL = 6,

	RANDOM_NUMBER = 56


};

FILE* log;

class cell
{
	private:
		int north_, west_, east_, south_; // много памяти
		int set_;
	public:
		int create_wall(char letter);
		int delete_wall(char letter);
		bool check_wall(char letter); 
		int& cset();// вторая функция с аргуметом изменения
};

class maze
{
	private:
		cell** cell_;
		int vertical_, horizontal_;
	public:
		maze(int vert, int horiz);
		~maze();

		int change_array_before_start(cell* array, int range);

		int last_line_processing (cell* array, int range);

		int print_maze();

};

int get_random();

maze:: maze(int vert, int horiz):
vertical_(vert),
horizontal_(horiz)

{
	cell_ = new(std:: nothrow) cell* [vert];

	if (cell_ == nullptr)
		printf("Not enough memmory\nProblem in maze constructor\n");

	for (int i = 0; i < vert; i++)
	{
		cell_[i] = new(std:: nothrow) cell[horiz];
		if (cell_[i] == nullptr)
			printf("Not enough memmory\nProblem in maze constructor\n");

		for (int j = 0; j < horiz; j++)
		{
			cell_[i][j].delete_wall('a');

			if (i == 0)
				cell_[i][j].create_wall('n');
		}
	}

	for (int j = 0; j < horiz; j++)
		cell_[0][j].cset() = j;


	// begin

	for (int i = 0; i < vert; i++)
	{
		cell_[i][0].create_wall('w'); // optimize (лишнее действие и так произойдет из-за копирования)
		cell_[i][horiz - 1].create_wall('e');

	

		for (int j = 0; j < horiz - 1; j++)
		{
			if (cell_[i][j].cset() != cell_[i][j + 1].cset())
				if (get_random() % 3 == 1)
				{
					cell_[i][j].create_wall('e');
					cell_[i][j + 1].create_wall('w');
				}

				else
					cell_[i][j + 1].cset() = cell_[i][j].cset(); 

			else
			{
				cell_[i][j].create_wall('e');
				cell_[i][j + 1].create_wall('w');
			}
		}




		bool was_opened_cell = false;

		for (int j = 0; j < horiz; j++)
			std:: cout << cell_[i][j].cset() << ' ';

		printf("\n");

		for (int j = 0; j < horiz - 1; j++)
		{

			if ((cell_[i][j].cset() != cell_[i][j + 1].cset() && was_opened_cell == true) || (cell_[i][j].cset() == cell_[i][j + 1].cset()))
				if (get_random() % 3 == 1)
				{
					cell_[i][j].create_wall('s');

					if (i + 1 < vert)
						cell_[i + 1][j].create_wall('n');
				}

				else
					was_opened_cell = true;
			else
				was_opened_cell = true;


			if (cell_[i][j].cset() != cell_[i][j + 1].cset())
				was_opened_cell = false;
		}

		if (was_opened_cell)
			if (get_random() % 3 == 1)
			{
				cell_[i][horiz - 1].create_wall('s');

				if (i + 1 < vert)
					cell_[i + 1][horiz - 1].create_wall('n');
			}			


		if (i + 1 < vert)
		{

			for (int j = 0; j < horiz; j++)
				cell_[i + 1][j] = cell_[i][j];

			int res = change_array_before_start(cell_[i + 1], horiz);
			if (res == ERROR)
				printf("There is a problem with change_array_before_start\n");
		}
	}

	int res = last_line_processing(cell_[vert - 1], horiz);
}

int get_random()
{
	static int a = 0;

	a += time(NULL);

	a -= RANDOM_NUMBER;

	a %= 124;

	return a;
}

int maze:: change_array_before_start(cell* array, int range)
{
	if (array == nullptr)
		return ERROR;

	int* array_of_set_number = (int*) calloc (range, sizeof(int));


	for (int i = 0; i < range; i++)
	{
		if (i > 0)
			array[i].delete_wall('w');
		if (i < range - 1)
			array[i].delete_wall('e');

		if (array[i].check_wall('s'))
		{
			array[i].cset() = -1;

			array[i].delete_wall('s');
		}
		else
		{
			array_of_set_number[array[i].cset()] = 1;
		}
	}

	int set_number = 0;

	for (int i = 0; i < range; i++)
	{
		if (array[i].cset() == -1)
		{
			while (array_of_set_number[set_number] != 0)
				set_number++;

			array[i].cset() = set_number;

			array_of_set_number[set_number] = 1;
		}
	}

	return 0;
}


int maze:: last_line_processing(cell* array, int range)
{
	int prev = array[0].cset();

	for (int i = 0; i < range - 1; i++)
	{
		if (prev != array[i + 1].cset())
		{
			prev = array[i + 1].cset();

			array[i + 1].cset() = array[i].cset();

			array[i + 1].delete_wall('w');

			array[i].delete_wall('e');
		}

		array[i].create_wall('s');
	}

	array[range - 1].create_wall('s');

	return 0;
}


int cell:: create_wall(char letter)
{
	switch (letter)
	{
		case 's':
			south_ = WALL;
			break;
		case 'n':
			north_ = WALL;
			break;
		case 'e':
			east_ = WALL;
			break;
		case 'w':
			west_ = WALL;
			break;
		case 'a':
			south_ = WALL;
			north_ = WALL;
			east_ = WALL;
			west_ = WALL;
			break;
		default:
			printf("Wrong letter in create_wall\n");
	}

	return 0;
}
int cell:: delete_wall(char letter)
{
	switch (letter)
	{
		case 's':
			south_ = NO_WALL;
			break;
		case 'n':
			north_ = NO_WALL;
			break;
		case 'e':
			east_ = NO_WALL;
			break;
		case 'w':
			west_ = NO_WALL;
			break;
		case 'a':
			south_ = NO_WALL;
			north_ = NO_WALL;
			east_ = NO_WALL;
			west_ = NO_WALL;
			break;
		default:
			printf("Wrong letter in delete_wall\n");
	}

	return 0;
}
bool cell:: check_wall(char letter)
{
	switch (letter)
	{
		case 's':
			if (south_ == WALL)
				return true;
			break;
		case 'n':
			if (north_ == WALL)
				return true;
			break;
		case 'e':
			if (east_ == WALL)
				return true;
			break;
		case 'w':
			if (west_ == WALL)
				return true;
			break;
		default:
			printf("Wrong letter in check_wall\n");
	}

	return false;
} 


int& cell:: cset()
{
	return set_;
}

int maze:: print_maze()
{

	for (int i = 0; i < horizontal_; i++)
		printf(" __");

	printf("\n");

	for (int i = 0; i < vertical_; i++)
	{
		printf("|");

		for (int j = 0; j < horizontal_; j++ )
		{
			if (cell_[i][j].check_wall('s'))
				printf("__");
			else
				printf("  ");

			if (cell_[i][j].check_wall('e'))
				printf("|");
			else
				printf(" ");
		}

		printf("\n");
	}

	return 0;
}


maze:: ~maze()
{
	for (int i = 0; i < vertical_; i++)
		delete[] cell_[i];

	delete[] cell_;

}



int main()
{
	log = fopen("log.txt", "w");

	fclose(log);



	log = fopen("log.txt", "a");

	fprintf(log, "begin\n");

	fclose(log);



	//printf("%d\n", time(NULL));

	maze a(5, 5);

	
	a.print_maze();



	return 0;
}