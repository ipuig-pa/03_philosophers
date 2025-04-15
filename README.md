# Philosophers

<img width="1567" alt="Screen Shot 2025-04-15 at 2 13 36 PM" src="https://github.com/user-attachments/assets/5f41df8a-24ab-46b1-85de-936e33346cc4" />


This project was developed individually by:

- @ipuig-pa

## Project Overview

---

This project simulates the classic Dining Philosophers problem, a famous example in concurrent algorithm design used to illustrate synchronization issues and techniques for resolving them. The simulation involves philosophers sitting at a table, alternating between eating, thinking, and sleeping while sharing limited resources (forks).

## Resources

- [Philosophers visualizer](https://nafuka11.github.io/philosophers-visualizer/): used for output visualization in a colored grid.

### Problem Description

- Philosophers sit at a round table with a large bowl of spaghetti in the center
- Each philosopher needs two forks to eat (one in each hand), but there are exactly as many forks as philosophers
- Philosophers alternate between three states:
    - **Eating**: Requires two forks, philosopher is not thinking or sleeping
    - **Thinking**: Philosopher is not eating or sleeping
    - **Sleeping**: Philosopher is not eating or thinking
- When a philosopher finishes eating, they put down both forks and start sleeping
- After sleeping, they start thinking again
- If a philosopher dies of starvation, simulation ends
- Philosophers don't communicate with each other
- Philosophers don't know when another philosopher is about to die

## Usage

---

### Compilation

- Use `make` to compile the project.

### Running

- Run the program with the following argument structure:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die` (ms): Time a philosopher can go without eating before dying
- `time_to_eat` (ms): Time it takes for a philosopher to eat
- `time_to_sleep` (ms): Time a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): If specified, simulation stops when all philosophers have eaten this many times

### Features / implementation details

- Thread-based implementation where each philosopher is a thread
- Mutex protection for forks to prevent duplications
- Proper timestamp-based logging of state changes
- Death detection within 10ms of actual death (a monitoring system checks if philosophers are dying)
- Proper synchronization techniques prevent deadlocks

## Examples of output

---

All state changes are logged with precise timestamps in milliseconds:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

Where `X` is the philosopher number (starting from 1).

```
./philo 5 800 200 200 4

0 2 is thinking
0 4 is thinking
0 5 is thinking
0 3 has taken a fork
0 3 has taken a fork
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 is eating
200 1 is sleeping
200 2 has taken a fork
200 3 is sleeping
200 2 has taken a fork
200 2 is eating
200 4 has taken a fork
200 4 has taken a fork
200 4 is eating
400 4 is sleeping
400 2 is sleeping
400 1 is thinking
400 5 has taken a fork
400 5 has taken a fork
400 5 is eating
400 3 is thinking
600 4 is thinking
600 2 is thinking
600 5 is sleeping
760 1 has taken a fork
760 1 has taken a fork
760 1 is eating
760 3 has taken a fork
760 3 has taken a fork
760 3 is eating
800 5 is thinking
960 3 is sleeping
960 1 is sleeping
960 2 has taken a fork
960 2 has taken a fork
960 2 is eating
960 4 has taken a fork
960 4 has taken a fork
960 4 is eating
1160 1 is thinking
1160 2 is sleeping
1160 5 has taken a fork
1160 5 has taken a fork
1160 4 is sleeping
1160 5 is eating
1160 3 is thinking
1360 5 is sleeping
1360 2 is thinking
1360 4 is thinking
1520 1 has taken a fork
1520 1 has taken a fork
1520 1 is eating
1520 3 has taken a fork
1520 3 has taken a fork
1520 3 is eating
1560 5 is thinking
1720 3 is sleeping
1720 4 has taken a fork
1720 4 has taken a fork
1720 4 is eating
1720 1 is sleeping
1720 2 has taken a fork
1720 2 has taken a fork
1720 2 is eating
1920 3 is thinking
1920 2 is sleeping
1920 1 is thinking
1920 4 is sleeping
1920 5 has taken a fork
1920 5 has taken a fork
1920 5 is eating
2120 2 is thinking
2120 5 is sleeping
2120 4 is thinking
2280 1 has taken a fork
2280 1 has taken a fork
2280 1 is eating
2280 3 has taken a fork
2280 3 has taken a fork
2280 3 is eating
2320 5 is thinking
2480 3 is sleeping
2480 4 has taken a fork
2480 4 has taken a fork
2480 4 is eating
2480 1 is sleeping
2480 2 has taken a fork
2480 2 has taken a fork
2480 2 is eating
2680 2 is sleeping
2680 4 is sleeping
2680 1 is thinking
2680 3 is thinking
2680 5 has taken a fork
2680 5 has taken a fork
2680 5 is eating
2880 4 is thinking
```

## License

---

This project was developed as part of the curriculum at 42 School. Use of this code must comply with the school's academic integrity policies.
