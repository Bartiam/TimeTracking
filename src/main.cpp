#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>

std::time_t timeBeginTask;

void begin_task(std::vector<std::tm*>& times, std::vector<std::string>& tasks, std::string& command)
{
	system("cls");
	std::cout << "Enter the name of the task: ";
	std::getline(std::cin, command);
	tasks.push_back(command);

	timeBeginTask = std::time(nullptr);
}

void end_task(std::vector<std::tm*>& times, std::vector<std::string>& tasks)
{
	if (timeBeginTask != 0)
	{
		std::time_t complitionTime = std::time(nullptr);
		std::time_t temp = complitionTime - timeBeginTask;
		std::tm* TMcomplitionTime = std::localtime(&complitionTime);

		int minutes = temp / 60;
		if (minutes > 59) minutes %= 60;
		int hours = minutes / 60;
		int seconds = temp % 60;

		TMcomplitionTime->tm_hour = 0;
		TMcomplitionTime->tm_min = 0;
		TMcomplitionTime->tm_sec = 0;

		TMcomplitionTime->tm_hour += hours;
		TMcomplitionTime->tm_min += minutes;
		TMcomplitionTime->tm_sec += seconds;

		times.push_back(TMcomplitionTime);

		timeBeginTask = 0;
	}
}

void status(std::vector<std::tm*>& times, std::vector<std::string>& tasks)
{
	for (int i = 0; i < times.size(); ++i)
	{
		std::cout << "Task: " << tasks[i] << " ";
		std::cout << std::setfill('0') << std::setw(2) << times[i]->tm_hour << ":" <<
		std::setfill('0') << std::setw(2) << times[i]->tm_min << ":" <<
		std::setfill('0') << std::setw(2) << times[i]->tm_sec << ":" << std::endl;
	}
}

int main()
{
	std::string command;
	std::vector<std::tm*> times;
	std::vector<std::string> tasks;

	while (command != "Exit" && command != "exit")
	{
		std::cout << "Commands: \nBegin - Select a new task. " <<
			"\nEnd - Finish tracking the current task. " <<
			"\nStatus - Information about all completed tasks. " << 
			"\nExit - Shut down the program." << std::endl;
		std::cout << "Enter the commad: ";
		std::getline(std::cin, command);

		system("cls");

		if (command == "begin" || command == "Begin")
		{
			end_task(times,tasks);
			begin_task(times, tasks, command);
		}
		else if (command == "End" || command == "end") end_task(times, tasks);
		else if (command == "Status" || command == "status") status(times, tasks);
		else if (command != "Exit" && command != "exit")
			std::cerr << "Error! Incorrect input command. Try again. " << std::endl;
	}


	return 0;
}
