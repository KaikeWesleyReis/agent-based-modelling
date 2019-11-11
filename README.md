# Agent-based Model - Scenario Fight and Run!

**Overview**: This project was created using C++ with the goal to improve my knowledge in this **programming language**, **encapsulation fundamentals**, **class in C++** and **design development of an application using QT Creator**. This simulation used agents that follows the command chain: *percept environment-think-action* as is made in Reinforcement Learning algorithms.

**Version**: During this project was used *QT Creator 5.9.8*, you can download [here](https://www.qt.io/offline-installers)

## MODEL
**Application**
![arenaFight](https://user-images.githubusercontent.com/32513366/63557321-93bf7680-c51e-11e9-9e46-0da6554e4bd4.gif)

**Concept**: The main idea is to analyze the following hypothesis: *Given the rules of combat, which feature prevails in the champions in the Arena?*.

**Agent Classes**: Based on RPG classic classes, a agent could be a *Rogue* or a *Warrior* based on *Agility* and *Strength* attributes respectively. In this simulation, those attributes has the same meaning from RPG. 

**Attributes**: Based on the class, there is only 10 points to distribute. A example can clarify this: if the agent is defined as a *warrior*, it will have 5 to 10 points (set randomly) in strength and the rest will go to agility. The opposite occurs for *rogue*.

**Rules of Combat**
- It is a singular combat, there is no formation of ties (as any death match in battlefield or any battle royale game)
- The environment deploy choice is random, i.e. there is no initial quantity set for warriors or rogues
- Its characteristics are randomly generated, so if a warrior is strong for example, that set was random
- An agent's vision changes with combat stagnation (that is a control over it)
- A characteristic that defines a class is unique, which means that a agent can not be a warrior and rogue at the same time and have higher strength and agility too.

**Battle Procedures**
- There are 4 actions on this battlefield: walk, combat, escape and enemy escape
- A fighter may be the enemy of more than one fighter in the same round
- Statistics are computed:
  - Wins - Takes Life (HP) From Another, which means that the winner agent will keep his HP
  - Defeat - Takes damage in HP from the loser
  - Evade - For *warriors* means avoid the chance to strike a *rogue* and for *rogues* means successful escape from a *warrior*
  - Clashes - Total amount of battles started in the battlefield
- A *warrior* never runs away from combat
- *Warriors* have more health compared to *rogue*
- *Rogue* always runs away from a *warrior*, but not from another *rogue*. The *rogue* will try to escape in the beggining, if fails it will get a damage from the *warrior*, losing that match!
- When the combat between two agents from the same classes occurs, the one that has greater agility hits first and win the fight.
- The damage in the HP is based on agent's strength
- Those who have a life less than one point dies!
- Battle ends when there is only three agents (the model stabilizes at this number)
- After the battle ends, the winner from that simulation is defined by this **formula**

![image](https://user-images.githubusercontent.com/32513366/63557826-a5098280-c520-11e9-920c-8ac74bbb3687.png)

## RESULTS
### Frequency Analysis for last three fighters in the battlefield
![Graph Champions Frequency](https://user-images.githubusercontent.com/32513366/63557679-0b41d580-c520-11e9-93fb-42afc9f27a19.JPG)

This graph, show that at the end more *rogues* stay alive! This could be explain because of the *warrior* nature to **NEVER RUN A SINGLE COMBAT!**. As you can see, there is ~33% for *warrior* and ~66% for *rogue* approximately (total of 50 simulations).

### Decay analysis of Warrior X Rogue during the simulation
![Graph Fighters Quantity](https://user-images.githubusercontent.com/32513366/63557680-0b41d580-c520-11e9-911a-088712077721.JPG)

Here, you can see the same results from the first graph. The number of *warriors* drops dramatically, as * rogues* always run out of combat when they see a *warrior*, implying that the nature of **NEVER RUN A SINGLE COMBAT!** makes the *warriors* kill each other faster and in the end the only one left in combat it becomes invincible! since the rogues will always run from him!

### Winners Attribute Graph - Strength X Agility
![Graph Power vs Agility](https://user-images.githubusercontent.com/32513366/63557681-0b41d580-c520-11e9-976e-d5ac5d3c74f0.png)

This is interesting, this graph shows that in the end the winners were independent of the class itself. These agents somehow bypassed the rules:
- If he was a *warrior*, he had a high agility (close to 5) and a medium strength (close to 5) which made him win any combat against the other *warriors*, even the strongest, because they hit first as han solo ;)
- If he were a *rogue*, he would be more likely to flee a *warrior* and his damage would be higher against *rogues* opponents, that has lower HP.
This result shows how AWESOME is the analysis of agent-based modeling.

## HOW TO RUN
- First you need to have installed *QT Creator* (recommend to use my version)
- **Application**: Open the folder **ArenaFight**, click in **ArenaFight (Qt Project File)** and run *main.cpp*
- **Simulation Results Generator**: Open the project **fightCage**, click in **fightCage (Qt Project File)** and run *main.cpp*
- **Generate the Graphs**: Run *graphs.py*. Have in mind that **fightCage** is not the main goal, so this part still in process

## CONTACT AND SOME NOTES
- Any question about this project functionalities, you can open a issue that I will be glad to help you
- If something was blur to you understand, you can send me a e-mail || talk with my through my *LinkedIn* that I will answer real soon!
- This code was commented in portuguese-br (my native language), so if you are not a speaker, I would glad to help you with some translation or quests! 
