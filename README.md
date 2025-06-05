This particular code is for Value iteration in reinforcement learning in C.
It is usually written in python but i have modified it for C also. Here our environment is a simple 1X6 grid with 6th state being the terminal state.
A reward of is given to the agent when it reaches the terminal state.
The algorithm is designed such that value of each state is calculated and then the most optimal path is calculated by going in the path of the higher state values.
Also the more steps is required the lesser the reward/value per state gets.
