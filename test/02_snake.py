import sys
sys.path.insert(0, '../libs_rl_python')
import pyrl



training_iterations  = 50000
testing_iterations   = 1000

env   = pyrl.EnvSnake()
agent = pyrl.AgentDQN(env, "02_snake_parameters.json")



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
    env.delay_ms(5)
