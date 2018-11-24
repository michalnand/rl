import sys
sys.path.insert(0, '../python')
import pyrl

import numpy




class QLearningAgent(pyrl.Agent):
    def __init__(self, env, hyperparameters):

        pyrl.Agent.__init__(self, env)

        self.hyperparameters = hyperparameters
        self.env = env

        self.state      = 0
        self.state_prev = self.state;

        self.action      = 0;
        self.action_prev = 0;

        self.actions_count = env.get_actions_count()
        self.states_count  = self.env.get_observation().size()
        print(self.actions_count, self.states_count)

        self.q_table = numpy.zeros((self.states_count, self.actions_count))

    def argmax(self, v):
        res = 0
        for i in range(0, len(v)):
            if v[i] > v[res]:
                res = i

        return res

    def select_action(self, v):
        action = self.argmax(v)
        epsilon = self.hyperparameters.epsilon
        if self.run_best_enabled():
            epsilon = self.hyperparameters.epsilon_best

        r =  numpy.random.uniform(0.0, 1.0)
        if r < epsilon:
            action = numpy.random.randint(0, self.actions_count)

        return action



    def main(self):
        self.state_prev = self.state
        self.state      = self.env.get_observation().argmax()

        self.action_prev    = self.action
        self.action         = self.select_action(self.q_table[self.state])

        reward = self.env.reward()

        gamma = self.hyperparameters.gamma
        alpha = self.hyperparameters.alpha

        d = reward + gamma*numpy.argmax(self.q_table[self.state]) - self.q_table[self.state_prev][self.action_prev]

        self.q_table[self.state_prev][self.action_prev]+= alpha*d

        self.env.action(self.action)

    def print_table(self):
        print(self.q_table)



class SarsaAgent(pyrl.Agent):
    def __init__(self, env, hyperparameters):

        pyrl.Agent.__init__(self, env)

        self.hyperparameters = hyperparameters
        self.env = env

        self.state      = 0
        self.state_prev = self.state;

        self.action      = 0;
        self.action_prev = 0;

        self.actions_count = env.get_actions_count()
        self.states_count  = self.env.get_observation().size()
        print(self.actions_count, self.states_count)

        self.q_table = numpy.zeros((self.states_count, self.actions_count))

    def argmax(self, v):
        res = 0
        for i in range(0, len(v)):
            if v[i] > v[res]:
                res = i

        return res

    def select_action(self, v):
        action = self.argmax(v)
        epsilon = self.hyperparameters.epsilon
        if self.run_best_enabled():
            epsilon = self.hyperparameters.epsilon_best

        r =  numpy.random.uniform(0.0, 1.0)
        if r < epsilon:
            action = numpy.random.randint(0, self.actions_count)

        return action


    def main(self):
        self.state_prev = self.state
        self.state      = self.env.get_observation().argmax()

        self.action_prev    = self.action
        self.action         = self.select_action(self.q_table[self.state])

        reward = self.env.reward()

        gamma = self.hyperparameters.gamma
        alpha = self.hyperparameters.alpha

        d = reward + gamma*self.q_table[self.state][self.action] - self.q_table[self.state_prev][self.action_prev]

        self.q_table[self.state_prev][self.action_prev]+= alpha*d

        self.env.action(self.action)

    def print_table(self):
        print(self.q_table)
