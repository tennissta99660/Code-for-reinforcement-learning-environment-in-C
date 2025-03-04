#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_STATES 7
#define NUM_ACTIONS 2
#define GAMMMA 0.9
#define THETA 0.01

double rewards[NUM_STATES] = {0, 0, 0, 0, 0, 0, 1};  // r = 1 for reaching the terminal state(6th state)
double state_values[NUM_STATES] = {0, 0, 0, 0, 0, 0, 0};  // Initializnig the values of states
char actions[NUM_ACTIONS] = {'L', 'R'};

double max(double a, double b) {  // defining a function to return the max of two numbers
    return (a > b) ? a : b;
}

int get_next_state(int state, char action) {  // function to determine the next state given the action either 'L' or 'R'
    if (action == 'L') {
        return (state == 0) ? 0 : state - 1;
    } else if (action == 'R') {
        return (state == NUM_STATES - 1) ? NUM_STATES - 1 : state + 1;
    }
    return state;
}

void value_iteration() {  
    double new_state_values[NUM_STATES];
    double delta;

    do {
        delta = 0.0;

        for (int s = 0; s < NUM_STATES; s++) { // we will be iterating for each state 
            double v = state_values[s];
            double max_value = -INFINITY;

            // Condition to skip value calculation for the terminal state
            if (s == NUM_STATES - 1) {
                new_state_values[s] = 0;
                continue;
            }

            for (int a = 0; a < NUM_ACTIONS; a++) { // all possible actions for each state
                int next_state = get_next_state(s, actions[a]);
                double value = rewards[next_state] + GAMMMA * state_values[next_state];
                if (value > max_value) {
                    max_value = value;
                }
            }

            new_state_values[s] = max_value; // new state value is the state value after the update rule applied above.
            delta = max(delta, fabs(v - new_state_values[s])); // updating delta
        }

        for (int s = 0; s < NUM_STATES; s++) { // storing the current state value in the state value.
            state_values[s] = new_state_values[s];// updating the state values from all 0 to some value.
        }

    } while (delta > THETA);
}

void optimal_policy() { // function to find the optimal policy
    char policy[NUM_STATES];

    for (int s = 0; s < NUM_STATES; s++) {
        double max_value = -INFINITY;
        char best_action = 'L'; // just to intialize

        // condition to skip policy calculation for the terminal state
        if (s == NUM_STATES - 1) {
            policy[s] = '-'; // if we reach he 6th state, then there is no need to further take actions as we are at the terminal state meaning the goal is achieved and the task has ended.
            continue;
        }

        for (int a = 0; a < NUM_ACTIONS; a++) {
            int next_state = get_next_state(s, actions[a]);
            double value = rewards[next_state] + GAMMMA * state_values[next_state];
            if (value > max_value) {
                max_value = value;
                best_action = actions[a]; // best action is storing the action which gave the highest return from that state
            }
        }

        policy[s] = best_action; // policy is just the collection of such best actions resulting in our optimal policy
    }

    printf("Optimal Policy:\n");
    for (int s = 0; s < NUM_STATES; s++) { // printing the policy 
        printf("State %d: %c\n", s, policy[s]);
    }
}

int main() {
    printf("Initial State Values:\n");
    for (int s = 0; s < NUM_STATES; s++) {
        printf("State %d: %.2f\n", s, state_values[s]);
    }

    value_iteration();

    printf("\nConverged State Values:\n");
    for (int s = 0; s < NUM_STATES; s++) {
        printf("State %d: %.2f\n", s, state_values[s]);
    }

    optimal_policy();

    return 0;
}
