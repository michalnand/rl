import sys
sys.path.insert(0, '../libs_rl_python')
import pyrl



training_iterations  = 100000;
testing_iterations   = 1000;

env   = pyrl.EnvCliff(8)

hyperparameters = pyrl.sAgentHyperparameters();

hyperparameters.alpha     = 0.1
hyperparameters.gamma     = 0.9
hyperparameters.epsilon   = 0.3
hyperparameters.epsilon_best   = 0.05


agent = pyrl.AgentSarsaTable(env, hyperparameters)



for i in range(0, training_iterations):
    agent.main()
    if ((i%1000) == 0):
        done = i*100.0/training_iterations
        print("training done = ", done, "score = ",  env.score())

print("training done\n")
print("normalised training score ", env.score()/training_iterations)

env.reset_score()
for i in range(0, testing_iterations):
    agent.main()

print("normalised testing score ", env.score()/testing_iterations)


env.reset_score();
agent.run_best_enable()

while True:
    env.render();
    agent.main();
    env.delay_ms(50)
