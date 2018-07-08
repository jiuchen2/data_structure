/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"
#include <string>
#include <cstdlib>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true) {
  for (unsigned i = 0; i <= startingTokens; i++) {
    g_.insertVertex("p1-" + std::to_string(i));
    g_.insertVertex("p2-" + std::to_string(i));
  }
  for (unsigned i = 1; i <= startingTokens; i++) {
    Vertex p1 = g_.getVertexByLabel("p1-" + std::to_string(i));
    Vertex p2 = g_.getVertexByLabel("p2-" + std::to_string(i));
    Vertex p11 = g_.getVertexByLabel("p1-" + std::to_string(i - 1));
    Vertex p21 = g_.getVertexByLabel("p2-" + std::to_string(i - 1));
    if (i != 1) {
      Vertex p12 = g_.getVertexByLabel("p1-" + std::to_string(i - 2));
      Vertex p22 = g_.getVertexByLabel("p2-" + std::to_string(i - 2));
      g_.insertEdge(p1, p22);
      g_.setEdgeWeight(p1, p22, 0);
      g_.insertEdge(p2, p12);
      g_.setEdgeWeight(p2, p12, 0);
    }
    g_.insertEdge(p1, p21);
    g_.setEdgeWeight(p1, p21, 0);
    g_.insertEdge(p2, p11);
    g_.setEdgeWeight(p2, p11, 0);
    startingVertex_ = g_.getVertexByLabel("p1-" + std::to_string(startingTokens));
  }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  unsigned player = 1;
  std::string label = g_.getVertexLabel(startingVertex_);
  label.erase(0, 3);
  unsigned cur = std::stoul(label, nullptr, 0);
  while (cur > 1) {
    unsigned move = rand() % 2 + 1;
    unsigned next = cur - move;
    Vertex v1 = g_.getVertexByLabel("p" + std::to_string(player) + "-" + std::to_string(cur));
    if (player == 1) {
      player = 2;
    } else {
      player = 1;
    }
    Vertex v2 = g_.getVertexByLabel("p" + std::to_string(player) + "-" + std::to_string(next));
    path.push_back(g_.getEdge(v1, v2));
    cur = next;
  }
  if (cur == 1) {
    Vertex v1 = g_.getVertexByLabel("p" + std::to_string(player) + "-" + std::to_string(cur));
    if (player == 1) {
      player = 2;
    } else {
      player = 1;
    }
    Vertex v2 = g_.getVertexByLabel("p" + std::to_string(player) + "-" + std::to_string(0));
    path.push_back(g_.getEdge(v1, v2));
  }
  return path;
}


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
  Vertex v = path[path.size() - 1].dest;
  string player1 = "1";
  string winnerLabel = g_.getVertexLabel(v);
  string winner;
  winner.assign(winnerLabel.begin() + 1, winnerLabel.begin() + 2);
  //std::cout<<winner<<std::endl;
  if (winner != player1) {
    int reward = 1;
    for (unsigned i = 0; i < path.size(); i++) {
      Vertex v1 = path[i].source;
      Vertex v2 = path[i].dest;
      int weight = g_.getEdgeWeight(v1, v2) + reward;
      g_.setEdgeWeight(v1, v2, weight);
      reward = -reward;
    }
  } else {
    int reward = -1;
    for (unsigned i = 0; i < path.size(); i++) {
      Vertex v1 = path[i].source;
      Vertex v2 = path[i].dest;
      int weight = g_.getEdgeWeight(v1, v2) + reward;
      g_.setEdgeWeight(v1, v2, weight);
      reward = -reward;
    }
  }
}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
