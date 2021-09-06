# DiningPhilosophers

n this project we start learning about multithreading and parallel programming.

The Dining Philosophers problem is a classical problem, originally formulated by E.W. Dijkstra, to demonstrate classical problems in computer science and the programming of concurrent or parallel processes.

The goal is to make 3 programs that takes a number of philosophers and several other parameters. Each program differs in the way they handle threads and variables but they all follow the same rules :

philo_one

In this part, the program must use mutexes. Since the philosophers cannot talk to each other, this is the only way to pass information. I have two versions of this first exercise. One is the traditional way of solving this problem, one is a slighty improved way, using pair magic.

philo_two

Here, instead of using mutexes to pass information around, I am required to use a single named semaphore. Each philosopher is still a thread.

philo_three

Much like philosophers two, I are also required to use a single semaphore to pass information around, but this time , each philsopher must be a process insted of a thread.

Usage
First, Make the program of your choice, then :

Usage : ./program_name [number] [time_to_die] [time_to_eat] [time_to_sleep] optional : [number_of_times_each_philosopher_must_eat]

# Compile the binary
make

# The execute binary example

<img width="665" alt="Screen Shot 2021-09-06 at 5 29 24 PM" src="https://user-images.githubusercontent.com/82203604/132233112-b1dcff72-d8ad-4797-93cf-26dee9442784.png">
