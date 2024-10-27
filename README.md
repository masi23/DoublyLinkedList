# Doubly Linked List in C++

## Description

This project implements a **doubly linked list** data structure in C++. The `list` class allows for adding, removing, and searching elements within the list, as well as converting its contents to a string format. The project is written in C++ standard and can be used as an example or a base for further development. The idea of this project comes from Algorithms Course at my University where we implement various structures from scratch with C++ language. It helps to understand and visualise better important algorithmical concepts.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Example](#example)
- [Testing](#testing)
- [License](#license)

## Features

- **Element Insertion**:
  - At the beginning of the list
  - At the end of the list
  - At a specified position based on comparison
- **Element Deletion**:
  - The first and last element
  - A specific element based on comparison
- **Element Searching**: Ability to find elements in the list.
- **String Conversion**: Convert the list to a string format for easy display.

## Installation

To run this project, ensure you have a C++ compiler installed (e.g., GCC or Visual Studio).

1. Clone the repository:
   ```bash
   git clone https://github.com/masi23/DoublyLinkedList
   cd <folder_name>

2. Compile the project:
	```bash
	g++ -o DoublyLinkedList DoublyLinkedList.cpp
	```

##Usage
	To use the list implementation, simply create an instance of the list class and utilize the available methods. Example usage:
	```cpp
	list<some_class>* listInstance = new list<some_class>();
	listInstance->insert_on_end(some_class{10, "Hello"});
	listInstance->insert_on_begin(some_class{20, "World"});
	std::cout << listInstance->to_string() << std::endl;
	```

##Example
	In the DoublyLinkedList.cpp file, there is an example where:
	-Random data is generated.
	-Elements are added to the list.
	-The time taken for adding and removing elements is measured.

##Testing
	You can test the project by running the DoublyLinkedList.cpp file. Doing so will display the execution time for adding and removing elements from the list.

##License
	This project is licensed under the MIT License. You can use, modify, and distribute it, provided that you include a copy of the license.