# Alpha-Beta for 2048
## General Description
This is a Alpha-Beta AI implementation in order to play 2048. This implementation is good for AI that plays 2048 instead of being an adversary since 2048 has a smaller search space. Please refer to MCTS implementation if you want to look at larger board space configs or adverserial play.

Includes a basic 2048 logic. Implementations of MCTS and 2048 Game are not optimal, this is a proof of concept project that is not funded. This was done as a Winter Break 2017 project as a MS-CSE student at UCSD with emphasis in AI/ML (more info about author on bottom).

2048 has been shown to be NP-HARD.

## Monte-Carlo Tree Search
Please refer to my other repository for MCTS [implementation] (https://github.com/ProgrammingIncluded/MCTS-2048).

## Evaluation Function.
1. Monotonically Weighted

    Give more reward for orientations with increasing columns and rows. Winning boards are given high positive weights and negative of that for losing nodes.

## Discoveries
TBD
## CPP Files
| File Name | Description |
| ---------------- |:-------------:|
| main.cpp | Main file to start an instance of AB and 2048. |
| AB.cpp | File housing Alpha-Beta Search. |
| ABNode.cpp | File to hold node implementation for MCTree. |
| TFE.cpp | File to hold 2048 program. |
| grid_util.cpp | File to hold grid manipulation helper functions. |
| config.cpp | Config files. |

## Common Questions
### Can I Use This Idea for a Better Version or Iteration?
Sure! I mean, Alpha-Beta trees have been known for a while. If you feel that this project has lead significantly to your next project, I would greatly appreciate a shout out or link to my website :) Good luck!

## About the Author
More info about the author can be found at the [ProgrammingIncluded website](http://programmingincluded.com/aboutme/)

I am always looking for feedback. If someone could fund me for my masters for the quarters when I don't have funds (the uncertainty of CSE Master's gradlife) or would like to hire me, I would greaty appreciate it, thanks!