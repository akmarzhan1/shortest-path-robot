# Shortest Path Robot
A shortest path solving algorithm in Arduino IDE using the Adafruit library and the left-hand rule heuristic to achieve successful execution.

Problem Definition
=============

People have been interested in solving mazes ever since they were created back in the 5th century BC (Krystec, 2001). Following the general hype around maze solving, I decided to construct a robot, which could solve simple mazes using the shortest path available.
Below is the problem definition:

<div align="center">
<img src="https://user-images.githubusercontent.com/47840436/124885570-3a1ea300-dff5-11eb-970f-422c438ca5fa.png"> </div> 

This problem is exciting for numerous reasons:
* It is an opportunity to apply theoretical knowledge from class in practice (i.e., building the robot from physical materials);
* This is not an easy problem and requires thorough consideration, as well as possibly can be used on larger scale problems (e.g., material handling, warehouse management, pipe inspection, and bomb disposal);
* It can be further used in other classes (i.e., for CS162 FP).

AI approaches are a good fit here because we are trying to create a tool that performs functions considered intelligent by humans, such as reasoning, knowledge representation, learning, and inference (i.e., applying logic rules to the available data to reach conclusions). Maze solver robots involve rational acting, as they act to achieve the best outcome (or best-expected outcome when there is uncertainty), which is reaching the end of the maze in this situation. It doesn’t only try to reach a solution but also optimizes learning from past mistakes (i.e., first exploration phase) to perform more effectively in the future, requiring less time and steps to solve the same problem. It acts autonomously in the environment it was placed in (i.e., maze), perceives the environment and pursues a goal (i.e., end of maze). The robot modifies its behavior based on the environment and as “AI is concerned with intelligent behavior in
1 artifacts”, maze solver robots are good examples of intelligent robots (Russell & Norvig, 2016) .

Solution Specification
======================


List of materials
-------------------

<div align="center">
  <img src="https://user-images.githubusercontent.com/47840436/124884618-435b4000-dff4-11eb-996f-cfe9827540c0.png"> </div> 

Wiring 
----------------------

Below I drew the wiring. The pins got messed up in the process, so I specified that the leftmost sensor is connected to A2, rightmost to A5, center left to A3, and center-right to A4. We will use the IR sensors since our line is made from black tape, and it will be easy to detect it as the black color doesn’t reflect the light.

<div align="center">
  <img src="https://user-images.githubusercontent.com/47840436/124884702-5a9a2d80-dff4-11eb-8125-7e57c5bb1351.png"> </div> 

 <div align="center">
  Figure 1. Wiring of the Line Maze Solver
  </div>
  
Code Implementation
---------------------

For the implementation of this line maze solver, I developed a framework in which the sensor and actuators interact (i.e., a combination of if-else statements) in order for the robot to follow the line, turn in the right place, and stop when it reached the end of the maze. Also, I identified a way to store the path that the robot took (i.e., an array filled with the type of actions, such as “L” for turning left and so on), and created a shortcut based on which it will find the shortest solution given the first exploration phase. The shortcut for the shortest path (i.e., optimization) is better explained through examples in the section below.

Analysis of Solution
------------------------
Through trials and errors, the robot started to work. Below are the two mazes that I tried it on (i.e., it is the same maze, only the starting point changed).
 <div align="center">
<img src="https://user-images.githubusercontent.com/47840436/124884941-959c6100-dff4-11eb-8cc9-8eecdd0aea71.png">
</div> 
We should first think about how we would solve this maze in theory. Just randomly wandering around will be of no help, which is why it is better to implement a heuristic to help find a solution for sure. There are numerous heuristics, such as dead-end filling, Trémaux’s algorithm, the pledge algorithm, or the shortest path algorithms (e.g., A*), but given the simplicity of the mazes we are going to solve, and no particular limit in time, we will use the wall follower heuristic, and specifically, the left-hand rule (LHR), where we hypothetically put our left hand on the left wall and follow the path always turning left, and going back if it is a dead-end (Wikipedia, n.d.). Given that all walls are connected in our mazes, this heuristic is complete but not optimal, as we are guaranteed to find a solution, but it won’t be the shortest one. However, that is of no problem, since we are going to store each action that the robot takes at each step and then decode the path using the following shortcuts. In other words, if we turn left, then go back and turn right, it is equivalent to just going backward. Following the same logic, we can make other shortcuts shown in the table below.
Also, I didn’t implement the PID control, as for this simple implementation, it wasn’t necessary. However, in the future, to improve the accuracy of the robot and the way it follows the reference path, we might include it after some tuning.
 
 <div align="center">
 
  <img src="https://user-images.githubusercontent.com/47840436/124885025-a947c780-dff4-11eb-8848-7a4b0d42508a.png"> </div> 


This shortcut will allow us to find the optimal path (i.e., the shortest) since we store each move the robot takes and just keep the needed steps. For example, in mazes 1 and 2, the robot will follow the next steps.
<div align="center">

![image](https://user-images.githubusercontent.com/47840436/124885078-b8c71080-dff4-11eb-8dd5-ade155682b99.png)
</div>

The shortcuts will substantially cut the path and we will get:
* **Maze 1:** [LBLLLBSBLLBSLL] ➝ [SLLBSBLLBSLL] ➝ [SLRBLLBSLL] ➝ [SLBLBSLL]➝ [SSBSLL] ➝ [SBLL] ➝ RL, which is our optimal solution.
* **Maze 2:** [LLBSLL] ➝ LRLL, which is our optimal solution.
This is a <a href="https://www.youtube.com/watch?v=L3lY1Y2_las">youtube video</a> with the robot solving these two mazes. The videos are also submitted as a secondary file zipped with the code.

Conclusion
====================
In this paper, I have created a simple maze solving robot, which optimizes its path after exploring the maze. Instead of implementing a search algorithm, which would consume additional memory and energy, our robot used a shortcut heuristic to solve the maze in the most efficient way. This robot could have been improved through additional sensors, actuators, and new heuristics or software (i.e., drawing out a map of the maze and, after the exploration, go in a direct line from the start to end using diagonals and so on). 
        
References
=====================
1. Adafruit. (2012). Adafruit Motor shield V1 firmware with basic Microstepping support. Retrieved from https://github.com/adafruit/Adafruit-Motor-Shield-library.
2. Krystec, L. (2001). Amazing Mazes. The Museum of Unnatural Mystery. Retrieved from http://www.unmuseum.org/maze.htm.
3. Russell, S. J., & Norvig, P. (2016). Artificial intelligence: a modern approach (3rd ed.). Boston: Pearson.
4. Wikipedia contributors. (n.d.). Maze Solving Algorithms. Wikipedia. Retrieved from https://en.wikipedia.org/wiki/Maze_solving_algorithm.
